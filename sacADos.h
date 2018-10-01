#ifndef SACADOS_H
#define SACADOS_H
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
	Objet noeud[SIZE];
	int visite[SIZE];
	int choix[SIZE];
	int pere;
	int filsGauche;
	int filsDroit;
};

int isPair(int number);
void lectureFichier(Objet *objet, double *poidMax,int *nbObjets);
void calculRate(Objet *objet, int nbObjets);
void afficheDonnees(Objet *objet,int nbObjets);
void quickSort(Objet *objet,int nbObjets);
void trieABulles(Objet *objet, int nbObjets);
void swap(Objet *obj1, Objet *obj2);
//void initialiserTableau(Arbre collectionObjet, int nbObjets);
void arrayCpy(Arbre *obj1,int size);
void branchAndBound(Arbre collectionObjet, Objet *objet,int nbObjets,double poidMax);
void descenteArbre(int fg,int fd,int side, Arbre *collectionObjet, double nbObjets,double *SommePoids,int *j,double poidMax);
void remonteeArbre(Arbre *collectionObjet,double *SommePoids,int *j);

#endif  
