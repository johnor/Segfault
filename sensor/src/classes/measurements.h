/*
* This file declares classes implementing the Measurement interface.
*/

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include "../headers/numeric_typedefs.h"
#include "../interfaces/measurement.h"

/*
* Abstract base class for scalar measurements
*/
class ScalarMeasurement : public Measurement
{
public:
	virtual ~ScalarMeasurement() {}
	F32 GetValue() const;
protected:
	explicit ScalarMeasurement(const F32 value);
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
	virtual std::string ToString() const override;
	virtual void Accept(const MeasurementVisitorPtr& visitor) const override;
private:
	AccelerometerMeasurement(const AccelerometerMeasurement&) = delete;
	AccelerometerMeasurement& operator=(const AccelerometerMeasurement&) = delete;
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
	virtual std::string ToString() const override;
	virtual void Accept(const MeasurementVisitorPtr& visitor) const override;
private:
	GyroscopeMeasurement(const GyroscopeMeasurement&) = delete;
	GyroscopeMeasurement& operator=(const GyroscopeMeasurement&) = delete;
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
	virtual std::string ToString() const override;
	virtual void Accept(const MeasurementVisitorPtr& visitor) const override;
private:
	CompassMeasurement(const CompassMeasurement&) = delete;
	CompassMeasurement& operator=(const CompassMeasurement&) = delete;
};

/*
* A pressure measurement contains a floating point value
* representing the local atmospheric pressure in hPa.
*/
class PressureMeasurement : public ScalarMeasurement
{
public:
	explicit PressureMeasurement(const F32 value);
	virtual ~PressureMeasurement() {}
	virtual std::string ToString() const override;
	virtual void Accept(const MeasurementVisitorPtr& visitor) const override;
private:
	PressureMeasurement(const PressureMeasurement&) = delete;
	PressureMeasurement& operator=(const PressureMeasurement&) = delete;
};

/*
* A temperature measurement contains a floating point value
* representing the local temperature in degrees Celcius.
*/
class TemperatureMeasurement : public ScalarMeasurement
{
public:
	explicit TemperatureMeasurement(const F32 value);
	virtual ~TemperatureMeasurement() {}
	virtual std::string ToString() const override;
	virtual void Accept(const MeasurementVisitorPtr& visitor) const override;
private:
	TemperatureMeasurement(const TemperatureMeasurement&) = delete;
	TemperatureMeasurement& operator=(const TemperatureMeasurement&) = delete;
};

#endif
