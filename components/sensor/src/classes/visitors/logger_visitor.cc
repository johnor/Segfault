#include "classes/measurements/measurements.h"
#include "logger_visitor.h"

LoggerVisitor::LoggerVisitor(const std::string& logFile)
    : logStream{logFile}
{
}

void LoggerVisitor::Visit(const AccelerometerMeasurement& accMeas)
{
    logStream << accMeas.GetTime().GetMicroSeconds() << ","
              << "ACC,"
              << accMeas.GetXValue() << ","
              << accMeas.GetYValue() << ","
              << accMeas.GetZValue()
              << std::endl;
}

void LoggerVisitor::Visit(const GyroscopeMeasurement& gyroMeas)
{
    logStream << gyroMeas.GetTime().GetMicroSeconds() << ','
              << "GYRO,"
              << gyroMeas.GetXValue() << ","
              << gyroMeas.GetYValue() << ","
              << gyroMeas.GetZValue()
              << std::endl;
}

void LoggerVisitor::Visit(const CompassMeasurement& compassMeas)
{
    logStream << compassMeas.GetTime().GetMicroSeconds() << ','
              << "MAG," << compassMeas.GetXValue() << ","
              << compassMeas.GetYValue() << ","
              << compassMeas.GetZValue()
              << std::endl;
}

void LoggerVisitor::Visit(const PressureMeasurement& pressureMeas)
{
    logStream << pressureMeas.GetTime().GetMicroSeconds() << ','
              << "BARO," << pressureMeas.GetValue()
              << std::endl;
}

void LoggerVisitor::Visit(const TemperatureMeasurement& tempMeas)
{
    logStream << tempMeas.GetTime().GetMicroSeconds() << ','
              << "TEMP," << tempMeas.GetValue()
              << std::endl;
}
