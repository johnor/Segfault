#include "logger_visitor.h"
#include "../../classes/measurements.h"

LoggerVisitor::LoggerVisitor(const std::string& accLogFile, const std::string& gyroLogFile, const std::string& baroLogFile)
	: accAngMagLogStream{accLogFile}, gyroscopeLogStream{gyroLogFile}, barometerLogStream{baroLogFile}
{
}

void LoggerVisitor::Visit(const AccelerometerMeasurement& accMeas)
{
	accAngMagLogStream << "ACC, " << accMeas.GetXValue() << ", " << accMeas.GetYValue() << ", " << accMeas.GetZValue() << std::endl;
}

void LoggerVisitor::Visit(const GyroscopeMeasurement& gyroMeas)
{
	gyroscopeLogStream << "GYRO, " << gyroMeas.GetXValue() << ", " << gyroMeas.GetYValue() << ", " << gyroMeas.GetZValue() << std::endl;
}

void LoggerVisitor::Visit(const CompassMeasurement& compassMeas)
{
	accAngMagLogStream << "MAG, " << compassMeas.GetXValue() << ", " << compassMeas.GetYValue() << ", " << compassMeas.GetZValue() << std::endl;
}

void LoggerVisitor::Visit(const PressureMeasurement& pressureMeas)
{
	barometerLogStream << "BARO, " << pressureMeas.GetValue() << std::endl;
}

void LoggerVisitor::Visit(const TemperatureMeasurement& tempMeas)
{
	barometerLogStream << "TEMP, " << tempMeas.GetValue() << std::endl;
}
