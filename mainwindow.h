#pragma once

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QLabel>
#include <QTime>
#include <QFileDialog>
#include <QSpinBox>
#include <QGroupBox>
#include <QLCDNumber>

#include <memory>

#include "engine.h"

#include "rle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Draw();
    void CalculateFps();

private slots:
    void on_pushButton_clicked();
    void Update();

    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_fpsButton_clicked();

    void on_sizeButton_clicked();

    void mousePressEvent(QMouseEvent*);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<QGraphicsScene> scene;
    //game
    std::unique_ptr<Engine> engine;
    //std::unique_ptr<Game> game;
    QTimer gameLoopTimer;
    //cell
    int size = 100;
    int rectSize;

    QPen blackPen;
    QBrush blackBrush;

    //fps
    int fpsCap = 30;
    QElapsedTimer timer;
};
