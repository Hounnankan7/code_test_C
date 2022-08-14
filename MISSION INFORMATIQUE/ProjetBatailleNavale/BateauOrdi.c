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

void VerifOrdi(char Gril[MAX][MAX], Bateau Bat[MAX],int c,int N)
{
    int i=0,j=0,k=0;/*compteur pour ligne,colonne,intermediaire*/

    switch(c)
    {
    case 0: //porte-avion
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<4; j++)
            {
            while(Gril[i][k]!='0'){
            Bat[N].x=rand()%(7-1)+1;
            Bat[N].y=rand()%(7-1)+1;
            i=Bat[N].x;
            k=Bat[N].y;
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
                while(Gril[k][j]!='0'){
            Bat[N].x=rand()%(7-1)+1;
            Bat[N].y=rand()%(7-1)+1;
            j=Bat[N].y;
            k=Bat[N].x;
                }
                k++;
            }
        }
        break;

    case 1:
        if(Bat[N].sens==1)
        {
            i=Bat[N].x;
            k=Bat[N].y;
            for(j=0; j<3; j++)
            {
                while(Gril[i][k]!='0'){
            Bat[N].x=rand()%(7-1)+1;
            Bat[N].y=rand()%(7-1)+1;
             i=Bat[N].x;
            k=Bat[N].y;
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
                while(Gril[k][j]!='0'){
            Bat[N].x=rand()%(7-1)+1;
            Bat[N].y=rand()%(7-1)+1;
            j=Bat[N].y;
            k=Bat[N].x;
                }
                k++;
            }
        }
        break;

    case 2:
        i=Bat[N].x;
        j=Bat[N].y;
        while(Gril[i][j]!='0')
        {
            Bat[N].x=rand()%(10-1)+1;
            Bat[N].y=rand()%(10-1)+1;
            i=Bat[N].x;
            j=Bat[N].y;
        }
        break;
    }

}

//DEBUT CODAGE NAVIRE DE L'ORDINATEUR
void CodBatoOrdi(char GrilOrdi[MAX][MAX],int TGril)
  {
   int t=0;  /*taille limite de generation des cordonnees*/
   int c=0;  /*choix aléatoire du type de bateau a placer*/
   Bateau BOrdi[MAX];  /*Tableau des bateau de l'ordinateur*/
   int i=0,j=0,w=0;    /*indice ligne, indice colonne dans la grille de l'ordi et indice type de bateau*/
   int v=0;            //indice boucle for pour les trois bateaux

     srand(time(NULL));
     for(v=1;v<=3;v++)
     {
    c=v-1;
      switch(c)
      {
      case 0://porte avion
       t=TGril-3;
       BOrdi[w].x=rand()%(t-1)+1;//GENERATION ALEATOIRE DES COORDONNEES AVEC VERIF SORTI DU TABLEAU
       BOrdi[w].y=rand()%(t-1)+1;
       BOrdi[w].sens=rand()%2;//generation aleatoire de sens 0: horizontal et 1:vertical
       VerifOrdi(GrilOrdi,BOrdi,c,w);
       switch(BOrdi[w].sens)
       {
       case 0:
        i=BOrdi[w].x;
        for(j=BOrdi[w].y;j<=BOrdi[w].y+3;j++){GrilOrdi[i][j]='P';}
       break;
       case 1:
       j=BOrdi[w].y;
       for(i=BOrdi[w].x;i<=BOrdi[w].x+3;i++){GrilOrdi[i][j]='P';}
       break;
       }
      break;
     case 1://les deux torpilleurs
     for(w=1;w<=2;w++)
     {
       t=TGril-2;
       BOrdi[w].x=rand()%(t-1)+1;//GENERATION ALEATOIRE DES COORDONNEES AVEC VERIF SORTI DU TABLEAU
       BOrdi[w].y=rand()%(t-1)+1;
       BOrdi[w].sens=rand()%2;
       VerifOrdi(GrilOrdi,BOrdi,c,w);
       switch(BOrdi[w].sens)
       {
       case 0:
        i=BOrdi[w].x;
        for(j=BOrdi[w].y;j<=BOrdi[w].y+2;j++){GrilOrdi[i][j]='T';}
       break;
       case 1:
       j=BOrdi[w].y;
       for(i=BOrdi[w].x;i<=BOrdi[w].x+2;i++){GrilOrdi[i][j]='T';}
       break;
       }
     }
    break;

     case 2://les trois sous-marins
     for(w=3;w<=5;w++)
       {
      t=TGril;
      BOrdi[w].x=rand()%(t-1)+1;//GENERATION ALEATOIRE DES COORDONNEES AVEC VERIF SORTI DU TABLEAU
      BOrdi[w].y=rand()%(t-1)+1;
      VerifOrdi(GrilOrdi,BOrdi,c,w);
      i=BOrdi[w].x;
      j=BOrdi[w].y;
      GrilOrdi[i][j]='S';
       }
      break;
      }
     }

  }//FIN FONCTION CODAGE NAVIRE ORDINATEUR

