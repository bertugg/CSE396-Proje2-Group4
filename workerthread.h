#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "Communication.h"
#include <QThread>
#include "Communication.h"
#include "coor.h"
#include <QImage>
/*
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
*/


#define JOE_SEEN_THRESHOLD 50
#define CANNY_THRESHOLD 50
#define MY_DIRECTIONS 8

//using namespace cv;

/**
 * @brief The WorkerThread class
 *
 * Main thread.
 *
 *  Main thread has infinite loop and in this loop
 * takes an image from video capture and create two
 * threads.
 *
 *  First thread process frame and searching for Joe.
 *  Second thread stabilizing given frames.
 *
 */
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject* parent=0);
    void run();
    bool isAlive();
    void terminate();
    //ProcesserThread *processer;
    //Stabilizer *stabilizer;

public slots:
    void slotGetProcessFrameResult(int result);

signals:
    void threadDebugLog(QString text);
    void threadDebugWarning(QString text);
    void threadDebugError(QString text);
    void threadShowJoe(int x, int y, float angle);
    void threadclearLines(); // Clear all drawed lines
    void threadUpdateMap(Coor currentPosition);
//    void signalProcessFrame(Mat frame);
    void showImage(QImage image);

private:
//    VideoCapture videoCapture;
//    Mat frame;
//    Mat processedFrame;
//    Mat stabilizedFrame;
//    void processFrame(Mat frame);
//    double calculate(Point2f point1, Point2f point2, double &sin, double &cos);
    Communication *com = NULL;

    bool found;
    bool alive;
    int result = -1;
    double angle;
/*    Mat image,
        convertedImage,
        gaussianImage,
        cannyImage,
        dilatedImage,
        cimage;
*/
};

#endif // WORKERTHREAD_H
