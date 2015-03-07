#include <vector>
#include <fstream>
#include <sstream>

#include "../../headers/exceptions.h"
#include "../../interfaces/clock.h"
#include "../measurements.h"

#include "log_reader_handler.h"

LogReaderHandler::LogReaderHandler(ClockPtr clock, const std::string& logFile)
    : clock{clock}
{
    std::ifstream logStream{logFile};
    if (!logStream)
    {
        throw LogReaderException{"Could not open log file: " + logFile};
    }

    std::string inputLine;
    while (std::getline(logStream, inputLine))
    {
        measurementList.push_back(CreateMeasurement(inputLine));
    }
}

MeasurementBatch LogReaderHandler::GetMeasurements() const
{
    MeasurementBatch currentMeasurements;

    while (!measurementList.empty())
    {
        if (HasAvailableMeasurements())
        {
            currentMeasurements.push_back(std::move(measurementList.front()));
            measurementList.erase(measurementList.begin());
        }
        else
        {
            break;
        }
    }

    return currentMeasurements;
}

bool LogReaderHandler::HasAvailableMeasurements() const
{
    const U32 currentTimeStamp{clock->GetTimeStampInMicroSecs()};
    return (measurementList.front()->GetTimeStamp() < currentTimeStamp);
}

MeasurementPtr LogReaderHandler::CreateMeasurement(const std::string &inputLine) const
{
    const std::vector<std::string> tokenizedString{SplitString(inputLine, ',')};
    const U32 timeStamp{std::stoul(tokenizedString.at(0))};
    const std::string measurementStr{tokenizedString.at(1)};

    if (measurementStr == "ACC")
    {
        return MeasurementPtr{new AccelerometerMeasurement{timeStamp,
                                                           std::stof(tokenizedString.at(2)),
                                                           std::stof(tokenizedString.at(3)),
                                                           std::stof(tokenizedString.at(4))}};
    }
    else if (measurementStr == "MAG")
    {
        return MeasurementPtr{new CompassMeasurement{timeStamp,
                                                     std::stof(tokenizedString.at(2)),
                                                     std::stof(tokenizedString.at(3)),
                                                     std::stof(tokenizedString.at(4))}};
    }
    else if (measurementStr == "GYRO")
    {
        return MeasurementPtr{new GyroscopeMeasurement{timeStamp,
                                                       std::stof(tokenizedString.at(2)),
                                                       std::stof(tokenizedString.at(3)),
                                                       std::stof(tokenizedString.at(4))}};
    }
    else if (measurementStr == "BARO")
    {
        return MeasurementPtr{new PressureMeasurement{timeStamp,
                                                      std::stof(tokenizedString.at(2))}};
    }
    else if (measurementStr == "TEMP")
    {
        return MeasurementPtr{new TemperatureMeasurement{timeStamp,
                                                         std::stof(tokenizedString.at(2))}};
    }
    else
    {
        throw LogReaderException{"Unknown measurement type: " + measurementStr};
    }
}

std::vector<std::string> LogReaderHandler::SplitString(const std::string& input, const char delim) const
{
    std::vector<std::string> elems;
    std::string item;

    std::stringstream inputStringStream{input};
    while (std::getline(inputStringStream, item, delim))
    {
        if (!item.empty())
        {
            elems.push_back(item);
        }
    }

    return elems;
}
