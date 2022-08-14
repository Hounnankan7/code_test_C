//DOSSOU-YOVO Jean-Marc
//DOSSOU-YOVO Tiphaine
//AKPLOGAN Mayette
//AKPATA Ozias

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include "jeu.h"




int JEU[m][m];//Grille de placement des bateaux du joueur//
int JEU_S[m][m];//grille des resultats du jeu du joueur//
int Ordi[m][m];//Grille de placement des bateaux de l'ordi//
int Ordi_S[m][m];//grille des resultats du jeu de l'ordi//
int compte=0,choix2;
int tour=1;
int rep=0;
int r1[4];
int r2[4];

void save();
void ordi_jeu();
void turn(int i,int j);
void joueur_jeu();
void joueur1_jeu();
void joueur2_jeu();

int t=0,r=0,p=0;
int O1[m*m],O2[m*m];
int J1[m*m],J2[m*m];// J1 et J2 sont des tableaux qui enregistrent les jeux du
                    //joueurs de facon à ce qu'il ne joue pas le même jeu 2 fois
int mesbateaux=0, sesbateaux=0;// variables permettant de compter le nombre de bateaux qui restent dans l'eau//

sous_m ved[3];
lance_t tor[2];
porte_a pora;


sous_m marin[3];
lance_t torp[2];
porte_a avion;






//fonction qui permet de sauvegarder une partie en cours et
//de la charger si on veut continuer a jouer cette partie là//
void charger(char beta[]) //beta[] est un tableau de caracrères qui recoit les noms de la sauvegarde//
{
    int i=0,j=0;
    FILE * loader=NULL;//declaration de la variable loader de type fichier//
    srand(time(NULL));//pour initialiser un nombre aleatoire//
    init_jeu(ved,tor,&pora,Ordi);//pour initialiser les etats
    init_jeu(ved,tor,&pora,Ordi_S);//des bateaux et les premiers tableaux
    init_jeu(marin,torp,&avion,JEU);//de jeux de l'ordinateur et du joueur//
    init_jeu(marin,torp,&avion,JEU_S);


    strcat(beta,".dat");//permet de coller deux chaines de charactères:

    loader = fopen(beta,"r+");//ouvrir le ficher en lecture/ecriture//
    if (loader == NULL) // verification de l'ouverture du fichier//
    {
        printf("Erreur d'Ouverture de la Sauvegarde");
    }
    else
    {
        fscanf(loader,"%d\n",&choix2);//affiche le niveau de difficulté du jeu//
        fscanf(loader,"%d,%d\n",&mesbateaux,&sesbateaux);//affiche les bateaux qui restaient dans le jeu lors de la sauvegarde//
        fscanf(loader,"%d,%d\n",&r,&t);//r pour compter le nombre de tours joué par l'ordinateur et t pour compter celui du joueur//
        fscanf(loader,"--Joueur1--\n");

        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fscanf(loader,"%d|",&JEU[i][j]);//charger l'etat du jeu précédent du joueur //

            }
            fscanf(loader,"\n");

        }

        fscanf(loader,"--Games--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fscanf(loader,"%d|",&JEU_S[i][j]);//charger l'etat de la grille qui montre
                                                  //au joueur son jeu dans le camp adverse:ce qu'il gagne et ce qu'il perd //
            }
            fscanf(loader,"\n");

        }

        for (i=0; i<t; i++)
        {
            fscanf(loader,"(%d,%d)",&J1[i],&J2[i]);//pour charger tout ce qui a été joué par le joueur//

        }
        fscanf(loader,"\n");

        fscanf(loader,"--Ordi--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fscanf(loader,"%d|",&Ordi[i][j]);//charger l'etat du jeu précédent de l'ordinateur//


            }
            fscanf(loader,"\n");
        }

        fscanf(loader,"--Games--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fscanf(loader,"%d|",&Ordi_S[i][j]);//charger l'etat de la grille qui montre a
                                                  //l'ordinateur son jeu dans le camp du joueur:ce que l'ordi gagne et ce qu'il perd//
            }
            fscanf(loader,"\n");
        }

        for (i=0; i<r; i++)
        {
            fscanf(loader,"(%d,%d)",&O1[i],&O2[i]);//pour charger tout ce qui a été joué par l'ordinateur//
        }
        fscanf(loader,"\n");


        for (i=0; i<2; i++)
        {
            for(j=0; j<3; j++)
            {
                fscanf(loader,"(%d %d)-",&torp[i].pos[j].x,&torp[i].pos[j].y);//enregistre l'emplacement et les positions des torpilles//
                fscanf(loader,"%d",&torp[i].etat[j]);//enregistre l'état des torpilles pour le joueur //
            }
            fscanf(loader,"\n");
        }

        for (i=0; i<3; i++)
        {

            fscanf(loader,"(%d %d)-",&marin[i].pos[0].x,&marin[i].pos[0].y);//enregistre l'emplacement et les positions des sous marin//
            fscanf(loader,"%d",&marin[i].etat);//enregistre l'état des sous marins pour le joueur //

            fscanf(loader,"\n");
        }

        for(j=0; j<4; j++)
        {
            fscanf(loader,"(%d %d)-",&avion.pos[j].x,&avion.pos[j].y);//enregistre l'emplacement et les positions des portes avions//
            fscanf(loader,"%d",&avion.etat[j]);//enregistre l'état des portes avions pour le joueur //
        }
        fscanf(loader,"\n");




        for (i=0; i<2; i++)
        {
            for(j=0; j<3; j++)
            {
                fscanf(loader,"(%d %d)-",&tor[i].pos[j].x,&tor[i].pos[j].y);//enregistre l'emplacement et les positions des torpilles//
                fscanf(loader,"%d",&tor[i].etat[j]);//enregistre l'état des torpilles pour l'ordi //
            }
            fscanf(loader,"\n");
        }

        for (i=0; i<3; i++)
        {

            fscanf(loader,"(%d %d)-",&ved[i].pos[0].x,&ved[i].pos[0].y);//enregistre l'emplacement et les positions des vedettes//
            fscanf(loader,"%d",&ved[i].etat);//enregistre l'état des sous marins pour l'ordi //

            fscanf(loader,"\n");
        }

        for(j=0; j<4; j++)
        {
            fscanf(loader,"(%d %d)-",&pora.pos[j].x,&pora.pos[j].y);//enregistre l'emplacement et les positions des portes avions//
            fscanf(loader,"%d",&pora.etat[j]);//enregistre l'état des portes avions pour l'ordi //
        }
        fscanf(loader,"\n");

        printf("Chargement Reussi\nAppuyez une touche pour continuer");
        getch();//por que l'écran ne s'efface pas avant que le joueur appuie sur une touche//
        if(choix2!=3){
        joueur_jeu();//fonction qui permet au joueur de jouer//
        } else {
        joueur1_jeu();
        }


    }


}

