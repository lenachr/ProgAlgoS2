#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        // init initial node without children
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    void insertNumber(int value) {
        // create a new node and insert it in right or left child
        SearchTreeNode* test = new SearchTreeNode(value);
        // si la valeur est plus grande que l'actuelle
        // et que la cellule de gauche est vide
        if(value < this->value && this->left == nullptr){
            this->left = test;
        }
        // si la valeur est plus petite que l'actuelle
        // et que la cellule de droite est vide
        if(value > this->value && this->right == nullptr){
            this->right = test;
        }

        //cas où les cellules à côté sont pas vides
        if(value < this->value && this->left != nullptr){
            this->left->insertNumber(value); // on réappelle la fonction pour les enfants
        }
        if(value > this->value && this->right != nullptr){
            this->right->insertNumber(value); // on réappelle la fonction pour les enfants
        }

    }

	uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself.
        if(!isLeaf()){
            uint hautg = 0, hautd = 0;
            if(this->left != nullptr) {hautg=this->left->height();}
            if(this->right != nullptr) {hautd=this->right->height();}
            if (hautg>hautd) return 1+hautg;
            else return 1+hautd;
        }
        // If there is no child, return
        // just 1
        else return 1;
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        if(isLeaf()) return 1;
        int g = 0;
        int d = 0;
        if(!isLeaf()){
            if(this->left != nullptr) {g=this->left->nodesCount();}
            if(this->right != nullptr){d=this->right->nodesCount();}
            return 1+g+d;
        }
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        if(this->right == nullptr && this->left == nullptr) return true;
        else return false;
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree

        if(isLeaf()){ //on vérifie que c'est une feuille
            leaves[leavesCount] = this; //on met le noeud dans le tableau
            leavesCount += 1; //on avance dans le tableau
        }else

        if(this->left != nullptr){ //si le noeud à gauche n'est pas vide
            this->left->allLeaves(leaves, leavesCount); // on rappelle la fonction sur le noeud de gauche
        }
        if(this->right != nullptr){ //si le noeud à droite n'est pas vide
            this->right->allLeaves(leaves, leavesCount); // on rappelle la fonction sur le noeud de gauche
        }
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
        if(this->left != nullptr){ // on part du fils gauche
            this->left->inorderTravel(nodes,nodesCount);
        }
        nodes[nodesCount] = this; // on ajoute le parent au milieu
        nodesCount += 1;
        if(this->right != nullptr){ // on termine par le fils droit
            this->right->inorderTravel(nodes,nodesCount);
        }
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
        nodes[nodesCount] = this; // on part du parent au début
        nodesCount += 1;
        if(this->left != nullptr){ // on ajoute le fils gauche au milieu
            this->left->preorderTravel(nodes,nodesCount);
        }
        if(this->right != nullptr){ // on termine par le fils droit
            this->right->preorderTravel(nodes,nodesCount);
        }
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
        if(this->left != nullptr){ // on part du fils gauche
            this->left->postorderTravel(nodes,nodesCount);
        }
        if(this->right != nullptr){ // on ajoute le fils droit au milieu
            this->right->postorderTravel(nodes,nodesCount);
        }
        nodes[nodesCount] = this; // on termine par le parent
        nodesCount += 1;
	}

	Node* find(int value) {
        // find the node containing value
        if(this->value == value){ // si la valeur est égale avec celle du noeud actuelle
            return this; // on peut retourner le noeud
        }
        else if(value < this->value && this->left != nullptr){ // si valeur plus petite que l'actuelle, on part sur le noeud de gauche
            this->left->find(value); // on rappelle la fonction sur le noeud de gauche
        }
        else if(value > this->value && this->right != nullptr){ // si valeur plus grande que l'actuelle, on part sur le noeud de droite
            this->right->find(value); // on rappelle la fonction sur le noeud de droite
        }
	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
