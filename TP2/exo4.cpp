#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    // si le tableau est comporte 0 ou 1 élément, on arrête la fonction
    if(size<=1) return;

	Array& lowerArray = w->newArray(size);
	Array& greaterArray= w->newArray(size);
	int lowerSize = 0, greaterSize = 0; // effectives sizes

	// split
    int pivot = toSort[size-1];

    for(int i = 0; i<size-1; i++){
        // si l'élément est inférieur au pivot
        if(toSort[i]<pivot){
            lowerArray[lowerSize] = toSort[i];
            lowerSize++;
        }
        // si l'élément est supérieur au pivot
        if(toSort[i]>pivot){
            greaterArray[greaterSize] = toSort[i];
            greaterSize++;
        }
    }
	
	// recursiv sort of lowerArray and greaterArray
    // appel récursive de la fonction
    recursivQuickSort(lowerArray, lowerSize);
    recursivQuickSort(greaterArray, greaterSize);

	// merge
    // on rassemble le 1er sous-tableau inférieur au pivot au tableau de départ
    for(int i = 0; i<lowerSize; i++){
        toSort[i] = lowerArray[i];
    }

    //on met le pivot au centre du tableau
    toSort[lowerSize] = pivot;

    // on rassemble le 2ème sous-tableau supérieur au pivot au tableau de départ
    for(int i = 0; i<greaterSize; i++){
        toSort[i+lowerSize+1] = greaterArray[i];
    }
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
