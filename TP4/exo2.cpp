#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "tp4.h"
#include "tp4_exo2.h"
#include "HuffmanNode.h"

_TestMainWindow* w1 = nullptr;
using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256);
    characterFrequences.fill(0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    qDebug() << priorityMinHeap.toString().toStdString().c_str();

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, *huffmanTree);

    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
}


void processCharFrequences(string data, Array& frequences)
{
    /**
      * Fill `frequences` array with each caracter frequence.
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/

    frequences.fill(0);
    for(uint i=0; i<data.size(); i++){
        frequences[data[i]]++;
    }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    /**
      * Insert a HuffmanNode into the lower heap. A min-heap put the lowest value
      * as the first cell, so check the parent should be lower than children.
      * Instead of storing int, the cells of HuffmanHeap store HuffmanNode*.
      * To compare these nodes use their frequences.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    int i = heapSize;
    (*this)[i] = newNode;
    while(i>0 && this->get(i)->frequences < this->get((i-1)/2)->frequences) { //parent doit être plus petit que l'enfant
        this->swap(i,(i-1)/2);
        i = (i-1)/2;
    }

}

void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
      * allocate a HuffmanNode with `new`
     **/

    heapSize = 0;
    for(uint i = 0; i<frequences.size(); i++){
        if(frequences[i] != 0){
            HuffmanNode* newNode = new HuffmanNode(i, frequences[i]);
            priorityMinHeap.insertHeapNode(heapSize, newNode);
            heapSize++;
        }
    }

}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
    /**
      * Repair the heap starting from nodeIndex. this is a min-heap,
      * so check the parent should be lower than children.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    int i_min = nodeIndex; // indice de la valeur la plus petite entre le noeud i et ses enfants
    int i = heapSize;

    if(this->get(i)->frequences<i && this->get(i)->frequences<this->get(i_min)->frequences){
        i_min = this->get(i)->frequences;
    }

    if(this->get(i)->frequences<i && this->get(i)->frequences<this->get(i_min)->frequences){
        i_min = this->get(i)->frequences;
    }

    if(i_min != i){
        swap(nodeIndex, i_min);
        heapify(heapSize, i_min);
    }

}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    /**
      * Extract the first cell, replace the first cell with the last one and
      * heapify the heap to get a new well-formed heap without the returned cell
      * you can use `this->swap`
     **/

    this->swap(0, heapSize);
    this->heapify(heapSize, 0);
    return this->get(heapSize);
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    /**
     * Make a subtree (parent + 2 children) with the given 2 nodes.
     * These 2 characters will be the children of a new parent node which character is '\0'
     * and frequence is the sum of the 2 children frequences
     * Return the new HuffmanNode* parent
     **/

    HuffmanNode* parent = new HuffmanNode('\0');
    parent->left = leftNode;
    parent->right = rightNode;
    parent->frequences = rightNode->frequences + leftNode->frequences;
    return parent;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    /**
      * Build Huffman Tree from the priorityMinHeap, pick nodes from the heap until having
      * one node in the heap. For every 2 min nodes, create a subtree and put the new parent
      * into the heap. The last node of the heap is the HuffmanTree;
      * use extractMinNode()
     **/

    // Your code

    return new HuffmanNode('?');
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    /**
      * Travel whole tree of HuffmanNode to determine the code of each
      * leaf/character.
      * Each time you call the left child, add '0' to the baseCode
      * and each time call the right child, add '1'.
      * If the node is a leaf, it takes the baseCode.
     **/

    if(!this->left && !this->right) this->code = baseCode;
    else {
        if(this->left) this->left->processCodes(baseCode+"0");
        if(this->right) this->right->processCodes(baseCode+"1");
    }
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";
    for(int i=0; i<toEncode.size();i++){
        encoded+=charactersCodes[toEncode[i]];
    }
    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman tree. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    // Your code
    string decoded = "";

    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w1 = new HuffmanMainWindow(main_function);
    w1->show();
    return a.exec();
}
