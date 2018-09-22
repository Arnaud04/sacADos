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

void afficheDonnees(Objet *objet,int nbObjets)
{
	int i=0;
	
	for(i=0; i<nbObjets; i++)
	{
		printf("val : %f  poids : %f\n",objet[i].valeur,objet[i].poids);
	}
}

int main(int argc, char * argv[])
{
	Objet objet[SIZE];
	double poidMax = 0;
	int nbObjets = 0;
	
	lectureFichier(objet,&poidMax,&nbObjets);
	
	afficheDonnees(objet,nbObjets);
	
	printf("Voici le poids max : %f\n",poidMax);
	printf("Voici le nombre d'objet %d\n",nbObjets);

	return 0;
}
