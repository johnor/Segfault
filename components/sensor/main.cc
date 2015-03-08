/* This file contains the entry point for the OrientationFilter application */

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "headers/smart_pointer_typedefs.h"

#include "interfaces/imu.h"
#include "classes/sensorhandlers/factories/log_reader_factory.h"
#include "classes/sensorhandlers/factories/default_handler_factory.h"
#include "classes/clock/softwareclock.h"
#include "classes/clock/hardwareclock.h"
#include "classes/filter/gyro_input_model.h"
#include "classes/alt_imu.h"

#include "server/src/server.h"
#include "server/src/job.h"

#include "sensor_app.h"

//void PrintAndLogMeasurements(const MeasurementBatch& measurementBatch);

int main(int argc, char **argv)
{
    /* Create default factory if compiling for target, else log reader factory. */
    try
    {
        #ifndef __arm__
            std::string logFileName{"logs/measurementslog_D2014-12-09_T18-49_180_degrees_rotation_and_back.txt"};
            if (argc > 1)
            {
                logFileName = argv[1];
            }
            ClockPtr clock{new SoftwareClock};
            SensorHandlerFactoryPtr factory{new LogReaderFactory{clock, logFileName}};
        #else
            ClockPtr clock{new HardwareClock};
            SensorHandlerFactoryPtr factory{new DefaultHandlerFactory{clock}};
        #endif

        SensorApp sensorApp{IMUPtr{new AltIMU{factory}}, ModelPtr{new GyroInputModel}, clock};

        asio::io_service ioService;
        Server server(ioService, SensorApp::serverPort);
        ConnectionManager &connectionManager = server.GetConnectionManager();

        std::function<void()> updateFunction{std::bind(&SensorApp::Update, &sensorApp)};
        Job updateJob{ioService, updateFunction, std::chrono::milliseconds{50}};

        std::function<void()> sendDataFunction = std::bind(&SensorApp::SendData, &sensorApp, std::ref(connectionManager));
        Job testSendJob{ ioService, sendDataFunction, std::chrono::milliseconds{ 100 } };

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

/*
void PrintAndLogMeasurements(const MeasurementBatch& measurementBatch)
{
    #ifndef _MSC_VER
        static LoggerVisitor loggerVisitor{ "measurementslog.txt"};
        for (const auto& measurement : measurementBatch)
        {
            measurement->Accept(loggerVisitor);
        }
    #endif

    for (const auto& measurement : measurementBatch)
    {
        Logger::Log(LogLevel::Debug) << measurement->ToString();
    }
}
*/