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

void lectureFichier(Objet *objet, double *poidMax,int *nbline)
{
	
	FILE *fichier = NULL;
	fichier = fopen("sac.txt","r+");
	char tmp[SIZE];
	
	if (fichier == NULL)
	{
		perror("fopen");
		exit(1);
	}
	
	int currentChar = 0;
	int indice = 0;
	int colonne = 0;
	int line = 0;
	double number = 0;
	
	fgets(tmp,LINE,fichier);
	*poidMax = strtod(tmp,NULL);


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
	*nbline = line;
	//printf("voici le poids maximal %f\n",poidMaximal);
	int i=0;
	for(i=0;i<line;i++)
	{
		printf("val : %f  poids : %f\n",objet[i].valeur,objet[i].poids);
	}
}

int main(int argc, char * argv[])
{
	Objet objet[SIZE];
	double poidMax = 0;
	int nbligne = 0;
	
	lectureFichier(objet,&poidMax,&nbligne);
	
	
	
	return 0;
}
