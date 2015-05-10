/*
* Contains typedefs for smart pointers types used in this project.
* This is used to reduce the amount of boilerplate template code.
*/

#ifndef SMART_POINTER_TYPEDEFS_H_
#define SMART_POINTER_TYPEDEFS_H_

#include <memory>
#include <vector>

class Measurement;
class IMU;
class Model;
class LogStream;

typedef std::unique_ptr<Measurement> MeasurementPtr;
typedef std::unique_ptr<IMU> IMUPtr;
typedef std::unique_ptr<Model> ModelPtr;
typedef std::unique_ptr<LogStream> LogStreamPtr;
typedef std::vector<MeasurementPtr> MeasurementBatch;

#endif
