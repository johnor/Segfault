#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLContext>
#include <QtGui/QWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QTimer>
#include <QScreen>
#include <QDebug>//TODO: REMOVE
#include <QtMath>

#include "cube.h"
#include "camera.h"

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWindow *parent = 0) :
        QWindow(parent),
        m_context(0),
        m_update_pending(false),
        m_frames(0),
        m_key(0)
    {
        setSurfaceType(OpenGLSurface);
        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        format.setSamples(4);
        setFormat(format);

        resize(640, 480);
        show();
        create();

        m_context = new QOpenGLContext(this);
        m_context->setFormat(format);
        m_context->create();
        m_context->makeCurrent(this);
        /*
        if ( !m_context->versionFunctions()) {
            qWarning( "Could not obtain OpenGL versions object" );
            exit( 1 );
        }
        m_context->versionFunctions()->initializeOpenGLFunctions();
        */
        initializeOpenGLFunctions();

        m_vao.create();
        m_vao.bind();

        m_cube.initialize();

        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.perspective(90, 4.0f/3.0f, 0.1f, 100.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        m_vao.release();
        m_context->doneCurrent();

        connect(&m_fpsTimer, SIGNAL(timeout()), SLOT(printfFps()));
        m_fpsTimer.start(1000);
    }

    virtual ~OpenGLWindow()
    {
        m_vao.release();
        m_vao.destroy();
        m_context->doneCurrent();
    }

protected:
    void resizeEvent(QResizeEvent * e) override
    {
        Q_UNUSED(e);

        m_context->makeCurrent(this);
        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);
        m_context->doneCurrent();
    }

private slots:
    void printfFps()
    {
        qDebug() << float(m_frames);
        m_frames = 0;
    }

    void keyPressEvent(QKeyEvent* e) override
    {
        if(!e->isAutoRepeat())
        {
            e->accept();
            switch (e->key())
            {
                case Qt::Key_Escape:
                    QCoreApplication::instance()->quit();
                    break;
                case Qt::Key_F:
                    showFullScreen();
                    break;
                case Qt::Key_S:
                    show();
                    break;
                default:
                    break;
            }
            m_key = e->key();
            qDebug() << e->text() << " pressed";
        }
        else
            e->ignore();
    }

    void keyReleaseEvent(QKeyEvent *e) override
    {
        if(!e->isAutoRepeat())
        {
            e->accept();
            if(m_key == e->key())
                m_key = 0;
            qDebug() << e->text() << " released";
        }
        else
            e->ignore();
    }

public slots:
    inline void renderNow(const QMatrix4x4 modelMatrix)
    {
        if (!isExposed())
            return;

        m_context->makeCurrent(this);
        m_vao.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glEnable(GL_DEPTH_TEST);

        m_cube.render(m_camera.getViewMatrix(), m_projectionMatrix, modelMatrix, m_camera.getPosition());

        m_vao.release();
        m_context->swapBuffers(this);
        m_context->doneCurrent();

        ++m_frames;
    }

private:
    QOpenGLContext *m_context;
    QOpenGLVertexArrayObject m_vao;
    QMatrix4x4 m_projectionMatrix;
    bool m_update_pending;
    unsigned int m_frames;
    QTimer m_fpsTimer;
    int m_key;
    Cube m_cube;
    Camera m_camera;
};

#endif // WINDOW_H
