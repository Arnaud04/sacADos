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

int isPair(int number);
void lectureFichier(Objet *objet, double *poidMax,int *nbObjets);
void calculRate(Objet *objet, int nbObjets);
void afficheDonnees(Objet *objet,int nbObjets);
void quickSort(Objet *objet,int nbObjets);
void trieABulles(Objet *objet, int nbObjets);



#endif  
