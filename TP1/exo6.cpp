#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
    Noeud* precedent;
};

struct Liste{
    Noeud* premier;
};

struct DynaTableau{
    int* donnees;
    int capacite; //taille max du tableau qui change si capacité dépassé
    int taille; //nb d'éléments actuelle dans le tableau
};

void initialise(Liste* liste)
{
    liste->premier = nullptr; 
}

bool est_vide(const Liste* liste)
{
    if(liste->premier != nullptr) return false;
    return true;
}

void ajoute(Liste* liste, int valeur)
{
    if(liste->premier == nullptr) {
        liste->premier = new Noeud {valeur, nullptr};
        return;
    }
    Noeud* temp = liste->premier;
    while(temp->suivant != nullptr) {
        temp = temp->suivant;
    }
    temp->suivant = new Noeud {valeur, nullptr};
}

void affiche(const Liste* liste)
{
    Noeud* temp = liste->premier;
    while(temp != nullptr) {
        cout << temp->donnee << endl;
        temp = temp->suivant;
    }
}

// Retourne le nième entier de la structure
int recupere(const Liste* liste, int n)
{
    Noeud* temp = liste->premier;
    for(int i=0; i<n; i++){
        if(temp == nullptr) return 0;
        temp = temp->suivant;
    }
    if(temp == nullptr) return 0;
    return temp->donnee;
}

// Retourne l’index de valeur dans la structure ou -1 s’il n’existe pas
int cherche(const Liste* liste, int valeur)
{
    Noeud* temp = liste->premier;
    int compt = 0;
    while(temp != nullptr){
        compt++;
        if(temp->donnee == valeur) return compt;
        temp = temp->suivant;
    }
}

// Redéfini la nième valeur de la structure avec valeur
void stocke(Liste* liste, int n, int valeur)
{
    Noeud* temp = liste->premier;
    for(int i=0; i<n-1; i++){
        temp = temp->suivant;
    }
    temp->donnee = valeur;
}

void ajoute(DynaTableau* tableau, int valeur)
{
    // réallocation de tableaux
    if(tableau->taille == tableau->capacite) {
        tableau->capacite = tableau->capacite*2;
        int* temp = new int[tableau->capacite];
        for(int i = 0; i < tableau->taille; i++) {
            temp[i] = tableau->donnees[i];
        }
        delete[] tableau->donnees; // libérer mémoire du tableau
        tableau->donnees = temp;
    }
    tableau->donnees[tableau->taille] = valeur;
    tableau->taille = tableau->taille + 1;
}

void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees = new int[capacite];
    tableau->capacite = capacite;
    tableau->taille = 0;
}

bool est_vide(const DynaTableau* tableau)
{
    if (tableau->taille != 0) return false;
    return true;
}

void affiche(const DynaTableau* tableau)
{
    for(int i = 0; i<tableau->taille; i++){
        cout << tableau->donnees[i] << endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    return tableau->donnees[n];
}

int cherche(const DynaTableau* tableau, int valeur)
{
    for(int i=0;i<tableau->taille;i++){
        if(tableau->donnees[i] == valeur) return i+1;
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    tableau->donnees[n-1] = valeur;
}

// pour pile, on travaille avec des tableaux
void pousse_pile(DynaTableau* tableau, int valeur){
    if(tableau->taille == tableau->capacite) {
        tableau->capacite = tableau->capacite*2;
        int* temp = new int[tableau->capacite];
        for(int i = 0; i < tableau->taille; i++) {
            temp[i] = tableau->donnees[i];
        }
        delete[] tableau->donnees; // libérer mémoire du tableau
        tableau->donnees = temp;
    }
    tableau->donnees[tableau->taille] = valeur; //ajoute une valeur au tableau
    tableau->taille = tableau->taille + 1; //augmente la taille du tableau (nb d'élements dans le tableau)
}

int retire_pile(DynaTableau* tableau){
    int taille = tableau->taille;
    int av_dernier = tableau->donnees[taille-2];
    /* Valeur qu'on a enlevé de la file */
    int dernier = tableau->donnees[taille-1];
    /* On remplace le dernier élément du tableau. */
    tableau->donnees[taille] = av_dernier;
    tableau->taille--;
    return dernier;
}

// pour file, on travaille avec des listes chainées
void pousse_file(Liste* liste, int valeur)
{
    if(liste->premier == nullptr) {
        liste->premier = new Noeud {valeur, nullptr};
        return;
    }
    Noeud* temp = liste->premier;
    while(temp->suivant != nullptr) {
        temp = temp->suivant;
    }
    temp->suivant = new Noeud {valeur, nullptr}; //ajout d'un nouveau noeud à la fin de la liste
}


int retire_file(Liste* liste)
{
    int val_ret = 0;
    if (liste != nullptr)
    {
        /* Pointeur vers le deuxième élément de la file. */
        Noeud* temp = liste->premier->suivant;
        /* Valeur qu'on a enlevé de la file */
        val_ret = liste->premier->donnee;
        /* On efface le premier élément puis on le met à null. */
        free(liste), liste->premier = nullptr;
        /* On fait pointer la file vers le deuxième élément. */
        liste->premier = temp;
    }
    return val_ret;
}


int main()
{
     Liste liste;
     initialise(&liste);
     DynaTableau tableau;
     initialise(&tableau, 5);

      if (!est_vide(&liste))
      {
          std::cout << "Oups y a une anguille dans ma liste" << std::endl;
      }

     if (!est_vide(&tableau))
     {
         std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
     }

     for (int i=1; i<=7; i++) {
         //ajoute(&liste, i*7);
         ajoute(&tableau, i*5);
     }

     if (est_vide(&liste))
     {
         std::cout << "Oups y a une anguille dans ma liste" << std::endl;
     }

     if (est_vide(&tableau))
     {
         std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
     }

     std::cout << "Elements initiaux:" << std::endl;
     //affiche(&liste);
     affiche(&tableau);
     std::cout << std::endl;

     //std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
     std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

     //std::cout << "21 se trouve dans la liste a " << cherche(&liste, 21) << std::endl;
     std::cout << "15 se trouve dans la liste a " << cherche(&tableau, 15) << std::endl;

     stocke(&liste, 4, 7);
     stocke(&tableau, 4, 7);

     std::cout << "Elements apres stockage de 7:" << std::endl;
     affiche(&liste);
     affiche(&tableau);
     std::cout << std::endl;

    DynaTableau pile;
    Liste file;

    initialise(&pile, 7);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        affiche(&file);
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

     compteur = 10;
     while(!est_vide(&pile) && compteur > 0)
     {
         //std::cout << retire_pile(&pile) << std::endl;
         retire_pile(&pile);
         affiche(&pile);
         compteur--;
     }

     if (compteur == 0)
     {
         std::cout << "Ah y a un soucis là..." << std::endl;
     }

    return 0;
}
