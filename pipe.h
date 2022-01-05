#ifndef PIPE_H
#define PIPE_H

#include <qrect.h>
#include <qimage.h>

class pipe
{
public:
    pipe(int, int);

    QRect getRect();
    QImage& getImage();
    void autoMove();

private:
    QRect rect;
    QImage image;
};

#endif // PIPE_H
