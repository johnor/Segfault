/* 
* Interface for measurements.
* A measurement can return a string representation of itself.
* It can also accept a MeasurementVisitor that can perform
* different operations depending on the type of measurement.
*/

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "../interfaces/measurement_visitor.h"
#include <memory>
#include <string>

class Measurement
{
public:
	virtual ~Measurement() = default;
	virtual void Accept(const std::unique_ptr<MeasurementVisitor>& visitor) const = 0;
	virtual std::string ToString() const = 0;
};

#endif
