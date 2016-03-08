#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QTimer>
#include <QOpenGLWidget>
#include <memory>

//Forward declaration
class Game;
class Texture;

class Canvas : public QOpenGLWidget
{
    Q_OBJECT


protected:
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event);

public:
    Canvas(QWidget* parent_ = 0);
    ~Canvas();
    void restart();
    void showTip() const;
    void startNewGame(std::string fileName_);
    void getCanvasSize(int& width, int& height) const;
    unsigned int getTextureID() const;
private:
    bool loadTexture(const std::string &name);
    void deleteTexture();
    void setAllGeometry();

    std::auto_ptr<Game> game;
    std::auto_ptr<Texture> texture;
    std::string imageName;
    static const std::string defaultImage;

    // For Animation
    QTimer timer;

signals:
    resizeParent(QSize size);
};

#endif // OPENGLWIDGET_H
