/*
* This file declares classes implementing the Measurement interface.
*/

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include "components/common/src/numeric_typedefs.h"
#include "components/common/src/time_point.h"
#include "interfaces/measurement.h"

class MeasurementBase : public Measurement
{
public:
    virtual ~MeasurementBase() {}
    virtual TimePoint GetTime() const override;
protected:
    explicit MeasurementBase(const TimePoint &timeStamp);
private:
    MeasurementBase(const MeasurementBase&) = delete;
    MeasurementBase& operator=(const MeasurementBase&) = delete;
    const TimePoint timeStamp;
};

/* 
* Abstract base class for scalar measurements
*/
class ScalarMeasurement : public MeasurementBase
{
public:
    virtual ~ScalarMeasurement() {}
    F32 GetValue() const;
protected:
    ScalarMeasurement(const TimePoint &timeStamp, const F32 value);
    std::string ToString(const std::string& header, const std::string& unit) const;
private:
    const F32 value;
};

/*
* Abstract base class for vectorial measurements.
*/
class VectorialMeasurement : public MeasurementBase
{
public:
    virtual ~VectorialMeasurement() {}
    F32 GetXValue() const;
    F32 GetYValue() const;
    F32 GetZValue() const;
protected:
    VectorialMeasurement(const TimePoint &timeStamp, const F32 xValue, const F32 yValue, const F32 zValue);
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
    AccelerometerMeasurement(const TimePoint &timeStamp, const F32 xValue, const F32 yValue, const F32 zValue);
    virtual ~AccelerometerMeasurement() {}
    virtual std::string ToString() const override;
    virtual void Accept(MeasurementVisitor& visitor) const override;
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
    GyroscopeMeasurement(const TimePoint &timeStamp, const F32 xValue, const F32 yValue, const F32 zValue);
    virtual ~GyroscopeMeasurement() {}
    virtual std::string ToString() const override;
    virtual void Accept(MeasurementVisitor& visitor) const override;
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
    CompassMeasurement(const TimePoint &timeStamp, const F32 xValue, const F32 yValue, const F32 zValue);
    virtual ~CompassMeasurement() {}
    virtual std::string ToString() const override;
    virtual void Accept(MeasurementVisitor& visitor) const override;
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
    explicit PressureMeasurement(const TimePoint &timeStamp, const F32 value);
    virtual ~PressureMeasurement() {}
    virtual std::string ToString() const override;
    virtual void Accept(MeasurementVisitor& visitor) const override;
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
    explicit TemperatureMeasurement(const TimePoint &timeStamp, const F32 value);
    virtual ~TemperatureMeasurement() {}
    virtual std::string ToString() const override;
    virtual void Accept(MeasurementVisitor& visitor) const override;
private:
    TemperatureMeasurement(const TemperatureMeasurement&) = delete;
    TemperatureMeasurement& operator=(const TemperatureMeasurement&) = delete;
};

#endif
