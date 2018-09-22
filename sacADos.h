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

void lectureFichier();

#endif  
