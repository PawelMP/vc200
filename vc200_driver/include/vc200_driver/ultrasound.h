#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserEcho.h>

#include <future>
#include <memory>
#include <string>

#include "stalker_driver/STInterfaceClientUDP.h"
#include "stalker_driver/ultrasound.h"
namespace vc200_driver
{
  class Ultrasound
  {
  public:
    Ultrasound(std::shared_ptr<STInterface::STInterfaceClientUDP> st_if, ros::NodeHandle &nh);
    std::shared_ptr<Interface::UpstreamData::UltrasoundFrame> UltrasoundUpstream;
    std::shared_ptr<STInterface::STInterfaceClientUDP> stClient_;
    ros::NodeHandle nh_;
    ros::NodeHandle priv_nh_;
    void readData();
    void publish();
    void writeData();

  private:
    Interface::UpstreamData::UltrasoundData data;

    std::vector<float> scans;
    sensor_msgs::LaserEcho msg;

    ros::Publisher distPublisher;
    std::future<void> future_task_;
  };
} // namespace vc200_driver
