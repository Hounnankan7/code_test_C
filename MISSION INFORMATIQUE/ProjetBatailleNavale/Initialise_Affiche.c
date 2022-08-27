#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 500
#define TPlato 6
#include "structure.h"
#include "Menu&Sauvegarde.h"
#include "Initialise&Affiche.h"
#include "BateauJoueur.h"
#include "BateauOrdi.h"
#include "Attaque.h"

//initialisation d'une grille
void InitGril(char Gril[MAX][MAX],int TGril)
{
    int i=0,j=0;/*i:compteur ligne et j:compteur colonne*/

    /*initialisation*/
    for(i=1; i<=TGril; i++)
    {
        for(j=1; j<=TGril; j++)
        {
            Gril[i][j]='0';
        }
    }
}//fin fonction d'initialisation

//fonction d'affichage d'une grille
void AffichGril(char Gril[MAX][MAX],int TGril)/*initialiser et presenter le plateau sans bateau*/
{
    int i=0,j=0;/*i:compteur ligne et j:compteur colonne*/
    /*affichage*/
    printf("  ");
    for(j=1; j<=TGril; j++)
    {
        printf(" ");
        printf("%7d ",j);
    }
    printf("\n\n");
    for(i=1; i<=TGril; i++)
    {
        printf("%d",i);
        if(i<10)
        {
            printf(" ");
        }

        for(j=1; j<=TGril; j++)
        {
            printf(" ");
            printf("%7c ",Gril[i][j]);

        }
        printf("\n\n");
    }
}// fin fonction d'affichage d'une grille
