#include <iostream>
#include "bird.h"

using namespace std;

bird::bird()
{
    image.load("_Images/bird.png");

    rect = image.rect();
    resetState();
}

bird::~bird()
{
    cout << "Bird is deleted!" << endl;
}

void bird::resetState()
{
    rect.translate(START_POS_X, START_POS_Y);
}

void bird::jump()
{
    rect.translate(0, -75);
}

void bird::autoMove()
{
    rect.translate(0, 1);
}

QRect bird::getRect()
{
    return rect;
}

QImage& bird::getImage()
{
    return image;
}

