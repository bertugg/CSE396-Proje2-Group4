/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#include "settings.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "Communication.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // Setup user interface.
    ui->setupUi(this);

    // Initialize Scenes.
    scene               = new QGraphicsScene(this);
    frameWidgetScene    = new QGraphicsScene(this);

    settings::Secure(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(frameWidgetScene);
    //ui->graphicsView_2->setFixedSize(size());

    lastKnownPosition = Coor(-1,-1);

    // Show Grid
    drawBackground();

    QPen blackPen(Qt::black); // Main Pen
    QBrush greenBrush(Qt::green); // Main Brush
    blackPen.setWidth(1);

    // Add Joe Asset
    joePixmap = scene -> addPixmap(QPixmap(JOEASSETPATH));
    if(QPixmap(JOEASSETPATH).isNull())
        DebugError("Joe image not found!");
    joePixmap->hide(); // Hide Joe
    joePixmap->setScale(0.2f); // May removed with the new asset

    // Set Timer that updates elapsedTime label every 1 sec.
    updateTimer = false; // Do not update timer panel by default
    timer = new QTimer(this);
    //timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    timer->start(16); // Set interval from here for more precise updates

    // Create a Location Marker
    //locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker = scene -> addRect(QRect(-20,-20,40,40), blackPen, greenBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    //drawLine(Coor(0,0), Coor(100,100), blackPen); // Draw a test line

    mainThread = new WorkerThread(this);

    connect(mainThread,SIGNAL(threadDebugLog(QString)),     this,   SLOT(DebugLog(QString)));
    connect(mainThread,SIGNAL(threadDebugError(QString)),   this,   SLOT(DebugError(QString)));
    connect(mainThread,SIGNAL(threadDebugWarning(QString)), this,   SLOT(DebugWarning(QString)));
    connect(mainThread,SIGNAL(threadclearLines()),          this,   SLOT(clearLines()));
    connect(mainThread,SIGNAL(threadShowJoe(int,int,float)),this,   SLOT(ShowJoe(int,int,float)));
    connect(mainThread,SIGNAL(threadUpdateMap(Coor)),       this,   SLOT(UpdateMap(Coor)));
    connect(mainThread,SIGNAL(showImage(QImage)),this,SLOT(showFrame(QImage)));
    mainThread->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Sends main procedure start signal
 * Now it s only test debug functions
 */
void MainWindow::on_startButton_clicked()
{
    DebugLog("Program Started Stub");
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    elapsedTime.restart();
    ui->timeLabel->setText("00:00");
    updateTimer = true;

    joePixmap->hide();
}

void MainWindow::on_stopButton_clicked()
{
    DebugLog("Program Stopped Stub");
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    updateTimer = false;
}

void MainWindow::UpdateMap(Coor currentPosition)
{
    QPen redPen(Qt::red);
    redPen.setWidth(5);

    if(lastKnownPosition != Coor(-1,-1))
    {
        QGraphicsLineItem *line;
        line = drawLine(lastKnownPosition, currentPosition, redPen);
        drawedLines.push_front(line);
    }
    lastKnownPosition = currentPosition;
}

// Tests Map Function
void MainWindow::on_testMapButton_clicked()
{
    Coor currentPosition = Coor(locationMarker->pos().x(), locationMarker->pos().y());
    UpdateMap(currentPosition);
    ShowJoe(20,20,60);
}

// Tests Debug Panel
void MainWindow::on_testDebugButton_clicked()
{
    DebugLog("Normal Text");
    DebugWarning("Warning Text");
    DebugError("Error Text");
}

/*
 *  Helper Functions
 */

// Shows given text in debug panel
void MainWindow::DebugLog(QString text)
{
    ui->textEdit->append(text);
}

// Shows given warning text in debug panel as blue
void MainWindow::DebugWarning(QString text)
{
    QString my_formatted_string = QString("<span style=\" font-size:7.8pt; color:#0000ff;\">%1</span>").arg(text);
    DebugLog(my_formatted_string);
}

// Shows given error text in debug panel as red
void MainWindow::DebugError(QString text)
{
    QString my_formatted_string = QString("<span style=\" font-size:7.8pt; color:#ff0000;\">%1</span>").arg(text);
    DebugLog(my_formatted_string);
}

QGraphicsLineItem* MainWindow::drawLine(Coor &c1, Coor &c2, QPen pen)
{
    return scene -> addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),pen);
}

void MainWindow::clearLines()
{
    for(int i = 0; i < drawedLines.size(); ++i)
    {
        scene->removeItem(drawedLines[i]);
        scene->update();
    }
}

void MainWindow::updateUI()
{
    if(updateTimer)
    {
        QString out = QString("%1:%2").arg( elapsedTime.elapsed() / 60000        , 2, 10, QChar('0'))
                                      .arg((elapsedTime.elapsed() % 60000) / 1000, 2, 10, QChar('0'));
        ui->timeLabel->setText(out);
    }
}


void MainWindow::ShowJoe(int x, int y, float angle)
{
    joePixmap->setPos(x,y);
    joePixmap->setRotation(angle);
    joePixmap->show();
}

inline qreal round(qreal val, int step) {
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}

void MainWindow::drawBackground()
{

    QPen _bgPen;  // creates a pen for Background Grids

    _bgPen.setStyle(Qt::DashDotLine);
    _bgPen.setWidth(1);
    _bgPen.setBrush(Qt::gray);
    _bgPen.setCapStyle(Qt::RoundCap);
    _bgPen.setJoinStyle(Qt::RoundJoin);

    // Add the vertical lines
    for (int x=0; x<=1000; x+=GRID_SIZE)
        scene->addLine(x,0,x,1000, _bgPen);

    // Add the horizontal lines
    for (int y=0; y<=1000; y+=GRID_SIZE)
        scene->addLine(0,y,1000,y, _bgPen);

    // Fit the view in the scene's bounding rect
    ui->graphicsView->fitInView(0,0,10,10,Qt::KeepAspectRatio);
}

void MainWindow::showFrame(QImage frame){
    frameWidgetScene->addPixmap(QPixmap::fromImage(frame.scaled(ui->graphicsView_2->size())));
}
