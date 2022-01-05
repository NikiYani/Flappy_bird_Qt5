#include "pipe.h"

pipe::pipe(int x, int y)
{
    image.load("_Images/pipe.png");
    rect = image.rect();

    rect.translate(x, y);
}


QRect pipe::getRect()
{
    return rect;
}

QImage& pipe::getImage()
{
    return image;
}

void pipe::autoMove()
{
    rect.translate(-1, 0);
}
