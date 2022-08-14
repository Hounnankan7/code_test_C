#define m 10
#include <stdio.h>
#include <ctype.h>>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <SDL.h>
int bloc=0,choix;



typedef struct
{
    int x;
    int y;
} coord;

typedef struct
{
    coord pos[4];
    int etat[4]; //0 si coulé, 1 si en vie
    int orr;//indique si le bateau est placé horizontalement(2) ou verticalement(1)
} porte_a;


typedef struct
{
    coord pos[1];
    int etat ;//0 si coulé, 1 si en vie
} sous_m;


typedef struct
{
    coord pos[3];
    int etat[3] ;//0 si coulé, 1 si en vie
    int orr;;//indique si le bateau est placé horizontalement(2) ou verticalement(1)
} lance_t;

void init_jeu (sous_m marin[],lance_t torp[],porte_a * avion,int jeu[m][m]);



int verif_case(int x,int y,int jeu[m][m])
{
    int good=1;
    if(x>m-1||y>m-1)
    {
        good=0;
        printf("Vous etes hors grille\n");
    }
    else if(jeu[x][y]==1 || jeu[x][y]==2)
    {
        good=0;
        printf("Vous ne pouvez pas placer un bateau a cet emplacement :-)\n");
    }
    return good;
}

int verif_casee(int x,int y,int jeu[m][m])
{
    int good=1;
    if(x>m-1||y>m-1)
    {
        good=0;
    }
    else if(jeu[x][y]==1 || jeu[x][y]==2)
    {
        good=0;
    }
    return good;
}







void colonne(int n,int jeu[m][m])
{
    int i;

    for (i=0; i<m; i++)
    {
        if(jeu[n][i]==0 || jeu[n][i]==2)
        {
            printf("|   ");
        }
        else if(jeu[n][i]==1)
        {
            printf("| + ");
        }
        else if(jeu[n][i]==3)
        {
            printf("| x ");
        }
        else if(jeu[n][i]==4)
        {
            printf("| o ");
        }
        else if(jeu[n][i]==5)
        {
            printf("| * ");
        }
    }
    printf("|");
}


void ligne ()
{
    int i;
    printf(" |");
    for (i=0; i<m; i++)
    {
        printf("___|");
    }
}



void affiche_grille(int param,int jeu[m][m])
{

    int i,j;
    if(param==0)
    {
        printf("    A   B   C   D   E   F   G   H   I   J \n");
        for (i=0; i<10; i++)
        {
            printf("%2d",i+1);
            colonne(i,jeu);
            printf("\n ");
            ligne();
            printf("\n");
        }
    }
    else
    {
        SDL_Surface *ecran = NULL,*rectangle = NULL;
        SDL_Rect position;
        ecran =SDL_SetVideoMode( 490, 980, 32, SDL_HWSURFACE) ;

        SDL_WM_SetCaption( "Bataille navale", NULL) ;

        SDL_FillRect( ecran, NULL, SDL_MapRGB( ecran->format, 47, 47,47) ) ;
        SDL_Flip( ecran) ;
        rectangle = SDL_CreateRGBSurface( SDL_HWSURFACE, 48, 48, 32, 0,0, 0, 0) ;

        for (i=0; i<10; i++)
        {
            position.y=i*48+1;
            for (j=0; j<m; j++)
            {
                position.x=j*48+1;
                if(jeu[i][j]==0 || jeu[i][j]==2)
                {//
                    SDL_FillRect( rectangle, NULL, SDL_MapRGB( ecran->format, 44, 149, 211) ) ;
                    SDL_BlitSurface( rectangle, NULL, ecran, &position) ;
                      SDL_Flip( ecran);
                }
                else if(jeu[i][j]==1)
                {
                    SDL_FillRect( rectangle, NULL, SDL_MapRGB( ecran->format, 160,80,80) ) ;
                    SDL_BlitSurface( rectangle, NULL, ecran, &position) ;
                    SDL_Flip( ecran);
                }
                else if(jeu[i][j]==3)
                {
                    SDL_FillRect( rectangle, NULL, SDL_MapRGB( ecran->format, 105,184,58) ) ;
                    SDL_BlitSurface( rectangle, NULL, ecran, &position) ;
                    SDL_Flip( ecran);
                }
                else if(jeu[i][j]==4)
                {
                    SDL_FillRect( rectangle, NULL, SDL_MapRGB( ecran->format, 242,0,0) ) ;
                    SDL_BlitSurface( rectangle, NULL, ecran, &position) ;
                    SDL_Flip( ecran);
                }
                else if(jeu[i][j]==5)
                {
                     SDL_FillRect( rectangle, NULL, SDL_MapRGB( ecran->format, 255,128,64) ) ;
                    SDL_BlitSurface( rectangle, NULL, ecran, &position) ;
                    SDL_Flip( ecran);
                }
            }
        }

    SDL_FreeSurface( rectangle) ;

    }
}





