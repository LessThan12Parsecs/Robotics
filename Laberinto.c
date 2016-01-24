
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

static int myFd ;

char *usage = "Usage: mcp3008 all|analogChannel[1-8] [-l] [-ce1] [-d]";
void loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

void spiSetup (int spiChannel)
{
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}

void corregirIzq(){
    softPwmWrite(0,14);
    softPwmWrite(1,20);
    delay(200);
    
}

void girarDerecha(){
    softPwmWrite(0,16)
    softPwmWrite(1,0);
    delay(1500); //90 grados
    softPwmWrite(0,15);
    softPwmWrite(1,15);
    delay(100);
}

void girarIzquierda(){
    softPwmWrite(1,14)
    softPwmWrite(0,0);
    delay(1500); //90 grados
    softPwmWrite(0,15);
    softPwmWrite(1,15);
    delay(100);
}

void run(){
    softPwmWrite(0,10);//servo izquierda
    softPwmWrite(1,20);//servo derecha
    int left = 0;
    int front = 1;
    while (myAnalogRead(spiChannel,channelConfig,left) > 370 && myAnalogRead(spiChannel,channelConfig,front)<200){ // hay que probar los valores de radio de giro y que este cerca
        printf("Siguiendo la pared");
    }
    if(myAnalogRead(spiChannel,channelConfig,front) > 201){
        printf("Giro derecha");
        girarDerecha();
        run();
    }
    else if (myAnalogRead(spiChannel,channelConfig,left) < 150 && myAnalogRead(spiChannel,channelConfig,front) < 201){
        printf("Giro Izquierda");
        girarIzquierda();
        run();
    }
    else if (myAnalogRead(spiChannel,channelConfig,left) > 151 && myAnalogRead(spiChannel,channelConfig,left) < 371){
        prinft("Corrigo izquierda");
        corregirIzq();
        run();
    }
    else{
        printf("STOP");
        return;
    }
}


int main (int argc, char *argv [])
{
    int analogChannel=1;
    int spiChannel=0;
    int channelConfig=CHAN_CONFIG_SINGLE;
    wiringPiSetup () ;
    spiSetup(spiChannel);
    pinMode(0,PWM_OUTPUT);
    pinMode(1,PWM_OUTPUT);
    softPwmCreate(1,0,100);
    softPwmCreate(0,0,100);
    run();
    softPwmWrite(0,15);
    softPwmWrite(1,15);
 
    delay(10000);	
    close (myFd);
    return 0;
}
