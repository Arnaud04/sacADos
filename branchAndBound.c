#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "branchAndBound.h"

int isPair(int number)
{
	int resultat=0;
	
	if(number % 2 == 0) 
		resultat = 1;
	else
		resultat = 0; 
	return resultat; //1 si il est pair 0 sinon 
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

void swap(Objet *obj1, Objet *obj2)
{
		Objet tmp;
		tmp = *obj1;
		*obj1 = *obj2;
		*obj2 = tmp;

}

void trieABulles(Objet *objet, int nbObjets)
{
	int i,j,k=nbObjets-1;
	
	for(i=0; i<nbObjets-1; i++)
	{
		for(j=0; j<k; j++)
		{
			if(objet[j].ratios > objet[j+1].ratios)
				swap(&objet[j],&objet[j+1]);	
		}	
		k--;
	}

}

void initialiserTableau(Arbre *collectionObjet, int nbObjets)
{
	int i=0;
	
	for(i=0; i<nbObjets; i++)
	{
		collectionObjet->choix[i] = 0;
		collectionObjet->visite[i] = 0;
	}
}


void arrayCpy(Arbre *obj1,int size)
{
	int i=0;

	for(i = 0; i <size; i++)
	{
		obj1->choix[i] = obj1->visite[i];
		
		printf("%d ",obj1->choix[i]);
	}
}

int power(int number, int power)
{
	int resultat = number;
	int i=0;
	
	if(power == 0)
		resultat = 1;
	else
	{
		for(i=0;i<power-1;i++)
			resultat = resultat * number;
	}
	return resultat;
}

void descenteArbre(int fg,int fd,int side, Arbre *collectionObjet, double nbObjets,double *SommePoids,int *j,double poidMax)
{
	int end = 0;
	
	//desecente fils gauche
	if(side == 0)
	{
			
			if((fg) > nbObjets-1) //si on est au niveau des fils
				end = 1;
			if((collectionObjet->visite[*j] == 1) && (end != 1))
			{
				
				*SommePoids += collectionObjet->noeud[*j].poids;
	
				if(*SommePoids <= poidMax) 
				{
					*j = collectionObjet->filsGauche; //on met a jour l'indice j
					collectionObjet->visite[fg] = 1;
					
				}

			}

	}
	//Descente fils droit 
	else
	{
		if(fd > nbObjets-1) //si on est au niveau des feuille (fin de l'arbre)
				end = 1;
			if((collectionObjet->visite[*j] == 1) && (end != 1))
			{
				
				*SommePoids += collectionObjet->noeud[*j].poids;
	
				if(*SommePoids <= poidMax) 
				{
					*j = collectionObjet->filsDroit;
					collectionObjet->visite[fd] = 1;
				}

			}

	}

}

void remonteeArbre(Arbre *collectionObjet,double *SommePoids,int *j)
{

		collectionObjet->visite[*j] = 2; //on supprime le fils courant
		if(isPair(*j) == 0) //si fils gauche
			*j = (*j/2);
		else
			*j = ((*j/2) -1);
		*SommePoids -= collectionObjet->noeud[*j].poids;
}

void afficheObjet(Arbre *collectionObjet, int nbObjets)
{
	int i=0;
	
	printf("liste d'objet saisie\n");
	for(i=0;i<nbObjets;i++)
	{
		if(collectionObjet->choix[i] == 1)
			printf("objet %d -> poids %f",i,collectionObjet->noeud[i].poids);
	}
	
}

void branchAndBound(Arbre collectionObjet, Objet *objet,int nbObjets,double poidMax)
{
	int i,j=0;
	int fils = 0; //0 left 1 right
	double SommePoids = 0;
	//copie du tableau d'objet dans le tableau de noeud de ma collection d'objet
	for(i=0;i<nbObjets; i++) 
		collectionObjet.noeud[i] = objet[i];
		
	//initialiserTableau a 0 les tableaux choix et visite
	initialiserTableau(&collectionObjet,nbObjets);

	//on met la première case à 1 pour pouvoir commencer l'ago ajouter teste poid
	collectionObjet.visite[0] = 1;
	
	fils = 0; 
	//SommePoids = collectionObjet.noeud[0].poids;
	double tmpPoids = 0;
	
	//======================================== Algo Branch and bound =========================================
	while(collectionObjet.visite[0]!=2)
	{
		collectionObjet.filsDroit = 2*j+2;
		collectionObjet.filsGauche = 2*j+1;
		
		//savoir quel coté de l'arbre empréter pour descendre
		if((collectionObjet.visite[collectionObjet.filsGauche]==2) && (collectionObjet.visite[collectionObjet.filsDroit] !=2))
			fils = 1;
		if((collectionObjet.visite[collectionObjet.filsGauche]!=2) && (collectionObjet.visite[collectionObjet.filsDroit] ==2))
			fils = 0;

	
		if(((collectionObjet.visite[collectionObjet.filsGauche] != 2)||(collectionObjet.visite[collectionObjet.filsDroit] != 2))&&((collectionObjet.filsGauche)<=nbObjets-1))
		{
			descenteArbre(collectionObjet.filsGauche,collectionObjet.filsDroit,fils,&collectionObjet,nbObjets,&SommePoids,&j,poidMax);
			//tmpPoids = collectionObjet.noeud[j].poids;


		}

		//si on est au niveau des feuille ou que les fils on déja été visité alors on remonte
		if(((collectionObjet.visite[collectionObjet.filsGauche] == 2)&&(collectionObjet.visite[collectionObjet.filsDroit] == 2))||((collectionObjet.filsGauche)>=nbObjets-1))
		{
			if((SommePoids+collectionObjet.noeud[j].poids) > (tmpPoids))
			{
				tmpPoids = SommePoids+collectionObjet.noeud[j].poids;
				arrayCpy(&collectionObjet,nbObjets);
			}
			remonteeArbre(&collectionObjet,&SommePoids,&j);

		}
		printf("La somme des poids est %f\n",SommePoids+collectionObjet.noeud[j].poids);			
	}
	
	afficheObjet(&collectionObjet,nbObjets);
	printf("Le poids max d'objet que nous avons saisie est :  %f\n",tmpPoids);
	//=========================================Fin algo ==========================================

}