void placer_sm(sous_m marin[],int jeu[m][m])
{
    int i,j,a,b,bon=0;
    char c;
    for(i=0; i<3; i++)
    {
        bon=0;
        while(bon==0)
        {
            printf("Veuillez entrer les coordonnees de votre Vedette\n");
            scanf("%d%c",&a,&c);
            b=toascii(c)-64;
            if(verif_case(a-1,b-1,jeu)==1)
            {
                marin[i].pos[0].x=a;
                marin[i].pos[0].y=b;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y-1]=1;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y-2]=2;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y]=2;
                jeu[marin[i].pos[0].x-2][marin[i].pos[0].y-1]=2;
                jeu[marin[i].pos[0].x][marin[i].pos[0].y-1]=2;

                marin[i].pos[0].x=marin[i].pos[0].x-1;
                marin[i].pos[0].y=marin[i].pos[0].y-1;


                affiche_grille(0,jeu);
                bon=1;
            }
        }
    }

}

void placer_lt(lance_t torp[],int jeu[m][m])
{
    int i,j,a,b,bon=0;
    char c;
    for(i=0; i<2; i++)
    {

        bon=0;
        while(bon==0)
        {
            printf("Veuillez entrer les coordonnees de votre Torpilleur\n");
            scanf("%d%c",&a,&c);
            b=toascii(c)-64;
            if(jeu[a-1][b-1]==0)
            {
                bloc=0;

                while(bloc==0)
                {
                    printf("Voulez vous le placer Verticalement ou Horizontalement\n1 - Je le veux vertical\n2- Je le veux horizontal\n");
                    scanf("%d",&choix);
                    if (choix==1)
                    {
                        if (verif_case(a-1,b-1,jeu)==1 && verif_case(a,b-1,jeu)==1 && verif_case(a+1,b-1,jeu)==1)
                        {
                            torp[i].pos[0].x=a;
                            torp[i].pos[0].y=b;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-1]=1;
                            jeu[torp[i].pos[0].x-2][torp[i].pos[0].y-1]=2;
                            torp[i].pos[0].x=torp[i].pos[0].x-1;
                            torp[i].pos[0].y=torp[i].pos[0].y-1;
                            jeu[torp[i].pos[0].x+3][torp[i].pos[0].y]=2;
                            torp[i].orr=choix;
                            for(j=0; j<3; j++)
                            {
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y]=1;
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y-1]=2;
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y+1]=2;
                                torp[i].pos[j].x=torp[i].pos[0].x+j;
                                torp[i].pos[j].y=torp[i].pos[0].y;
                            }
                            bon=1;
                        }
                        bloc=1;

                    }
                    else if (choix==2)
                    {
                        if (verif_case(a-1,b-1,jeu)==1 && verif_case(a-1,b,jeu)==1 && verif_case(a-1,b+1,jeu)==1)
                        {
                            torp[i].pos[0].x=a;
                            torp[i].pos[0].y=b;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-1]=1;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-2]=2;
                            torp[i].pos[0].x=torp[i].pos[0].x-1;
                            torp[i].pos[0].y=torp[i].pos[0].y-1;
                            jeu[torp[i].pos[0].x][torp[i].pos[0].y+3]=2;
                            torp[i].orr=choix;
                            for(j=0; j<3; j++)
                            {

                                jeu[torp[i].pos[0].x][torp[i].pos[0].y+j]=1;
                                jeu[torp[i].pos[0].x-1][torp[i].pos[0].y+j]=2;
                                jeu[torp[i].pos[0].x+1][torp[i].pos[0].y+j]=2;
                                torp[i].pos[j].y=torp[i].pos[0].y+j;
                                torp[i].pos[j].x=torp[i].pos[0].x;
                            }
                            bon=1;
                        }
                        bloc=1;

                    }
                }
            }
            else
            {
                printf("Vous ne pouvez pas placer un bateau la.\n");
                bon=0;
            }
        }

        affiche_grille(0,jeu);
    }



}

