
// control de motores paso a paso -Practica 2 
// Grupo 5

#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT);
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (10) ;
    digitalWrite (0,  0) ; delay (10) ;
  }
  return 0 ;
}
