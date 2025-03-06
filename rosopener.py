#!/usr/bin/env python3
import serial
import subprocess
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped

# Initialize serial port
ser = serial.Serial('/dev/ttyUSB-Dynamixel', 9600)
ser.flush()

# Command list
commands = [
    ["gnome-terminal", "--", "bash", "-c", "source ~/catkin_ws/devel/setup.bash && roslaunch '/home/ichinoseki-b/catkin_ws/src/nav/launch/ros_max.launch'"],
]

def callback(data):
    message = "{:.6f},{:.6f},{:.6f},{:.6f}\n".format(
        data.pose.pose.position.x, data.pose.pose.position.y, data.pose.pose.orientation.z, data.pose.pose.orientation.w
    )
    ser.write(message.encode('ASCII'))

def listener():
    rospy.init_node('amcl_pose_listener', anonymous=True)
    rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, callback)
    rospy.spin()

for command in commands:
    subprocess.Popen(command)

listener()
