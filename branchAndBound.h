#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H
#define SIZE 15
#define LINE 250

typedef struct Objet Objet;
struct Objet{
	double valeur;
	double poids;
	double ratios;
};

typedef struct Arbre Arbre;
struct Arbre{
	Objet *noeud;
	int *visite;
	int *choix;
	int pere;
	int filsGauche;
	int filsDroit;
};

int isPair(int number);
void calculRate(Objet *objet, int nbObjets);
void afficheDonnees(Objet *objet,int nbObjets);
void swap(Objet *obj1, Objet *obj2);
void trieABulles(Objet *objet, int nbObjets);
void initialiserTableau(Arbre *collectionObjet, int nbObjets);
void arrayCpy(Arbre *obj1,int size);
int power(int number, int power);
void descenteArbre(int fg,int fd,int side, Arbre *collectionObjet, double nbObjets,double *SommePoids,int *j,double poidMax);
void remonteeArbre(Arbre *collectionObjet,double *SommePoids,int *j);
void afficheObjetSaisie(Arbre *collectionObjet, int nbObjets,double *tmpPoids,double poidMax);
void branchAndBound(Arbre collectionObjet, Objet *objet,int nbObjets,double poidMax);
void ecritureFichier(Arbre *collectionObjet,int nbObjets,double tmpPoids,double SommeValeur,double poidMax);

#endif  
