#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){
	// selectionSort

    for(int j=0; j<toSort.size(); j++){
        int min = j; // determine l'index du minimum comme le premier index du tableau
        for(int i=j+1; i<toSort.size(); i++){
            if(toSort[min]>toSort[i]) min = i; // cherche le minimum
        }
        toSort.swap(min,j); // inverse le minimum et la case courante
    }

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
