/* 
* Interface for measurements.
* A measurement can return a string representation of itself.
* It can also accept a MeasurementVisitor that can perform
* different operations depending on the type of measurement.
*/

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include <string>

class MeasurementVisitor;

class Measurement
{
public:
	virtual ~Measurement() {}
	virtual void Accept(MeasurementVisitor& visitor) const = 0;
	virtual std::string ToString() const = 0;
};

#endif
