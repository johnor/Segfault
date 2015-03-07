/*
* Contains typedefs for smart pointers types used in this project.
* This is used to reduce the amount of boilerplate template code.
*/

#ifndef SMART_POINTER_TYPEDEFS_H_
#define SMART_POINTER_TYPEDEFS_H_

#include <memory>
#include <vector>

class Measurement;
class SensorHandler;
class SensorHandlerFactory;
class IMU;
class State;
class Model;
class LogStream;
class Clock;
class Client;

typedef std::unique_ptr<Measurement> MeasurementPtr;
typedef std::unique_ptr<SensorHandler> SensorHandlerPtr;
typedef std::unique_ptr<SensorHandlerFactory> SensorHandlerFactoryPtr;
typedef std::unique_ptr<IMU> IMUPtr;
typedef std::unique_ptr<State> StatePtr;
typedef std::unique_ptr<Model> ModelPtr;
typedef std::unique_ptr<LogStream> LogStreamPtr;

typedef std::vector<MeasurementPtr> MeasurementBatch;

typedef std::shared_ptr<Clock> ClockPtr;
typedef std::shared_ptr<Client> ClientPtr;

#endif
