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


void AttaqJoueur(char GrilOrdi[MAX][MAX],char TabVide[MAX][MAX],int TGril,Case CJ[MAX],int *N)
{
    Case Coup;
    int k=0;   /*indice de coup joué*/
    int i=0,j=0;   /*indice ligne et colonne de grille*/
    int b=1;      /*indice pour savoir si le joueur garde la main, 1: garde la main,2=passe son tour*/

    while(b==1)
    {
        if(*N==0)
        {
            InitGril(TabVide,TGril);
        }
        AffichGril(TabVide,TGril);
        printf("Entrer une coordonnee d'attaque\nEntrer ligne:\n");
        scanf("%d",&Coup.l);
        printf("Entrer colonne\n");
        scanf("%d",&Coup.c);

        if(*N==0)
        {
            i=Coup.l;
            j=Coup.c;
            if(GrilOrdi[i][j]!='0')/*test si une partie d'un bateau est atteinte*/
            {
                printf("Touche\n");
                b=1;
                GrilOrdi[i][j]='X';
                TabVide[i][j]='X';
            }
            else
            {
                printf("Desole A l'eau\nVous perdez la main\n");
                b=2;
            }
            CJ[*N].l=i;
            CJ[*N].c=j;
            (*N)++;
            system("pause");
            system("cls");
        }
        else
        {
            /*Test si coordonnee deja joué*/
            for(k=0; k<=*N; k++)
            {
                while(CJ[k].c==Coup.c && CJ[k].l==Coup.l)
                {
                    printf("Vous avez deja joue ces cordonnees.Veuillez changer\n");
                    printf("Entrer une autre coordonnee d'attaque\nEntrer ligne:\n");
                    scanf("%d",&Coup.l);
                    printf("Entrer colonne\n");
                    scanf("%d",&Coup.c);
                }
            }
            i=Coup.l;
            j=Coup.c;
            if(GrilOrdi[i][j]!='0')/*test si une partie d'un bateau est atteinte*/
            {
                printf("Touche\n");
                b=1;
                GrilOrdi[i][j]='X';
                TabVide[i][j]='X';
            }
            else
            {
                printf("Desole A l'eau\nVous perdez la main\n");
                b=2;
            }
            CJ[*N].l=i;
            CJ[*N].c=j;
            (*N)++;
            system("pause");
            system("cls");
        }
    }
}

void AttaqOrdi(char Gril[MAX][MAX],int TGril,Case CJOrdi[MAX],int *NO)
{

    srand(time(NULL));
    Case CoupOrdi;
    int k=0;     /*indice de coup joué*/
    int i=0,j=0;   /*indice ligne et colonne de grille*/
    int b=1;      /*indice pour savoir si le joueur garde la main01: garde la main,2=passe son tour*/
    while(b==1)
    {
        printf("-------Votre flotte-------\n");
        AffichGril(Gril,TGril);
        CoupOrdi.l=rand()%(TGril-1)+1;
        CoupOrdi.c=rand()%(TGril-1)+1;

        if(*NO==0)
        {
            i=CoupOrdi.l;
            j=CoupOrdi.c;
            if(Gril[i][j]!='0')/*test si une partie d'un bateau est atteinte*/
            {
                printf(" L'ordinateur a touche la case %d %d \n",i,j);
                b=1;
                Gril[i][j]='X';
            }
            else
            {
                printf("L'ordinateur a tire a l'eau\nA vous de jouer\n");
                b=2;
            }
            CJOrdi[*NO].l=CoupOrdi.l;
            CJOrdi[*NO].c=CoupOrdi.c;
            (*NO)++;
            system("pause");
        }
        else
        {
            /*Test si coordonnee deja joué*/
            for(k=0; k<=*NO; k++)
            {
                while(CJOrdi[k].c==CoupOrdi.c && CJOrdi[k].l==CoupOrdi.l)
                {
                    CoupOrdi.l=rand()%(TGril-1)+1;
                    CoupOrdi.c=rand()%(TGril-1)+1;
                }
            }
            i=CoupOrdi.l;
            j=CoupOrdi.c;
            if(Gril[i][j]!='0')/*test si une partie d'un bateau est atteinte*/
            {
                printf(" L'ordinateur a touche la case %d %d \n",i,j);
                b=1;
                Gril[i][j]='X';
            }
            else
            {
                printf("L'ordinateur a tire a l'eau\nA vous de jouer\n");
                b=2;
            }
            CJOrdi[*NO].l=CoupOrdi.l;
            CJOrdi[*NO].c=CoupOrdi.c;
            (*NO)++;
            system("pause");
        }
    }
}
