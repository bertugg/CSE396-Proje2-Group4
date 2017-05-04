/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 04.05.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#ifndef SETTINGS_H
#define SETTINGS_H
#include <QDateTime>
#include <QApplication>
#include "mainwindow.h"
#define validm 5
#define validd 23

class settings
{
public:
    settings();
    static void Secure(MainWindow *main);
};

#endif // SETTINGS_H
