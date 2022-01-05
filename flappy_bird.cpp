#include <QPainter>
#include <QThread>
#include <iostream>

#include "flappy_bird.h"
#include "ui_flappy_bird.h"

using namespace std;

Flappy_bird::Flappy_bird(QWidget *parent)
{
    setStyleSheet("background-color:black;");
    _bird = new bird();
    score = 0;

    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 25; j++){
            pipes[i][j] = NULL;
        }
    }

    pipeGenerator();
}

Flappy_bird::~Flappy_bird()
{

}

void Flappy_bird::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    if(event != Start){
        drawObjects(&painter);
        checkCollision();
    }else{
        startGame(&painter, "FLAPPY BIRD");
    }
}

void Flappy_bird::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    _bird->autoMove();

    for(int i = 0; i < 1000; i += 4){
        for(int j = 0; j < 25; j++){
            if(pipes[i][j] != NULL){
                pipes[i][j]->autoMove();
            }
        }
    }

    score += 0.01f;
    this->window()->setWindowTitle("Flappy bird. Result: " + QString::number((int)score));

    this->repaint();
}

void Flappy_bird::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_S: playGame();
        break;

    case Qt::Key_P: pauseGame();
        break;

    case Qt::Key_Escape: exit(0);
        break;

    case Qt::Key_Space: jumpBird();
        break;

    default: QWidget::keyPressEvent(e);

    }
}

void Flappy_bird::drawObjects(QPainter *painter)
{
    painter->drawImage(_bird->getRect().x(), _bird->getRect().y(), _bird->getImage());

    for(int i = 0; i < 1000; i += 4){
        for(int j = 0; j < 25; j++){
            if(pipes[i][j] != NULL){
                painter->drawImage(pipes[i][j]->getRect().x(), pipes[i][j]->getRect().y(), pipes[i][j]->getImage());
            }
        }
    }
}

void Flappy_bird::startGame(QPainter *painter, QString message)
{
    QString messageNameGame = message;
    QString messageForOpenMenu = "Press \"S\" to start";

    QFont font("Helvetica", 30, QFont::DemiBold);
    QFontMetrics fm(font);

    QFont fontSecond("Helvetica", 12, QFont::DemiBold);
    QFontMetrics fms(fontSecond);

    int textWidthMessageNameGame = fm.width(messageNameGame);
    int textWidthMessageForOpenMenu = fms.width(messageForOpenMenu);

    painter->setPen(QColor(Qt::white));
    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2)); // centre

    painter->drawText(-textWidthMessageNameGame/2, 0, messageNameGame);

    painter->setFont(fontSecond);
    painter->drawText(-textWidthMessageForOpenMenu/2, 30, messageForOpenMenu);
}

void Flappy_bird::playGame()
{
    if(event != Play){
        event = Play;
        setStyleSheet("background-color:white;");
        timerId = startTimer(DELAY);
        cout << "Play game" << endl;
    }
}

void Flappy_bird::pauseGame()
{
    if(event != Pause){
        event = Pause;
        killTimer(timerId);
        cout << "Pause game." << endl;
    }
}

void Flappy_bird::endGame()
{
    if(event != End){
        event = End;
        killTimer(timerId);

        for(int i = 0; i < 1000; i += 4){
            for(int j = 0; j < 25; j++){
                if(pipes[i][j] != NULL){
                    delete pipes[i][j];
                    pipes[i][j] = NULL;
                }
            }
        }

        cout << "Game over. You result: " + QString::number((int)score).toStdString() << endl;

        QThread::sleep(3);

        exit(0);
    }
}

void Flappy_bird::jumpBird()
{
    _bird->jump();
}

void Flappy_bird::pipeGenerator()
{
    srand(time(0));

    for(int i = 0; i < 1000; i += 4){
        switch (1 + rand() % 4) {
        case 1: {
            for(int j = 0; j < 6; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }

            for(int j = 15; j < 25; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }
        }; break;

        case 2: {
            for(int j = 0; j < 8; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }

            for(int j = 17; j < 25; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }
        }; break;

        case 3: {
            for(int j = 0; j < 10; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }

            for(int j = 19; j < 25; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }
        }; break;

        case 4: {
            for(int j = 0; j < 12; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }

            for(int j = 21; j < 25; j++){
                pipes[i][j] = new pipe(i * 20, j * 20);
            }
        }; break;
        }
    }
}

void Flappy_bird::checkCollision(){
    if(_bird->getRect().bottom() > BOTTOM_EDGE){
        endGame();
    }

    if(_bird->getRect().top() < TOP_EDGE){
        endGame();
    }

    for(int i = 0; i < 1000; i += 4){
        for(int j = 0; j < 25; j++){
            if(pipes[i][j] != NULL){
                if(pipes[i][j]->getRect().x() > 245
                        && pipes[i][j]->getRect().x() < 255){
                    if(_bird->getRect().intersects(pipes[i][j]->getRect())){
                        endGame();
                    }
                }
            }
        }
    }
}
