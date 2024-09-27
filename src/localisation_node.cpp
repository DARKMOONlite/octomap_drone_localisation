#include <ros/ros.h>
#include "localisation_node.hpp"



DroneLocalisationNode::DroneLocalisationNode()
{
    nh = ros::NodeHandle("~");


    nh.param("odom_frame_id", odom_frame_id, odom_frame_id);
    nh.param("base_frame_id", base_frame_id, base_frame_id);
    nh.param("world_frame_id", reference_frame_id, reference_frame_id);


}


DroneLocalisationNode::~DroneLocalisationNode()
{
}





int main(int argc, char* argv[])
{
    ros::init(argc, argv, "/*node_name*/");
    DroneLocalisationNode drone_localisation_node;
    ros::spin();
    
}