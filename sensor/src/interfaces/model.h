/*
* Interface for general Kalman filter models.
* A model can perform a time- and measurement update.
* A model can also return a string representation of its
* internal state.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include "../interfaces/measurement.h"
#include "../headers/numeric_typedefs.h"
#include <memory>
#include <vector>
#include <string>

class Model
{
public:
	virtual ~Model() = default;
	virtual void TimeUpdate(const U32 dtInMilliseconds) = 0;
	virtual void MeasurementUpdate(const std::vector<std::unique_ptr<Measurement>>& measurementBatch) = 0;
	virtual std::string CurrentStateToString() const = 0;
};

#endif
