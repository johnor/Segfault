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
class I2CHandler;
class I2CHandlerFactory;
class IMU;
class Model;

typedef std::unique_ptr<Measurement> MeasurementPtr;
typedef std::unique_ptr<MeasurementVisitor> MeasurementVisitorPtr;
typedef std::unique_ptr<I2CHandler> I2CHandlerPtr;
typedef std::unique_ptr<I2CHandlerFactory> I2CHandlerFactoryPtr;
typedef std::unique_ptr<IMU> IMUPtr;
typedef std::unique_ptr<Model> ModelPtr;

typedef std::vector<std::unique_ptr<Measurement>> MeasurementBatch;

#endif
