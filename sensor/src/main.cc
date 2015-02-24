/* This file contains the entry point for the OrientationFilter application */

#include "headers/smart_pointer_typedefs.h"
#include "headers/exceptions.h"

#include "interfaces/imu.h"
#include "interfaces/measurement.h"
#include "classes/sensorhandlers/factories/default_handler_factory.h"
#include "classes/sensorhandlers/factories/log_reader_factory.h"
#include "classes/visitors/logger_visitor.h"
#include "classes/alt_imu.h"
#include "classes/logger.h"
#include "classes/clock/hardwareclock.h"
#include "classes/clock/softwareclock.h"
#include "classes/filter/quaternion_state.h"
#include "classes/filter/ekf_filter.h"
#include "classes/filter/gyro_input_model.h"
#include "classes/measurements.h"

#include "server/server.h"
#include "server/job.h"

#include <iostream>

#include <windows.h>

void PrintAndLogMeasurements(const MeasurementBatch& measurementBatch);
void SendTest(ConnectionManager &connectionManager);

class SensorApp
{
public:
    SensorApp(const SensorHandlerFactoryPtr &sensorHandlerFactory, Clock &clock)
        : imu{ new AltIMU{ sensorHandlerFactory } }, model{ new GyroInputModel{ state } }, clock{ clock }
    {
    };

    ~SensorApp() = default;

    void Update()
    {
        MeasurementBatch measurementBatch{ imu->GetNextMeasurementBatch() };
        //PrintAndLogMeasurements(measurementBatch);

        filter.Update(model, measurementBatch);
        std::cout << state.GetEulerAngles();
    };
private:
    SensorApp(const SensorApp&) = delete;
    SensorApp& operator=(const SensorApp&) = delete;

    IMUPtr imu;
    QuaternionState state;
    KalmanModelPtr model;
    EkfFilter filter;

    Clock &clock;

};

int main(int argc, char* argv[])
{
    Logger::Log(LogLevel::Info) << "SensorApp initialized";

    /* Create factory and IMU */
    #ifdef _MSC_VER
        std::string logFileName = "logs/measurementslog_D2014-12-09_T18-49_180_degrees_rotation_and_back.txt";
        if (argc > 1)
        {
            logFileName = argv[1];
        }
        SoftwareClock clock;
        SensorHandlerFactoryPtr factory{ new LogReaderFactory{ clock, logFileName } };
    #else
        HardwareClock clock;
        SensorHandlerFactoryPtr factory{ new DefaultHandlerFactory{ clock } };
    #endif

    try
    {
        asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 5001);

        Server server(io_service, endpoint);
        ConnectionManager &connectionManager = server.GetConnectionManager();

        SensorApp sensorApp{ factory, clock };

        while (true)
        {
            #ifdef _MSC_VER
                clock.IncreaseTimeStamp(1 / 20.f);
            #endif
            sensorApp.Update();
            Sleep(50);
        }


        std::function<void()> sendTestFunction = std::bind(SendTest, std::ref(connectionManager));
        Job job{ io_service, sendTestFunction, std::chrono::milliseconds{ 1000 } };

        io_service.run();

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
    catch (const std::exception &e)
    {
        Logger::Log(LogLevel::Error) << "An unknown exception occurred.";
        Logger::Log(LogLevel::Error) << e.what();
        Logger::Log(LogLevel::Info) << "Exiting application due to unrecoverable error.";
        return EXIT_FAILURE;
    }
    catch (...)
    {
        Logger::Log(LogLevel::Error) << "An unknown exception occurred.";
        Logger::Log(LogLevel::Info) << "Exiting application due to unrecoverable error.";
        return EXIT_FAILURE;
    }

    return 0;
}

void SendTest(ConnectionManager &connectionManager)
{
    Logger::Log(LogLevel::Debug) << "SendTest";

    Message msg;
    msg.SetMsgType(1);
    msg.SetBodyLength(3);
    msg.EncodeHeader();
    msg.WriteChar('H');
    msg.WriteChar('e');
    msg.WriteChar('j');
    connectionManager.SendToAll(msg);

    Message msg2;
    msg2.SetMsgType(2);
    msg2.SetBodyLength(sizeof(F32) * 3);
    msg2.EncodeHeader();
    msg2.WriteFloat(1.0f);
    msg2.WriteFloat(10.0f);
    msg2.WriteFloat(15.0f);
    connectionManager.SendToAll(msg2);
}

void PrintAndLogMeasurements(const MeasurementBatch& measurementBatch)
{
    #ifndef _MSC_VER
        LoggerVisitor loggerVisitor{ "measurementslog.txt"};
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
