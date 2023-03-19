#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

/**
 * @brief define indexMin and indexMax as the first and the last index of toSearch
 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */
void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
    // création de booléens pour repérer si toSearch est bien dans le tableau
    bool foundMin = false;
    bool foundMax = false;

    // parcours du tableau partant du début pour chercher l'indexMin
    for(indexMin = 0;indexMin<array.size()-1;indexMin++){
        if(toSearch==array[indexMin]){
            foundMin = true; // toSearch est trouvée
            break; // on sort de la boucle
        }
    }

    // parcours du tableau à l'envers pour chercher l'indexMax
    for(indexMax = array.size()-1;indexMax>=0;indexMax--){
        if(toSearch==array[indexMax]){
            foundMax = true; // toSearch est trouvée
            break; // on sort de la boucle
        }
    }

    // après avoir parcouru le tableau, si toSearch n'est pas trouvée, les index sont mis à -1
    if(foundMin == false && foundMax == false) indexMin = indexMax = -1;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
