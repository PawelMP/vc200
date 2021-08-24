#include "stalker_driver/minilidar.h"

namespace Interface
{
    namespace UpstreamData
    {
        MinilidarFrame::MinilidarFrame()
        {
            std::cout << "Konstruktor Minilidar" << std::endl;
            protocolIndentificator = uint8_t{0x09};
            datasetBinarySize = 0x5;
            data.distance = 0;
        }
        
        void MinilidarFrame::readData(MinilidarData &dest)
        {
            std::cout << "Odczyt danych z Minilidar - dystans " << data.distance << " cm" << std::endl;
            std::cout << "Odczyt danych z Minilidar - sila " << data.signalStrength << std::endl;
            std::lock_guard<std::mutex> lock(dataMutex);
            dest = data;
        }

        MinilidarFrame::~MinilidarFrame() {}

        void MinilidarFrame::deserialize(const uint8_t *iDataStream, const int iDataSize)
        {
            if (iDataSize % datasetBinarySize != 0)
            {
                std::cout << "Bad Minilidar sensor data - length mismatch" << std::endl;
                return;
            }

            std::lock_guard<std::mutex> lock(dataMutex);

            dataset.distance = uint16_t((iDataStream[0] << 8) | (iDataStream[1] & 0xFF));
	    dataset.signalStrength = uint16_t((iDataStream[2] << 8) | (iDataStream[3] & 0xFF));

            data.distance = dataset.distance;
            data.signalStrength = dataset.signalStrength;

            std::cout << "RAW Minilidar data: " << data.distance << std::endl;

            //doTheProcessing();
        }

        void MinilidarFrame::doTheProcessing()
        {


        }

    } // namespace UpstreamData
} // namespace Interface
