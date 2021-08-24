#pragma once

#include "stalker_driver/UpstreamDataType.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace Interface
{

  namespace UpstreamData
  {
    struct UltrasoundData
    {
      uint16_t distance;
    };

    class UltrasoundFrame : public Interface::UpstreamDataType
    {
    private:
      UltrasoundData dataset;
      void filter();
      UltrasoundData data;
      void doTheProcessing() override;

    public:
      UltrasoundFrame();
      virtual ~UltrasoundFrame();
      void readData(UltrasoundData &dest);
      void deserialize(const uint8_t *iDataStream, const int iDataSize) override;
      // std::unique_ptr<Interface::UpstreamDataType> getClone() override;
    };
  } // namespace UpstreamData
} // namespace Interface
