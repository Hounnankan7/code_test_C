//Ryan AZANDEGBE
//Joseph TOHUNGODO
//Jores AMOUZOUN
#include<stdio.h> //* les differentes bibliotheques dont on a besoin *//
#include<strings.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h> //* la bibliotheque permettant de gerer le temps *//
//* l   a fonction delay permet dde geger le temps entre l'affichage de deux lettres sucessives *//
void delay(clock_t a)
{
    clock_t start;
    start  = clock();
    while(clock()-start<a)
    {

    }
}
int main()
{
   system("COLOR CF "); //* lpermet de gerer la couleur du terminal (ecriture et fond)*//
    //A:porte avion
    //T:torpillleur
    //S:sous marris
//* initialisation des variables de type entiers*//
//* win est un compteur , probab est la probablité d'entree de l'ordinateur*//
    int i,j,k=0,x,y,chk=0,win=0,posia[5][2],posib[4][2],posid[3][2],posic[2][2],a=0,b=0,c=0,d=0,probab;
    //* les differentes variables de type char et les tableaux dont on aura besoin*//
    //* tab permet d'afficher la grille du joueur etgriduv celle de l'ordinateur *//
    //* str est initialisée par bataille navale et permettra par suite de l'afficher sans lire de meme orient permet de donner l'orientation h ou v sans lire*//
    char tab[10][10],griduv[10][10],gridc[10][10],gridcv[10][10],orient[2],tempstr[10],str[30]="BATAILLE NAVALE",ch;
    for(i=0;i<10;i++)               //*va a la ligne 10 fois*//
    {
        printf(".......................................................................................................................\n");
    }
    for(i=0;i<50;i++)              //*Cree de l'espace*//
    {
        printf(" ");
    }
    for(i=0;str[i]!='\0';i++)      //*Affiche BATAILLE NAVALE*//
    {
        printf("%c",str[i]);
        delay(60);
    }
    printf("\n");

    delay(1500);
    system("cls"); //* system(cls) tourne la page ou revient en haut du terminal*//
    for(;;)
    {
        system("cls");
        for(i=0;i<10;i++)
            printf("\n");
        for(i=0;i<30;i++)
            printf(" ");
        printf("1.Jouer BATAILLE NAVALE\n");
        for(i=0;i<30;i++)
            printf(" ");
        printf("2.Regles\n");
        ch=getch();
        if(ch==49)
            break;
        if(ch==50)           //*il s'agit ici des regles du jeu*//
        {
            system("cls");
            printf("Bienvenue dans BATAILLE NAVALE de Jaures AMOUZOUN Ryan AZANDEGBE et de Joseph TOHUNGODO\n");
            printf("1.l'objectif du jeu, c'est de detruire touts les bateaux de l'ennemi avant qu'il ne detruise les votres.\n");
            printf("2.Le champ de bataille est une grille de taille 10 X 10 ou vous pouvez poser vos bateaux");
            printf("3.vous pouvez placer vos navires en entrant leurrs orientation:(h) pour horizontale et (v) pour verticale\n");
            printf("4.Ensuite vous devez entrer les coordonnées x et y des bateaux, x et y etant des entiers naturels ,avec x le numero de ligne et y le numero de colonne \n");
            printf("4.vous avez 3 differents bateaux que sont: le porte avion(4 unites de longueur), les torpilleurs(3 unites de longueur) et les sous-marrins(1 unitee de longueur)\n");
            printf("5.Apres avoir placé vos bateaux, vous pouvez ataquer la zone adverse, pour attaquer une zone specifique, entrez ses coordonnées x et y\n");
            printf("6.les attaques touchant les bateaux ennemis seront notés par un 'H',ce qui vous donne la possiblite de rejouer\n");
            printf("7.vos attaques a l'eau seront noté par un 'O' et vous passez votre tour\n");
            printf("appuyez entrer pour continuer :).........");
            fflush(stdin);
            gets(tempstr);
            continue;
        }
    }
    system("cls");        //*le systeme("cls") permet de touner la page si on veut ou de revenir en haut lors de la compilation*//

    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            gridc[i][j]='.';
            tab[i][j]='.';
            gridcv[i][j]='.';
        }
    }
    for(i=1;i<11;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==1)
        {
            printf("  ");
            for(j=1;j<11;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=1;j<11;j++)
            printf("%c ",tab[i][j]);
        printf("\n");
    }
    //* les verifivations et les differentes conditions pour le joueur 1 *//
   /*porte avion*/
    for(;;)
    {
        printf("porte avion:\n");
        printf("Orientation h ou v: ");
        scanf("%s",&orient);
        printf(" coordonnées de x et y (x y) : ");  //*Entree des coordonnees sous forme (x y)*//
        scanf("%d %d",&x,&y);
        if(strcmp(orient,"h")==0)
        {
            if(y>7 || y<1 || x>10 || x<1)          //*conditons pour ne pas etre hors grille*//
            {
                printf("vous etes hors grille, reessayez\n"); //*conditions et placement du porte avion horizontal*//
                continue;
            }
            else
            {
                for(i=y;i<y+4;i++)             //*remplace les points par des A si les conditions sont remplis*//
                {
                    tab[x][i]='A';
                    posia[k][0]=x;
                    posia[k][1]=i;
                    k++;
                }
                break;
            }

        }
        if(strcmp(orient,"v")==0)       //*conditions et placement du porte avion verticale*//
        {
            if(x>7 || x<1 || y>10 || y<1)
            {
                printf("vous etes hors grille ,reessayez\n");
                continue;
            }
             else
            {
                for(i=x;i<x+4;i++)
                {
                    tab[i][y]='A';
                    posia[k][0]=i;
                    posia[k][1]=y;
                    k++;
                }
                break;
            }
        }
    }
    k=0;
    system("cls");
    for(i=1;i<11;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==1)
        {
            printf("  ");
            for(j=1;j<11;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=1;j<11;j++)
            printf("%c ",tab[i][j]);
        printf("\n");
    }
    /*B:torpilleur 1*/
    for(;;)
    {
        chk=0;
        printf("Torpilleur 1:\n");
        printf("Orientation h ou v: ");
        scanf("%s",&orient);
        printf("coordonnées x et y (x y): ");
        scanf("%d %d",&x,&y);
        if(strcmp(orient,"h")==0)                    //*conditions et placement du torpilleur 1 horizontal*//
        {
            if(y>8 || y<1 || x>10 || x<1)             //*conditions pour ne pas etre hors grille*//
            {
                printf("vous ne pouvez pas placer le bateau,réesayez\n");
                continue;
            }
            else
            {
                for(i=y-1;i<y+4;i++)               //*permet de verifier si il n'y a aucun bateau a gauche et a droite du torpilleur*//
                {
                    if(tab[x][i]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                for(i=y;i<y+3;i++)                  //*permet de verifier si il n'y a aucun bateau au dessus et en dessous du torpilleur*//
                {
                    if(tab[x][i]!='.' || tab[x-1][i]!='.' || tab[x+1][i]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)       //*si toutes les conditions sont verifiés mettre des T sur les 3 cases suivantes en fonction de l'orientation*//
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                    {
                        tab[x][i]='T';
                        posib[k][0]=x;
                        posib[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0)  //*memes commentaires que ceux pour l'orientation verticale *//
        {
            if(x>8 || x<1 || y>10 || y<1)
            {
                printf("vous etes hors grille ,reesssayez\n");
                continue;
            }
             else
            {
                 for(i=x-1;i<x+4;i++)
                {
                    if(tab[i][y]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                 for(i=x;i<x+3;i++)
                {
                    if(tab[i][y]!='.' || tab[i][y-1]!='.' || tab[i][y+1]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                   for(i=x;i<x+3;i++)
                    {
                        tab[i][y]='T';
                        posib[k][0]=i;
                        posib[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }

    k=0;
    system("cls");
    for(i=1;i<11;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==1)
        {
            printf("  ");
            for(j=1;j<11;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=1;j<11;j++)
            printf("%c ",tab[i][j]);
        printf("\n");
    }
    /*B:torpilleur 2*/  //*meme commentaires que ceux du torpilleur 1 *//
    for(;;)
    {
        chk=0;
        printf("Torpilleur 2:\n");
        printf("Orientation h ou v: ");
        scanf("%s",&orient);
        printf("coordonnées x et y (x y): ");
        scanf("%d %d",&x,&y);
        if(strcmp(orient,"h")==0)
        {
            if(y>8 || y<1 || x>10 || x<1)
            {
                printf("vous etes hors grille,reesayez\n");
                continue;
            }
            else
            {
                for(i=y-1;i<y+4;i++)
                {
                    if(tab[x][i]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                for(i=y;i<y+3;i++)
                {
                    if(tab[x][i]!='.' || tab[x-1][i]!='.' || tab[x+1][i]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                    {
                        tab[x][i]='T';
                        posib[k][0]=x;
                        posib[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0)
        {
            if(x>8 || x<1 || y>10 || y<1)
            {
                printf("");
                continue;
            }
             else
            {
                 for(i=x-1;i<x+4;i++)
                {
                    if(tab[i][y]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                 for(i=x;i<x+3;i++)
                {
                    if(tab[i][y]!='.' || tab[i][y-1]!='.' || tab[i][y+1]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                   for(i=x;i<x+3;i++)
                    {
                        tab[i][y]='T';
                        posib[k][0]=i;
                        posib[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }
    k=0;
    system("cls");
    for(i=1;i<11;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==1)
        {
            printf("  ");
            for(j=1;j<11;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=1;j<11;j++)
            printf("%c ",tab[i][j]);
        printf("\n");
    }
    int t=0;
    for (t=0;t<2;t++)
    {


    /*sous marrins*/
    for(;;)
    {
        chk=0;
        printf("sous marrins:\n");
        printf("Orientation h ou v: ");     //*orientation du sous marrins *//
        scanf("%s",&orient);
        printf("coordonnées de x et y(x y): ");  //* les coordonnees*//
        scanf("%d %d",&x,&y);
        if(strcmp(orient,"h")==0)         //*pour une orientation horizontale*//
        {
            if(y>10 || y<1 || x>10 || x<1)
            {
                printf("vous etes hors grille,reessayez\n");
                continue;
            }
            else
            {
                 for(i=y-1;i<y+2;i++)  //*Verifie si la gauche et la droite du sous marrin sont libre*//
                {
                    if(tab[x][i]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                for(i=y;i<y+1;i++)  //*verifie si le haut et le bas du sous marrrin sont libre*//
                {
                    if(tab[x][i]!='.' || tab[x-1][i]!='.' || tab[x+1][i]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+1;i++)
                    {
                        tab[x][i]='S';  //*si toutes les conditions sont verifiees alors ca place le sous marrrin*//
                        posid[k][0]=x;
                        posid[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0)  //*meme commentaires que pour une orientation horizontale *//
        {
            if(x>10 || x<1 || y>10 || y<1)
            {
                printf("vous etes hors grille reessayez\n");
                continue;
            }
             else
            {
                  for(i=x-1;i<x+2;i++)
                {
                    if(tab[i][y]!='.')
                      {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                      }
                }
                 for(i=x;i<x+1;i++)
                {
                    if(tab[i][y]!='.' || tab[i][y-1]!='.' || tab[i][y+1]!='.')
                    {
                        printf("vous ne pouvez pas placer le bateau,réessayez\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+1;i++)
                    {
                        tab[i][y]='S';
                        posid[k][0]=i;
                        posid[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }

    k=0;
    system("cls");
     for(i=1;i<11;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==1)
        {
            printf("  ");
            for(j=1;j<11;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=1;j<11;j++)
            printf("%c ",tab[i][j]);
        printf("\n");
    }
    }
    printf("tapez entrer pour continuer.......");
    fflush(stdin);
    gets(tempstr);
    srand(time(NULL));
     //*la programmation de l'ordinateur commence ici*//
      //*rand est ce qui permet a l'ordinateur de faire le remplissage aleatoire*//

    /*porte avion cpu*/
    for(;;)
    {
        if(rand()%2 == 1)
            strcpy(orient,"h");
        else strcpy(orient,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orient,"h")==0)     //*pour une orientation horizontale*//
        {
            if(y>7 || y<1 || x>10 || x<1)   //*applique les conditions d'entree du joueur a l'ordinateur*//
            {
                continue;
            }
            else
            {
                for(i=y;i<y+4;i++)
                    gridc[x][i]='A';
            break;
            }
        }
        if(strcmp(orient,"v")==0)   //*meme commentaires pour une orientation verticale*//
        {
            if(x>7 || x<1 || y>10 || y<1)
            {
                continue;
            }
             else
            {
                for(i=x;i<x+4;i++)
                    gridc[i][y]='A';
                break;
            }
        }
    }
    /*T:torpilleur 1 cpu*/
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orient,"h");
        else strcpy(orient,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orient,"h")==0)   //*pour une orientation horizontale*//
        {
            if(y>8 || y<1 || x>10 || x<1) //*applique les conditions d'entree du joueur a l'ordinateur pour le cas du torpiolleur 1*//
                continue;
            else
            {
                 for(i=y-1;i<y+4;i++)
                {
                    if(gridc[x][i]!='.')
                      {

                        chk=1;
                        break;
                      }
                }
                for(i=y;i<y+3;i++)
                {
                    if(gridc[x][i]!='.' || gridc[x-1][i]!='.' || gridc[x+1][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                        gridc[x][i]='T';
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0) //*meme commentaires pour l'orientation verticale*//
        {
            if(x>8 || x<1 || y>10 || y<1)
            {
                continue;
            }
             else
            {

                    for(i=x-1;i<x+4;i++)
                {
                    if(gridc[i][y]!='.')
                      {
                        chk=1;
                        break;
                      }
                }
                    for(i=x;i<x+3;i++)
                {
                    if(gridc[i][y]!='.' || gridc[i][y-1]!='.' || gridc[i][y+1]!='.')
                    {
                        chk=1;
                        break;
                    }
                }

                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+3;i++)
                        gridc[i][y]='T';
                    break;
                }
            }
        }
    }
     /*T:torpilleur 2 cpu*/  //*applique les conditions d'entree du joueur a l'ordinateur pour le cas du torpilleur 2*//
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orient,"h");
        else strcpy(orient,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orient,"h")==0)
        {
            if(y>8 || y<1 || x>10 || x<1) //* conditions pour ne pas etre hors grille pour une orientation horizontale*//
                continue;
            else
            {
                 for(i=y-1;i<y+4;i++)
                {
                    if(gridc[x][i]!='.')
                      {

                        chk=1;
                        break;
                      }
                }
                for(i=y;i<y+3;i++)
                {
                    if(gridc[x][i]!='.' || gridc[x-1][i]!='.' || gridc[x+1][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                        gridc[x][i]='T';
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0)
        {
            if(x>8 || x<1 || y>10 || y<1)
            {
                continue;
            }
             else
            {

                    for(i=x-1;i<x+4;i++)
                {
                    if(gridc[i][y]!='.')
                      {
                        chk=1;
                        break;
                      }
                }
                    for(i=x;i<x+3;i++)
                {
                    if(gridc[i][y]!='.' || gridc[i][y-1]!='.' || gridc[i][y+1]!='.')
                    {
                        chk=1;
                        break;
                    }
                }

                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+3;i++)
                        gridc[i][y]='T';
                    break;
                }
            }
        }
    }
    int m=2;
    for(m=0;m<2;m++)
    {
    /* Sous marrins cpu*/
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orient,"h");
        else strcpy(orient,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orient,"h")==0)
        {
            if(y>10 || y<1 || x>10 || x<1)
            {
               continue;
            }
            else
            {
               for(i=y-1;i<y+2;i++)
                {
                    if(gridc[x][i]!='.')
                      {
                        chk=1;
                        break;
                      }
                }
            for(i=y;i<y+1;i++)
                {
                    if(gridc[x][i]!='.' || gridc[x-1][i]!='.' || gridc[x+1][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+1;i++)
                        gridc[x][i]='S';
                    break;
                }
            }
        }
        if(strcmp(orient,"v")==0)
        {
            if(x>10 || x<1 || y>10 || y<1)
            {
                continue;
            }
             else
            {     for(i=x-1;i<x+2;i++)
                {
                    if(gridc[i][y]!='.')
                      {

                        chk=1;
                        break;
                      }
                }
                 for(i=x;i<x+1;i++)
                {
                    if(gridc[i][y]!='.' || gridc[i][y-1]!='.' || gridc[i][y+1]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+1;i++)
                        gridc[i][y]='S';
                    break;
                }
            }
        }
    }
    }

    for(i=0;i<12;i++)   //*affichage de la grille de l'ordinateur *//
    {
        for(j=0;j<12;j++)
            griduv[i][j]=tab[i][j];
    }
    for(;;)
    {
        system("cls");
        for(i=1;i<11;i++)
        {
            for(j=0;j<30;j++)
            printf(" ");
            if(i==1)
            {
                printf("  ");
                for(j=1;j<11;j++)
                printf("%d ",j);
                printf("\n");
                for(j=0;j<30;j++)
                printf(" ");
            }
            printf("%d ",i);
            for(j=1;j<11;j++)
                printf("%c ",gridcv[i][j]);
            printf("\n");
        }
        printf("\n");
        for(i=1;i<11;i++)
        {
            for(j=0;j<30;j++)
            printf(" ");
            if(i==1)
            {
                printf("  ");
                for(j=1;j<11;j++)
                printf("%d ",j);
                printf("\n");
                for(j=0;j<30;j++)
                printf(" ");
            }
            printf("%d ",i);
            for(j=1;j<11;j++)
                printf("%c ",griduv[i][j]);
            printf("\n");
        }
        for(;;) //*programmation de l'ordinateur pour le jeu*//
        {
            printf("Entrez x et y: "); //*demande a l'ordibateur d'entree ss coordonnees tout en respecta,t le format du joueur*//
            scanf("%d %d", &x,&y);     //*lit les coordonnes de l'ordinateur *//
            if(x>10 || x<1 || y>10 || y<1 || gridcv[x][y]=='H' || gridcv[x][y]=='O') //*conditions pour verifier si l'ordinateur est hors grille ou si il avait deja joué dans la case *//
            {
                printf("Entrée non validée, Réessayez\n"); //*lui demande de reessayer si ses conditions sont verifies*//
                continue;
            }
            else
            {
                if(gridc[x][y]=='A' || gridc[x][y]=='T'||gridc[x][y]=='S') //*sinon si la case qu'il entre est occupee par un A un T ou un S *//
                {
                    if(gridcv[x][y]!='H')  //*et si il n'avait pas deja touche*//
                    {
                        gridcv[x][y]='H'; //*de mettre un H a l  place , c 'est a dire qu'il a touché*//
                        system("cls"); //*tourne la page*//
                        for(i=1;i<11;i++) //*c'est le code d'affichage*//
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==1)
                            {
                                printf("  ");
                                for(j=1;j<11;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=1;j<11;j++)
                                printf("%c ",gridcv[i][j]);
                            printf("\n");
                        }
                        printf("\n");
                         for(i=1;i<11;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==1)
                            {
                                printf("  ");
                                for(j=1;j<11;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=1;j<11;j++)
                                printf("%c ",griduv[i][j]);
                            printf("\n");
                        }
                        for(i=1;i<11;i++)
                        {
                            for(j=1;j<11;j++) //*win est un compteur et a chaque fois qu'il touche une fois,il compte 1*//
                            {
                                if(gridcv[i][j]=='H')
                                    win++;
                            }
                        }
                        if(win==12) //*si le compteur atteint 12 on gagne*//
                        {
                            printf(" bravo vous avez Gagné\n");
                            break;
                        }
                        win=0;//*innitialisation du compteur win*//
                        continue;
                    }
                    else
                    {
                        printf("Entrée non validée Réessayez\n");
                        continue;
                    }
                }
                else
                {
                    gridcv[x][y]='O'; //*si la case entree par l'ordinateur est a l'eau*//
                    break;
                }
            }
        }
        for(;;)
        {
            probab=rand()%9; //*il s'agit ici de la difficuté*//
            if(probab==6&& a<4) //*si le bateau est un porte avion, l'ordinateur aura tendance a placer les coordonnees a coté du premiere case touchee *//
            {
                x=posia[a][0]; //* les coordonnees seront celles des cases a cotees jusqua ce qu'il detruise tout le porte avion*//
                y=posia[a][1];
                a++;
            }
            else if(probab==8 && b<3)  //*memes commentaires que ceux pour le cas du torpilleur 1*//
            {
                x=posib[b][0];
                y=posib[b][1];
                b++;
            }
            else if(probab==4 && d<3) //*meme commentaires que ceux  pour le cas du torpilleur 2*//
            {
                x=posid[d][0];
                y=posid[d][1];
                d++;
            }
            else if(probab==3 && c<1) //*memes commentaires que ceux pour le cas des sous marrins*//
            {
                x=posic[c][0];
                y=posic[c][1];
                c++;
            }
            else
            {
                x=rand()%10;//*si aucune des conditions n'est verifiee l'ordinateur entre les coordonnes de maniere aleatoire*//
                y=rand()%10;
            }
            if(x>10 || x<1 || y>10 || y<1 || griduv[x][y]=='H' || griduv[x][y]=='0') //*si le l'ordi est hors grille ou si il touche ou si ikl coule*//
            {
                continue;
            }
            //*c'est au tour du joueur de jouer*//
            else
            {
                if(tab[x][y]=='A' || tab[x][y]=='T'|| tab[x][y]=='S') //*si la case enttree est occupee par un sous une torpille ou un porte avion*//
                {
                    if(griduv[x][y]!='H') //*et si il n"avait pas deja touche la case*//
                    {
                        griduv[x][y]='H'; //*alors le point dans la case se transforme en h c'est a dire touche*//
                        system("cls");
                        for(i=1;i<11;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==1)
                            {
                                printf("  ");
                                for(j=1;j<11;j++)
                                printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=1;j<11;j++)
                                printf("%c ",gridcv[i][j]);
                            printf("\n");
                        }
                        printf("\n");
                        for(i=1;i<11;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==1)
                            {
                                printf("  ");
                                for(j=1;j<11;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=1;j<11;j++)
                                printf("%c ",griduv[i][j]);
                            printf("\n");
                        }
                        delay(1000);
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    griduv[x][y]='0'; //*si aucune des conditions precedante n'est remplie alors il a coule et c"est aun tour du joueur de jouer*//
                    break;
                }
            }

        }
        for(i=1;i<11;i++) //*dans la  grille*//
        {
            for(j=1;j<11;j++)
            {
                if(gridcv[i][j]=='H') //*a chaque fois qu'il touche une fois ca fait plus 1 pour le compteur win qui est initialisé" a 0*//
                    win++;
            }
        }
        if(win==12) //*si le compteur atteint douze c'est a dire si il touche toutes les cases *//
        {
            printf("\nBravo, vous avez Gagne\n");//* le joueur a gagné *//
             printf("touts les bateaux ont ete detruit\n");
            break;
        }
        win=0; //* initialisation du compteur win a zero*//
        //* condition pour que l'ordinateur gagne*//
        for(i=1;i<11;i++)
        {
            for(j=1;j<11;j++)
            {
                if(griduv[i][j]=='H')//* faire +1 a chaque fois que l'ordibateur touche*//
                    win++;
            }
        }
        if(win==12) //* si l'ordi touche toutes les cases*//
        {
            printf("\nvous avez perdu\n"); //* le joueur a perdu et l'ordi a gagne*//
            break;
        }
        win=0;//* initialisation du win a ZERO*//
    }
    return 0;//* fin du game*//
}


