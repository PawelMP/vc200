#include "vc200_driver/minilidar.h"

namespace vc200_driver
{
  Minilidar::Minilidar(std::shared_ptr<STInterface::STInterfaceClientUDP> st_if, ros::NodeHandle &nh)
      : MinilidarUpstream(new Interface::UpstreamData::MinilidarFrame), stClient_(st_if), nh_(nh)
  {
    stClient_->addExpectedDataType(MinilidarUpstream);
    scans.clear();
    scans.resize(1);
    priv_nh_ = ros::NodeHandle(nh_, "Minilidar_sensor");

    distPublisher = priv_nh_.advertise<sensor_msgs::LaserEcho>("scan", 1, true);
    future_task_ = std::async([]() {});
  }

  void Minilidar::publish()
  {
    //std::cout << "dupsko przed\n";
    if ((future_task_.valid()) && (scans.size() > 0))
    {
      future_task_ = std::async([this]()
                                {
                                  //std::cout << "dupsko\n";
                                  msg.echoes = this->scans;
                                  this->distPublisher.publish(msg);
                                });
    }
  }

  void Minilidar::readData() 
  {
    //std::cout << "se czytam z linijki"<<std::endl;
    MinilidarUpstream->readData(data);
//std::cout << "se czytam z linijki 0.45"<< (float)(data.distance) <<std::endl;
    scans[0] = float(data.distance);
//std::cout << "se czytam z linijki 0.8"<<std::endl;
    publish();
    //std::cout << "se czytam z linijki 2"<<std::endl;
  }

  void Minilidar::writeData()
  { // nothing
  }

} // namespace vc200_driver
