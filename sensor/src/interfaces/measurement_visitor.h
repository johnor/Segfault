/*
* Interface for measurement visitor.
* A MeasurementVisitor is used in the visitor pattern
* to enable performing operations on a list of measurements.
*/

#ifndef MEASUREMENT_VISITOR_H_
#define MEASUREMENT_VISITOR_H_

class AccelerometerMeasurement;
class GyroscopeMeasurement;
class CompassMeasurement;
class PressureMeasurement;
class TemperatureMeasurement;

class MeasurementVisitor
{
public:
	virtual ~MeasurementVisitor() {};
	virtual void Visit(const AccelerometerMeasurement& accMeas) = 0;
	virtual void Visit(const GyroscopeMeasurement& gyroMeas) = 0;
	virtual void Visit(const CompassMeasurement& compassMeas) = 0;
	virtual void Visit(const PressureMeasurement& pressureMeas) = 0;
	virtual void Visit(const TemperatureMeasurement& tempMeas) = 0;
};

#endif
