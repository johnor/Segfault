/* This file contains the entry point for the OrientationFilter application */

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "headers/smart_pointer_typedefs.h"

#include "interfaces/imu.h"
#include "classes/imu/alt_imu.h"
#include "classes/imu/log_reader_imu.h"
#include "classes/service_locator/service_locator.h"
#include "classes/filter/bias_model/bias_model.h"
#include "classes/measurements/measurements.h"

#include "server/src/server.h"
#include "server/src/job.h"

#include "common/src/logger.h"

#include "sensor_app.h"

int main(int argc, char **argv)
{
    Logger::SetMinLogLevel(LogLevel::Info);
    Logger::Log(LogLevel::Info) << "Starting SensorApp!";

    try
    {
        #ifndef __arm__
            std::string logFileName{"logs/measurementslog_D2014-12-09_T18-49_180_degrees_rotation_and_back.txt"};
            if (argc > 1)
            {
                logFileName = argv[1];
            }
            ServiceLocator::UseSoftwareClock();
            SensorApp sensorApp{IMUPtr{new LogReaderIMU{logFileName}}};
        #else
            ServiceLocator::UseHardwareClock();
            SensorApp sensorApp{IMUPtr{new AltIMU}};
        #endif

        asio::io_service ioService;
        Server server(ioService, SensorApp::serverPort);
        ConnectionManager &connectionManager = server.GetConnectionManager();

        std::function<void()> updateFunction{std::bind(&SensorApp::Update, &sensorApp)};
        Job updateJob{ioService, updateFunction, std::chrono::milliseconds{50}};

        std::function<void()> sendDataFunction = std::bind(&SensorApp::SendData, &sensorApp, std::ref(connectionManager));
        Job sendDataJob{ ioService, sendDataFunction, std::chrono::milliseconds{50}};

        asio::signal_set signal_set(ioService, SIGINT);
        signal_set.async_wait(
            [](const std::error_code &errorCode,
               const int signalNumber)
        {
            if (!errorCode)
            {
                std::cout << "Caught signal: " << signalNumber << std::endl;
            }
            else
            {
                Logger::Log(LogLevel::Error) << errorCode;
            }
            exit(0);
        });

        ioService.run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "An unknown error occured." << std::endl;
        return 1;
    }

    return 0;
}
