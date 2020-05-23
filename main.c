#include<stdio.h>
#include<stdlib.h>

#include"SerialPort.h"

#define MAX_DATA_LENGTH 255

#define ON 1
#define OFF 0

//FUNCIONES SERIAL PORT

void Crear_Conexion(SerialPort *PuertoSerie, char *portName);
void CerrarConexion(SerialPort * PuertoSerie);
int isConnected(SerialPort *PuertoSerie);

int readSerialPort(SerialPort * PuertoSerie, char *buffer, unsigned int buf_size); 	
int writeSerialPort(SerialPort *PuertoSerie, char *buffer, unsigned int buf_size);

//FUNCIONES DEL SEMAFORO
void funcion_titulo(void);
int menu(void);
int menu2(void);
void comprobar_luz(SerialPort *PuertoSerie, int);
void iniciarsemaforo(SerialPort *arduino);

void Rojo(SerialPort *PuertoSerie, int);
void Verde(SerialPort *PuertoSerie, int);
void Naranja(SerialPort *PuertoSerie, int);


//FUNCION PRINCIPAL

int main()
{
	int opcion,opcion2;

	//CONEXION ARDUINO
	SerialPort *arduino;
	
	// Puerto serie en el que está Arduino
	char* portName = "COM3";
	
	// Buffer para datos procedentes de Arduino
	char incomingData[MAX_DATA_LENGTH];
	
	// Crear estructura de datos del puerto serie
	arduino = (SerialPort *)malloc(sizeof(SerialPort));
	
	// Apertura del puerto serie
	Crear_Conexion(arduino, portName);
	
	funcion_titulo();
	system("cls");
	while(isConnected(arduino)!=0 && opcion!=7)    //  while(isConnected(arduino) && opcion!=4)
	{	
    do
    {
	    opcion = menu();
	    switch(opcion)
	    {
	    	case 1:
	    		{
	    			do{
	    			opcion2=menu2();
	    			comprobar_luz(arduino, opcion2);
	    			}while(opcion2!=7);
	    			break;
				}
			case 2:
				{
					iniciarsemaforo(arduino);
					break;
				}
			case 3:
				break;
			//no ponemos default porque ya esta comprobado el numro que entra
		}    
    }while(opcion!=3);
	system("cls");
	// Cerrar puerto serie
	if(opcion==3)
	{
		CerrarConexion(arduino);
	}
	else
	    printf("El pueto serie sigue abierto");
	}
	printf("\n\tFIN PROGRAMA");	
	return 0;
}

//FUNCIONES SEMAFORO
//TITULO DEL SEMAFORO
void funcion_titulo(void) 
{
	int a,w;
	
	for (w = 5; w >= 0; w--)
	{
	FILE *titulo;
	titulo = fopen("tit.txt", "r");
	if(titulo==NULL)
		printf("no se ha podido abrir el fichero");
	printf("\n\n\n");
	while (!feof(titulo))
	{ 
		fscanf(titulo, "%d", &a);
		if (a == 13)
			printf("\n");
		else
		{
			if (a == 124)
				printf("%c", 219);
			else
				printf("%c", a);
		}
	}
	fclose(titulo);
		printf("El programa se ejecutara en %d",w);
		Sleep(1000);
		system("cls");
	}
}
//MENU 1
int menu(void) 
{
	int n;	
	do 
	{
		system("cls");
		printf("-----MENU PRINCIPAL-----\n\n1-Comprobar las luces \n2-iniciar semaforo\n3-Cerrar aplicacion\n------------------------\nseleccione una opcion: ");
		scanf_s("%d", &n);
		if(n<1||n>3)
	    {
	    	printf("\nseleccione una opcion posible\n");   
	    	system("pause");
		}
	} while (n < 1 || n>3);
	return n;
}
//MENU 2
int menu2(void)
{
	int op;
	do{
		system("cls");
	    printf("-----comprobar luces----\n1-encender rojo\n2-encender verde\n3-encender naranja\n4-apagar rojo\n5-apagar verde\n6-apagar naranja\n7-cerrar programa\n------------------------\n\nseleccione una opcion: ");
	    scanf("%d",&op);
	    if(op<1||op>7)
	    {
	    	printf("\nseleccione una opcion posible\n");   
	    	system("pause");
		}
	}while(op<1||op>7);
	return op;
}
//COMPROBAR LUCES
void comprobar_luz(SerialPort *PuertoSerie, int n)
{
	switch(n)
	    {
	    	case 1:
	    			Rojo(PuertoSerie,ON);
	    			break;	
			case 2:
					Verde(PuertoSerie,ON);
					break;
			case 3:
					Naranja(PuertoSerie,ON);
					break;					
			case 4:
					Rojo(PuertoSerie,OFF);
					break;	
			case 5:
					Verde(PuertoSerie,OFF);
					break;
			case 6:
					Naranja(PuertoSerie,OFF);
					break;
			case 7:
					Rojo(PuertoSerie,OFF);
					Verde(PuertoSerie,OFF);
					Naranja(PuertoSerie,OFF);
					printf("\ntodas las luces apagadas\nvuelve al menu principal\n");
					system("pause");
					break;
		}
}
//BUCLE DEL SEMAFORO
void iniciarsemaforo(SerialPort *arduino)
{
	int flag;
	char llamada_pulsador;
	Verde(arduino,ON);
	do
	{
		flag=0;
		do{
		system("cls");
		printf("el semaforo esta en verde\n");
	 	printf("Desea cruzar la calle (una 's' o 'S' si quieres cruzar y una 'n' o 'N' si no quiere): ");
	 	fflush(stdin);
	 	scanf("%c", &llamada_pulsador);
	 	if(llamada_pulsador!='s' && llamada_pulsador!='S' && llamada_pulsador!='n' && llamada_pulsador!='N')
	 	{
	 		printf("\nutiliza una letra valida\n");
	 		system("pause");
		}
	 }while(llamada_pulsador!='s' && llamada_pulsador!='S' && llamada_pulsador!='n' && llamada_pulsador!='N');
	  //fflush(stdin);
 	  if(llamada_pulsador=='s' || llamada_pulsador=='S')
	  {
	  	printf("verde ON   ");
	  	sleep(6);
	    Verde(arduino,OFF);
	    printf("verde OFF   ");
	    Naranja(arduino,ON);
	    printf("naranja ON   ");
	    Sleep(500);
	    Naranja(arduino,OFF);
	    printf("naranja OFF   ");
	    Sleep(500);
	    Naranja(arduino,ON);
	    printf("naranja ON   ");
	    Sleep(500);
	    Naranja(arduino,OFF);
	    printf("naranja OFF   ");
	    Sleep(500); 
	    Naranja(arduino,ON);
	    printf("naranja ON   ");
	    Sleep(500);
	    Naranja(arduino,OFF);
	    printf("naranja OFF   ");
	    Rojo(arduino,ON);
	    printf("rojo ON   ");
	    sleep(6);
	    Rojo(arduino,OFF);
	    printf("rojo OFF   ");
	    Naranja(arduino,ON);
	    printf("naranja ON   ");
	    sleep(1);
	     Naranja(arduino,OFF);
	    printf("naranja OFF   ");
	    Verde(arduino,ON);
	    printf("verde ON   ");
	    sleep(2);
	  }
	 else
	 {
	 	do
	 	{
	 	printf("\nque desea hacer entonces (esperar 'e' o 'E', salir al menu principal 'm' o 'M'): ");
	 	fflush(stdin);
	 	scanf("%c",&llamada_pulsador);
	 	if(llamada_pulsador!='e' && llamada_pulsador!='E' && llamada_pulsador!='m' && llamada_pulsador!='M')
	 	{
	 		printf("\nutiliza una letra valida\n\n");
		}
	 	}while(llamada_pulsador!='e' && llamada_pulsador!='E' && llamada_pulsador!='m' && llamada_pulsador!='M');
	 	
	 	if(llamada_pulsador=='e' || llamada_pulsador=='E')
	 	{
	 		printf("\nEsperando... el semaforo sigue en verde y los coches estan pasando");
	 		sleep(5);
		}
		else
		{
			flag=1;
			printf("\n\nVa a volver al menu principal\n");
			system("pause");
		}
	
	 }

    }while(flag==0);	
}

