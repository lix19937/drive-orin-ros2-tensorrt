

## 模型推理加速   

+ 0 验证
  + 确认**编译以及相关soc配置命令**，复现官方samples与官方给出的常见开源模型（结构）推理耗时统计，看是否匹配   

+ 1 板端 benchmark        
  + 1.0 生成板端引擎文件，分析layer_info.profile  看瓶颈模块（如top-20  backbone, neck, head  ）    
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
    > `预处理硬件加速（或色彩空间转换，规范化放在网络里面了） -> zerocopy -> network in tensor ---- infer ----> network out tensor -> zerocopy --> dsp/cpu decode/后处理`    
  + 4.2 是否指定/绑定多核（如果npu 是多核的，亲和性设置等）
  + 4.3 尾部算子fallback 的权衡   
