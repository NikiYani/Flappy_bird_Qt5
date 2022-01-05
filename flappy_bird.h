#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <QWidget>
#include <QKeyEvent>

#include "bird.h"
#include "pipe.h"

enum events{
    Start,
    Play,
    Pause,
    End
};

class Flappy_bird : public QWidget
{
    Q_OBJECT

public:
    Flappy_bird(QWidget *parent = nullptr);
    ~Flappy_bird();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    void startGame(QPainter *, QString);
    void playGame();
    void pauseGame();
    void endGame();
    void jumpBird();
    void pipeGenerator();
    void checkCollision();

private:
    float score;
    events event = Start;
    bird *_bird;
    pipe *pipes[1000][25];
    int timerId;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 500;
    static const int TOP_EDGE = 0;

};
#endif // FLAPPY_BIRD_H
