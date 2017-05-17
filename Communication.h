//
// Created by emre on 03.12.2016.
//

#ifndef PROJE_COMMUNUCATION_H
#define PROJE_COMMUNUCATION_H

#include "SerialPort.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Serial communication class
 */
class Communication {

private :
    int motorXStep;
    int motorYStep;
    bool communicationReady ;
    SerialPort *port;
    void makeHandShake();
    void checkConnection();
    vector<int> v;

public:

    /**
     * Constructor
     * str : Serial port name
     * baud : Serial Baud rate
     */
    Communication(string str,SerialPort::BaudRate baud);
    /**
     * Attention: received data should be like ("X%3.2lfY%3.2lfx%dy%d!",double ,double,int,int)
     * Reads the serial port and assigns the motor angles
     */
    bool readUntil();

    inline bool isCommunicationReady() const {
        return communicationReady;
    }

    inline int getXMotorStep() const {
        return motorXStep;
    }

    inline int getYMotorStep() const {
        return motorYStep;
    }

    bool moveRight(int step);

    bool moveLeft(int step);

    bool moveUp(int step);

    bool moveDown(int step);

    void pressButton();

    bool write(char *msg);

    bool write(char ch);

    void close(){port->close();}

    void sendStep(int step);

    void endConnection();

    void Write();

    void readFile(string Filename);

};


#endif //PROJE_COMMUNUCATİON_H
