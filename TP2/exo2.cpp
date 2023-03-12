#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());

    // insertion sort from toSort to sorted
    sorted[0] = toSort[0];
    for(uint n=1;n<toSort.size();n++){ // Pour chaque nombre n du tableau (excepté le premier) faire
        for(uint m=0;m<toSort.size();m++){
            if(m==n){
                sorted[m] = toSort[n];
            }
            if(sorted[m]>toSort[n]){
                for(uint i=(sorted.size()-1);i>m;i--){ // boucle pour le décalage des valeurs du tableau
                    sorted[i] = sorted[i-1];
                }
                sorted[m] = toSort[n]; // insérer n à la position de m
                break;
            }
        }
    }

    toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
