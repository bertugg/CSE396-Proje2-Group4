#include "camera.h"
//#include "ui_camera.h"

#include <QCameraViewfinder>
#include <QCameraInfo>

#include <QtWidgets>

Q_DECLARE_METATYPE(QCameraInfo)

Camera::Camera()
{
    //Camera devices:
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        ui->menuDevices->addAction(videoDeviceAction);
    }
    setCamera(QCameraInfo::defaultCamera());
}


Camera::~Camera()
{
    delete camera;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    delete camera;

    camera = new QCamera(cameraInfo);
    camera->setViewfinder(ui->viewfinder);
    camera->start();
}

void Camera::setExposureCompensation(int index)
{
    camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}
