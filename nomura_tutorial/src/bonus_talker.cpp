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


/* If you are intersted in publishing "Odometory", see this page. */
/*                                                                */
/*  http://wiki.ros.org/ja/navigation/Tutorials/RobotSetup/Odom   */
/*                                                                */
/* ============================================================== */


std_msgs::Int32 Imsg;
std_msgs::Float32 Fmsg;
std_msgs::String Smsg;
std_msgs::Bool Bmsg;
std_msgs::Int32MultiArray IMAmsg;
std_msgs::Float32MultiArray FMAmsg;
geometry_msgs::Twist Tmsg;
visualization_msgs::Marker Mmsg;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "bonus_talker");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	ros::Publisher pub1 = nh.advertise<std_msgs::Int32>("/nomura_tutorial/int",1);
	ros::Publisher pub2 = nh.advertise<std_msgs::Float32>("/nomura_tutorial/float",1);
	ros::Publisher pub3 = nh.advertise<std_msgs::String>("/nomura_tutorial/string",1);
	ros::Publisher pub4 = nh.advertise<std_msgs::Bool>("/nomura_tutorial/bool",1);
	ros::Publisher pub5 = nh.advertise<std_msgs::Int32MultiArray>("/nomura_tutorial/iarray",1);
	ros::Publisher pub6 = nh.advertise<std_msgs::Float32MultiArray>("/nomura_tutorial/farray",1);
	ros::Publisher pub7 = nh.advertise<geometry_msgs::Twist>("/nomura_tutorial/twist",1);
	ros::Publisher pub8 = nh.advertise<visualization_msgs::Marker>("/visualization_marker",1);


	while(ros::ok())
	{
		ros::spinOnce();


		int itmp = rand()%128;
		Imsg.data = itmp;
		pub1.publish(Imsg);
		
		float ftmp = rand()%128 + 0.1 * (rand()%10);
		Fmsg.data = ftmp;
		pub2.publish(Fmsg);

		std::string stmp = "wadanyan";
		Smsg.data = stmp;
		pub3.publish(Smsg);

		bool btmp = true;
		Bmsg.data = btmp;
		pub4.publish(Bmsg);

		IMAmsg.data.resize(3);
		IMAmsg.data[0] = rand()%128;
		IMAmsg.data[1] = rand()%128;
		IMAmsg.data[2] = rand()%128;
		pub5.publish(IMAmsg);

		FMAmsg.data.resize(2);
		float x = rand()%10 - 5.0 + 0.1 * (rand()%10);
		float y = rand()%10 - 5.0 + 0.1 * (rand()%10);
		FMAmsg.data[0] = x;
		FMAmsg.data[1] = y;
		pub6.publish(FMAmsg);

		Tmsg.linear.x = rand()%5;
		Tmsg.angular.z = rand()%5;
		pub7.publish(Tmsg);

		Mmsg.header.stamp = ros::Time::now();
		// Get more infos in https://qiita.com/srs/items/3d16bf8cc60a364bd783
		Mmsg.header.frame_id = "Marker_example";
		Mmsg.ns = "nomura_tutorial";
		Mmsg.id = 0;
		Mmsg.type = visualization_msgs::Marker::CUBE;
		Mmsg.pose.position.z = 0;
		Mmsg.pose.orientation.x = 0.0;
		Mmsg.pose.orientation.y = 0.0;
		Mmsg.pose.orientation.z = 0.0;
		Mmsg.pose.orientation.w = 1.0;
		Mmsg.scale.x = 0.35;
		Mmsg.scale.y = 0.35;
		Mmsg.scale.z = 0.9;
		Mmsg.color.a = 1.0;
		Mmsg.color.r = 1.0;
		Mmsg.color.g = 0.5;
		Mmsg.color.b = 0.0;
		// DELETE -> delete the former object
		Mmsg.action = visualization_msgs::Marker::DELETE;
		Mmsg.pose.position.x = x;
		Mmsg.pose.position.y = y;
		Mmsg.action = visualization_msgs::Marker::ADD;
		pub8.publish(Mmsg);


		loop_rate.sleep();
	}

	return 0;
}