void placer_av(porte_a * avion,int jeu[m][m])
{

    int i,j,a,b,bon=0;
    char c;

    bon=0;
    while(bon==0)
    {
        printf("Veuillez entrer les coordonnees de votre Porte-Avion\n");
        scanf("%d%c",&a,&c);
        b=toascii(c)-64;
        if(jeu[a-1][b-1]==0)
        {
            bloc=0;

            while(bloc==0)
            {
                printf("Voulez vous le placer Verticalement ou Horizontalement\n1 - Je le veux vertical\n2- Je le veux horizontal\n");
                scanf("%d",&choix);
                if (choix==1)
                {
                    if (verif_case(a-1,b-1,jeu)==1 && verif_case(a,b-1,jeu)==1 && verif_case(a+1,b-1,jeu)==1 && verif_case(a+2,b-1,jeu)==1)
                    {
                        avion[0].pos[0].x=a;
                        avion[0].pos[0].y=b;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-1]=1;
                        jeu[avion[0].pos[0].x-2][avion[0].pos[0].y-1]=2;
                        avion[0].pos[0].x=avion[0].pos[0].x-1;
                        avion[0].pos[0].y=avion[0].pos[0].y-1;
                        jeu[avion[0].pos[0].x+4][avion[0].pos[0].y]=2;
                        avion[0].orr=choix;
                        for(j=0; j<4; j++)
                        {
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y]=1;
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y-1]=2;
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y+1]=2;
                            avion[0].pos[j].x=avion[0].pos[0].x+j;
                            avion[0].pos[j].y=avion[0].pos[0].y;
                        }
                        bon=1;
                    }
                    bloc=1;

                }
                else if (choix==2)
                {
                    if (verif_case(a-1,b-1,jeu)==1 && verif_case(a-1,b,jeu)==1 && verif_case(a-1,b+1,jeu)==1 && verif_case(a-1,b+2,jeu)==1)
                    {
                        avion[0].pos[0].x=a;
                        avion[0].pos[0].y=b;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-1]=1;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-2]=2;
                        avion[0].pos[0].x=avion[0].pos[0].x-1;
                        avion[0].pos[0].y=avion[0].pos[0].y-1;
                        jeu[avion[0].pos[0].x][avion[0].pos[0].y+4]=2;
                        avion[0].orr=choix;
                        for(j=0; j<4; j++)
                        {

                            jeu[avion[0].pos[0].x][avion[0].pos[0].y+j]=1;
                            jeu[avion[0].pos[0].x-1][avion[0].pos[0].y+j]=2;
                            jeu[avion[0].pos[0].x+1][avion[0].pos[0].y+j]=2;
                            avion[0].pos[j].y=avion[0].pos[0].y+j;
                            avion[0].pos[j].x=avion[0].pos[0].x;
                        }
                        bon=1;
                    }
                    bloc=1;

                }
            }
        }
        else
        {
            printf("Vous ne pouvez pas placer un bateau la.\n");
            bon=0;
        }
    }

    affiche_grille(0,jeu);



}




void ordi_sm(sous_m marin[],int jeu[m][m])
{
    int i,j,a,b,bon=0;
    for(i=0; i<3; i++)
    {
        bon=0;
        while(bon==0)
        {

            a=(rand() % (m))+1;
            b=(rand() % (m))+1;
            if(verif_casee(a-1,b-1,jeu)==1)
            {
                marin[i].pos[0].x=a;
                marin[i].pos[0].y=b;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y-1]=1;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y-2]=2;
                jeu[marin[i].pos[0].x-1][marin[i].pos[0].y]=2;
                jeu[marin[i].pos[0].x-2][marin[i].pos[0].y-1]=2;
                jeu[marin[i].pos[0].x][marin[i].pos[0].y-1]=2;

                marin[i].pos[0].x=marin[i].pos[0].x-1;
                marin[i].pos[0].y=marin[i].pos[0].y-1;


                bon=1;
            }
        }
    }

}





