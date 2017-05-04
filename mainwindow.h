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
#include "coor.h"
#include "camera.h"

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

    void clearLines(); // Clear all drawed lines
    QGraphicsLineItem *drawLine(Coor &c1, Coor &c2, QPen pen); // Draw A line between 2 coordinates
    void UpdateMap(Coor currentPosition);
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    QGraphicsScene *scene;
    //QGraphicsPolygonItem *locationMarker;
    QGraphicsEllipseItem *locationMarker;
    QList<QGraphicsItem *> drawedLines;
    Coor lastKnownPosition;
    Camera *camera;
};

#endif // MAINWINDOW_H
