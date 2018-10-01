#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "branchAndBound.h"
#include "lecture.h"

void lectureFichier(Objet *objet, double *poidMax)
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
		
	fclose(fichier);
}

int getObjectNumber()
{
	FILE *fichier = NULL;
	fichier = fopen("sac.txt","r+");
	
	if (fichier == NULL)
	{
		perror("fopen");
		exit(1);
	}
	int currentChar=0;
	int nbLigne=0;
	while((currentChar = fgetc(fichier)) != EOF)
	{
		if(currentChar == '\n')
			nbLigne++;
	}
	
	fclose(fichier);
	
	return nbLigne-1;
}

int main()
{
	
	Arbre collectionObjet;
	
	double poidMax = 0;
	int nbObjets = getObjectNumber();
	
	//==Allocation Dynamique==
	
	Objet *objet =NULL;
	objet = malloc(nbObjets * sizeof(Objet));
	if(objet == NULL)
		exit(0);
		
	//========================
	
	lectureFichier(objet,&poidMax);

	calculRate(objet,nbObjets);
	
	trieABulles(objet,nbObjets);
	
	afficheDonnees(objet,nbObjets);
	
	branchAndBound(collectionObjet, objet, nbObjets,poidMax);
	
	printf("Voici le poids max d'objet que l'on peu prendre : %f\n",poidMax);
	
	printf("Voici le nombre d'objet %d\n",nbObjets);

	return 0;
}
