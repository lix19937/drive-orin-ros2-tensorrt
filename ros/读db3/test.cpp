
int test()
{
    // https://blog.csdn.net/m0_57124501/article/details/128665215
    rosbag2_storage::StorageOptions storage_options;
    storage_options.uri = "/ota/rosbag2_2024_08_09-06_16_31";
    storage_options.storage_id = "sqlite3";

    rosbag2_cpp::ConverterOptions converter_options;
    converter_options.input_serialization_format = "cdr";
    converter_options.output_serialization_format = "cdr";

    rosbag2_storage::StorageFilter storage_filter;

    // use follow topics  
    storage_filter.topics.push_back("/sensors/camera/around/front");
    storage_filter.topics.push_back("/sensors/camera/around/left");
    storage_filter.topics.push_back("/sensors/camera/around/right");
    storage_filter.topics.push_back("/sensors/camera/around/rear");

    rosbag2_cpp::readers::SequentialReader reader;
    reader.open(storage_options, converter_options);
    // Set filter only after file has been opened, otherwise storage is null and filter will not be set.
    reader.set_filter(storage_filter);

    std::shared_ptr<rosbag2_storage::SerializedBagMessage> msg;

    int i = 0;
    INFO("ReadDb3Pattern ... while ");

    while (reader.has_next())
    {
        msg = reader.read_next();

        std::cerr << i << std::endl;
        std::cerr << msg->time_stamp << std::endl;
        std::cerr << msg->topic_name << std::endl;

        auto serialized_message = rclcpp::SerializedMessage(*msg->serialized_data);
        auto serializer = rclcpp::Serialization<driver_interfaces::msg::Camera5400K>();

        driver_interfaces::msg::Camera5400K image_msg;
        serializer.deserialize_message(&serialized_message, &image_msg);

        // save img data  
        savebin("camera.bin", image_msg.img_data.data(), 5529600);
        break;

        i++;
    }
    return 0;
}
