#include <QApplication>
#include <QString>
#include <time.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include <tp5.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;


std::vector<string> TP5::names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});

unsigned long int hash(string key)
{
    // return an unique hash id from key
    // on utilise le hachage polynomiale
    unsigned long int hash_value = 0;
    for(int i = 0 ; i < key.size() ; i++)
    {
        hash_value += key[i] * pow(128, key.size()-1-i); // somme de la valeur ASCII de chaque caractère
    }
    return hash_value;
}


struct MapNode : public BinaryTree
{

    string key;
    unsigned long int key_hash;

    int value;

    MapNode* left;
    MapNode* right;

    MapNode(string key, int value) : BinaryTree (value)
    {
        this->key = key;
        this->value = value;
        this->key_hash = hash(key);

        this->left = this->right = nullptr;
    }

    /**
     * @brief insertNode insert a new node according to the key hash
     * @param node
     */
    void insertNode(MapNode* node)
    {
        // si la valeur est plus grande que l'actuelle
        // et que la cellule de gauche est vide
        if(node->key_hash < this->key_hash && this->left == nullptr){
            this->left = node;
        }
        // si la valeur est plus petite que l'actuelle
        // et que la cellule de droite est vide
        else if(node->key_hash > this->key_hash && this->right == nullptr){
            this->right = node;
        }

        //cas où les cellules à côté sont pas vides
        else if(node->key_hash < this->key_hash && this->left != nullptr){
            this->left->insertNode(node); // on réappelle la fonction pour les enfants
        }
        else if(node->key_hash > this->key_hash && this->right != nullptr){
            this->right->insertNode(node); // on réappelle la fonction pour les enfants
        }
    }

    void insertNode(string key, int value)
    {
        this->insertNode(new MapNode(key, value));
    }

    virtual ~MapNode() {}
    QString toString() const override {return QString("%1:\n%2").arg(QString::fromStdString(key)).arg(value);}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

struct Map
{
    MapNode* root;

    Map() {
        this->root = nullptr;
    }

    /**
     * @brief insert create a node and insert it to the map
     * @param key
     * @param value
     */
    void insert(string key, int value)
    {
        MapNode* node = new MapNode(key, value);
        if (this->root == nullptr){
            this->root = node;
        }
        else this->root->insertNode(node);
    }

    /**
     * @brief get return the value of the node corresponding to key
     * @param key
     * @return
     */
    int get(string key)
    {
        unsigned long int h_key = hash(key);
        MapNode* temp = this->root;
        while(temp != nullptr){
            if(temp->key_hash == h_key){
                return temp->value;
            }
            else if(h_key < temp->key_hash){
                temp = temp->left;
            }
            else if(h_key > temp->key_hash){
                temp = temp->right;
            }
        }
    }
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
    Map map;
    std::vector<std::string> inserted;

    map.insert("Yolo", 20);
    for (std::string& name : TP5::names)
    {
        if (rand() % 3 == 0)
        {
            map.insert(name, rand() % 21);
            inserted.push_back(name);
        }
    }


    printf("map[\"Margot\"]=%d\n", map.get("Margot"));
    printf("map[\"Jolan\"]=%d\n", map.get("Jolan"));
    printf("map[\"Lucas\"]=%d\n", map.get("Lucas"));
    printf("map[\"Clemence\"]=%d\n", map.get("Clemence"));
    printf("map[\"Yolo\"]=%d\n", map.get("Yolo"));
    printf("map[\"Tanguy\"]=%d\n", map.get("Tanguy"));

    printf("\n");
    for (size_t i=0; i<inserted.size()/2; i++)
        printf("map[\"%s\"]=%d\n", inserted[i].c_str(), map.get(inserted[i]));


    std::cout.flush();


    QApplication a(argc, argv);
    MainWindow::instruction_duration = 200;
    w = new MapWindow(*map.root);
    w->show();
    return a.exec();
}
