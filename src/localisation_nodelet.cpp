#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include "localisation_node.hpp"
#include <pluginlib/class_list_macros.hpp>


namespace drone_localisation{

class DroneLocalisationNodelet : public nodelet::Nodelet {
    public:
        DroneLocalisationNodelet() = default;
        ~DroneLocalisationNodelet() = default;

        virtual void onInit() override{
            drone_localisation_node = std::make_shared<DroneLocalisationNode>();
        }

    private:
        std::shared_ptr<DroneLocalisationNode> drone_localisation_node;

};







} // namespace drone_localisation
PLUGINLIB_EXPORT_CLASS(drone_localisation::DroneLocalisationNodelet, nodelet::Nodelet)