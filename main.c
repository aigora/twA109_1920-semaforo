#include<stdio.h>
#include<stdlib.h>


#include"SerialPort.h"

#define MAX_DATA_LENGTH 255

#define ON 1
#define OFF 0



//FUNCIONES SERIAL PORT

void Crear_Conexion(SerialPort *PuertoSerie, char *portName);
void CerrarConexion(SerialPort * PuertoSerie);

//void autoConnect(SerialPort *arduino,char *, char *);

int isConnected(SerialPort *PuertoSerie);

int readSerialPort(SerialPort * PuertoSerie, char *buffer, unsigned int buf_size); //readSerialPort(arduino, incomingData, MAX_DATA_LENGTH);	//lee el primer dato de lo escrito en arduino	
int writeSerialPort(SerialPort *PuertoSerie, char *buffer, unsigned int buf_size);


//FUNCIONES DEL SEMAFORO

int menu(void);

void Rojo(SerialPort *PuertoSerie, int);
//void Verde(int);
//void Naranja(int);

//FUNCION PRINCIPAL

int main()
{
	int opcion=0;
	char rojo ='1';
	

	//CONEXION ARDUINO
	SerialPort *arduino;
	
	// Puerto serie en el que está Arduino
	char* portName = "COM3";
	
	// Buffer para datos procedentes de Arduino
	char incomingData[MAX_DATA_LENGTH];
	
	
	// Crear estructura de datos del puerto serie
	arduino = (SerialPort *)malloc(sizeof(SerialPort));
	
	// Apertura del puerto serie
	
	printf("espere mientras se conecta el arduino...");
	Crear_Conexion(arduino, portName);
	system("pause");
	
	
	while(isConnected(arduino)!=0 && opcion!=7)    //  while(isConnected(arduino) && opcion!=4)
	{
    do
    {
	    opcion = menu();
	    switch(opcion)
	    {
	    	case 1:
	    		{
	    			Rojo(arduino,ON);
	    			Sleep(10000);  //10 segundos, 10 000 milisegundos
	    			Rojo(arduino,OFF);
	    			break;	
				}
			case 2:
				{
					Verde(arduino,ON);
					break;
				}
			case 3:
				{
					Naranja(arduino,ON);
					break;
				}	
					
			case 4:
				{
					Rojo(arduino,OFF);
					break;	
				}
			case 5:
				{
					Verde(arduino,OFF);
					break;
				}
			case 6:
				{
					Naranja(arduino,OFF);
					break;
				}
			case 7:
				{
					break;
				}	
			
				
		}	   
    }while(opcion!=7);
	
	// Cerrar puerto serie
	if(opcion==7)
	{
		CerrarConexion(arduino);
		printf("\nEl pueto serie cerrado\n ");
	}
	else
	    printf("El pueto serie sigue abierto");
	//autoConnect(arduino, incomingData, pass); //Dentro de esta funcion escribiremos la aplicacion
}
	
	printf("\n\tFIN PROGRAMA");	
	return 0;
}
