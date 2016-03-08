#include "Canvas/texture.h"

#include <QGLWidget>
#include <iostream>

Texture::Texture()
    :id(0)
{
}

bool Texture::load(const std::string &name_)
{
    name = name_;
    QImage image;

    if(!image.load(name_.c_str())) {
        std::cout << "Could not load image " << name_ << std::endl;
        return false;
    }
    else {
        data = QGLWidget::convertToGLFormat(image);
        width = data.width();
        height = data.height();
        return true;
    }
}

unsigned int Texture::getID() const
{
    return id;
}
