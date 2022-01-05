#ifndef BIRD_H
#define BIRD_H

#pragma once

#include <qrect.h>
#include <qimage.h>


class bird
{
public:
    bird();
    ~bird();

    void resetState();
    void jump();
    void autoMove();
    QRect getRect();
    QImage& getImage();

private:
    QRect rect;
    QImage image;
    static const int START_POS_X = 250;
    static const int START_POS_Y = 250;
};

#endif // BIRD_H