void ordi_lt(lance_t torp[],int jeu[m][m])
{
    int i,j,a,b,bon=0;
    int c;
    for(i=0; i<2; i++)
    {

        bon=0;
        while(bon==0)
        {

            a=(rand() % (m))+1;
            b=(rand() % (m))+1;
            if(jeu[a-1][b-1]==0)
            {
                bloc=0;

                while(bloc==0)
                {

                    choix=(rand() % (2))+1;

                    if (choix==1)
                    {
                        if (verif_casee(a-1,b-1,jeu)==1 && verif_casee(a,b-1,jeu)==1 && verif_casee(a+1,b-1,jeu)==1)
                        {
                            torp[i].pos[0].x=a;
                            torp[i].pos[0].y=b;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-1]=1;
                            jeu[torp[i].pos[0].x-2][torp[i].pos[0].y-1]=2;
                            torp[i].pos[0].x=torp[i].pos[0].x-1;
                            torp[i].pos[0].y=torp[i].pos[0].y-1;
                            jeu[torp[i].pos[0].x+3][torp[i].pos[0].y]=2;
                            for(j=0; j<3; j++)
                            {
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y]=1;
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y-1]=2;
                                jeu[torp[i].pos[0].x+j][torp[i].pos[0].y+1]=2;
                                torp[i].pos[j].x=torp[i].pos[0].x+j;
                                torp[i].pos[j].y=torp[i].pos[0].y;
                            }
                            bon=1;
                        }
                        bloc=1;

                    }
                    else if (choix==2)
                    {
                        if (verif_casee(a-1,b-1,jeu)==1 && verif_casee(a-1,b,jeu)==1 && verif_casee(a-1,b+1,jeu)==1)
                        {
                            torp[i].pos[0].x=a;
                            torp[i].pos[0].y=b;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-1]=1;
                            jeu[torp[i].pos[0].x-1][torp[i].pos[0].y-2]=2;
                            torp[i].pos[0].x=torp[i].pos[0].x-1;
                            torp[i].pos[0].y=torp[i].pos[0].y-1;
                            jeu[torp[i].pos[0].x][torp[i].pos[0].y+3]=2;
                            for(j=0; j<3; j++)
                            {

                                jeu[torp[i].pos[0].x][torp[i].pos[0].y+j]=1;
                                jeu[torp[i].pos[0].x-1][torp[i].pos[0].y+j]=2;
                                jeu[torp[i].pos[0].x+1][torp[i].pos[0].y+j]=2;
                                torp[i].pos[j].y=torp[i].pos[0].y+j;
                                torp[i].pos[j].x=torp[i].pos[0].x;
                            }
                            bon=1;
                        }
                        bloc=1;

                    }
                }
            }
            else
            {
                bon=0;
            }
        }

    }



}





void ordi_av(porte_a * avion,int jeu[m][m])
{

    int i,j,a,b,bon=0;
    char c;

    bon=0;
    while(bon==0)
    {

        a=(rand() % (m))+1;
        b=(rand() % (m))+1;
        if(jeu[a-1][b-1]==0)
        {
            bloc=0;

            while(bloc==0)
            {

                choix=(rand() % (2))+1;
                if (choix==1)
                {
                    if (verif_casee(a-1,b-1,jeu)==1 && verif_casee(a,b-1,jeu)==1 && verif_casee(a+1,b-1,jeu)==1 && verif_casee(a+2,b-1,jeu)==1)
                    {
                        avion[0].pos[0].x=a;
                        avion[0].pos[0].y=b;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-1]=1;
                        jeu[avion[0].pos[0].x-2][avion[0].pos[0].y-1]=2;
                        avion[0].pos[0].x=avion[0].pos[0].x-1;
                        avion[0].pos[0].y=avion[0].pos[0].y-1;
                        jeu[avion[0].pos[0].x+4][avion[0].pos[0].y]=2;
                        for(j=0; j<4; j++)
                        {
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y]=1;
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y-1]=2;
                            jeu[avion[0].pos[0].x+j][avion[0].pos[0].y+1]=2;
                            avion[0].pos[j].x=avion[0].pos[0].x+j;
                            avion[0].pos[j].y=avion[0].pos[0].y;
                        }
                        bon=1;
                    }
                    bloc=1;

                }
                else if (choix==2)
                {
                    if (verif_casee(a-1,b-1,jeu)==1 && verif_casee(a-1,b,jeu)==1 && verif_casee(a-1,b+1,jeu)==1 && verif_casee(a-1,b+2,jeu)==1)
                    {
                        avion[0].pos[0].x=a;
                        avion[0].pos[0].y=b;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-1]=1;
                        jeu[avion[0].pos[0].x-1][avion[0].pos[0].y-2]=2;
                        avion[0].pos[0].x=avion[0].pos[0].x-1;
                        avion[0].pos[0].y=avion[0].pos[0].y-1;
                        jeu[avion[0].pos[0].x][avion[0].pos[0].y+4]=2;
                        for(j=0; j<4; j++)
                        {

                            jeu[avion[0].pos[0].x][avion[0].pos[0].y+j]=1;
                            jeu[avion[0].pos[0].x-1][avion[0].pos[0].y+j]=2;
                            jeu[avion[0].pos[0].x+1][avion[0].pos[0].y+j]=2;
                            avion[0].pos[j].y=avion[0].pos[0].y+j;
                            avion[0].pos[j].x=avion[0].pos[0].x;
                        }
                        bon=1;
                    }
                    bloc=1;

                }
            }
        }
        else
        {

            bon=0;
        }
    }



}


