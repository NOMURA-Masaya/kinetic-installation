#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "../include/date.hpp"

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>


/**************************/
// Global variables
float cmd[3] = {};
// cmd[0] = vel_linear_x
// cmd[1] = vel_angular_z
// cmd[2] = timeout flag
//	0.0 >> updated
//	1.0 >> not updated
/**************************/


// Callback function of a topic-subscriber.
void cmdCallback(const geometry_msgs::Twist::ConstPtr& Vmsg)
{
	cmd[0] = Vmsg->linear.x;
	cmd[1] = Vmsg->angular.z;
	cmd[2] = 0.0;
	return;
}

int main(int argc, char **argv)
{
	// Entry the ros master
	ros::init(argc, argv, "nomura_tutorial");
	ros::NodeHandle nh;
	ros::NodeHandle nh_private("~");

	// Subscribers of topic : subscriber-name("topic-name", buffer, callback-name);
	ros::Subscriber sub1 = nh.subscribe("/nomura_tutorial/cmd_vel", 10, cmdCallback);

	// The publisher of topic : publisher-name = nh.advertise<type>("topic-name", buffer);
	ros::Publisher pub1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);

	//----------------------------------------------------------------------//
	// Prameters : n_private.param("parameter-name", variable, default-value);
	float timeout = 1.0;
	nh_private.param("timeout", timeout, timeout);
	float vel_linear_x = 2.0;
	nh_private.param("vel_linear_x", vel_linear_x, vel_linear_x);
	float vel_angular_z = 2.0;
	nh_private.param("vel_angular_z", vel_angular_z, vel_angular_z);
	//----------------------------------------------------------------------//

	// Logs distances
	std::string path = "/home/nomura/catkin_ws/src/nomura_tutorial/log/log-";
	std::string fname = path + datetime() + ".csv";
	std::ofstream log(fname,std::ios::binary);
	if (!log)
    {
		ROS_FATAL("A file-path error is occurred in log.");
        return 1;
    }

	// The while-loop frequency
	ros::Rate loop_rate(10);

	// Velocity commands for publish
	geometry_msgs::Twist Vcmd;

	// for timeout judging
	ros::Time past = ros::Time::now();

	// The main loop
	while(ros::ok())
	{
		// Run callbacks
		ros::spinOnce();

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		// [YOUR PROCCESSES OR SOLUTIONS]

		// If keyboard inputs are updated, the timeout will be updated too
		if(cmd[2] == 0.0)
		{
			past = ros::Time::now();
		}
		cmd[2] = 1.0;

		// If the not-update time > timeout, reset the vel
		if(ros::Time::now() - past > ros::Duration(timeout))
		{
			cmd[0] = 0.0;
			cmd[1] = 0.0;
			past = ros::Time::now();
		}

		// Checking input vels
		if(cmd[0]<0.0)
		{
			Vcmd.linear.x = -1 * vel_linear_x;
		}
		else if(cmd[0]==0.0)
		{
			Vcmd.linear.x = 0.0;
		}
		else
		{
			Vcmd.linear.x = vel_linear_x;
		}

		if(cmd[1]<0.0)
		{
			Vcmd.angular.z = -1 * vel_angular_z;
		}
		else if(cmd[1]==0.0)
		{
			Vcmd.angular.z = 0.0;
		}
		else
		{
			Vcmd.angular.z = vel_angular_z;
		}
		
		// Publish the new vel
		pub1.publish(Vcmd);

		// Logging generated vels
		log<<"(velX & velZ)"<<","<<Vcmd.linear.x<<","<<Vcmd.angular.z<<std::endl;
		log.flush();

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		// Adjust time for the frequency
		loop_rate.sleep();
	}

	log.close();
	return 0;
}
