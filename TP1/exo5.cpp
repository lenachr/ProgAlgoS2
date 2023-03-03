#include "tp1.h"
#include <QApplication>
#include <time.h>
#include <math.h>

// retourne vrai si le point appartient à l’ensemble de
// Mandelbrot pour la fonction f(z) ! z2 + point. Un point appartient à cet ensemble si la
// suite zn est bornée, autrement-dit s’il existe un i < n tel que |zi| > 2. Attention, z est un
// complexe, autrement-dit il représente un réel et un imaginaire x + iy et donc z2 = (x + iy)2.
// Posez le calcul et déterminer le nouveau réel et le nouvel imaginaire.
int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot

    // check n
    if(n==0) return 1;

    // check length of z
    // if Mandelbrot, return 1 or n (check the difference)
    if(sqrt((z.x)*(z.x)+(z.y)*(z.y))>2){ //module de z>2
        return n;
    }

    // otherwise, process the square of z and recall
    // isMandebrot
    else{
        float_t old_x = z.x;
        z.x = (z.x+point.x)*(z.x+point.x) - (z.y+point.y)*(z.y+point.y); //partie réel du z au carré
        z.y = 2*(old_x+point.x)*(z.y+point.y); //partie imaginaire du z au carré
        return isMandelbrot(z,n-1,point); //on rappelle la fonction
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



