#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    lastKnownPosition = Coor(-1,-1);

    QPen blackPen(Qt::black); // Main Pen
    QBrush blueBrush(Qt::blue); // Main Brush
    blackPen.setWidth(6);

    // Create a Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    //drawLine(Coor(0,0), Coor(100,100), blackPen); // Draw a test line
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Sends main procedure start signal
 * Now it s only test debug functions
 */
void MainWindow::on_pushButton_clicked()
{
    /*
    DebugLog("Normal Text");
    DebugWarning("Warning Text");
    DebugError("Error Text");
    */

    Coor currentPosition = Coor(locationMarker->pos().x(), locationMarker->pos().y());
    UpdateMap(currentPosition);
}

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

void MainWindow::clearLines()
{
    for(int i = 0; i < drawedLines.size(); ++i)
    {
        scene->removeItem(drawedLines[i]);
        scene->update();
    }
}
