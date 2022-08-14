#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Ce programme est un mini-jeu de dévinette d'un chiffre ou un nombre aléatoire*/

int main()
{
    //variable partie solo
    const int MAX=100,MIN=1;
    int NmbrMyster=0,NmbrEntre=0,ComptTour=0,Rejouer=1;

    //variable partie a deux
    int CTP=0;//Choix type de partie
    char J1[50],J2[50];
    int NmbrMyster1=0,NmbrMyster2=0,TirageSort=0;
    int NmbrEntre1=0,NmbrEntre2=0,ComptTour1=0,ComptTour2=0;
    int PasseMain=0;/*prends 1 quand c'est le joueur 1 qui a la main, 2 quand
    c,est le joueur 2 et 0 quand l'un des joueurs trouve le nombre mystere de l'autre*/
    int Rejouer2=1;


    printf("Bienvenu sur ~~DEVINE LE NOMBRE~~\n");
    while(CTP!=1 && CTP!=2)
    {
        printf("Choisissez le type de partie\n1-Solo contre IA\n2-A deux\n");
        scanf("%d",&CTP);
    }

    if(CTP==1) //instructions partie en solo
    {
//On genere le nombre de maniere aleatoire
        srand(time(NULL));
        NmbrMyster = (rand() % (MAX - MIN + 1)) + MIN;


        while(Rejouer==1)
        {
            printf("\n--Vous vs IA--\nNombre genere au hasard entre 1 et 100\nVous allez le devinez\n");

//Boucle à repeter tant que le nombre n'est pas trouve
            do
            {
                printf("Quel est le nombre?\n");
                scanf("%d",&NmbrEntre);
                ComptTour++;

                if(NmbrEntre<NmbrMyster)
                {
                    printf("C'est moins!\n");
                    system("cls");
                }
                else if(NmbrEntre>NmbrMyster)
                {
                    printf("C'est plus!\n");
                    system("cls");
                }
                else
                {
                    printf("Youpi!!!\nVous avez devinez apres %d coup(s)\n",ComptTour);
                }
            }
            while(NmbrEntre!=NmbrMyster);
            printf("\nVoulez-vous rejouez?\n1-Oui\n2-Non\n");
            scanf("%d",&Rejouer);
        }
    }//fin de partie solo


    else //instructions partie a deux
    {
        while(Rejouer2==1)
        {
            printf("Le premier qui devine le nombre mystere de l'adversiare l'emporte\n");
            printf("Pseudo joueur 1:");
            scanf("%s",&J1);
            printf("Pseudo joueur 2:");
            scanf("%s",&J2);
            printf("%s entrez votre nombre mystere entre 1 et 100\n",J1);
            scanf("%d",&NmbrMyster1);
            printf("%s entrez votre nombre mystere entre 1 et 100\n",J2);
            scanf("%d",&NmbrMyster2);

            //partie proprement dit
            srand(time(NULL));
            TirageSort=(rand()%(2-1+1))+1;
            if(TirageSort==1)
            {
                printf("%s a gagne le tirage au sort\nIl commence\n",J1);
                PasseMain=TirageSort;
            }
            else
            {
                printf("%s a gagne le tirage au sort\nIl commence\n",J2);
                PasseMain=TirageSort;
            }
            system("cls");
            while(PasseMain==1 || PasseMain==2 || PasseMain==3)
            {
                if(TirageSort==1)
                {
                    PasseMain=TirageSort;
                    while(PasseMain==1)
                    {
                        printf(" %s, quel est le nombre myster de %s?\n",J1,J2);
                        scanf("%d",&NmbrEntre1);
                        ComptTour1++;

                        if(NmbrEntre1<NmbrMyster2)
                        {
                            printf("C'est moins!\nVous perdez la main\n");
                            PasseMain=2;
                        }
                        else if(NmbrEntre1>NmbrMyster2)
                        {
                            printf("C'est plus!\nVous perdez la main\n");
                            PasseMain=2;
                        }
                        else
                        {
                            printf("Youpi!!!\n %s a devine apres %d coup(s) et il gagne\n",J1,ComptTour1);
                            PasseMain=0;
                        }
                    }
                    system("cls");
//s'il ne trouve pas on passe la main
                    while(PasseMain==2)
                    {
                        printf("%s, a ton tour\n",J2);
                        printf(" %s, quel est le nombre mystere de %s?\n",J2,J1);
                        scanf("%d",&NmbrEntre2);
                        ComptTour2++;

                        if(NmbrEntre2<NmbrMyster1)
                        {
                            printf("C'est moins!\nVous perdez la main\n");
                            PasseMain=3;
                        }
                        else if(NmbrEntre2>NmbrMyster1)
                        {
                            printf("C'est plus!\nVous perdez la main\n");
                            PasseMain=3;
                        }
                        else
                        {
                            printf("Youpi!!!\n %s a devine apres %d coup(s) et il gagne\n",J2,ComptTour2);
                            PasseMain=0;
                        }
                    }
                    system("cls");
                }
//on suppose maintenant que c'est le joueur 2 qui a la premiere main
                else
                {
                    PasseMain=TirageSort;
//Joueur 2 joue d'abord
                    while(PasseMain==2)
                    {
                        printf(" %s, quel est le nombre myster de %s?\n",J2,J1);
                        scanf("%d",&NmbrEntre2);
                        ComptTour2++;

                        if(NmbrEntre2<NmbrMyster1)
                        {
                            printf("C'est moins!\nVous perdez la main\n");
                            PasseMain=1;
                        }
                        else if(NmbrEntre2<NmbrMyster1)
                        {
                            printf("C'est plus!\nVous perdez la main\n");
                            PasseMain=1;
                        }
                        else
                        {
                            printf("Youpi!!!\n %s a devine apres %d coup(s) et il gagne\n",J2,ComptTour2);
                            PasseMain=0;
                        }
                    }
                    system("cls");
//s'il ne trouve pas on passe la main
                    while(PasseMain==1)
                    {
                        printf("%s, a ton tour\n",J1);
                        printf(" %s, quel est le nombre mystere de %s?\n",J1,J2);
                        scanf("%d",&NmbrEntre1);
                        ComptTour1++;

                        if(NmbrEntre1<NmbrMyster2)
                        {
                            printf("C'est moins!\nVous perdez la main\n");
                            PasseMain=3;
                        }
                        else if(NmbrEntre1>NmbrMyster2)
                        {
                            printf("C'est plus!\nVous perdez la main\n");
                            PasseMain=3;
                        }
                        else
                        {
                            printf("Youpi!!!\n %s a devine apres %d coup(s) et il gagne\n",J1,ComptTour1);
                            PasseMain=0;
                        }
                    }
                    system("cls");

                }

            }
            printf("\nVoulez-vous rejouez?\n1-Oui\n2-Non\n");
            scanf("%d",&Rejouer2);
        }
    }
    return 0;

}
