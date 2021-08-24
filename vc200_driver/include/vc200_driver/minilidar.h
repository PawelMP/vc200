#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserEcho.h>

#include <future>
#include <memory>
#include <string>

#include "stalker_driver/STInterfaceClientUDP.h"
#include "stalker_driver/minilidar.h"
namespace vc200_driver
{
  class Minilidar
  {
  public:
    Minilidar(std::shared_ptr<STInterface::STInterfaceClientUDP> st_if, ros::NodeHandle &nh);
    std::shared_ptr<Interface::UpstreamData::MinilidarFrame> MinilidarUpstream;
    std::shared_ptr<STInterface::STInterfaceClientUDP> stClient_;
    ros::NodeHandle nh_;
    ros::NodeHandle priv_nh_;
    void readData();
    void publish();
    void writeData();

  private:
    Interface::UpstreamData::MinilidarData data;

    std::vector<float> scans;
    sensor_msgs::LaserEcho msg;

    ros::Publisher distPublisher;
    std::future<void> future_task_;
  };
} // namespace vc200_driver
