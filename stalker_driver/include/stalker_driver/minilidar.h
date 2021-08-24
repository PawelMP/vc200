#pragma once

#include "stalker_driver/UpstreamDataType.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace Interface
{

  namespace UpstreamData
  {
    struct MinilidarData
    {
      uint16_t distance;
      uint16_t signalStrength;
      uint8_t lidarMode;
    };

    class MinilidarFrame : public Interface::UpstreamDataType
    {
    private:
      MinilidarData dataset;
      void filter();
      MinilidarData data;
      void doTheProcessing() override;

    public:
      MinilidarFrame();
      virtual ~MinilidarFrame();
      void readData(MinilidarData &dest);
      void deserialize(const uint8_t *iDataStream, const int iDataSize) override;
      // std::unique_ptr<Interface::UpstreamDataType> getClone() override;
    };
  } // namespace UpstreamData
} // namespace Interface
