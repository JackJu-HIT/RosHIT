# RosHIT
这是一个关于履带车的控制程序，包括上位机（ROS）和下位机arduino代码，以及对激光雷达、IMU、kinect v2.0、GPS等传感器信号的数据读取。
# brief introduction
# Author：Jack Ju
# institute：HITWH606
# Function：履带车运行程序
# 20200620
# 本程序包含：
# 1、履带车底盘驱动程序
# 2、激光雷达驱动程序
# 3、惯性元件IMU驱动程序
# 4、GPS元件驱动程序

# 你需要配置ROS运行环境。同时设置好USB端口号，建议用UDEv端口配置规则
# 运行：
# 1、履带车底盘驱动程序---rosrun rosserial_python serial_node
# 2、激光雷达驱动程序-----roslaunch rplidar_ros rplidar_s1.launch
# 3、惯性元件GPS驱动程序---roslaunch nmea_navsat_driver  nmea_serial_driver.launch
# 4、IMU元件驱动程序----roslaunch razor_imu_9dof  razor-pub.launch
