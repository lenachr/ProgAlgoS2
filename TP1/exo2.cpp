#include "tp1.h"
#include <QApplication>
#include <time.h>

#define return_and_display(result) return _.store(result);

int fibonacci(int n)
{
    Context _("fibonacci", n); // do not care about this, it allow the display of call stack

    // your code
    if (n==0)
        return 0;
    if (n==1)
        return 1;
    return_and_display(fibonacci(n-2)+fibonacci(n-1));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // create a window manager
    MainWindow::instruction_duration = 400;  // make a pause between instruction display
    MainWindow* w = new FibonacciWindow(fibonacci); // create a window for this exercice
    w->show(); // show exercice

    return a.exec(); // main loop while window is opened
}
