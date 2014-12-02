/* 
* Interface for measurements.
* A measurement can return a string representation of itself.
* It can also accept a MeasurementVisitor that can perform
* different operations depending on the type of measurement.
*/

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "../headers/smart_pointer_typedefs.h"
#include "../headers/numeric_typedefs.h"
#include "measurement_visitor.h"
#include <string>

class Measurement
{
public:
    Measurement() = default;
    virtual ~Measurement() {};

    virtual void Accept(MeasurementVisitor& visitor) const = 0;
    virtual std::string ToString() const = 0;
    virtual U32 GetTimeStamp() const = 0;
private:
    Measurement(const Measurement&) = delete;
    Measurement& operator=(const Measurement&) = delete;
};

#endif