void init_jeu (sous_m marin[],lance_t torp[],porte_a * avion,int jeu[m][m])
{
    int i,j;
    for(i=0; i>m; i++)
    {
        for(j=0; j>m; j++)
        {
            jeu[i][j]=0;
        }
    }


    for(i=0; i<3; i++)
    {
        marin[i].etat = 1;
    }

    for(i=0; i<2; i++)
    {
        for(j=0; j<3; j++)
        {
            torp[i].etat[j]=1;
        }
    }

    for(j=0; j<4; j++)
    {
        avion[0].etat[j]=1;
    }


}





void ordi_place()
{
    srand(time(NULL));
    init_jeu(ved,tor,&pora,Ordi);
    init_jeu(ved,tor,&pora,Ordi_S);
    ordi_sm(ved,Ordi);
    ordi_lt(tor,Ordi);
    ordi_av(&pora,Ordi);
    system("cls");



}

void fin_du_game()
{
    if(choix2!=3){
    if(sesbateaux==0)
    {
        system("cls");
        affiche_grille(0,Ordi);
        printf("\nGrrrrrrr......\nVous avez gagne !!!!!!!!\n;-(\n Ce fut une belle partie\n");
    }
    else if(mesbateaux==0)
    {
        system("cls");
        affiche_grille(0,Ordi);
        printf("\nHahahahaha....\nJ'ai gagne!!!!!!!!\n;-)\n Ce fut une belle partie\n");
    }} else
    {

    if(sesbateaux==0)
    {
        system("cls");
        affiche_grille(0,Ordi);
        printf("\nHahahahh......\nJoueur1 a gagne !!!!!!!!\n;-(\n Ce fut une belle partie\n");
    }
    else if(mesbateaux==0)
    {
        system("cls");
        affiche_grille(0,Ordi);
        printf("\nHahahahaha....\nJoueur2 a gagne!!!!!!!!\n;-)\n Ce fut une belle partie\n");
    }
    }

}




