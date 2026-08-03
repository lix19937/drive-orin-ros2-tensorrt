

## 模型推理加速   

+ 0 验证
  + 确认**编译以及相关soc配置命令**，复现官方samples与官方给出的常见开源模型（结构）推理耗时统计，看是否匹配   

+ 1 板端 benchmark        
  + 1.0 生成板端引擎文件，分析layer_info.profile  看瓶颈模块耗时/DDR带宽（如top-20  backbone, neck, head  ）    
  + 1.1 看layer fusion情况   
+ 2 不改结构      
  + 2.0 图优化  
  + 2.1 自定义高效/融合算子替换native 实现（如果开放了外部开发接口）      
  + 2.2 **低bit 量化**， Q_8,Q_4 试验看看最小latency （再QAT）   
  + 2.3 ASP（稀疏化），需要硬件特性支持    
  + 2.4 **蒸馏**（需 retrain），最好能多机并行试验        
+ 3 改结构      
  + 3.0 设计前期要参考芯片支持layer的matrix   
  + 3.1 尽量换成芯片厂商推荐的backbone neck ffn 等结构      
  + 3.2 尽量静态shape       
+ 4 工程集成       
  + 4.0 锁频 max_freq      
  + 4.1 runtime 板端推理
    > `预处理硬件加速（或色彩空间转换，归一化等放在网络里面了） -> zerocopy -> network in tensor ---- infer ----> network out tensor -> zerocopy --> dsp/cpu decode/后处理`    
  + 4.2 是否指定/绑定多核（如果npu 是多核的，亲和性设置等），推理线程绑定cpu核
  + 4.3 尾部算子fallback 的权衡
  + 4.4 最大程度降低异核交互      

-------------------------------     
## M57 NPU 硬件基础  

10 TOPS INT8， 单实例 NPU （1 个 NPU Core，包含 1 个 CONV、1 个 TENG、1 个 DAU、1 个 SDMA ， 无 vNPU 划分）， CPU 4×Cortex‑A55    

+ 所有模型只能调度到唯一1组 NPU 硬件上运行；多模型并发依靠 AXEngine 任务队列分时调度，无法硬件并行分流到不同 NPU 核      
+ 系统瓶颈主要为DDR访问带宽，优化核心思路：最大化NPU片上SRAM复用，减少特征图DDR来回搬运    
 
## 模型结构设计约束     

1. 卷积算子：优先使用芯片推荐的conv 配置，比如3×3标准卷积、对称padding；规避奇异尺寸卷积、非对称padding   
2. 插值算子：Resize优先bilinear模式    
3. 激活函数：首选ReLU、ReLU6；尽量减少Swish / SiLU / GELU，该类算子难以流水线融合，TENG单元负载高     
4. 网络拓扑：规避碎片化结构——大量分散小卷积、连续1×1卷积堆叠、高频Concat/Split分支   
5. 张量操作：减少大尺寸Permute、Gather、Scatter、Slice使用，此类算子容易触发DDR数据重排拷贝   
6. 形状控制：尽量使用固定维度，严控动态shape；避免ONNX内置NonZero, If、Loop等控制流条件判断算子， where 算子使用fixed shape 模式      


