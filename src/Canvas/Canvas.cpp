#include "Game/Game.h"
#include "Canvas/Canvas.h"
#include "Canvas/texture.h"

#include <QtGui>
#include <QString>
#include <iostream>

Canvas::Canvas(QWidget */*parent_*/)
    :game(new Game(this))
    ,texture()
    ,timer(this)
{
        connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

}

Canvas::~Canvas()
{
    deleteTexture();
}

const std::string Canvas::defaultImage = "Image1.jpg";

bool Canvas::loadTexture(const std::string & name)
{
    std::cout << name << std::endl;
    texture.reset(new Texture());
    if (texture->load(std::string(":/images/images/") + name))
    {
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->width, texture->height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return true;
    }
    else {
        return false;
    }
}

void Canvas::startNewGame(std::string fileName_)
{
    imageName = fileName_;
    deleteTexture();
    loadTexture(imageName);
    setAllGeometry();
    game.reset(new Game(this));
    game->Initialize();
}

void Canvas::getCanvasSize(int &width, int &height) const
{
    width = texture->width;
    height = texture->height;
}

unsigned int Canvas::getTextureID() const
{
    return texture->getID();
}

void Canvas::deleteTexture()
{
    if(texture.get()) {
        glDeleteTextures(1, &texture->id);
    }
    texture.release();
}

void Canvas::setAllGeometry()
{
    this->setMaximumSize(texture->width, texture->height);
    this->setMinimumSize(texture->width, texture->height);
    emit resizeParent(QSize(texture->width*1.1, texture->height*1.1));
}

void Canvas::restart()
{
    game->restart();
    update();
}

void Canvas::showTip() const
{
    if(!game->IsCompleted()) {
        game->showTip();
    }
}

void Canvas::initializeGL()
{
    loadTexture(defaultImage);
    glEnable(GL_TEXTURE_2D);
    game->Initialize();
    timer.start(25);
}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    game->update();
    game->Render();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(!game->IsCompleted()) {
         game->Click(event->pos().x(), event->pos().y());
    }
    update();
}

void DrawRect(const Rect& screenCoords, int textureId, const Rect& textureCoord)
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
         glTexCoord2f(textureCoord.left, textureCoord.top);
         glVertex2f(screenCoords.left, screenCoords.top);

         glTexCoord2f(textureCoord.right, textureCoord.top);
         glVertex2f(screenCoords.right, screenCoords.top);

         glTexCoord2f(textureCoord.right, textureCoord.bottom);
         glVertex2f(screenCoords.right, screenCoords.bottom);

         glTexCoord2f(textureCoord.left, textureCoord.bottom);
         glVertex2f(screenCoords.left, screenCoords.bottom);
    glEnd();
}
