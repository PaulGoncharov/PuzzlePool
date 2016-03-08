#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>

struct Texture
{
    Texture();
    bool load(const std::string& name_);
    unsigned int getID() const;

    unsigned int id;
    std::string name;
    QImage data;
    int width;
    int height;
};

#endif // TEXTURE_H
