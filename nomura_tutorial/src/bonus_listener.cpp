#include <iostream>
#include <string>
#include <stdlib.h>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>


int Imsg = 0;
float Fmsg = 0.0;
std::string Smsg = "";
bool Bmsg = false;
int IMAmsg[100] = {};
float FMAmsg[2] = {};
float Tmsg_linear_x = 0.0;
float Tmsg_angular_z = 0.0;


void intCallback(const std_msgs::Int32::ConstPtr& msg)
{
	Imsg = msg->data;
}

void floatCallback(const std_msgs::Float32::ConstPtr& msg)
{
	Fmsg = msg->data;
}

void stringCallback(const std_msgs::String::ConstPtr& msg)
{
	Smsg = msg->data;
}

void boolCallback(const std_msgs::Bool::ConstPtr& msg)
{
	Bmsg = msg->data;
}

void iarrayCallback(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
	int i = 0;
	for(std::vector<int>::const_iterator it = msg->data.begin(); it != msg->data.end(); ++it){
		IMAmsg[i] = (*it);
		i++;
	}
	IMAmsg[i]='\0';
}

void farrayCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	FMAmsg[0] = msg->data[0];
	FMAmsg[1] = msg->data[1];
}

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	Tmsg_linear_x = msg->linear.x;
	Tmsg_angular_z = msg->angular.z;
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "bonus_listener");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	ros::Subscriber sub1 = nh.subscribe("/nomura_tutorial/int", 1, intCallback);
	ros::Subscriber sub2 = nh.subscribe("/nomura_tutorial/float", 1, floatCallback);
	ros::Subscriber sub3 = nh.subscribe("/nomura_tutorial/string", 1, stringCallback);
	ros::Subscriber sub4 = nh.subscribe("/nomura_tutorial/bool", 1, boolCallback);
	ros::Subscriber sub5 = nh.subscribe("/nomura_tutorial/iarray", 1, iarrayCallback);
	ros::Subscriber sub6 = nh.subscribe("/nomura_tutorial/farray", 1, farrayCallback);
	ros::Subscriber sub7 = nh.subscribe("/nomura_tutorial/twist", 1, twistCallback);


	while(ros::ok())
	{
		ros::spinOnce();

		ROS_INFO("UPDATE");
		std::cout<< "int_msg: " << '\t' << Imsg <<std::endl;
		std::cout<< "float_msg: " << '\t' << Fmsg <<std::endl;
		std::cout<< "string_msg: " << '\t' << Smsg <<std::endl;
		std::cout<< "bool_msg: " << '\t' << Bmsg <<std::endl;
		std::cout<< "iarray_msg: " << '\t' << IMAmsg[0] << "," << IMAmsg[1] << "," << IMAmsg[2] <<std::endl;
		std::cout<< "farray_msg: " << '\t' << FMAmsg[0] << "," << FMAmsg[1] <<std::endl;
		std::cout<< "twist_msg: " << '\t' << Tmsg_linear_x << "," << Tmsg_angular_z <<std::endl;

		loop_rate.sleep();
	}
}
