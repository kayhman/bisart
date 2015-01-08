#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <iostream>
 
void nativePainting()
{
    static const float vertexPositions[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
 
    static const float vertexColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
 
    QOpenGLBuffer vertexPositionBuffer(QOpenGLBuffer::VertexBuffer);
    vertexPositionBuffer.create();
    vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexPositionBuffer.bind();
    vertexPositionBuffer.allocate(vertexPositions, 9 * sizeof(float));
 
    QOpenGLBuffer vertexColorBuffer(QOpenGLBuffer::VertexBuffer);
    vertexColorBuffer.create();
    vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexColorBuffer.bind();
    vertexColorBuffer.allocate(vertexColors, 9 * sizeof(float));
 
    QOpenGLShaderProgram program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                    "#version 330\n"
                                    "in vec3 position;\n"
                                    "in vec3 color;\n"
                                    "out vec3 fragColor;\n"
                                    "void main() {\n"
                                    "    fragColor = color;\n"
                                    "    gl_Position = vec4(position, 1.0);\n"
                                    "}\n"
                                    );
    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    "#version 330\n"
                                    "in vec3 fragColor;\n"
                                    "out vec4 color;\n"
                                    "void main() {\n"
                                    "    color = vec4(fragColor, 1.0);\n"
                                    "}\n"
                                    );
    program.link();
    program.bind();
 
    vertexPositionBuffer.bind();
    program.enableAttributeArray("position");
    program.setAttributeBuffer("position", GL_FLOAT, 0, 3);
 
    vertexColorBuffer.bind();
    program.enableAttributeArray("color");
    program.setAttributeBuffer("color", GL_FLOAT, 0, 3);
 
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
 
QImage createImageWithFBO()
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
 
    std::cout << "eh " << __LINE__ << std::endl;

    QWindow window;
    window.setSurfaceType(QWindow::OpenGLSurface);
    window.setFormat(format);
    window.create();
 
    std::cout << "eh " << __LINE__ << std::endl;

    QOpenGLContext context;
    context.setFormat(format);
    if (!context.create())
        qFatal("Cannot create the requested OpenGL context!");
    context.makeCurrent(&window);
 
    const QRect drawRect(0, 0, 400, 400);
    const QSize drawRectSize = drawRect.size();
 
    std::cout << "eh " << __LINE__ <<  ""  << std::endl;

    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setSamples(16);
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
 
    QOpenGLFramebufferObject fbo(drawRectSize, fboFormat);
    fbo.bind();
 

    std::cout << "eh " << __LINE__ << std::endl;
    QOpenGLPaintDevice device(drawRectSize);
    QPainter painter;
    painter.begin(&device);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
 
    std::cout << "eh " << __LINE__ << std::endl;

    painter.fillRect(drawRect, Qt::blue);
    
    std::cout << "eh " << __LINE__ << std::endl;

    std::cout << "openpixmap" << std::endl;
 
    painter.drawTiledPixmap(drawRect, QPixmap("/tmp/hop.png"));
 
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::red);
    painter.drawEllipse(0, 100, 400, 200);
    painter.drawEllipse(100, 0, 200, 400);
 
    painter.beginNativePainting();
    nativePainting();
    painter.endNativePainting();
 
    painter.setPen(QPen(Qt::white, 0));
    QFont font;
    font.setPointSize(24);
    painter.setFont(font);
    painter.drawText(drawRect, "Hello FBO", QTextOption(Qt::AlignCenter));
 
    painter.end();
 
    fbo.release();
    return fbo.toImage();
}
 
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
 
    std::cout << "coucou" << std::endl;
    QImage targetImage = createImageWithFBO();
 
    QLabel label;
    label.setPixmap(QPixmap::fromImage(targetImage));
    label.show();
    return app.exec();
}
