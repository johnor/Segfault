/*
* This file declares classes implementing the Measurement interface.
*/

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include "../headers/numeric_typedefs.h"
#include "../interfaces/measurement.h"
#include <string>

class MeasurementVisitor;

/*
* Abstract base class for scalar measurements
*/
class ScalarMeasurement : public Measurement
{
public:
	virtual ~ScalarMeasurement() {}
	F32 GetValue() const;
protected:
	ScalarMeasurement(const F32 value);
	std::string ToString(const std::string& header, const std::string& unit) const;
private:
	const F32 value;
};

/*
* Abstract base class for vectorial measurements.
*/
class VectorialMeasurement : public Measurement
{
public:
	virtual ~VectorialMeasurement() {}
	F32 GetXValue() const;
	F32 GetYValue() const;
	F32 GetZValue() const;
protected:
	VectorialMeasurement(const F32 xValue, const F32 yValue, const F32 zValue);
	std::string ToString(const std::string& header, const std::string& unit) const;
private:
	const F32 xValue;
	const F32 yValue;
	const F32 zValue;
};

/*
* An accelerometer measurement contains three floating point
* numbers representing acceleration in m/s^2 parallel to the
* corresponding axes.
*/
class AccelerometerMeasurement : public VectorialMeasurement
{
public:
	AccelerometerMeasurement(const F32 xValue, const F32 yValue, const F32 zValue);
	virtual ~AccelerometerMeasurement() {}
	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	AccelerometerMeasurement(const AccelerometerMeasurement&);
	AccelerometerMeasurement& operator=(const AccelerometerMeasurement&);
};

/*
* A gyroscope measurement contains three floating point
* numbers representing angular velocity in rad/s around
* the corresponding axes.
*/
class GyroscopeMeasurement : public VectorialMeasurement
{
public:
	GyroscopeMeasurement(const F32 xValue, const F32 yValue, const F32 zValue);
	virtual ~GyroscopeMeasurement() {}
	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	GyroscopeMeasurement(const GyroscopeMeasurement&);
	GyroscopeMeasurement& operator=(const GyroscopeMeasurement&);
};

/*
* A compass measurement contains three floating point
* numbers representing local magnetic field density
* in T parallel to the corresponding axes.
*/
class CompassMeasurement : public VectorialMeasurement
{
public:
	CompassMeasurement(const F32 xValue, const F32 yValue, const F32 zValue);
	virtual ~CompassMeasurement() {}
	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	CompassMeasurement(const CompassMeasurement&);
	CompassMeasurement& operator=(const CompassMeasurement&);
};

/*
* A pressure measurement contains a floating point value
* representing the local atmospheric pressure in hPa.
*/
class PressureMeasurement : public ScalarMeasurement
{
public:
	PressureMeasurement(const F32 value);
	virtual ~PressureMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	PressureMeasurement(const PressureMeasurement&);
	PressureMeasurement& operator=(const PressureMeasurement&);
};

/*
* A temperature measurement contains a floating point value
* representing the local temperature in degrees Celcius.
*/
class TemperatureMeasurement : public ScalarMeasurement
{
public:
	TemperatureMeasurement(const F32 value);
	virtual ~TemperatureMeasurement() {}
	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	TemperatureMeasurement(const TemperatureMeasurement&);
	TemperatureMeasurement& operator=(const TemperatureMeasurement&);
};

#endif
