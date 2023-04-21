#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChild(int nodeIndex)
{
    // retourne l’index du fils gauche du noeud à l’indice nodeIndex

    return (nodeIndex*2)+1;
}

int Heap::rightChild(int nodeIndex)
{
    return (nodeIndex*2)+2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i = heapSize;
    this->get(i) = value;
    while(i>0 && this->get(i) > this->get((i-1)/2)) {
        swap(i,(i-1)/2);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
//	// use (*this)[i] or this->get(i) to get a value at index i

    int i_max = nodeIndex; // indice de la valeur la plus grande entre le noeud i et ses enfants
    int i = heapSize;

    if(rightChild(nodeIndex)<i && this->get(rightChild(nodeIndex))>this->get(nodeIndex)){
        i_max = this->rightChild(nodeIndex);
    }

    if(leftChild(nodeIndex)<i && this->get(leftChild(nodeIndex))>this->get(i_max)){
        i_max = this->leftChild(nodeIndex);
    }

    if(i_max != i){
        swap(nodeIndex, i_max);
        heapify(heapSize, i_max);
    }
}

void Heap::buildHeap(Array& numbers)
{
    // Construit un tas à partir des valeurs de numbers
    for(int i = 0; i<numbers.size(); i++){
        insertHeapNode(numbers.size(), numbers[i]);
    }
}

void Heap::heapSort()
{
    // Construit un tableau trié à partir d’un tas heap
    for(int i=size()-1; i>0; i--){
        swap(0, i);
        heapify(i,0);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
