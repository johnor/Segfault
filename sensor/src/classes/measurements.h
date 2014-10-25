/*
* This file declares concrete classes implementing the Measurement interface.
*/

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include "../headers/int_typedefs.h"
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
	S16 GetValue() const;
protected:
	ScalarMeasurement(const S16 value);
	std::string ToString(const std::string& header, const std::string& unit) const;
private:
	const S16 value;
};

/*
* Abstract base class for vectorial measurements.
*/
class VectorialMeasurement : public Measurement
{
public:
	virtual ~VectorialMeasurement() {}
	S16 GetXValue() const;
	S16 GetYValue() const;
	S16 GetZValue() const;
protected:
	VectorialMeasurement(const S16 xValue, const S16 yValue, const S16 zValue);
	std::string ToString(const std::string& header, const std::string& unit) const;
private:
	const S16 xValue;
	const S16 yValue;
	const S16 zValue;
};

class AccelerometerMeasurement : public VectorialMeasurement
{
public:
	AccelerometerMeasurement(const S16 xValue, const S16 yValue, const S16 zValue);
	virtual ~AccelerometerMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	AccelerometerMeasurement(const AccelerometerMeasurement&);
	AccelerometerMeasurement& operator=(const AccelerometerMeasurement&);
};

class GyroscopeMeasurement : public VectorialMeasurement
{
public:
	GyroscopeMeasurement(const S16 xValue, const S16 yValue, const S16 zValue);
	virtual ~GyroscopeMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	GyroscopeMeasurement(const GyroscopeMeasurement&);
	GyroscopeMeasurement& operator=(const GyroscopeMeasurement&);
};

class CompassMeasurement : public VectorialMeasurement
{
public:
	CompassMeasurement(const S16 xValue, const S16 yValue, const S16 zValue);
	virtual ~CompassMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	CompassMeasurement(const CompassMeasurement&);
	CompassMeasurement& operator=(const CompassMeasurement&);
};

class PressureMeasurement : public ScalarMeasurement
{
public:
	PressureMeasurement(const S16 value);
	virtual ~PressureMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	PressureMeasurement(const PressureMeasurement&);
	PressureMeasurement& operator=(const PressureMeasurement&);
};

class TemperatureMeasurement : public ScalarMeasurement
{
public:
	TemperatureMeasurement(const S16 value);
	virtual ~TemperatureMeasurement() {}

	virtual std::string ToString() const;
	virtual void Accept(MeasurementVisitor& visitor) const;
private:
	TemperatureMeasurement(const TemperatureMeasurement&);
	TemperatureMeasurement& operator=(const TemperatureMeasurement&);
};

#endif
