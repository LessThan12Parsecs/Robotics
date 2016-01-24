
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>



int main (void)
{ 
  wiringPiSetup () ;
  pinMode (6,INPUT);//SENSOR DERECHA
  pinMode (3,INPUT);//SENSOR IZQUIERDA
  while(1)
  {
   if(digitalRead(6)){
       printf("SI DERECHA\n");
       softPwmWrite(0,10);
       softPwmWrite(1,16);
       delay(100);
	}
   else if(digitalRead(3)) {
       printf("SI IZQUIERDA\n");
       softPwmWrite(0,14);
       softPwmWrite(1,20);
       delay(100);
       }
   else{
       printf("NO\n");
       softPwmWrite(0,14);
       softPwmWrite(1,15);
       delay(100);
       }
  }
    return 0;
}
