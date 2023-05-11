#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
	/**
	  * Make a graph from a matrix
	  * first create all nodes, add it to the graph then connect them
	  * this->appendNewNode
	  * this->nodes[i]->appendNewEdge
	  */

    /* Construit un graphe à partir d’une matrice d’adjacence.
     * La valeur d’un sommet représente son indice dans le tableau.
    adjencies est tableau 2D de taille nodeCount.*/

    // création de noeuds en fonction de la taille du tableau, ajout des noeuds au graphe
    for(int i=0; i<nodeCount; i++){
        GraphNode *node = new GraphNode(i);
        this->appendNewNode(node);
    }

    // ajout des liens entre les noeuds
    for(int i=0; i<nodeCount; i++){
        for(int j=0; j<nodeCount; j++){
            if(adjacencies[i][j] > 0){ // il existe une arète entre sommets i et j (peut être >=1)
                // il existe une arète partant du sommet i au sommet j de taille adjacencies[i][j]
                this->nodes[i]->appendNewEdge(this->nodes[j], adjacencies[i][j]);
            }
        }
    }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	  * Fill nodes array by travelling graph starting from first and using recursivity
	  */

    nodes[nodesSize] = first; // on remplit le tableau nodes par les noeuds de chaque sommet du graphe
    nodesSize++; // on incrémente nodesSize qui est au départ égale à 0
    visited[first->value]=true; // on dit qu'on est passé par ce sommet
    for(Edge *e=first->edges; e!=nullptr; e=e->next)
    {
        if(!visited[e->destination->value]){ // si on n'est pas déjà passé par le sommet
            deepTravel(e->destination,nodes,nodesSize,visited); // on appelle la fonction récursive sur le sommet destinataire
        }
    }

}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	 * Fill nodes array by travelling graph starting from first and using queue
	 * nodeQueue.push(a_node)
	 * nodeQueue.front() -> first node of the queue
	 * nodeQueue.pop() -> remove first node of the queue
	 * nodeQueue.size() -> size of the queue
	 */
	std::queue<GraphNode*> nodeQueue;
    nodeQueue.push(first);
    visited[first->value] = true;

    while (!nodeQueue.empty())
    {
        GraphNode* current_node = nodeQueue.front(); // le noeud tout en haut de la liste
        nodes[nodesSize] = current_node; // on remplit le tableau nodes par les noeuds de chaque sommet du graphe
        nodesSize++; // on incrémente nodesSize qui est au départ égale à 0

        for(Edge *e=current_node->edges; e!=nullptr; e=e->next)
        {
            if(!visited[e->destination->value]){ // si on n'est pas déjà passé par le sommet
                visited[e->destination->value] = true; // on dit qu'on est passé par ce sommet
                nodeQueue.push(e->destination); // on rajoute le sommet destinataire à la liste
            }
        }
        nodeQueue.pop(); // tout premier noeud de la liste qui est retiré
    }
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/
    std::queue<GraphNode*> nodeQueue;
    nodeQueue.push(first);
    visited[first->value] = true;

    while (!nodeQueue.empty())
    {
        GraphNode* current_node = nodeQueue.front(); // le noeud tout en haut de la liste

        for(Edge *e=current_node->edges; e!=nullptr; e=e->next)
        {
            if(e->destination == first) return true; // si on retombe sur le sommet de départ, on a bouclé, c'est un circuit
            if(!visited[e->destination->value]){ // si on n'est pas déjà passé par le sommet
                nodeQueue.push(e->destination); // on rajoute le sommet destinataire à la liste
            }
        }
        nodeQueue.pop(); // tout premier noeud de la liste qui est retiré
    }
    return false; // dans le cas où ce n'est pas un circuit
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 150;
	w = new GraphWindow();
	w->show();

	return a.exec();
}
