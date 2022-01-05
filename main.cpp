#include "flappy_bird.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Flappy_bird w;
    w.resize(500, 500);
    w.setWindowTitle("Flappy bird");
    w.show();
    return a.exec();
}
