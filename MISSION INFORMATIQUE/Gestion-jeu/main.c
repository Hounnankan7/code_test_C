#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 500
#define TPlato 10

typedef struct
{
    int sens;/*1 horizontal et 2 vertical*/
    int x;/*ligne*/
    int y;/*colonne*/
} Bateau;
typedef struct
{
    int l;//ligne
    int c;//colonne
} Case;

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
}

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
}

void VerifOrdi(char Gril[MAX][MAX], Bateau Bat[MAX],int c,int N)/*pas la vrai*/
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
                while(Gril[i][k]!='0')
                {
                    Bat[N].x=rand()%(7-1)+1;
                    Bat[N].y=rand()%(7-1)+1;
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
                while(Gril[k][j]!='0')
                {
                    Bat[N].x=rand()%(7-1)+1;
                    Bat[N].y=rand()%(7-1)+1;
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
                while(Gril[i][k]!='0')
                {
                    Bat[N].x=rand()%(7-1)+1;
                    Bat[N].y=rand()%(7-1)+1;
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
                while(Gril[k][j]!='0')
                {
                    Bat[N].x=rand()%(7-1)+1;
                    Bat[N].y=rand()%(7-1)+1;
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
    for(v=1; v<=3; v++)
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
                for(j=BOrdi[w].y; j<=BOrdi[w].y+3; j++)
                {
                    GrilOrdi[i][j]='P';
                }
                break;
            case 1:
                j=BOrdi[w].y;
                for(i=BOrdi[w].x; i<=BOrdi[w].x+3; i++)
                {
                    GrilOrdi[i][j]='P';
                }
                break;
            }
            break;
        case 1://les deux torpilleurs
            for(w=1; w<=2; w++)
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
                    for(j=BOrdi[w].y; j<=BOrdi[w].y+2; j++)
                    {
                        GrilOrdi[i][j]='T';
                    }
                    break;
                case 1:
                    j=BOrdi[w].y;
                    for(i=BOrdi[w].x; i<=BOrdi[w].x+2; i++)
                    {
                        GrilOrdi[i][j]='T';
                    }
                    break;
                }
            }
            break;

        case 2://les trois sous-marins
            for(w=3; w<=5; w++)
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
            TabVide[i][j]='D';
            (*N)++;
            system("pause");
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
                system("cls");
            }
            else
            {
                printf("Desole A l'eau\nVous perdez la main\n");
                b=2;
                system("cls");
            }
            CJ[*N].l=i;
            CJ[*N].c=j;
            TabVide[i][j]='D';
            (*N)++;
            system("pause");
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

int main()
{
    Case CoupJoue[MAX],CoupJoueO[MAX];  /*Tableau des coups deja joué par le joueur*/
    int Nmbr=0,NmbrO=0;           /*Compter le nombre de coup joué*/
    char PlatoOrdi[MAX][MAX],PlatoJeu[MAX][MAX],PlatoVide[MAX][MAX];
    int i=0,j=0,nul=0,nulO=0;/*nul est le compteur de cases qui ne sont pas des parties d'un bateau*/

    InitGril(PlatoOrdi,TPlato);
    CodBatoOrdi(PlatoOrdi,TPlato);
    InitGril(PlatoJeu,TPlato);
    CodBatoOrdi(PlatoJeu,TPlato);
        do{
        printf("Le joueur commence\n");
        AttaqJoueur(PlatoOrdi,PlatoVide,TPlato,CoupJoue,&Nmbr);
        for(i=1; i<TPlato; i++)
        {
            for(j=1; j<TPlato; j++)
            {
                if(PlatoOrdi[i][j]=='X')
                {
                    nul++;
                }
            }
        }
        if(nul==0)
        {
            printf("Vous n'avez encore touche aucun bateau\n");
        }
        else
        {
            printf("vous avez touch %d case(s) de bateau\n Il vous reste donc %d cases a atteindre\n",nul,13-nul);
        }

        printf(" A L'ordinateur\n");
        AttaqOrdi(PlatoJeu,TPlato,CoupJoueO,&NmbrO);
        for(i=1; i<TPlato; i++)
        {
            for(j=1; j<TPlato; j++)
            {
                if(PlatoJeu[i][j]=='X')
                {
                    nulO++;
                }
            }
        }
        if(nulO==0)
        {
            printf("L'Ordinateur n'a encore touche aucun bateau\n");
        }
        else
        {
            printf("L'ordinateur a touche %d case(s) de votre flotte\n Il vous reste donc %d cases a proteger\n",nulO,13-nulO);
        }
        }while(nul!=13 || nulO!=13);
        if(nul==13)
        {
            printf("Victoire\nVous avez abattu tous les bateaux de l'ordinateur\n");
        }
        else if(nulO==13)
        {
            printf("Defaite\nL'ordinateur a abattu votre flotte\n");
        }
    return 0;
}
