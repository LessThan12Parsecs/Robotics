#Practica 2 - Control de Servos (Version en Python con control por teclas)
#Grupo 5 
import wiringpi2
from tkinter import *

wiringpi2.wiringPiSetup() #hacemos setup con los valores de
#Elegimos el modo OUTPUT (1) para ambos pines 0 y 1 
wiringpi2.pinMode(0,1)
wiringpi2.pinMode(1,1)
#creamos el PWM en pin 1 y 0 con rango 100 y valor inicial 0
wiringpi2.softPwmCreate(0,0,100) 
wiringpi2.softPwmCreate(1,0,100)

#Definimos funciones para 4 direcciones de movimiento 
# El valor de bloqueo de posicion es 15 y menor de esto gira en sentido opuesto a horario
# y mayor que 15 gira en sentido horario.
def adelante():
    wiringpi2.softPwmWrite(1,14)
    wiringpi2.softPwmWrite(0,16)
def parar():
    wiringpi2.softPwmWrite(1,0)
    wiringpi2.softPwmWrite(0,0)
def derecha():
    wiringpi2.softPwmWrite(1,16)
    wiringpi2.softPwmWrite(0,16)
def izquierda():
    wiringpi2.softPwmWrite(1,14)
    wiringpi2.softPwmWrite(0,14)
def atras():
    wiringpi2.softPwmWrite(0,14)
    wiringpi2.softPwmWrite(1,16)
    
#definimos como reaccionar con un evento de tecla presionada
    
def key_input(event):
    print ("Cambio de direccion")
    key_press = event.char
    if key_press.lower() == "w":
        adelante()
    elif key_press.lower() == "s":
        atras()
    elif key_press.lower() == "a":
        izquierda()
    elif key_press.lower() == "d":
        derecha()
    elif key_press.lower() == "q":
        parar()

#abrimos una ventana tk
# asignamos la tecla presionada como input.     
command = Tk()
command.bind('<KeyPress>',key_input)

#continua el loop de programa.
command.mainloop()
