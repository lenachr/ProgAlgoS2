#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;


void bubbleSort(Array& toSort){
	// bubbleSort
    for(uint j = 0; j<toSort.size()-1;j++){ //boucle qui permet de faire le maximum d'échanges pour assurer le bon ordre du tableau
        for(uint i = 0; i<toSort.size()-1;i++){
            if(toSort[i]>toSort[i+1]){
                toSort.swap(i,i+1); // intervertit la valeur de la case actuelle avec celle de la case d'après
            }
        }
    }
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 100;
	w = new TestMainWindow(bubbleSort);
	w->show();

	return a.exec();
}
