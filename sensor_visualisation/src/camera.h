#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    Camera()
    {
        const QVector3D forward(0.0f, 0.0f, 1.0f);
        const QVector3D up(0.0f, 1.0f, 0.0f);
        const QVector3D center(0.0f, 0.0f, 0.0f);
        const QVector3D& eyeRotationAxis = up;
        const float eyeRotation = 0.0f;
        m_eye = center - 2.0f * forward + 2.0f * up;

        QMatrix4x4 tempMatrix;
        tempMatrix.setToIdentity();
        tempMatrix.rotate(eyeRotation, eyeRotationAxis);
        const QVector3D rotatedUp(up * tempMatrix);
        m_viewMatrix.setToIdentity();
        m_viewMatrix.lookAt(m_eye, center, rotatedUp);
    }

    inline const QVector3D& getPosition() const
    {
        return m_eye;
    }

    inline const QMatrix4x4& getViewMatrix() const
    {
        return m_viewMatrix;
    }

private:
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    QVector3D m_eye;
    QMatrix4x4 m_viewMatrix;
};
#endif // CAMERA_H
