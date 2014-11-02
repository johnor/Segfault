/*
* This file defines classes implementing the Measurement interface.
*/

#include "measurements.h"
#include "../interfaces/measurement_visitor.h"

#include <sstream>
#include <iomanip>

/* Scalar measurement */
ScalarMeasurement::ScalarMeasurement(const F32 value)
	: value{value}
{
}

std::string ScalarMeasurement::ToString(const std::string& header, const std::string& unit) const
{
	std::ostringstream os{};

	os << std::fixed << std::setprecision(2);
	os << header << '\n';
	os << "Value: " << value << ' ' << unit;
	os << '\n';

	return os.str();
}

F32 ScalarMeasurement::GetValue() const
{
	return value;
}

/* Vectorial measurement */
VectorialMeasurement::VectorialMeasurement(const F32 xValue, const F32 yValue, const F32 zValue)
	: xValue{xValue}, yValue{yValue}, zValue{zValue}
{
}

std::string VectorialMeasurement::ToString(const std::string& header, const std::string& unit) const
{
	std::ostringstream os{};

	os << std::fixed << std::setprecision(2);
	os << header << '\n';
	os << "X: " << xValue << ' ';
	os << "Y: " << yValue << ' ';
	os << "Z: " << zValue << ' ' << unit;
	os << '\n';

	return os.str();
}

F32 VectorialMeasurement::GetXValue() const
{
	return xValue;
}

F32 VectorialMeasurement::GetYValue() const
{
	return yValue;
}

F32 VectorialMeasurement::GetZValue() const
{
	return zValue;
}

/* Accelerometer measurement */
AccelerometerMeasurement::AccelerometerMeasurement(const F32 xValue, const F32 yValue, const F32 zValue)
	: VectorialMeasurement{xValue, yValue, zValue}
{
}

std::string AccelerometerMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Accelerometer measurement", "[m/s^2]");
}

void AccelerometerMeasurement::Accept(const MeasurementVisitorPtr& visitor) const
{
	visitor->Visit(*this);
}

/* Gyroscope measurement */
GyroscopeMeasurement::GyroscopeMeasurement(const F32 xValue, const F32 yValue, const F32 zValue)
	: VectorialMeasurement{xValue, yValue, zValue}
{
}

std::string GyroscopeMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Gyroscope measurement", "[rad/s]");
}

void GyroscopeMeasurement::Accept(const MeasurementVisitorPtr& visitor) const
{
	visitor->Visit(*this);
}

/* Compass measurement */
CompassMeasurement::CompassMeasurement(const F32 xValue, const F32 yValue, const F32 zValue)
	: VectorialMeasurement{xValue, yValue, zValue}
{
}

std::string CompassMeasurement::ToString() const
{
	return VectorialMeasurement::ToString("Compass measurement", "[T]");
}

void CompassMeasurement::Accept(const MeasurementVisitorPtr& visitor) const
{
	visitor->Visit(*this);
}

/* Pressure measurement */
PressureMeasurement::PressureMeasurement(const F32 value)
	: ScalarMeasurement{value}
{
}

std::string PressureMeasurement::ToString() const
{
	return ScalarMeasurement::ToString("Pressure measurement", "[hPa]");
}

void PressureMeasurement::Accept(const MeasurementVisitorPtr& visitor) const
{
	visitor->Visit(*this);
}

/* Temperature measurement */
TemperatureMeasurement::TemperatureMeasurement(const F32 value)
	: ScalarMeasurement{value}
{
}

std::string TemperatureMeasurement::ToString() const
{
	return ScalarMeasurement::ToString("Temperature measurement", "[degrees Celcius]");
}

void TemperatureMeasurement::Accept(const MeasurementVisitorPtr& visitor) const
{
	visitor->Visit(*this);
}
