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

void quickSort(Objet *objet,int nbObjets)
{
	
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
	printf("il y a %d coup pour trier le tableau",count);
}

int main(int argc, char * argv[])
{
	Objet objet[SIZE];
	double poidMax = 0;
	int nbObjets = 0;
	
	lectureFichier(objet,&poidMax,&nbObjets);
	
	calculRate(objet,nbObjets);
	
	afficheDonnees(objet,nbObjets);
	
	trieABulles(objet,nbObjets);
	afficheDonnees(objet,nbObjets);
	printf("Voici le poids max : %f\n",poidMax);
	printf("Voici le nombre d'objet %d\n",nbObjets);

	return 0;
}
