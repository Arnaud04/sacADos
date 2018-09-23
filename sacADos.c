#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sacADos.h"

int isPair(int number)
{
	int resultat=0;
	
	if(number % 2 == 0) 
		resultat = 1;
	else
		resultat = 0; 
	return resultat; //1 si il est pair 0 sinon 
}

void lectureFichier(Objet *objet, double *poidMax,int *nbObjets)
{
	
	FILE *fichier = NULL;
	fichier = fopen("sac.txt","r+");
	
	if (fichier == NULL)
	{
		perror("fopen");
		exit(1);
	}
	
	char tmp[SIZE];
	fgets(tmp,LINE,fichier);
	*poidMax = strtod(tmp,NULL);
	
	int currentChar = 0;
	
	int indice = 0;
	double number = 0;
	int colonne = 0;
	int line = 0;
	
	while(currentChar != EOF)
	{
		currentChar = fgetc(fichier);
		if((currentChar != ' ') && (currentChar != '\n')) //lecture [a-z,A-Z,1-9]
		{
			tmp[indice] = currentChar;
			indice ++;
		}
		
		else 
		{
			tmp[indice] = '\0';
			number = strtod(tmp,NULL);
			
			indice = 0;
			colonne ++;
			
			if(isPair(colonne))
			{
					objet[line].valeur = number;
			}
			else
			{
					objet[line].poids = number;		
			}

			if(currentChar == '\n')
				line ++;
			
		}
	}
		
	*nbObjets = line;
}

void calculRate(Objet *objet, int nbObjets)
{
	int i;
	for(i=0; i<nbObjets; i++)
	{
		objet[i].ratios = (objet[i].poids)/(objet[i].valeur);
	}
}

void afficheDonnees(Objet *objet,int nbObjets)
{
	int i=0;
	
	for(i=0; i<nbObjets; i++)
	{
		printf("objet[%d] => valeur : %f poids : %f, ratio : %f\n",i,objet[i].valeur,objet[i].poids,objet[i].ratios);
	}
	printf("\n");
}

//QuickSort ne fonctionne pas encore
/* 
void quickSort(Objet *objet,int nbObjets)
{
	int mur,courant;
	double pivot;
	Objet tmp;
	
	if(nbObjets < 2)
		return;
	pivot = objet[nbObjets - 1].ratios;
	mur = courant = 0;
	while (courant < nbObjets)
	{
		if(objet[courant].ratios <= pivot)
		{
			if(mur != courant)
			{
				tmp = objet[courant];
				objet[courant] = objet[mur];
				objet[mur] = tmp;
			}
			mur ++;
		}
		courant ++;
	}
	quickSort(objet,mur-1);
	quickSort(objet+mur-1, nbObjets - mur +1);
	
	
}*/ 
void swap(Objet obj1, Objet obj2)
{
		Objet tmp;
		tmp = obj1;
		obj1 = obj2;
		obj2 = tmp;

}
void trieABulles(Objet *objet, int nbObjets)
{
	int i,j,k=nbObjets-1;
	int count =0;
	Objet tmp;
	
	for(i=0; i<nbObjets-1; i++)
	{
		for(j=0; j<k; j++)
		{
			count ++;
			if(objet[j].ratios > objet[j+1].ratios)
			{
				tmp = objet[j];
				objet[j] = objet[j+1];
				objet[j+1] = tmp;
				
			}

		}
		
		k--;
	}
	printf("trie fait en %d cout\n",count);
}

void initialiserTableau(Arbre collectionObjet, int nbObjets)
{
	int i=0;
	
	for(i=0; i<nbObjets; i++)
	{
		collectionObjet.visite[i] = 0;
	}
}

void branchAndBound(Arbre collectionObjet, Objet *objet,int nbObjets,double poidMax)
{
	int i,j;
	int SommePoids = 0;
	for(i=0;i<nbObjets; i++) //copie du tableau d'objet dans le tableau de noeud de ma collection d'objet
		collectionObjet.noeud[i] = objet[i];
		
	initialiserTableau(collectionObjet, nbObjets);
		
	for(j=0;j<nbObjets;j++)
	{
		SommePoids += collectionObjet.noeud[i].poids;
		if(SommePoids < poidMax)
		{
			//collectionObjet.visite[i]
		}
	}
}

int main(int argc, char * argv[])
{
	Objet objet[SIZE];
	Arbre collectionObjet;
	
	double poidMax = 0;
	int nbObjets = 0;
	
	lectureFichier(objet,&poidMax,&nbObjets);
	
	calculRate(objet,nbObjets);
	
	trieABulles(objet,nbObjets);
	afficheDonnees(objet,nbObjets);
	branchAndBound(collectionObjet, objet, nbObjets,poidMax);
	
	printf("Voici le poids max : %f\n",poidMax);
	printf("Voici le nombre d'objet %d\n",nbObjets);

	return 0;
}
