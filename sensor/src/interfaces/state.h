/*
* Interface for model states
* A State can return its own representation in different formats.
*/

#include <eigen/Eigen>

class State
{
public:
    virtual ~State() {}
    virtual Eigen::Quaternionf GetQuaternion() const = 0;
    virtual Eigen::Vector3f GetEulerAngles() const = 0;
    virtual Eigen::Matrix3f GetRotationMatrix() const = 0;
};
