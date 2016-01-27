//Progama para seguir pista de linea con robot movil
//Emanuel Ramirez Catapano
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define SENSOR_IZQ      25
#define SENSOR_DER      22
#define SERVO_IZQ       19
#define SERVO_DER       18


// IZQUIERDO > 73 hacia adelante
// DERECHO < 73 hacia adelante
int main (void)
{
    
  // para usar el modo PWM por hardware iniciamos el WiringPi con numeracion GPIO
  wiringPiSetupGpio () ;
    
  //iniciamos los sensores como INPUT
  pinMode (SENSOR_DER,INPUT);
  pinMode (SENSOR_IZQ,INPUT);
  //iniciamos los servos como PWM
  pinMode (SERVO_DER,2);
  pwmSetMode(0);
  pwmSetClock(400);
  pwmSetRange(1024);
  pinMode(SERVO_IZQ,2);
  pwmSetMode(0);
  pwmSetClock(400);
  pwmSetRange(1024);
  //Bucle
  while(1)
  {
      // el circuito esta hecho para que de Alta en blanco
      // por lo que si el sensor derecho pasa a baja (Negro) Gira a la derecha
   if(!digitalRead(SENSOR_DER)){
       //printf("SI DERECHA\n");
       pwmWrite(SERVO_DER,77);
       pwmWrite(SERVO_IZQ,80);
       delay(1);
	}
      //si el sensor izquierdo pasa a baja (Negro) Gira a la izquierda
   else if(!digitalRead(SENSOR_IZQ)) {
       //printf("SI IZQUIERDA\n");
       pwmWrite(SERVO_IZQ,71);
       pwmWrite(SERVO_DER,40);
       delay(1);
       }
      // si ambos estan en alta, continua recto.
   else{
       //printf("NO\n");
       pwmWrite(SERVO_DER,66);
       pwmWrite(SERVO_IZQ,80);
       delay(1);
       }
  }
    return 0;
}
