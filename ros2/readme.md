
host 安装docker  

docker 里面    
```
os2 安装  https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html    
```

docker 安装 conda ,  conda 创建虚拟环境   
```
https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/
```

```
conda create --name mcap  python=3.10    
conda activate mcap   
python3

source /opt/ros/humble/setup.bash  
python3 -c "from rclpy.serialization import deserialize_message"

strings /root/anaconda3/envs/mcap/lib/libstdc++.so.6 | grep GLIBCXX
strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX

rm -fr  /root/anaconda3/envs/mcap/lib/libstdc++.so*
cp -fr /usr/lib/x86_64-linux-gnu/libstdc++.so.6*   /root/anaconda3/envs/mcap/lib/

python3 -c "from rclpy.serialization import deserialize_message"
pip list
pip install mcap-ros2-support
python3  ./parse_mcap.py 


pip install  rosidl_runtime_py
pip install empy
./platform/build.sh -n havp_dr_msgs
python -c "import em; print(em.__version__)"
> AttributeError: module ‘em‘ has no attribute ‘BUFFERED_OPT‘
> https://blog.csdn.net/shuia64649495/article/details/143818573

pip uninstall empty
pip3 install empy==3.3.4
python -c "import em; print(em.__version__)"
 
./platform/build.sh -n havp_dr_msgs

> ROS2使用colcon build编译时报：ModuleNotFoundError: No module named ‘catkin_pkg‘
> https://blog.csdn.net/m0_37384819/article/details/140154050  

conda install -c conda-forge catkin_pkg empy lark
./platform/build.sh -n havp_dr_msgs
source  ./output/x86/install_x86/setup.bash 
```
