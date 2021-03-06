/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/


#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    HANDLE handler;
    int connected;
    COMSTAT status;
    DWORD errors;
    char * portName;
} SerialPort;


void Crear_Conexion(SerialPort * PuertoSerie,char *portName);
void CerrarConexion(SerialPort * PuertoSerie);

int readSerialPort(SerialPort *PuertoSerie,char *buffer, unsigned int buf_size);
int writeSerialPort(SerialPort *PuertoSerie,char *buffer, unsigned int buf_size);
int isConnected(SerialPort *);


#endif // SERIALPORT_H
