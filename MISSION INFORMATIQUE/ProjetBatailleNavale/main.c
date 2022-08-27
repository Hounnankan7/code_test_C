/*
Projet realise par
HOUNNANKAN Donald
IDOHOU Larissa
NENEHIDINI Ursule
VISSOH Vianney
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 500
#define TPlato 6
#include "structure.h"
#include "Menu_Sauvegarde.h"
#include "Initialise_Affiche.h"
#include "BateauJoueur.h"
#include "BateauOrdi.h"
#include "Attaque.h"

int main()
{
    //Champ de variables
    char PlatoOrdi[MAX][MAX],PlatoJeu[MAX][MAX],PlatoVide[MAX][MAX];/*respectivement la grille de l'ordinateur,celle du joueur.
        La derniere est celle  qui precise les cases deja jouees par le joueur*/
    int w=0,num=0;/*respectivement indice boucle for,numero des bateaux allant de 0 a 5*/
    int ChoixBato=0,choix=0;
    Bateau B[6];/*tableau des bateaux que le joueur veut placer*/
    Case CoupJoue[MAX],CoupJoueO[MAX];  /*Tableau des coups deja jou� par le joueur et l'ordinateur respectivement*/
    int Nmbr=0,NmbrO=0;           /*Compter le nombre de coup jou� par le joueur et l'ordinateur respectivement*/
    int i=0,j=0;
    int nul=0,nulO=0;/*nul est le compteur de cases qui ne sont pas des parties d'un bateau*/
    int NDuel=1;/*Le nombre de duel fait par le joueuer*/
    int SaveChoix=0;

    //Debut de jeu
    choix=Menu();
    if(choix==1)
    {
        /*Appel fonction affichage*/
        printf("------------Grille initialisee--------------\n");
        InitGril(PlatoJeu,TPlato);
        AffichGril(PlatoJeu,TPlato);

        /*disposition des bateaux du joueur*/
        /*enregistrement des informations de dispositions*/
        printf("\nComment voulez vous placer vos bateaux?\nVous avez droit a 1 porte-avion,2 torpilleur et 3 sous-marin\n\n");
        for(w=1; w<=3; w++) /*boucle pour demander le type de bateau et enregistrer selon le nombre*/
        {
            ChoixBato=w;
            /*le porte-avion est le bateau 0, les torpilleurs sont respectivement
            bateau 1 et bateau 2, et les sous marins sont bateau 3,bateau 4,bateau 5*/
            switch(ChoixBato)
            {
            case 1:
                printf(" Placons le Bateau 0:Porte-avion\n");
                num=0;
                B[num]=SaveBato(ChoixBato);
                Verif1Bato(B,TPlato,ChoixBato,num);
                Verif2Bato(PlatoJeu,B,ChoixBato,num);
                PlacerBato(PlatoJeu,B,TPlato,ChoixBato,num);
                system("cls");
                AffichGril(PlatoJeu,TPlato);
                break;

            case 2:
                printf("Placons les deux torpilleurs\n");
                for(num=1; num<=2; num++)
                {
                    printf("Bateau %d:torpilleur\n",num);
                    B[num]=SaveBato(ChoixBato);
                    Verif1Bato(B,TPlato,ChoixBato,num);
                    Verif2Bato(PlatoJeu,B,ChoixBato,num);
                    PlacerBato(PlatoJeu,B,TPlato,ChoixBato,num);
                    system("cls");
                    AffichGril(PlatoJeu,TPlato);
                }
                break;

            case 3:
                printf("Placons les trois sous-marins\n");
                for(num=3; num<=5; num++)
                {
                    printf("Bateau %d:Sous-marin\n",num);
                    B[num]=SaveBato(ChoixBato);
                    Verif1Bato(B,TPlato,ChoixBato,num);
                    Verif2Bato(PlatoJeu,B,ChoixBato,num);
                    PlacerBato(PlatoJeu,B,TPlato,ChoixBato,num);
                    system("cls");
                    AffichGril(PlatoJeu,TPlato);
                }
                break;
            }
        }
        /*affichage de la disposition retenue*/
        system("cls");
        printf(" Donc votre flotte se presente comme suit\n");
        AffichGril(PlatoJeu,TPlato);

        /*generation aleatoire de la grille de l'ordinateur*/
        printf("Nous generons la grille de l'ordinateur\n");
        InitGril(PlatoOrdi,TPlato);
        CodBatoOrdi(PlatoOrdi,TPlato);

        /*debut de la partie*/
        do
        {
            printf("Le joueur commence\n");
            AttaqJoueur(PlatoOrdi,PlatoVide,TPlato,CoupJoue,&Nmbr);
            for(i=1; i<TPlato; i++)
            {
                for(j=1; j<TPlato; j++)
                {
                    if(PlatoOrdi[i][j]=='X')
                    {
                        nul++;
                        PlatoOrdi[i][j]='Y';
                    }
                }
            }
            if(nul==0)
            {
                printf("Vous n'avez encore touche aucun bateau\n");
            }
            else
            {
                printf("vous avez touche %d case(s) de bateau\n Il vous reste donc %d cases a atteindre\n",nul,13-nul);
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
                        PlatoJeu[i][j]='Y';
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
        }
        while(nul!=13 || nulO!=13);
        if(nul==13)
        {
            printf("****************************\n");
            printf("  ********VICTOIRE********  \n");
            printf("    ********************     \n");
        }
        else if(nulO==13)
        {
            printf("!!!!!!!!!!!!Defaite!!!!!!!!!!!!!\nVous etes un looser.\n");
        }
        /*fin de la partie*/

        printf("Voulez-vous sauvegarder votre score?\n1.Oui\n2.Non");
        scanf("%d",&SaveChoix);
        if(SaveChoix==1)
        {
            SaveScore(&NDuel,&nul);
        }
        else
        {
            printf("Au revoir\n");
            system("exit");
        }
    }
    else if(choix==2)
    {
        printf("--------BATAILLE NAVALE--------\n    Version 1.0.0\n      AUTEURS :\n      HOUNNANKAN Prince-Donald\n      IDOHOU Larissa\n      NENEHIDINI Ursule\n      VISSOH Vianney\n");
    }
    else
    {
        printf("Au revoir\n");
        system("exit");
    }

    return 0;
}
