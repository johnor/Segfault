#include "../../interfaces/measurement_visitor.h"

#include <fstream>
#include <string>

class LoggerVisitor : public MeasurementVisitor
{
public:
    LoggerVisitor(const std::string& logFile);
    virtual ~LoggerVisitor() {}

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;
private:
    LoggerVisitor(const LoggerVisitor&) = delete;
    LoggerVisitor& operator=(const LoggerVisitor&) = delete;

    std::ofstream logStream;
};
