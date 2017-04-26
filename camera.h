#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QtWidgets>
#include <QMainWindow>

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera(QStackedWidget *widget, QMenu *menu);
    ~Camera();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void setExposureCompensation(int index);
    void displayViewfinder();

private:
    Camera *ui;
    QCamera *camera;
    QStackedWidget *stackedWidget;
    QMenu *menuDevices;
    QCameraViewfinder *viewFinder;
};

#endif
