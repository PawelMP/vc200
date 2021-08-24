#include "vc200_driver/ultrasound.h"

namespace vc200_driver
{
  Ultrasound::Ultrasound(std::shared_ptr<STInterface::STInterfaceClientUDP> st_if, ros::NodeHandle &nh)
      : UltrasoundUpstream(new Interface::UpstreamData::UltrasoundFrame), stClient_(st_if), nh_(nh)
  {
    stClient_->addExpectedDataType(UltrasoundUpstream);
    scans.clear();
    scans.resize(1);
    priv_nh_ = ros::NodeHandle(nh_, "ultrasound_sensor");

    distPublisher = priv_nh_.advertise<sensor_msgs::LaserEcho>("scan", 1, true);
    future_task_ = std::async([]() {});
  }

  void Ultrasound::publish()
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

  void Ultrasound::readData() 
  {
    //std::cout << "se czytam z linijki"<<std::endl;
    UltrasoundUpstream->readData(data);
//std::cout << "se czytam z linijki 0.45"<< (float)(data.distance) <<std::endl;
    scans[0] = float(data.distance);
//std::cout << "se czytam z linijki 0.8"<<std::endl;
    publish();
    //std::cout << "se czytam z linijki 2"<<std::endl;
  }

  void Ultrasound::writeData()
  { // nothing
  }

} // namespace vc200_driver
