#include "measurements.h"
#include "../headers/int_typedefs.h"
#include "../interfaces/measurement.h"
#include "../interfaces/measurement_visitor.h"
#include <string>
#include <sstream>

/* Scalar measurement */
ScalarMeasurement::ScalarMeasurement(const S16 value)
	: value(value)
{
}

std::string ScalarMeasurement::ToString(const std::string& header, const std::string& unit) const
{
	std::ostringstream os;

	os << header << '\n';
	os << "Value: " << value << ' ' << unit;
	os << '\n';

	return os.str();
}

S16 ScalarMeasurement::GetValue() const
{
	return value;
}

/* Vectorial measurement */
VectorialMeasurement::VectorialMeasurement(const S16 xValue, const S16 yValue, const S16 zValue)
	: xValue(xValue), yValue(yValue), zValue(zValue)
{
}

std::string VectorialMeasurement::ToString(const std::string& header, const std::string& unit) const
{
	std::ostringstream os;

	os << header << '\n';
	os << "X: " << xValue << ' ' << unit;
	os << "Y: " << yValue << ' ' << unit;
	os << "Z: " << zValue << ' ' << unit;
	os << '\n';

	return os.str();
}

S16 VectorialMeasurement::GetXValue() const
{
	return xValue;
}

S16 VectorialMeasurement::GetYValue() const
{
	return yValue;
}

S16 VectorialMeasurement::GetZValue() const
{
	return zValue;
}

/* Accelerometer measurement */
AccelerometerMeasurement::AccelerometerMeasurement(const S16 xValue, const S16 yValue, const S16 zValue)
	: VectorialMeasurement(xValue, yValue, zValue)
{
}

std::string AccelerometerMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Accelerometer measurement", "m/s^2");
}

void AccelerometerMeasurement::Accept(MeasurementVisitor& visitor) const
{
	visitor.Visit(*this);
}

/* Gyroscope measurement */
GyroscopeMeasurement::GyroscopeMeasurement(const S16 xValue, const S16 yValue, const S16 zValue)
	: VectorialMeasurement(xValue, yValue, zValue)
{
}

std::string GyroscopeMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Gyroscope measurement", "rad/s");
}

void GyroscopeMeasurement::Accept(MeasurementVisitor& visitor) const
{
	visitor.Visit(*this);
}

/* Compass measurement */
CompassMeasurement::CompassMeasurement(const S16 xValue, const S16 yValue, const S16 zValue)
	: VectorialMeasurement(xValue, yValue, zValue)
{
}

std::string CompassMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Accelerometer measurement", "m/s^2");
}

void CompassMeasurement::Accept(MeasurementVisitor& visitor) const
{
	visitor.Visit(*this);
}

/* Pressure measurement */
PressureMeasurement::PressureMeasurement(const S16 value)
	: ScalarMeasurement(value)
{
}

std::string PressureMeasurement::ToString() const
{
	return ScalarMeasurement::ToString("Pressure measurement", "hPa");
}

void PressureMeasurement::Accept(MeasurementVisitor& visitor) const
{
	visitor.Visit(*this);
}

/* Temperature measurement */
TemperatureMeasurement::TemperatureMeasurement(const S16 value)
	: ScalarMeasurement(value)
{
}

std::string TemperatureMeasurement::ToString() const
{
	return ScalarMeasurement::ToString("Temperature measurement", "degrees Celcius");
}

void TemperatureMeasurement::Accept(MeasurementVisitor& visitor) const
{
	visitor.Visit(*this);
}
