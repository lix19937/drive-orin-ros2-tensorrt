
message_filters_sync_shm_msg   

同步多个topic   
每一个topic对应的msg 支持共享内存通信，实现零拷贝      

cyclonedds vs fastrtps   

Note that we have to specify the middleware implementation with RMW_IMPLEMENTATION=rmw_cyclonedds_cpp since otherwise rmw fastrtps cpp is used by default.

