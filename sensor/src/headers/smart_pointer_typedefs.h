/*
* Contains typedefs for smart pointers types used in this project.
* This is used to reduce the amount of boilerplate template code.
*/

#ifndef SMART_POINTER_TYPEDEFS_H_
#define SMART_POINTER_TYPEDESFS_H_

#include <memory>
#include <vector>

class Measurement;
class MeasurementVisitor;
class SensorHandler;
class SensorHandlerFactory;
class IMU;
class Model;

typedef std::unique_ptr<const Measurement> MeasurementPtr;
typedef std::unique_ptr<MeasurementVisitor> MeasurementVisitorPtr;
typedef std::unique_ptr<SensorHandler> SensorHandlerPtr;
typedef std::unique_ptr<const SensorHandlerFactory> SensorHandlerFactoryPtr;
typedef std::unique_ptr<const IMU> IMUPtr;
typedef std::unique_ptr<Model> ModelPtr;

typedef std::vector<MeasurementPtr> MeasurementBatch;

#endif
