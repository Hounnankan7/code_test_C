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

/*Enregistrer un bateau en fonction des preferences et le retourner*/
Bateau SaveBato(int c)/*prendre la disposition choisi par le joueur pour un bateau*/
{
    Bateau Bat[MAX];

    if(c==3)
    {
        printf("Coordonnnes de la premiere case du bateau (chiffre-chiffre)\nEntrer la ligne:\n");
        scanf("%d",&Bat[c].x);
        printf("entrer la colonne:\n");
        scanf("%d",&Bat[c].y);
        while(Bat[c].x==0 ||  Bat[c].y==0)
        {
            printf("Aucun zero admis.reprenez\n");
            printf("Entrer la ligne:\n");
            scanf("%d",&Bat[c].x);
            printf("entrer la colonne:\n");
            scanf("%d",&Bat[c].y);
        }
        printf("Pas besoin de sens pour ce cas\n");
    }
    else
    {
        printf("Donner les coordonnnes de la premiere case du bateau a placer de la forme (chiffre-chiffre)\nEntrer la ligne:\n");
        scanf("%d",&Bat[c].x);
        printf("entrer la colonne:\n");
        scanf("%d",&Bat[c].y);
        while(Bat[c].x==0 ||  Bat[c].y==0)
        {
            printf("Aucun zero admis.reprenez\n");
            printf("Entrer la ligne:\n");
            scanf("%d",&Bat[c].x);
            printf("entrer la colonne:\n");
            scanf("%d",&Bat[c].y);
        }
        printf("Enfin preciser le sens dans lequel oriente le bateau\nChoisir un numero(1.horizontal,2.vertical)\n");
        scanf("%d",&Bat[c].sens);

        while(Bat[c].sens!=1 && Bat[c].sens!=2)
        {
            printf("Erreur vous n'avez pas entrer le bon numero\n");
            scanf("%d",&Bat[c].sens);
        }

    }


    return Bat[c];
}

void Verif1Bato(Bateau Bat[MAX],int TGril,int c,int N)/*tester si le bateau peut rester dans limites de la grille*/
{
    int t=0;/*compteur pour ligne,colonne,intermediaire,taille pour le test*/

    switch(c)
    {
    case 1:
        t=TGril-3;
        if(Bat[N].sens==1)
        {
            while(Bat[N].y>t)/*test bateau 0(porte-avion) peut rester sur l'horizontal*/
            {
                printf("votre porte-avion ne reste pas dans les limites du plateau\n");
                printf("Entrer une autre ligne\n");
                scanf("%d",&Bat[N].x);
                printf("Entrer une autre colonne\n");
                scanf("%d",&Bat[N].y);
            }
        }
        else
        {
            while(Bat[N].x>t)/*test bateau 0(porte-avion) peut rester sur la vertical*/
            {
                printf("votre porte-avion ne reste pas dans les limites du plateau\n");
                printf("Entrer une autre ligne\n");
                scanf("%d",&Bat[N].x);
                printf("Entrer une autre colonne\n");
                scanf("%d",&Bat[N].y);
            }
        }
        break;

    case 2:
        t=TGril-2;
        if(Bat[N].sens==1)
        {
            while(Bat[N].y>t)
            {
                printf("ce torpilleur ne reste pas dans les limites du plateau\n");
                printf("Entrer une autre ligne\n");
                scanf("%d",&Bat[N].x);
                printf("Entrer une autre colonne\n");
                scanf("%d",&Bat[N].y);
            }
        }
        else
        {
            while(Bat[N].x>t)
            {
                printf("ce torpilleur ne reste pas dans les limites du plateau\n");
                printf("Entrer une autre ligne\n");
                scanf("%d",&Bat[N].x);
                printf("Entrer une autre colonne\n");
                scanf("%d",&Bat[N].y);
            }
        }
        break;

    case 3:
        t=TGril;
        while(Bat[N].x>t || Bat[N].y>t)
        {
            printf("Coordonne hors du plateau\n");
            printf("Entrer une autre ligne\n");
            scanf("%d",&Bat[N].x);
            printf("Entrer une autre colonne\n");
            scanf("%d",&Bat[N].y);
        }
        break;
    }
}

