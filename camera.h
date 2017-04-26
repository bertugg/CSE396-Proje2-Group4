#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>

#include <QMainWindow>

namespace Ui { class Camera; }

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera();
    ~Camera();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void setExposureCompensation(int index);
    void displayViewfinder();

private:
    Ui::Camera *ui;
    QCamera *camera;
};

#endif
