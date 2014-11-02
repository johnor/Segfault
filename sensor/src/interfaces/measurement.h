/* 
* Interface for measurements.
* A measurement can return a string representation of itself.
* It can also accept a MeasurementVisitor that can perform
* different operations depending on the type of measurement.
*/

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "../headers/smart_pointer_typedefs.h"
#include <string>

class Measurement
{
public:
	virtual ~Measurement() {}
	virtual void Accept(const MeasurementVisitorPtr& visitor) const = 0;
	virtual std::string ToString() const = 0;
private:
	Measurement& operator=(const Measurement&) = delete;
};

#endif