void Verif2Bato(char Gril[MAX][MAX], Bateau Bat[MAX],int c,int N)
{
    int i=0,j=0,k=0;/*compteur pour ligne,colonne,intermediaire*/

    switch(c)
    {
    case 1: //porte-avion
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<4; j++)
            {
            if(i==TPlato){while(Gril[i][k]!='0' || Gril[i][k+1]!='0'  || Gril[i-1][k]!='0')
                {
                    printf("Le porte avion ne pourra etre place dans ces conditions\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    i=Bat[N].x;
                    k=Bat[N].y;
                }}
            else{
                /*une boucle pour verifier que la case et les cases autour ne sont pas occupee*/
                while(Gril[i][k]!='0' || Gril[i][k+1]!='0'  || Gril[i+1][k]!='0')
                {
                    printf("Le porte avion ne pourra etre place dans ces conditions\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    i=Bat[N].x;
                    k=Bat[N].y;
                }
                }
                k++;
            }
        }
        else
        {
            j=Bat[N].y;
            k=Bat[N].x;
            for(i=0; i<4; i++)
            {
                if(j==TPlato){
                while(Gril[k][j]!='0' || Gril[k][j-1]!='0' || Gril[k+1][j]!='0')
                {
                    printf("Le porte avion ne pourra etre place\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    j=Bat[N].y;
                    k=Bat[N].x;
                }
                }
                else{
                 while(Gril[k][j]!='0' || Gril[k][j+1]!='0' || Gril[k+1][j]!='0')
                {
                    printf("Le porte avion ne pourra etre place\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    j=Bat[N].y;
                    k=Bat[N].x;
                }
                }
                k++;
            }
        }
        break;

    case 2:
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<3; j++)
            {
                if(i==TPlato){while(Gril[i][k]!='0' || Gril[i][k+1]!='0'  || Gril[i-1][k]!='0')
                {
                    printf("Le porte avion ne pourra etre place dans ces conditions\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    i=Bat[N].x;
                    k=Bat[N].y;
                }}
            else{
                /*une boucle pour verifier que la case et les cases autour ne sont pas occupee*/
                while(Gril[i][k]!='0' || Gril[i][k+1]!='0'  || Gril[i+1][k]!='0')
                {
                    printf("Le porte avion ne pourra etre place dans ces conditions\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    i=Bat[N].x;
                    k=Bat[N].y;
                }
                }
                k++;
            }
        }
        else
        {
            j=Bat[N].y;
            k=Bat[N].x;
            for(i=0; i<3; i++)
            {
                if(j==TPlato){
                while(Gril[k][j]!='0' || Gril[k][j-1]!='0' || Gril[k+1][j]!='0')
                {
                    printf("Le porte avion ne pourra etre place\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    j=Bat[N].y;
                    k=Bat[N].x;
                }
                }
                else{
                 while(Gril[k][j]!='0' || Gril[k][j+1]!='0' || Gril[k+1][j]!='0')
                {
                    printf("Le porte avion ne pourra etre place\nChanger de coordonee\n");
                    printf("Entrer une autre ligne\n");
                    scanf("%d",&Bat[N].x);
                    printf("Entrer une autre colonne\n");
                    scanf("%d",&Bat[N].y);
                    j=Bat[N].y;
                    k=Bat[N].x;
                }
                }
                k++;
            }
        }
        break;

    case 3:
        i=Bat[N].x;
        j=Bat[N].y;
        if(i==1 || j==1){
        while(Gril[i][j]!='0' || Gril[i][j+1]!='0' || Gril[i+1][j]!='0')
        {
            printf("Le sous marin ne pourra etre place dans ces conditions\nChanger de coordonee\n");
            printf("Entrer une autre ligne\n");
            scanf("%d",&Bat[N].x);
            printf("Entrer une autre colonne\n");
            scanf("%d",&Bat[N].y);
            i=Bat[N].x;
            j=Bat[N].y;
        }
        }
        else if(i==TPlato || j==TPlato){
         while(Gril[i][j]!='0' || Gril[i][j-1]!='0' || Gril[i-1][j]!='0')
        {
            printf("Le sous marin ne pourra etre place dans ces conditions\nChanger de coordonee\n");
            printf("Entrer une autre ligne\n");
            scanf("%d",&Bat[N].x);
            printf("Entrer une autre colonne\n");
            scanf("%d",&Bat[N].y);
        i=Bat[N].x;
        j=Bat[N].y;
        }
        }
        else{
          while(Gril[i][j]!='0' || Gril[i][j+1]!='0' || Gril[i][j-1]!='0' || Gril[i+1][j]!='0' || Gril[i-1][j]!='0')
        {
            printf("Le sous marin ne pourra etre place dans ces conditions\nChanger de coordonee\n");
            printf("Entrer une autre ligne\n");
            scanf("%d",&Bat[N].x);
            printf("Entrer une autre colonne\n");
            scanf("%d",&Bat[N].y);
            i=Bat[N].x;
            j=Bat[N].y;
        }
        }
        break;
    }

}

/*Placer un bateau en fonction des preferences du joueur et en testant si le placement est possible*/
void PlacerBato(char Gril[MAX][MAX], Bateau Bat[MAX],int TGril,int c,int N)/* N: numero de bateau*/
{
    int i=0,j=0,k=0;/*compteur pour ligne,colonne,intermediaire*/

    switch(c)
    {
    case 1:
        /*placer P dans les cases pour les porte-avion suivants le sens*/
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<4; j++)
            {
                Gril[i][k]='P';
                k++;
            }
        }
        else
        {
            j=Bat[N].y;
            k=Bat[N].x;
            for(i=0; i<4; i++)
            {
                Gril[k][j]='P';
                k++;
            }
        }
        break;
    /*fin placement porte avion*/

    case 2:
        /*placer T dans les cases pour les torpilleurs selon le sens*/
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<3; j++)
            {
                Gril[i][k]='T';
                k++;
            }
        }

        else
        {
            j=Bat[N].y;
            k=Bat[N].x;
            for(i=0; i<3; i++)
            {
                Gril[k][j]='T';
                k++;
            }
        }
        break;
    /*fin placement torpilleur*/

    case 3:
        /*mettre S pour reconnaitre les sous-marins*/
        i=Bat[N].x;
        j=Bat[N].y;
        Gril[i][j]='S';
        break;
        /*fin placement sous-marin*/
    }
}

