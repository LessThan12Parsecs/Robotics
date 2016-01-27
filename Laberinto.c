
// Programa para salir de laberinto con robot movil
// Emanuel Ramirez Catapano

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiSPI.h>

#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0
//para el uso de los pines que tienen señal PWM por hardware en la raspberry pi 2 se usan los GPIO 19 y 18
#define SERVO_IZQ           19
#define SERVO_DER           18
#define SENSOR_LEFT          0
#define SENSOR_FRONT          1
static int myFd ;


//Lectura de sensores analogicos
char *usage = "Usage: mcp3008 all|analogChannel[1-8] [-l] [-ce1] [-d]";
void loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        //fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

void spiSetup (int spiChannel)
{
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        //fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

//Lectura de sensores analogicos

int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}


// SERVO_IZQUIERDO > 76 hacia adelante
// SERVO_DERECHO < 76 hacia adelante

void girarDerecha(){
    pwmWrite(SERVO_DER,0);
    pwmWrite(SERVO_IZQ,0);
    delay(300);
    pwmWrite(SERVO_DER,77);
    pwmWrite(SERVO_IZQ,77);
    delay(900); //+-90 grados
}

void girarIzquierda(){
    delay(650);
    pwmWrite(SERVO_DER,69);
    pwmWrite(SERVO_IZQ,69);
    delay(1250); // +-90 grados
    pwmWrite(SERVO_IZQ,77);
    pwmWrite(SERVO_DER,69);
    delay(1800);
}


//estas funciones fueron de prueba para tratar de rectificar los movimientos cambiando las velocidades de los servos
/*
void corregirDer(){
    pwmWrite(SERVO_DER,70);
    pwmWrite(SERVO_IZQ,77);
    delay(100);
    pwmWrite(SERVO_IZQ,77);
    pwmWrite(SERVO_DER,69);
    delay(200);
}

void corregirIzq(){
    pwmWrite(SERVO_IZQ,75);
    pwmWrite(SERVO_DER,70);
    delay(100);
    pwmWrite(SERVO_IZQ,77);
    pwmWrite(SERVO_DER,69);
    delay(200);
}
*/


//Funcion principal de movimiento.
void run(){
    
    
    delay(50);
    //Movimiento que sigue la pared.
    pwmWrite(SERVO_IZQ,77); // >76 hacia adelante.
    pwmWrite(SERVO_DER,69); // <76 hacia atras.
    
    // se mantiene mientas no se aleje o acerque demasiado, y no tenga un bloqueo en el sensor frontal.
    while (myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) >  220 && myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) < 350
		&& myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_FRONT)<210){ // hay que probar los valores de radio de giro y que este cerca
        //printf("Siguiendo la pared\n");
        
	delay(50);
    } // sale del bucle y busca la razon del cambio de estado.
    
    
    //si detecta un objeto al frente gira a la derecha
    if(myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_FRONT) >= 210){
        //printf("GIRO DERECHA\n");
        girarDerecha();
        //Llamada recursiva de la funcion.
        run();
    }
    //Si detecta que la pared izquierda esta muy lejos gira a la izquierda
    else if (myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) <= 150){
        //printf("GIRO IZQUIERDA\n");
        girarIzquierda();
        //Llamada recursiva de la funcion.
        run();
    }
    
    
    
    /*else if (myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) > 200  && myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) < 280){
        //printf("Corrigo izquierda\n");
        corregirIzq();
        run();
    }
    else if (myAnalogRead(0,CHAN_CONFIG_SINGLE,SENSOR_LEFT) >500){
	//printf("Corrigo Derecha\n");
	corregirDer();
	delay(300);
	run();
	}*/
    
    
    
    
    else{
        //printf("Nada\n");
	run();
    }
}


int main (int argc, char *argv [])
{
   // para el uso de los pines 18 y 19 GPIO Iniciamos wiring pi en modo GPIO
    wiringPiSetupGpio();
    spiSetup(0);
    //iniciamos ambos servos en modo PWM
    pinMode(SERVO_DER,2);
    pwmSetMode(0);
    pwmSetClock(400);
    pwmSetRange(1024);
    pinMode(SERVO_IZQ,2);
    pwmSetMode(0);
    pwmSetClock(400);
    pwmSetRange(1024);
    run();
    //printf("Sale del Main");
    pwmWrite(SERVO_DER,0);
    pwmWrite(SERVO_IZQ,0);
    delay(10);	
    close (myFd);
    return 0;
}
