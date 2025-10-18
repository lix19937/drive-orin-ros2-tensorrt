
from mcap.reader import make_reader
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message

# source  /opt/ros/humble/setup.bash 
# source  ./output/x86/install_x86/setup.bash 

def read_mcap_messages(mcap_file: str, topic_name: str):
    with open(mcap_file, "rb") as f:
        reader = make_reader(f)
        icnt = 0
        for schema, channel, message in reader.iter_messages():
            if channel.topic == topic_name:
                # 获取消息类型并反序列化
                msg_type = get_message(schema.name)
                msg = deserialize_message(message.data, msg_type)

                # 示例：打印消息字段（需根据实际消息类型调整）
                # print(f"{icnt:5d}, {message.log_time} ", end=' ')
                # for field in dir(msg):
                #     if not field.startswith('_'):
                #       print(f"{field}: {getattr(msg, field)}")
                print(f"{msg.x},{msg.y},{msg.z},{msg.roll_angle},{msg.pitch_angle},{msg.yaw_angle}" )
                icnt +=1            

if __name__ == "__main__":
    mcap_file = "./20251016_141505_qa_all_debug_0.mcap"
  
    read_mcap_messages(mcap_file, '/localization/dr')

