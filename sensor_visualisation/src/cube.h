#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#define NUMB_OF_VERTICES 36

class Cube
{
public:
    Cube() = default;

    void initialize()
    {
        const char*vertexPath = ":/shaders/cube.vert";
        const char*fragmentPath = ":/shaders/cube.frag";
        if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath))
            qCritical() << QObject::tr("Could not compile vertex shader: ") << vertexPath << m_program.log();
        if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath))
            qCritical() << QObject::tr("Could not compile fragment shader: ") << fragmentPath << m_program.log();
        if(!m_program.link())
            qCritical() << QObject::tr("Could not link shader program: ") << m_program.log();

        m_vertexPositionBuffer.create();
        m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertexPositionBuffer.bind();
        m_vertexPositionBuffer.allocate(m_vertices, sizeof(m_vertices));

        m_vertexColorBuffer.create();
        m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertexColorBuffer.bind();
        m_vertexColorBuffer.allocate(m_colors, sizeof(m_colors));

        m_vertexNormalBuffer.create();
        m_vertexNormalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertexNormalBuffer.bind();
        m_vertexNormalBuffer.allocate(m_normals, sizeof(m_normals));

        m_vertexNormalBuffer.release();
        m_vertexPositionBuffer.release();
        m_vertexColorBuffer.release();
        m_program.release();
    }

    ~Cube()
    {
        m_vertexNormalBuffer.release();
        m_vertexPositionBuffer.release();
        m_vertexColorBuffer.release();
        m_program.release();

        m_vertexNormalBuffer.destroy();
        m_vertexPositionBuffer.destroy();
        m_vertexColorBuffer.destroy();
        m_program.removeAllShaders();
    }

    inline void render(const QMatrix4x4& viewMatrix, const QMatrix4x4& projectionMatrix, const QMatrix4x4& modelMatrix, const QVector3D& cameraPosition)
    {
        const QMatrix4x4& modelViewMatrix = viewMatrix * modelMatrix;
        const QMatrix3x3& normalMatrix = modelViewMatrix.normalMatrix();
        const QMatrix4x4& mvp = projectionMatrix * modelViewMatrix;

        m_program.bind();
        m_program.setUniformValue("modelViewMatrix", modelViewMatrix);
        m_program.setUniformValue("cameraPosition", cameraPosition);
        m_program.setUniformValue("modelMatrix", modelMatrix);
        m_program.setUniformValue("normalMatrix", normalMatrix);
        m_program.setUniformValue("projectionMatrix", projectionMatrix);
        m_program.setUniformValue("mvp", mvp);

        m_vertexNormalBuffer.bind();
        m_program.enableAttributeArray("vertexNormal");
        m_program.setAttributeBuffer("vertexNormal", GL_FLOAT, 0, 3);
        m_vertexPositionBuffer.bind();
        m_program.enableAttributeArray("vertexPosition");
        m_program.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);
        m_vertexColorBuffer.bind();
        m_program.enableAttributeArray("vertexColor");
        m_program.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);

        glDrawArrays(GL_TRIANGLES, 0, NUMB_OF_VERTICES);

        m_vertexNormalBuffer.release();
        m_vertexPositionBuffer.release();
        m_vertexColorBuffer.release();
        m_program.release();
    }

private:
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;
    QOpenGLBuffer m_vertexNormalBuffer;
    QOpenGLShaderProgram m_program;

    static const GLfloat m_vertices[3*NUMB_OF_VERTICES];
    static const GLfloat m_colors[3*NUMB_OF_VERTICES];
    static const GLfloat m_normals[3*NUMB_OF_VERTICES];

    Cube(const Cube&) = delete;
    Cube& operator=(const Cube&) = delete;
};
#endif // CUBE_H
