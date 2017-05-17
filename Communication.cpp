//
// Created by emre on 03.12.2016.
//

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <zconf.h>
#include "Communication.h"
#include <fstream>
#include <string>
#include <vector>



#define END_CHAR '}'

using namespace std;

Communication::Communication(string str, SerialPort::BaudRate baud) {

    port = new SerialPort(str,baud);

    communicationReady = false;
    checkConnection();
    makeHandShake();

    readFile("out.txt");

}

void Communication::makeHandShake() {
    char ch;
    cout << "Handshake starting" << endl;
    do {
        write('I');
        port->wait(100);
        port->read(&ch);
    }while(ch != 'O');
    cout << "Handshake succesfull" << endl;
    communicationReady = true;
}

bool Communication::write(char *msg) {
    return port->write(msg);
}

bool Communication::write(char ch) {
    return port->write(ch);
}

void Communication::checkConnection() {
    while( !( port->open()) ){
        sleep(1);
        cout << "Open failed" << endl;
        cout << "Trying to connect again " << endl;
    }
    while( !( port->prepare()) ){
        //sleep(1);
        cout << "Prepare failed" << endl;
        cout << "Trying to connect again " << endl;
    }
}

bool Communication::readUntil() {
    if(!communicationReady)
        return false;
    write('G');
    int xMotor,yMotor;
    string input;
    char temp;
    port->readUntil(input,END_CHAR);
    //{int int}
    sscanf(input.c_str(),"%c%c%d%c%d%c%c",&temp,&temp,&xMotor,&temp,&yMotor,&temp,&temp);
    if (xMotor == -1 && yMotor == -1)
        cout << "Button pressed" << endl;
    else{
        motorXStep = xMotor;
        motorYStep = yMotor;
    }

    return true;
}

void Communication::pressButton() {
    write('P');
}

bool Communication::moveRight(int step) {

    write('D');
    sendStep(step);
    return true;

}

bool Communication::moveLeft(int step) {

    write('A');
    sendStep(step);
    return true;

}

bool Communication::moveUp(int step){

    write('W');
    sendStep(step);
    return true;
}

bool Communication::moveDown(int step) {

    write('S');
    sendStep(step);
    return true;
}

void Communication::sendStep(int step) {

    char temp;
    char str[10];

    port->read(&temp);
    sprintf(str,"%d",step);
    write(str);

}

void Communication::endConnection(){
    cout << "F" << endl;
    write('F');
}

void Communication::readFile(string Filename)

{
    ifstream myfile (Filename.c_str());



    if (myfile.is_open())
    {
        int i;

        while(myfile >> i)
        {
            v.push_back(i);
        }

        moveRight(v[0]);
        moveUp(v[1]);
        port->write('B');
    }

   //v[0] X ekseni
   //v[1] Y ekseni


    //cout<<"vector: "<<v[0] <<" "<< v[1]<< endl;

    // Motorları baslangıca getir

    else
        port->write('B');

    myfile.close();
}
