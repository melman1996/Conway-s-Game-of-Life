#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //generate UI
    ui->setupUi(this);
    scene = std::make_unique<QGraphicsScene>(this);
    ui->graphicsView->setScene(scene.get());

    //create game
    //game = std::make_unique<Game>(size);
    engine = std::make_unique<Engine>(size, size);
    rectSize = 500 / size;
    if(rectSize < 1) rectSize = 1;

    ui->graphicsView->setFixedSize(size * rectSize, size * rectSize);
    ui->graphicsView->setSceneRect(0, 0, size * rectSize, size * rectSize);

    blackBrush = QBrush(Qt::black);
    blackPen = QPen(Qt::black);
    Draw();

    //create timer
    connect(&gameLoopTimer, SIGNAL(timeout()), this, SLOT(Update()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::Draw()
{
    scene->clear();
    std::vector<std::vector<bool>> board = engine->GetBoard();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(engine->Get(i, j)){
                scene->addRect(j * rectSize, i * rectSize, rectSize, rectSize, blackPen, blackBrush);
            }
        }
    }
}

void MainWindow::CalculateFps()
{
    int now = timer.elapsed();
    timer.restart();
    ui->fpsLcd->display(QString::number(1000 / now));
}

void MainWindow::on_pushButton_clicked()
{
    if(!gameLoopTimer.isActive()){
        timer.start();
        gameLoopTimer.start(1000/fpsCap);
    }
    else {
        gameLoopTimer.stop();
    }
}

void MainWindow::Update()
{
    CalculateFps();
    engine->Evolve();
    Draw();
}

void MainWindow::on_backButton_clicked()
{
    engine->Back();
    Draw();
}

void MainWindow::on_forwardButton_clicked()
{
    engine->Evolve();
    Draw();
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "Create RLE file",
                QDir::currentPath(),
                "All files (*.*)");
    RLE::SaveFile(fileName.toUtf8().constData(), engine->Export());
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                "Open RLE file",
                QDir::currentPath(),
                "All files (*.*)");

    engine->Import(RLE::LoadFile(fileName.toUtf8().constData()));
    Draw();
}

void MainWindow::on_fpsButton_clicked()
{
    fpsCap = ui->fpsSpinBox->value();
    if(gameLoopTimer.isActive()){
        gameLoopTimer.setInterval(1000/fpsCap);
    }
}

void MainWindow::on_sizeButton_clicked()
{
    size = ui->sizeSpinBox->value();
    if(gameLoopTimer.isActive()){
        gameLoopTimer.stop();
    }
    engine->Resize(size, size);
    rectSize = ui->graphicsView->width() / size;

    if(rectSize < 1) rectSize = 1;

    ui->graphicsView->setFixedSize(size * rectSize, size * rectSize);
    ui->graphicsView->setSceneRect(0, 0, size * rectSize, size * rectSize);

    Draw();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint remapped = ui->graphicsView->mapFromParent(event->pos());
    if(ui->graphicsView->rect().contains(remapped)){
        engine->ChangeValue(remapped.y() / rectSize, remapped.x() / rectSize);
    }
    Draw();
}
