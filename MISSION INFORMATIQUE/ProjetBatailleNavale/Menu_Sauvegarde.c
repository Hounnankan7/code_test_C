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

int Menu()
{
    int choix;
    printf("-----------------------MENU PRINCIPAL----------------------------\n");
    printf("    1.Jouer\n    2.A propos\n    3.Quitter\n");
    scanf("%d",&choix);

   return choix;
}
void SaveScore(int *e,int *f)
{
FILE *fichier;

fichier=fopen("Score.txt","a");
if(fichier==NULL)
{
    printf("erreur de sauvegarde\nReessayer\n");
}
else
{
    fprintf(fichier,">>Score Duel %d<<\n",*e);
    if(*f==13)
    {
        fprintf(fichier,"Victoire. Les %d bateaux ont ete detruits\n\n",*f);
    }
    else
    {
      fprintf(fichier,"Defaite\n Vous avez abbatu seulement %d cases de bateaux\n\n",*f);
    }
    (*e)++;
}
fclose(fichier);
}
