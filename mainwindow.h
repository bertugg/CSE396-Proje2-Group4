/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include <QElapsedTimer>
#include <QTimer>
#include "coor.h"
#include "camera.h"
#define JOEASSETPATH "C:/Users/bertugg/Documents/QTWorkspace/CSE396-Proje2-Group4.git/joe.jpg"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DebugLog(QString text);
    void DebugWarning(QString text);
    void DebugError(QString text);
    void ShowJoe(int x, int y, float angle);
    void clearLines(); // Clear all drawed lines
    QGraphicsLineItem *drawLine(Coor &c1, Coor &c2, QPen pen); // Draw A line between 2 coordinates
    void UpdateMap(Coor currentPosition);
    Ui::MainWindow *ui;

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_testMapButton_clicked();

    void on_testDebugButton_clicked();

    void updateUI();

private:
    QGraphicsScene *scene;
    //QGraphicsPolygonItem *locationMarker;
    QGraphicsRectItem *locationMarker;
    QList<QGraphicsItem *> drawedLines;
    QGraphicsPixmapItem *joePixmap;
    Coor lastKnownPosition;
    Camera *camera;
    QElapsedTimer elapsedTime;
    QTimer *timer;
    bool updateTimer;
};

#endif // MAINWINDOW_H
