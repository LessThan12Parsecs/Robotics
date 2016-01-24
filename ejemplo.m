% DATOS DE ENTRADA:

% Puntos objetivos
pP=[5,1];
pF=[10,12];

% tiempo para cada segmento:
t1=5;
t2=3;

% --------------------------------------------------------

% Calculo de los tiempos intermedios:
t0=0;
tP=t0+t1;
tF=t0+t1+t2;


% MATRIZ CON LAS ECUACIONES QUE HAY QUE RESOLVER:

% Se resuelve la matriz general mostrada en el ejemplo:

M=[     t0^4,   t0^3,   t0^2,   t0, 1,        0,      0,     0,  0,  0
      4*t0^3, 3*t0^2,   2*t0,   1,  0,        0,      0,     0,  0,  0
    4*3*t0^2, 3*2*t0,      2,   0,  0,        0,      0,     0,  0,  0
           0,      0,      0,   0,  0,     tF^4,   tF^3,  tF^2, tF,  1
           0,      0,      0,   0,  0,   4*tF^3, 3*tF^2,  2*tF,  1,  0
           0,      0,      0,   0,  0, 4*3*tF^2, 3*2*tF,     2,  0,  0
        tP^4,   tP^3,   tP^2,   tP, 1,    -tP^4,  -tP^3, -tP^2,-tP, -1
      4*tP^3, 3*tP^2,   2*tP,   1,  0,  -4*tP^3,-3*tP^2, -2*tP, -1,  0  
    4*3*tP^2, 3*2*tP,      2,   0,  0,-4*3*tP^2,-3*2*tP,    -2,  0,  0
        tP^4,   tP^3,   tP^2,  tP,  1,        0,      0,     0,  0,  0];
       

Bx=[p0(1), 0, 0, pF(1), 0, 0, 0, 0, 0, pP(1)]';
By=[p0(2), 0, 0, pF(2), 0, 0, 0, 0, 0, pP(2)]';

% RESOLVER LAS ECUACIONES:

% Ecuaci?n:  M*pX=Bx
pX=M\Bx;
% Ecuaci?n:  M*pY=By
pY=M\By;

% SOLUCI?N PARA CADA VARIABLE (X,Y)

% Coeficientes de X e Y para las curvas 1 y 2:
pX1=pX(1:5)
pX2=pX(6:10)
pY1=pY(1:5)
pY2=pY(6:10)

% ----------------------------------------------------

% C?LCULO DE LOS PUNTOS (DIBUJO):

% C?lculo de la curva, la velocidad y la aceleraci?n:
t1=t0:0.1:tP;
t2=tP:0.1:tF;

% Posici?n:
x1=polyval(pX1,t1);
y1=polyval(pY1,t1);
x2=polyval(pX2,t2);
y2=polyval(pY2,t2);

% Velocidad:
dpX1=polyder(pX1);
dpY1=polyder(pY1);
dpX2=polyder(pX2);
dpY2=polyder(pY2);
dx1=polyval(dpX1,t1);
dy1=polyval(dpY1,t1);
dx2=polyval(dpX2,t2);
dy2=polyval(dpY2,t2);

% Aceleraci?n:
ddpX1=polyder(dpX1);
ddpY1=polyder(dpY1);
ddpX2=polyder(dpX2);
ddpY2=polyder(dpY2);
ddx1=polyval(ddpX1,t1);
ddy1=polyval(ddpY1,t1);
ddx2=polyval(ddpX2,t2);
ddy2=polyval(ddpY2,t2);

% Dibujo de la soluci?n:

figure
plot(x1,y1,'r',x2,y2,'b',p0(1),p0(2),'o',pP(1),pP(2),'x',pF(1),pF(2),'o')
title('Curvas 1 (rojo) y 2 (azul)');

figure
subplot(3,2,1), plot(t1,x1,'r',t2,x2,'b'),title('x(t)')
subplot(3,2,2), plot(t1,y1,'r',t2,y2,'b'),title('y(t)')
subplot(3,2,3), plot(t1,dx1,'r',t2,dx2,'b'),title('dx(t)')
subplot(3,2,4), plot(t1,dy1,'r',t2,dy2,'b'),title('dy(t)')
subplot(3,2,5), plot(t1,ddx1,'r',t2,ddx2,'b'),title('ddx(t)')
subplot(3,2,6), plot(t1,ddy1,'r',t2,ddy2,'b'),title('ddy(t)')

