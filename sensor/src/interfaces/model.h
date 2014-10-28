/*
* Interface for general Kalman filter models.
* A model can perform a time- and measurement update.
* A model can also return a string representation of its
* internal state.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include "../headers/numeric_typedefs.h"
#include <string>
#include <vector>

class Measurement;

class Model
{
public:
	virtual ~Model() {}
	virtual void TimeUpdate(const U32 dtInMilliseconds) = 0;
	virtual void MeasurementUpdate(const std::vector<const Measurement*>& measurementBatch) = 0;
	virtual std::string CurrentStateToString() const = 0;
};

#endif
