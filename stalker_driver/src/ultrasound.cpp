#include "stalker_driver/ultrasound.h"

namespace Interface
{
    namespace UpstreamData
    {
        UltrasoundFrame::UltrasoundFrame()
        {
            std::cout << "Konstruktor ultrasound" << std::endl;
            protocolIndentificator = uint8_t{0x0F};
            datasetBinarySize = 0x2;
            //data.distance = 5;
        }
        
        void UltrasoundFrame::readData(UltrasoundData &dest)
        {
            std::cout << "Odczyt danych z ultrasound " << data.distance << " cm" << std::endl;
            std::lock_guard<std::mutex> lock(dataMutex);
            dest = data;
        }

        UltrasoundFrame::~UltrasoundFrame() {}

        void UltrasoundFrame::deserialize(const uint8_t *iDataStream, const int iDataSize)
        {
            if (iDataSize % datasetBinarySize != 0)
            {
                std::cout << "Bad ultrasound sensor data - length mismatch" << std::endl;
                return;
            }

            std::lock_guard<std::mutex> lock(dataMutex);

            dataset.distance = uint16_t((iDataStream[0] << 8) | (iDataStream[1] & 0xFF));
	    //dataset.distance = uint16_t(iDataStream[1] << 8);
	    //dataset.distance = dataset.distance + uint16_t(iDataStream[2]);

            data.distance = dataset.distance;

            std::cout << "RAW ultrasound data: " << data.distance << std::endl;

            //doTheProcessing();
        }

        void UltrasoundFrame::doTheProcessing()
        {


        }

    } // namespace UpstreamData
} // namespace Interface
