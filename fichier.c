#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "branchAndBound.h"
#include "fichier.h"

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

void lectureFichier(Objet *objet, double *poidMax)
{
	
	FILE *fichier = NULL;
	fichier = fopen("sac.txt","r+");
	
	if (fichier == NULL)
	{
		perror("fopen");
		exit(1);
	}
	
	char tmp[LINE];
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

int main()
{
	
	Arbre collectionObjet;
	
	double poidMax = 0;
	int nbObjets = getObjectNumber();

	printf("Voici le nombre d'objet %d\n",nbObjets);
	
	//====== Allocation Dynamique (récupération du nombre total d'objets à voler) ======
	
	Objet *objet = NULL;
	objet = malloc(nbObjets * sizeof(Objet));
	if(objet == NULL)
		exit(0);
		
	//=========================================================================
	//=======Allocation dynamique de CollectionObjets =========================
	
	collectionObjet.noeud = NULL;
	collectionObjet.noeud = malloc(nbObjets * sizeof(Objet));
	if(collectionObjet.noeud == NULL)
		exit(0);
	//==========================================================================
	//============Allocation dynamique des tableau visite et choix =============
		
	collectionObjet.visite = NULL;
	collectionObjet.visite = malloc(nbObjets * sizeof(int));
	if(collectionObjet.visite == NULL)
		exit(0);
			
	collectionObjet.choix = NULL;
	collectionObjet.choix = malloc(nbObjets * sizeof(int));
	if(collectionObjet.choix == NULL)
		exit(0);
	
	//==========================================================================

	
	
	lectureFichier(objet,&poidMax);
	
	calculRate(objet,nbObjets);
	
	trieABulles(objet,nbObjets);
	
	afficheDonnees(objet,nbObjets);

	branchAndBound(collectionObjet, objet, nbObjets,poidMax);
	
	free(objet);
	
	return 0;
}
