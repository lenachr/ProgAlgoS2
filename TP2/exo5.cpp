#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if(origin.size()<=1) return;
	// initialisation
	Array& first = w->newArray(origin.size()/2);
	Array& second = w->newArray(origin.size()-first.size());
	// split

        for(int i=0; i < (origin.size())/2 ;i++){
            first[i]=origin[i];
        }

        for(int i=0; i < (origin.size())/2 ;i++){
            second[i]=origin[i + first.size()];
        }
        // recursiv splitAndMerge of first and second
        splitAndMerge(first);
        splitAndMerge(second);

	// merge
        merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result)
{
//    for(int i=0; i<first.size(); i++){
//        result[i]=first[i];
//    }
//    for(int i=first.size()+1; i<second.size(); i++){
//        result[i]=second[i-first.size() -1];
//    }

     int cursorfirst=0;
     int cursorsecond=0;
    for (int i = 0; i < result.size(); ++i) {
            //regarder qui est le minimum
        if(first[cursorfirst]< second[cursorsecond]){
            result[i]=first[cursorfirst];
            cursorfirst++;
        }else{
            result[i]=second[cursorsecond];
            cursorsecond++;
        }
        //cursorfirst ou cursor second dépasse
        if(first.size()==cursorfirst){
//            for(int j=0; j < second.size()-cursorsecond; j++){
//            result[j]=second[cursorsecond]; //compliqué parce que plus de conditions
//            }
            while(cursorsecond <second.size()){
                result[i]=second[cursorsecond];
                cursorsecond++;
                i++;
            }
            break;
        }

        if(second.size()==cursorsecond){
            while(cursorfirst <first.size()){
                result[i]=second[cursorfirst];
                cursorfirst++;
                i++;
            }
            break;
        }
    }
}



void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
