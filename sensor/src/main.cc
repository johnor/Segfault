/* This file contains the entry point for the OrientationFilter application */

#include "headers/smart_pointer_typedefs.h"
#include "headers/exceptions.h"

#include "interfaces/imu.h"
#include "interfaces/measurement.h"
#include "classes/sensorhandlers/default_handler_factory.h"
#include "classes/sensorhandlers/log_reader_factory.h"
#include "classes/alt_imu.h"
#include "classes/logger.h"

#include <iostream>

void PrintMeasurements(const MeasurementBatch& measurementBatch);

int main(int argc, char* argv[])
{
    Logger::Log(LogLevel::Info) << "SensorApp initialized";

    /* Create factory and IMU */
    #ifdef _MSC_VER
        SensorHandlerFactoryPtr factory{ new LogReaderFactory{} };
    #else
        SensorHandlerFactoryPtr factory{ new DefaultHandlerFactory{} };
    #endif

    try
    {
        IMUPtr imu{new AltIMU{factory}};
        MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};
        PrintMeasurements(measurementBatch);

        /* Do not close console immediately */
        Logger::LogToConsole(LogLevel::Info) << "Press any key to exit the application.";
        std::cin.get();
        Logger::LogToFile(LogLevel::Info) << "SensorApp exiting...";
    }
    catch (const I2CException& e)
    {
        Logger::Log(LogLevel::Error) << "Could not instantiate IMU due to I2C problems.";
        Logger::Log(LogLevel::Error) << e.what();
        Logger::Log(LogLevel::Info) << "Exiting application due to unrecoverable error.";
        return EXIT_FAILURE;
    }
    catch (...)
    {
        Logger::Log(LogLevel::Error) << "An unknown exception occured.";
        Logger::Log(LogLevel::Info) << "Exiting application due to unrecoverable error.";
        return EXIT_FAILURE;
    }

    return 0;
}

void PrintMeasurements(const MeasurementBatch& measurementBatch)
{
    for (const auto& measurement : measurementBatch)
    {
        Logger::Log(LogLevel::Debug) << measurement->ToString();
    }
}