void turn (int i,int j)
{
    int k,l;
    char c;
    if(choix2==2 || choix2==1){
    if (tour==1)
    {

        if (i<=m && j<=m)
        {
            if(Ordi[i-1][j-1]==1)
            {
                JEU_S[i-1][j-1]=3;
                Ordi[i-1][j-1]=5;
                tour=1;
                for (k=0; k<3; k++)
                {
                    if(ved[k].pos[0].x==i-1 && ved[k].pos[0].y==j-1)
                    {
                        printf("Touche Coule ;-(\nAppuyez sur une touche pour continuer\n");
                        getch();
                        ved[k].etat =0;
                        sesbateaux--;
                    }
                }

                for(k=0; k<2; k++)
                {
                    for(l=0; l<3; l++)
                    {
                        if(tor[k].pos[l].x==i-1 && tor[k].pos[l].y==j-1)
                        {
                            printf("Touche \n");
                            tor[k].etat[l]=0;
                            if (tor[k].etat[0]==0 && tor[k].etat[1]==0 && tor[k].etat[2]==0)
                            {
                                printf("Coule ;-( \n");
                                sesbateaux--;
                            }
                            printf("\nAppuyez sur une touche pour continuer\n");
                            getch();
                        }
                    }
                }

                for(l=0; l<4; l++)
                {
                    if(pora.pos[l].x==i-1 && pora.pos[l].y==j-1)
                    {
                        printf("Touche \n");
                        pora.etat[l]=0;
                        if (pora.etat[0]==0 && pora.etat[1]==0 && pora.etat[2]==0 && pora.etat[3]==0)
                        {
                            printf("Coule ;-( \n");
                            sesbateaux--;
                        }
                        printf("\nAppuyez sur une touche pour continuer\n");
                        getch();
                    }
                }
                if(sesbateaux>0)
                {
                    printf("\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
                    c=getch();
                    if(c=='S')
                    {
                        save();
                    }
                    else
                    {
                        joueur_jeu();
                    }

                }
                else
                {
                    fin_du_game();
                }
            }
            else
            {
                JEU_S[i-1][j-1]=4;
                tour=0;
                printf("A l'eau\nVeuillez appuyer sur une touche pour continuer\n");
                p=0;
                getch();
                ordi_jeu();
            }
        }
        else
        {
            printf("Vous avez joue hors de la grille\n");
            tour=1;
            printf("\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
            c=getch();
            if(c=='S')
            {
                save();
            }
            else
            {
                joueur_jeu();
            }
        }

    }
    else if(tour==0)
    {
        if (i<=m && j<=m)
        {
            printf("L'ordi joue %d%c\n",i,j+64);
            if(JEU[i-1][j-1]==1)
            {
                Ordi_S[i-1][j-1]=3;
                tour=0;
                for (k=0; k<3; k++)
                {
                    if(marin[k].pos[0].x==i-1 && marin[k].pos[0].y==j-1)
                    {
                        printf("L'ordi a touche et coule ;-(\nAppuyez sur une touche pour continuer\n");
                        mesbateaux--;
                        O1[r]=i;
                        O2[r]=j-1;
                        O1[r+1]=i-2;
                        O2[r+1]=j-1;
                        O1[r+2]=i-1;
                        O2[r+2]=j-2;
                        O1[r+3]=i-1;
                        O2[r+3]=j;
                        r=r+4;
                        getch();
                        marin[k].etat =0;
                    }
                }

                for(k=0; k<2; k++)
                {
                    for(l=0; l<3; l++)
                    {
                        if(torp[k].pos[l].x==i-1 && torp[k].pos[l].y==j-1)
                        {
                            printf("L'ordi a Touche \n");
                            torp[k].etat[l]=0;
                            if (torp[k].etat[0]==0 && torp[k].etat[1]==0 && torp[k].etat[2]==0)
                            {
                                if(torp[k].or==1)
                                {
                                    O1[r]=i-2;
                                    O2[r]=j-1;

                                    O1[r+1]=i+2;
                                    O2[r+1]=j-1;

                                    O1[r+2]=i-1;
                                    O2[r+2]=j-2;

                                    O1[r+3]=i-1;
                                    O2[r+3]=j;

                                    O1[r+4]=i;
                                    O2[r+4]=j-2;

                                    O1[r+5]=i;
                                    O2[r+5]=j;

                                    O1[r+6]=i+1;
                                    O2[r+6]=j-2;

                                    O1[r+7]=i+1;
                                    O2[r+7]=j;
                                    r=r+8;


                                }
                                else if (torp[k].or==2)
                                {
                                    O1[r]=i-1;
                                    O2[r]=j-2;

                                    O1[r+1]=i-1;
                                    O2[r+1]=j+2;

                                    O1[r+2]=i-2;
                                    O2[r+2]=j-1;

                                    O1[r+3]=i;
                                    O2[r+3]=j-1;

                                    O1[r+4]=i-2;
                                    O2[r+4]=j;

                                    O1[r+5]=i;
                                    O2[r+5]=j;

                                    O1[r+6]=i-2;
                                    O2[r+6]=j+1;

                                    O1[r+7]=i;
                                    O2[r+7]=j+1;

                                    r=r+8;


                                }
                                printf("et Coule ;-( \n");
                                mesbateaux--;

                                rep=0;

                            }
                            else
                            {
                                p=0;
                                rep=1;
                                r1[0]=i-1;
                                r2[0]=j;
                                r1[1]=i+1;
                                r2[1]=j;
                                r1[2]=i;
                                r2[2]=j+1;
                                r1[3]=i;
                                r2[3]=j-1;
                            }

                            printf("\nAppuyez sur une touche pour continuer\n");
                            getch();
                        }
                    }
                }

                for(l=0; l<4; l++)
                {
                    if(avion.pos[l].x==i-1 && avion.pos[l].y==j-1)
                    {
                        printf("L'ordi a Touche \n");
                        avion.etat[l]=0;
                        if (avion.etat[0]==0 && avion.etat[1]==0 && avion.etat[2]==0 && avion.etat[3]==0)
                        {
                            if (avion.or==1)
                            {

                                O1[r]=i-2;
                                O2[r]=j-1;

                                O1[r+1]=i+3;
                                O2[r+1]=j-1;

                                O1[r+2]=i-1;
                                O2[r+2]=j-2;

                                O1[r+3]=i-1;
                                O2[r+3]=j;

                                O1[r+4]=i;
                                O2[r+4]=j-2;

                                O1[r+5]=i;
                                O2[r+5]=j;

                                O1[r+6]=i+1;
                                O2[r+6]=j-2;

                                O1[r+7]=i+1;
                                O2[r+7]=j;

                                O1[r+8]=i+2;
                                O2[r+8]=j-2;

                                O1[r+9]=i+2;
                                O2[r+9]=j;

                                r=r+10;

                            }
                            else if(avion.or==2)
                            {

                                O1[r]=i-1;
                                O2[r]=j-2;

                                O1[r+1]=i-1;
                                O2[r+1]=j+3;

                                O1[r+2]=i-2;
                                O2[r+2]=j-1;

                                O1[r+3]=i;
                                O2[r+3]=j-1;

                                O1[r+4]=i-2;
                                O2[r+4]=j;

                                O1[r+5]=i;
                                O2[r+5]=j;

                                O1[r+6]=i-2;
                                O2[r+6]=j+1;

                                O1[r+7]=i;
                                O2[r+7]=j+1;

                                O1[r+8]=i-2;
                                O2[r+8]=j+2;

                                O1[r+9]=i;
                                O2[r+9]=j+2;

                                r=r+10;

                            }

                            printf("et Coule ;-( \n");
                            mesbateaux--;
                            rep=0;

                        }
                        else
                        {
                            p=0;
                            rep=1;
                            r1[0]=i-1;
                            r2[0]=j;
                            r1[1]=i+1;
                            r2[1]=j;
                            r1[2]=i;
                            r2[2]=j+1;
                            r1[3]=i;
                            r2[3]=j-1;
                        }
                        printf("\nAppuyez sur une touche pour continuer\n");
                        getch();
                    }
                }
                printf("C'est a l'ordi de jouer\n");
                printf("Appuyez sur une touche pour continuer.....\n");

                getch();
                JEU[i-1][j-1]=5;
                if(mesbateaux>0)
                {
                    ordi_jeu();
                }
                else
                {
                    fin_du_game();
                }

            }
            else
            {
                Ordi_S[i-1][j-1]=4;
                tour=1;
                compte++;
                printf("L'ordi a tire dans l'eau\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
                c=getch();
                if(c=='S')
                {
                    save();
                }
                else
                {
                    joueur_jeu();
                }
            }
        }

    }
    } else if(choix2==3){
            if (tour==1)
    {

        if (i<=m && j<=m)
        {
            if(Ordi[i-1][j-1]==1)
            {
                JEU_S[i-1][j-1]=3;
                Ordi[i-1][j-1]=5;
                tour=1;
                for (k=0; k<3; k++)
                {
                    if(ved[k].pos[0].x==i-1 && ved[k].pos[0].y==j-1)
                    {
                        printf("Touche Coule ;-(\nAppuyez sur une touche pour continuer\n");
                        getch();
                        ved[k].etat =0;
                        sesbateaux--;
                    }
                }

                for(k=0; k<2; k++)
                {
                    for(l=0; l<3; l++)
                    {
                        if(tor[k].pos[l].x==i-1 && tor[k].pos[l].y==j-1)
                        {
                            printf("Touche \n");
                            tor[k].etat[l]=0;
                            if (tor[k].etat[0]==0 && tor[k].etat[1]==0 && tor[k].etat[2]==0)
                            {
                                printf("Coule ;-( \n");
                                sesbateaux--;
                            }
                            printf("\nAppuyez sur une touche pour continuer\n");
                            getch();
                        }
                    }
                }

                for(l=0; l<4; l++)
                {
                    if(pora.pos[l].x==i-1 && pora.pos[l].y==j-1)
                    {
                        printf("Touche \n");
                        pora.etat[l]=0;
                        if (pora.etat[0]==0 && pora.etat[1]==0 && pora.etat[2]==0 && pora.etat[3]==0)
                        {
                            printf("Coule ;-( \n");
                            sesbateaux--;
                        }
                        printf("\nAppuyez sur une touche pour continuer\n");
                        getch();
                    }
                }
                if(sesbateaux>0)
                {
                    printf("\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
                    c=getch();
                    if(c=='S')
                    {
                        save();
                    }
                    else
                    {
                        joueur1_jeu();
                    }

                }
                else
                {
                    fin_du_game();
                }
            }
            else
            {
                JEU_S[i-1][j-1]=4;
                tour=0;
                printf("A l'eau\nVeuillez appuyer sur une touche pour continuer\n");
                p=0;
                getch();
                joueur2_jeu();
            }
        }
        else
        {
            printf("Vous avez joue hors de la grille\n");
            tour=1;
            printf("\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
            c=getch();
            if(c=='S')
            {
                save();
            }
            else
            {
                joueur1_jeu();
            }
        }

    }
    else if(tour==0)
    {
        if (i<=m && j<=m)
        {
            printf("Joueur2 joue %d%c\n",i,j+64);
            if(JEU[i-1][j-1]==1)
            {
                Ordi_S[i-1][j-1]=3;
                tour=0;
                for (k=0; k<3; k++)
                {
                    if(marin[k].pos[0].x==i-1 && marin[k].pos[0].y==j-1)
                    {
                        printf("Joueur2 a touche et coule ;-(\nAppuyez sur une touche pour continuer\n");
                        mesbateaux--;
                        getch();
                        marin[k].etat =0;
                    }
                }

                for(k=0; k<2; k++)
                {
                    for(l=0; l<3; l++)
                    {
                        if(torp[k].pos[l].x==i-1 && torp[k].pos[l].y==j-1)
                        {
                            printf("Joueur2 a Touche \n");
                            torp[k].etat[l]=0;
                            if (torp[k].etat[0]==0 && torp[k].etat[1]==0 && torp[k].etat[2]==0)
                            {

                                printf("et Coule ;-( \n");
                                mesbateaux--;

                            }

                            printf("\nAppuyez sur une touche pour continuer\n");
                            getch();
                        }
                    }
                }

                for(l=0; l<4; l++)
                {
                    if(avion.pos[l].x==i-1 && avion.pos[l].y==j-1)
                    {
                        printf("Joueur2 a Touche \n");
                        avion.etat[l]=0;
                        if (avion.etat[0]==0 && avion.etat[1]==0 && avion.etat[2]==0 && avion.etat[3]==0)
                        {


                            printf("et Coule ;-( \n");
                            mesbateaux--;
                            rep=0;

                        }
                        printf("\nAppuyez sur une touche pour continuer\n");
                        getch();
                    }
                }
                printf("C'est a Joueur2 de jouer\n");
                printf("Appuyez sur une touche pour continuer.....\n");

                getch();
                JEU[i-1][j-1]=5;
                if(mesbateaux>0)
                {
                    joueur2_jeu();
                }
                else
                {
                    fin_du_game();
                }

            }
            else
            {
                Ordi_S[i-1][j-1]=4;
                tour=1;
                compte++;
                printf("Joueur2 a tire dans l'eau\nAppuyez sur S pour Sauvegarder et Quitter\nAppuyez sur une touche pour continuer\n");
                c=getch();
                if(c=='S')
                {
                    save();
                }
                else
                {
                    joueur1_jeu();
                }
            }
        }

    }




    }


}

void save()
{
    int i,j;
    FILE * reg=NULL;
    FILE * mysave=NULL;
    char dy[30];
    printf("Veuillez nommer votre Sauvegarde\n");
    scanf("%s",&dy);
    reg = fopen("registre.dat","a+");
    if(reg==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
    }
    else
    {
        fprintf(reg,"%s\n",dy);
        fclose(reg);
        strcat(dy,".dat");
    }
    mysave = fopen(dy,"w");
    if(mysave==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
    }
    else
    {
        fprintf(mysave,"%d\n",&choix2);
        fprintf(mysave,"%d,%d\n",mesbateaux,sesbateaux);
        fprintf(mysave,"%d,%d\n",r,t);
        fprintf(mysave,"--Joueur1--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fprintf(mysave,"%d|",JEU[i][j]);
            }
            fprintf(mysave,"\n");
        }

        fprintf(mysave,"--Games--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fprintf(mysave,"%d|",JEU_S[i][j]);
            }
            fprintf(mysave,"\n");
        }

        for (i=0; i<t; i++)
        {
            fprintf(mysave,"(%d,%d)",J1[i],J2[i]);
        }
        fprintf(mysave,"\n");

        fprintf(mysave,"--Ordi--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fprintf(mysave,"%d|",Ordi[i][j]);
            }
            fprintf(mysave,"\n");
        }

        fprintf(mysave,"--Games--\n");
        for (i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fprintf(mysave,"%d|",Ordi_S[i][j]);
            }
            fprintf(mysave,"\n");
        }

        for (i=0; i<r; i++)
        {
            fprintf(mysave,"(%d,%d)",O1[i],O2[i]);
        }
        fprintf(mysave,"\n");


        for (i=0; i<2; i++)
        {
            for(j=0; j<3; j++)
            {
                fprintf(mysave,"(%d %d)-",torp[i].pos[j].x,torp[i].pos[j].y);
                fprintf(mysave,"%d",torp[i].etat[j]);
            }
            fprintf(mysave,"\n");
        }

        for (i=0; i<3; i++)
        {

            fprintf(mysave,"(%d %d)-",marin[i].pos[0].x,marin[i].pos[0].y);
            fprintf(mysave,"%d",marin[i].etat);

            fprintf(mysave,"\n");
        }

        for(j=0; j<4; j++)
        {
            fprintf(mysave,"(%d %d)-",avion.pos[j].x,avion.pos[j].y);
            fprintf(mysave,"%d",avion.etat[j]);
        }
        fprintf(mysave,"\n");




        for (i=0; i<2; i++)
        {
            for(j=0; j<3; j++)
            {
                fprintf(mysave,"(%d %d)-",tor[i].pos[j].x,tor[i].pos[j].y);
                fprintf(mysave,"%d",tor[i].etat[j]);
            }
            fprintf(mysave,"\n");
        }

        for (i=0; i<3; i++)
        {

            fprintf(mysave,"(%d %d)-",ved[i].pos[0].x,ved[i].pos[0].y);
            fprintf(mysave,"%d",ved[i].etat);

            fprintf(mysave,"\n");
        }

        for(j=0; j<4; j++)
        {
            fprintf(mysave,"(%d %d)-",pora.pos[j].x,pora.pos[j].y);
            fprintf(mysave,"%d",pora.etat[j]);
        }
        fprintf(mysave,"\n");






        printf("Sauvegarde Reussie\n");
        fclose(mysave);
    }




}



void ordi_jeu()
{
    int a=1,b=1,k;
    int good=0;
    system("cls");
    if(choix2==1)
    {
        while(good==0)
        {
            good=1;
            if(rep==0)
            {
                a=(rand() % (m))+1;
                b=(rand() % (m))+1;
            }
            else
            {
                if(p<3)
                {
                    a=r1[p];
                    b=r2[p];
                    p++;
                }
                else
                {
                    p=0;
                    rep=0;
                }
            }

            for(k=0; k<r; k++)
            {
                if(O1[k]==a-1 && O2[k]==b-1)
                {
                    good=0;
                }

            }
        }
    }
    else if (choix2==2)
    {

        while(good==0)
        {
            good=1;
            if (compte<3)
            {
                if(rep==0)
                {
                    a=(rand() % (m))+1;
                    b=(rand() % (m))+1;
                }
                else
                {
                    if(p<3)
                    {
                        a=r1[p];
                        b=r2[p];
                        p++;
                    }
                    else
                    {
                        p=0;
                        rep=0;
                    }
                }
            }
            else
            {
                while(JEU[a-1][b-1]!=1)
                {
                    a=(rand() % (m))+1;
                    b=(rand() % (m))+1;
                }
                compte=0;
            }
            if(a<1 || a>20 || b<1 || b>20 )
            {
                good=0;

            }
            for(k=0; k<r; k++)
            {
                if(O1[k]==a-1 && O2[k]==b-1)
                {
                    good=0;
                }

            }
        }

    }


    O1[r]=a-1;
    O2[r]=b-1;
    r++;
    turn(a,b);
}



void joueur_jeu()
{
    int a,b,bon=0,k,l;
    char c;
    system("cls");

    printf("C'est a vous de jouer\n");
    affiche_grille(0,JEU);
    printf("\n");
    affiche_grille(0,JEU_S);
    while(bon==0)
    {
        bon=1;
        printf("Veuillez entrer la case sur laquelle vous jouez\n");
        scanf("%d%c",&a,&c);
        b=toascii(c)-64;
        for(k=0; k<t; k++)
        {
            if(J1[k]==a-1 && J2[k]==b-1)
            {
                bon=0;
                printf("Vous avez deja joue dans cette case\n");
            }
        }
    }
    J1[t]=a-1;
    J2[t]=b-1;
    t++;
    turn(a,b);
}



void joueur1_jeu()
{
    int a,b,bon=0,k,l;
    char c;
    system("cls");

    printf("C'est a Joueur 1 de jouer\n");
    affiche_grille(0,JEU);
    printf("\n");
    affiche_grille(0,JEU_S);
    while(bon==0)
    {
        bon=1;
        printf("Veuillez entrer la case sur laquelle vous jouez\n");
        scanf("%d%c",&a,&c);
        b=toascii(c)-64;
        for(k=0; k<t; k++)
        {
            if(J1[k]==a-1 && J2[k]==b-1)
            {
                bon=0;
                printf("Vous avez deja joue dans cette case\n");
            }
        }
    }
    J1[t]=a-1;
    J2[t]=b-1;
    t++;
    turn(a,b);
}

void joueur2_jeu()
{
    int a,b,bon=0,k,l;
    char c;
    system("cls");

    printf("C'est a Joueur 2 de jouer\n");
    affiche_grille(0,Ordi);
    printf("\n");
    affiche_grille(0,Ordi_S);
    while(bon==0)
    {
        bon=1;
        printf("Veuillez entrer la case sur laquelle vous jouez\n");
        scanf("%d%c",&a,&c);
        b=toascii(c)-64;
        for(k=0; k<t; k++)
        {
            if(O1[k]==a-1 && O2[k]==b-1)
            {
                bon=0;
                printf("Vous avez deja joue dans cette case\n");
            }
        }
    }
    O1[t]=a-1;
    O2[t]=b-1;
    r++;
    turn(a,b);
}




void afficheraide(){
    FILE * aide;
    char papa;
    system("cls");

    aide= fopen("rule.txt","r");
    while(!feof(aide)){
        fscanf(aide,"%c",&papa);
        printf("%c",papa);
    }

    fclose(aide);


}



void main()
{
    FILE * regstr;
    int i=0,j;
    int bloc=0,choix;
    char alpha[100][30];
    regstr=fopen("registre.dat","a+");
    int continuer=0;

    while(continuer==0){
    printf("======Bataille Navale=======\n   -------Menu-------\n1. Nouvelle partie\n2. Charger une partie\n3. Aide\n4. Quitter\n");
    scanf("%d",&choix);
    system("cls");
    switch(choix)
    {
    case 1:
    {
        system("cls");
        printf("----Nouvelle Partie----\n1. Normal\n2. Difficile\n3. Deux Joueurs \n");
        scanf("%d",&choix2);
        switch(choix2)
        {
        case 1:
        {

            mesbateaux=6;
            sesbateaux=6;
            ordi_place();
            init_jeu(marin,torp,&avion,JEU);
            init_jeu(marin,torp,&avion,JEU_S);
            affiche_grille(0,JEU);
            printf("Pour entrer les coordonnees, Il vous suffit d'entrer le chiffre suivi de la lettre en majuscule\nExemple:7A\n");
            placer_sm(marin,JEU);
            placer_lt(torp,JEU);
            placer_av(&avion,JEU);
            joueur_jeu();
            break;
        }
        case 2:
        {

            mesbateaux=6;
            sesbateaux=6;
            ordi_place();
            init_jeu(marin,torp,&avion,JEU);
            init_jeu(marin,torp,&avion,JEU_S);
            affiche_grille(0,JEU);
            printf("Pour entrer les coordonnees, Il vous suffit d'entrer le chiffre suivi de la lettre en majuscule\nExemple:7A\n");
            placer_sm(marin,JEU);
            placer_lt(torp,JEU);
            placer_av(&avion,JEU);
            joueur_jeu();
            break;
        }
        case 3:{
             mesbateaux=6;
             sesbateaux=6;
            init_jeu(marin,torp,&avion,JEU);
            init_jeu(marin,torp,&avion,JEU_S);
            init_jeu(ved,tor,&pora,Ordi);
            init_jeu(ved,tor,&pora,Ordi_S);
            printf("Joueur 1.\nVeuillez placer vos bateaux\n");
            affiche_grille(0,JEU);
            placer_sm(marin,JEU);
            placer_lt(torp,JEU);
            placer_av(&avion,JEU);
            system("cls");
            printf("Joueur 2.\nVeuillez placer vos bateaux\n");

            affiche_grille(0,Ordi);
            placer_sm(ved,Ordi);
            placer_lt(tor,Ordi);
            placer_av(&pora,Ordi);
            system("cls");
            printf("C'est au de Joueur 1 de jouer\n");
            joueur1_jeu();

        }
        }
        break;
    }
    case 2:
    {
        printf("Voici les parties sauvegardees\n");
        while(!feof(regstr))
        {
            fscanf(regstr,"%s\n",alpha[i]);
            printf("%d -%s\n",i+1,alpha[i]);
            i++;
        }
        printf("Veuillez entrer l'indice de la partie a charger\n");
        scanf("%d",&j);
        charger(alpha[j-1]);
        break;
    }
    case 3:{
        system("cls");
        afficheraide();

    }
    }
    printf("Voulez vous quitter le programme? (Oui:1 Non:0)\n");
    scanf("%d",&continuer);
     system("cls");
    }

}