//LED ROJO
void Rojo(SerialPort *PuertoSerie, int r)
{
	char rojo='1';
	if(r==OFF)
		rojo='4';
	writeSerialPort(PuertoSerie,&rojo,sizeof(char));
}
//LED VERDE
void Verde(SerialPort *PuertoSerie, int r)
{
	char verde='2';
	if(r==OFF)
		verde='5';
	writeSerialPort(PuertoSerie, &verde, sizeof(char));
	
}
//LED NARANJA
void Naranja(SerialPort *PuertoSerie, int r)
{
	char naranja='3';
	if(r==OFF)
		naranja='6';
	writeSerialPort(PuertoSerie, &naranja, sizeof(char));
}

//COMUNICACIÓN SERIAL CON EL ARDUINO

void Crear_Conexion(SerialPort *PuertoSerie, char *portName)
{

	PuertoSerie->connected = 0;
	PuertoSerie->portName = portName;
	PuertoSerie->handler = CreateFileA((portName),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
		printf("espere mientras se conecta el arduino...");
	if (PuertoSerie->handler == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			system("cls");
			printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
		}
		else
		{
			system("cls");
			printf("ERROR!!!");
		}
	}
	else
	{
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(PuertoSerie->handler, &dcbSerialParameters))
		{
			system("cls");
			printf("failed to get current serial parameters");
		}
		else
		{
			dcbSerialParameters.BaudRate = CBR_9600;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(PuertoSerie->handler, &dcbSerialParameters))
			{
				system("cls");
				printf("ALERT: could not set Serial port parameters\n");
			}
			else
			{
				PuertoSerie->connected = 1;
				PurgeComm(PuertoSerie->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
				system("cls");
				printf("ARDUINO CONECTADO\n\n");
			}
		}
	}
	return;
}

void CerrarConexion(SerialPort * PuertoSerie)
{
	if (PuertoSerie->connected)
	{
		PuertoSerie->connected = 0;
		CloseHandle(PuertoSerie->handler);
		printf("\n\tpuerto %s cerrado",PuertoSerie->portName);
	}
}

int isConnected(SerialPort *PuertoSerie)
{
	if (!ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status))
		PuertoSerie->connected = 0;
	return PuertoSerie->connected;
}

int readSerialPort(SerialPort * PuertoSerie, char *buffer, unsigned int buf_size)
{
	DWORD bytesRead;
	unsigned int toRead = 0;

	ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);

	if (PuertoSerie->status.cbInQue > 0)
	{
		if (PuertoSerie->status.cbInQue > buf_size)
		{
			toRead = buf_size;
		}
		else 
		    toRead = PuertoSerie->status.cbInQue;
	}

	memset(buffer, 0, buf_size);

	if (ReadFile(PuertoSerie->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

	return 0;
}

int writeSerialPort(SerialPort *PuertoSerie, char *buffer, unsigned int buf_size)
{
	DWORD bytesSend;

	if (!WriteFile(PuertoSerie->handler, (void*)buffer, buf_size, &bytesSend, 0))
	{
		ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);
		return 0;
	}
	else return 1;
}
