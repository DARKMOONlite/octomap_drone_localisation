#ifndef LOCALISATION_NODE_HPP
#define LOCALISATION_NODE_HPP
#include <ros/ros.h>
#include <string>

class DroneLocalisationNode{
    public:

    DroneLocalisationNode();
    ~DroneLocalisationNode();

    void init();

    private:

    ros::NodeHandle nh;
    std::string odom_frame_id="odom", base_frame_id="base_link", reference_frame_id="map";
 



};
#endif // LOCALISATION_NODE_HPP