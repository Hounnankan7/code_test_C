/*****************************************************/
/* Auteur: Groupe n°12                               */
/* ADIKPETO Artine, BOKO Célia, DEDJINOU Martine     */
/* et DIOP Ndiack                                    */
/*                                                   */
/* Date: 31/01/2018                                  */
/*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
/*****************************************************/
/* On définit la taille maximale de notre grille     */
/*****************************************************/
#define MAX 10
int n=0;
/*****************************************************/
/* Permet de garder en memoire les infos pour chaque */
/* bateau telles que sa taille ,les coordonnees de la*/
/* premiere case du bateau et sa direction(verticale */
/* ou horizontale)                                   */
/*****************************************************/
typedef struct
{
    int taille,ligne, colonne, direction;

} bateau;
/******************************************************/
/* Permet de garder en memoire les informations de    */
/* chaque joueur telles que l'emplacement des bateaux,*/
/* le nombre de coups qu'il a effectué, le nombre     */
/* de bateaux coulés par l'adversaire                 */
/******************************************************/
typedef struct
{
    char nomFic[2];
    bateau b[6];
    char tab[MAX][MAX];
    int placement[MAX][MAX];
    int coup,coule;
} joueur;

/******************************************************/
/* Permet de choisir un des coordonnees aleatoires    */
/* entre 1 et MAX                                     */
/******************************************************/
void hasard1(int *ligne, int *colonne)
{
    srand(time(NULL));//fonction permettant de choisir un nombre aléatoire

    *ligne=(rand() % (MAX))+1;

    *colonne=(rand() % (MAX))+1;
}
/*****************************************************/
/* Permet à l'Ordinateur de choisir aléatoirement    */
/*une case differente de celle choisie precedemment  */
/*par hasard1 puis de choisir aléatoirement une des  */
/*cases au tour de la case trouvée.(Elle intervient  */
/* dans le cas ou l'Ordinateur avait précedemment    */
/*touché une case                                    */
/*****************************************************/
void hasard2(int *ligne, int *colonne)
{
    srand(time(NULL));
    if(*ligne!=MAX  && *ligne!=1 )
    {
        *ligne=(rand() %(3))+ *ligne -1;
    }
    else if(*ligne==1)
    {
        *ligne=(rand() % 2) + 1;
    }
    else
    {
        *ligne=(rand() %2)+MAX-1;
    }


    if(*colonne!=MAX  && *colonne!=1 )
    {
        *colonne=(rand() %(3))+ *colonne -1;
    }
    else if(*colonne==1)
    {
        *colonne=(rand() % 2) + 1;
    }
    else
    {
        *colonne=(rand() %2)+MAX-1;
    }

}
/**********************************************/
/* Permet de sauvegarder le meilleur score du */
/* jeu en mode 1 vs IA.                        */
/**********************************************/
void meilleurScore(joueur *p)
{
    char nom[20], prenom[30];
    FILE *fichier=NULL, *fic=NULL;
    int coups=0;
    fichier =fopen("mscore.txt","r");
    if(fic==NULL)
    {
        fic=fopen("mscore.txt","w");
        printf("Vous avez fait le meilleur score!\nEntrez votre nom et votre prenom: ");
        scanf("%s %s", nom, prenom);
        fprintf(fic,"%s %s %d",nom, prenom,p->coup);
        fclose(fic);
    }
    else
    {
        fscanf(fichier,"%s %s %d", nom, prenom,&coups);
        if(p->coup<coups)
        {
            printf("Vous avez fait le meilleur score!\nEntrez votre nom et votre prenom: ");
            scanf("%s %s", nom, prenom);
            fprintf(fichier,"%s %s %d",nom, prenom,p->coup);
            fclose(fichier);
        }
    }
}

/*****************************************************/
/* Initialise toutes les cases de notre matrice à '.'*/
/* qui représente l'eau en memoire                   */
/*****************************************************/
void initialisation( char tab[MAX][MAX], int placement[MAX][MAX])
{
    int i, j;
    for(i=0; i<MAX; i++)//permet de parcourir les lignes
    {
        for(j=0; j<MAX; j++)//permet de parcourir les colonnes
        {
            tab[i][j]='.';
            placement[i][j]=0;//initialise les emplacements a 0

        }
    }
}


/*****************************************************/
/* Permet de representer en memoire les emplacement  */
/* qui sont occupables ou inoccupables               */
/*                                                   */
/* Principe de resolution:                           */
/* Remplace par 1 les emplacements qui sont Sensés   */
/* etre inoccupables                                 */
/*****************************************************/
void placementPos(bateau b, char tab[MAX][MAX], int placement[MAX][MAX])
{
    int i;

    switch(b.direction)
    {
    case 1:
        for(i=b.colonne-1; i< b.taille+b.colonne-1; i++)
        {
            placement[b.ligne-1][i]=1;
            placement[b.ligne][i]=1;


            if(b.ligne-2>0)
            {
                placement[b.ligne-2][i]=1;
            }
            if(i-1>0)
            {
                placement[b.ligne-1][i-1]=1;
            }

            placement[b.ligne-1][i+1]=1;
        }
        break;
    case 2:
        for(i=b.ligne-1; i< b.taille+b.ligne-1; i++)
        {
            placement[i][b.colonne-1]=1;
            placement[i][b.colonne]=1;


            if(b.colonne-2>0)
            {
                placement[i][b.colonne-2]=1;
            }
            if(i-1>0)
            {
                placement [i-1][b.colonne-1]=1;
            }
            placement[i+1][b.colonne-1]=1;
        }
        break;
    }
}

/*****************************************************/
/* Permet d'afficher la grille du joueur.            */
/*                                                   */
/* '~' represente les vagues et 'O' reprente une     */
/* partie du bateau                                  */
/*****************************************************/
void affichage(char tab[MAX][MAX])
{
    int i,j;
    printf("   ");
    for(i=1; i<=MAX; i++)
    {
        printf("%c  ", i+64);
    }
    printf("\n");
    for(i=0; i<MAX; i++)
    {
        if(i<9)
        {
            printf("0");
        }
        printf("%d",i+1);
        for(j=0; j<MAX; j++)
        {
            if(tab[i][j]=='.')
            {
                printf(" ~ ");
            }
            else
                printf(" %c ",tab[i][j]);
        }
        printf("\n");
    }
}

/*****************************************************/
/* Permet d'afficher la grille de l'adversaire en ne */
/* devoilant que les cases ou on a joué.             */
/*                                                   */
/* C represente un bateau touche et X l'eau.         */
/*****************************************************/
void affichageX(char tab[MAX][MAX])
{
    int i,j;
    printf("   ");
    for(i=1; i<=MAX; i++)
    {
        printf("%c  ", i+64);
    }
    printf("\n");
    for(i=0; i<MAX; i++)
    {
        if(i<9)
        {
            printf("0");
        }
        printf("%d",i+1);
        for(j=0; j<MAX; j++)
        {
            if(tab[i][j]!='O' && tab[i][j]!='.' )
            {
                printf(" %c ",tab[i][j]);

            }
            else
                printf(" ~ ");
        }
        printf("\n");
    }
}

/*****************************************************/
/* Verifie si l'emplacement choisit par le joueur    */
/* est disponible.                                   */
/*                                                   */
/* Renvoie 0 si le navire depasse la grille ou si la */
/* somme des elements des cases du bateau (en consi- */
/* le tableau placement) est differente de 0         */
/*****************************************************/
int verification(bateau b, int placement[MAX][MAX])
{
    int i,j;
    int n=0;
    i=b.ligne-1;
    j=b.colonne-1;
    switch(b.direction)
    {
    case 1:
        if(b.colonne+b.taille-1>MAX)
        {
            return 0;
        }

        else
        {
            for(j=b.colonne-1; j<b.colonne+b.taille-1; j++)
            {
                if(  placement[i][j]==1  )
                {
                    n++;
                }

            }
            if(n!=0)
            {
                return 0;
            }
            else
            {

                return 1;
            }
        }

    case 2:
        if(b.ligne+b.taille-1>MAX)
        {
            return 0;
        }

        else
        {
            for(i=b.ligne-1; i<b.ligne+b.taille-1; i++)
            {
                if(  placement[i][j]==1)
                {
                    n++;
                }

            }
            if(n!=0)
            {
                return 0;

            }
            else
            {
                return 1;
            }
            break;
        }

    }
    return 0;
}


/*****************************************************/
/* Permet de sauvegarder une partie en cours dans un */
/* fichier et de reprendre la partie plus tard.      */
/*****************************************************/
void save(joueur *p,int mode, int niveau)
{

    FILE *fic=NULL;
    strcpy(p[0].nomFic,"j1");
    strcpy(p[1].nomFic,"j2");
    int i,j,k;
    fic=fopen("sauvegarde","w");
    fprintf(fic,"%d %d",mode, niveau);//enregistre le mode et le niveau dans le fichier "sauvegarde"
    fclose(fic);
    for(i=0; i<2; i++)// enregistre les joueurs dans deux fichiers differents
    {
        fic=fopen(p[i].nomFic,"w");
        fprintf(fic,"%d %d\n",p[i].coup, p[i].coule);//sauvegarde le nombre de coups effectue et de bateaux coulés par l'adversaire
        for(j=0; j<6; j++)
        {
            fprintf(fic,"%d %d %d %d\n",p[i].b[j].taille,p[i].b[j].ligne,p[i].b[j].colonne,p[i].b[j].direction);// enregistre les infos de chaque bateau
        }
        for(j=0; j<MAX; j++)//enregistre la grille du joueur
        {
            for(k=0; k<MAX; k++)
            {
                fprintf(fic,"%c ",p[i].tab[j][k]);
            }
            fputc('\n',fic);
        }

        fclose(fic);
    }
}
/*****************************************************/
/* permet de recuperer les informations stockées dans*/
/* les fichiers de sauvegarde                        */
/*****************************************************/
int chargerPartie(joueur *p,int *mode, int *niveau)
{
    strcpy(p[0].nomFic,"j1");
    strcpy(p[1].nomFic,"j2");

    FILE *fic=NULL;
    int i,j,k;
    fic=fopen("sauvegarde","r");

    if(fic==NULL)
    {
        printf("Pas de partie sauvegardee!!!\n");
        return 0;
    }

    fscanf(fic,"%d %d",mode, niveau);
    fclose(fic);
    printf("OK");
    for(i=0; i<2; i++)
    {
        fic=fopen(p[i].nomFic,"r");
        if(fic==NULL)
        {
            printf("Impossible de charger la partie\n");
        }
        fscanf(fic,"%d %d\n",&p[i].coup, &p[i].coule);
        for(j=0; j<6; j++)
        {
            fscanf(fic,"%d %d %d %d\n",&p[i].b[j].taille,&p[i].b[j].ligne,&p[i].b[j].colonne,&p[i].b[j].direction);
        }
        for(j=0; j<MAX; j++)
        {
            for(k=0; k<MAX; k++)
            {
                fscanf(fic,"%c ",&p[i].tab[j][k]);
            }

        }



        fclose(fic);
    }
    return 1;
}

/*****************************************************/
/* Permet a l'utilisateur de choisir les emplacements*/
/* de ses bateaux tout en verifiant si ces           */
/* emplacements sont disponibles                     */
/*****************************************************/
void ajoutBateauJoueur(bateau *b, int placement[MAX][MAX],char tab[MAX][MAX])
{
    char c;
    int i,v=1,a=0;
    b[0].taille=4;
    for(i=1; i<3; i++)
    {
        b[i].taille=3;
    }
    for(i=3; i<6; i++)
    {
        b[i].taille=1;
    }
    system("cls");
    affichage(tab);
    printf("\nEntrez les coordonnees et la direction de vos navires\n");

    do
    {
        if(a!=0)
        {
            printf("\nCet emplacement n'est pas disponible! Veuillez ressayer!\n");
        }
        do
        {


            printf("Porte-avion:\nCoordonnees(EX: 10F):\n");



            scanf("%d",& b[0].ligne);
            scanf("%s",&c);
            b[0].colonne=toascii(c)-64;
        }
        while(b[0].ligne<1 || b[0].colonne<1);
        do
        {
            printf("Disposition(1 pour horizontale, 2 pour verticale): ");
            scanf("%d", &b[0].direction);
        }
        while(b[0].direction!=1 && b[0].direction !=2);
        v=verification(b[0],placement);
        a++;
    }
    while(v==0);
    placementPos(b[0], tab, placement);


    for(i=1; i<3; i++)
    {
        placementBateau(&b[i-1],tab);
        system("cls");
        affichage(tab);
        a=0;
        do
        {
            if(a!=0)
            {
                printf("\nCet emplacement n'est pas disponible! Veuillez ressayer!\n");
            }
            do
            {


                printf("Torpille %d:\nCoordonnees(EX: 10F):\n",i);



                scanf("%d",& b[i].ligne);
                scanf("%s",&c);
                b[i].colonne=toascii(c)-64;
            }
            while(b[i].ligne<1 || b[i].colonne<1);
            do
            {
                printf("Disposition(1 pour horizontale, 2 pour verticale): ");
                scanf("%d", &b[i].direction);
            }
            while(b[i].direction!=1 && b[i].direction !=2);
            v=verification(b[i],placement);
            a++;
        }
        while(v==0);
        placementPos(b[i], tab, placement);
    }

    for(i=3; i<6; i++)
    {
        a=0;
        placementBateau(&b[i-1],tab);
        system("cls");
        affichage(tab);
        do
        {
            if(a!=0)
            {
                printf("\nCet emplacement n'est pas disponible! Veuillez ressayer!\n");
            }
            do
            {


                printf("Sous-Marin %d:\nCoordonnees(EX: 10F):\n",i-2);
                scanf("%d",& b[i].ligne);
                scanf("%s",&c);
                b[i].colonne=toascii(c)-64;
            }
            while(b[i].ligne<1 || b[i].colonne<1);
            b[i].direction=1;
            v=verification(b[i],placement);
            a++;
        }
        while(v==0);
        placementPos(b[i], tab, placement);

    }
    placementBateau(&b[5],tab);
    system("cls");
    affichage(tab);
}
/*****************************************************/
/* Permet a l'ordinateur de choisir des coordonnees  */
/* aleatoirement pour positionner ses bateaux        */
/*                                                   */
/*****************************************************/
void ajoutBateauIA(bateau *b, int placement[MAX][MAX],char tab[MAX][MAX])
{
    srand(time(NULL));
    int i;
    b[0].taille=4;
    for(i=1; i<3; i++)
    {
        b[i].taille=3;
    }

    for(i=3; i<6; i++)
    {
        b[i].taille=1;
    }

    for(i=0; i<6; i++)
    {
        do
        {
            b[i].ligne = (rand() % (MAX)) + 1;
            b[i].colonne = (rand() % (MAX)) + 1;
            b[i].direction=(rand() % 2) + 1;
        }
        while(verification(b[i],placement)==0);
        placementPos(b[i], tab, placement);
    }

}
/*****************************************************/
/* Permet de placer les bateaux du joueur sur la     */
/* grille                                            */
/*****************************************************/
void placementBateau(bateau *b, char tab[MAX][MAX])
{
    int i;

    switch(b->direction)
    {
    case 1:
        for(i=b->colonne-1; i< b->taille+b->colonne-1; i++)
        {
            tab[b->ligne-1][i]='O';
        }
        break;

    case 2:
        for(i=b->ligne-1; i< b->taille+b->ligne-1; i++)
        {
            tab[i][b->colonne-1]='O';
        }
        break;
    }


}
/*****************************************************/
/*permet de verifier si un bateau coule ou pas       */
/*****************************************************/
void couler(joueur *p)
{
    int i,j,a=0;
    p->coule=0;

    for(i=0; i<6; i++)
    {
        switch(p->b[i].direction)
        {
        case 1:
            for(j=p->b[i].colonne-1; j<p->b[i].colonne+p->b[i].taille-1; j++)
            {
                if(p->tab[p->b[i].ligne-1][j]=='C')
                {
                    a++;
                }
            }

            break;

        case 2:
            for(j=p->b[i].ligne-1; j<p->b[i].ligne+p->b[i].taille-1; j++)
            {
                if(p->tab[j][p->b[i].colonne-1]=='C')
                {
                    a++;
                }
            }
            break;
        }

        if(p->b[i].taille==a)
        {
            p->coule++;
        }
        a=0;
    }
}
/*****************************************************/
/* permet de verifier si  les coordonnees choisies   */
/* correspondent a un bateau ou pas                  */
/*                                                   */
/* Renvoie 1 si c'est touche ou touche coule et 0 si */
/* c'est a l'eau                                     */
/*****************************************************/
int toucheOuEau(int l, int c,joueur *p)
{
    n=p->coule;
    if(p->tab[l-1][c-1]=='O')
    {
        p->tab[l-1][c-1]='C';
        couler(p);

        if(n<p->coule)
        {
            printf("Touche coule!\n");

        }
        else
        {
            printf("Touche!\n");

        }
        return 1;
    }

    else if(p->tab[l-1][c-1]=='.' || p->tab[l-1][c-1]=='C' )
    {
        printf("A l'eau!\n");
        if(p->tab[l-1][c-1]=='.')
        {
            p->tab[l-1][c-1]='X';
        }

        return 0;
    }

}

/*****************************************************/
/* Permet d'agencer les differentes fonctions        */
/* intervenant dans la mise en place d'une partie.   */
/*****************************************************/
void creationPartie(joueur *p, int a)
{


    initialisation( p->tab, p->placement);

    switch(a)
    {
        int i;
    case 0:
        ajoutBateauJoueur(p->b, p->placement,p->tab);
        break;

    case 1:
        ajoutBateauIA(p->b, p->placement,p->tab);
        for(i=0; i<6; i++)
        {
            placementBateau(&p->b[i],p->tab);
        }
        break;
    }




}

/*****************************************************/
/* Permet d'agencer les fonctions intervenants au    */
/* au cours de la partie (attaque, touche ou eau...) */
/*****************************************************/
int partie( joueur *p, int mode, int niveau)
{
    p[0].coule=0;
    p[1].coule=0;
    int x, y,j=0,i=0,q=2;
    char c;
    switch(mode)
    {
    case 1:
        do
        {
            do
            {
                system("cls");
                affichageX(p[(i+1)%2].tab);
                printf("joueur %d:\nEntrer la case a attaquer (EX: 5A):\n",i+1);
                scanf("%d%c", &x,&c);
                y=toascii(c)-64;
                j=toucheOuEau(x,y,&p[(i+1)%2]);
                if(p[0].coule==6 || p[1].coule==6)
                {
                    j=0;
                }

                printf("Appuyez sur la touche ECHAP pour quitter ou sur une autre touche pour continuer!\n");
                fflush(stdin);
                if(getch()==27)
                {
                    system("cls");
                    printf("voulez vous vraiment quitter la partie?\n1.Oui\n2.Non\n");
                    scanf("%d", &q);
                    if(q==1)
                    {
                        system("cls");
                        printf("voulez vous sauvegarder la partie avant de quitter?\n1.Oui\n2.Non\n");
                        scanf("%d", &q);
                        if(q==1)
                        {
                            save(p,mode,niveau);
                            printf("Fichier sauvegarde\n");
                        }
                        return 0;
                    }

                }
            }
            while(j!=0);
            i++;
            i%=2;
        }
        while(p[0].coule<6 && p[1].coule<6);
        printf("Vainqueur: Joueur %d\n",i);

        break;

    case 2:


        do
        {
            do
            {

                system("cls");
                affichageX(p[(i+1)%2].tab);

                if(i==0)
                {
                    printf("joueur :\nEntrer la case a attaquer (EX: 5A):\n");
                    scanf("%d%c", &x,&c);
                    y=toascii(c)-64;
                    j=toucheOuEau(x,y,&p[(i+1)%2]);

                }

                else
                {
                    printf("Ordinateur: ");
                    switch(niveau)
                    {
                    case 1:

                        do
                        {
                            hasard1(&x, &y);
                        }
                        while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');
                        break;

                    case 2:

                        if(j==0)
                        {
                            do
                            {
                                hasard1(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }

                        else
                        {
                            do
                            {
                                hasard2(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }
                        break;

                    case 3:

                        if(j!=1)
                        {
                            do
                            {
                                hasard1(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }

                        else if(j==1)
                        {
                            do
                            {
                                hasard2(&x,&y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C' || p[(i+1)%2].placement[x-1][y-1]==0);
                        }
                        break;
                        if(p[0].coule==6 || p[1].coule==6)
                        {
                            j=0;
                        }

                    }

                    printf("%d%c ",x,y+64);
                    j=toucheOuEau(x,y,&p[(i+1)%2]);

                }
                p[i].coup++;
                if(p[0].coule==6 || p[1].coule==6)
                {

                    j=0;
                }
                printf("Appuyez sur la touche ECHAP pour quitter ou sur une autre touche pour continuer!\n");
                fflush(stdin);
                if(getch()==27)
                {
                    system("cls");
                    printf("voulez vous vraiment quitter la partie?\n1.Oui\n2.Non\n");
                    scanf("%d", &q);
                    if(q==1)
                    {
                        system("cls");
                        printf("voulez vous sauvegarder la partie avant de quitter?\n1.Oui\n2.Non\n");
                        scanf("%d", &q);
                        if(q==1)
                        {
                            printf("ok\n");
                            save(p,mode,niveau);
                        }
                        return 0;
                    }

                }




            }
            while(j!=0);
            i++;
            i%=2;
        }
        while(p[0].coule<6 && p[1].coule<6);
        if(i==0)
        {

            printf("Vous avez perdu!\n");
        }
        else
        {
            printf("Bravo!\n");
            printf("Nombre de coups: %d\nAppuyer sur La touche Entree pour continuer!\n", p[0].coup);
            meilleurScore(&p[0]);
            printf("Appuyez sur la touche Entrée pour continuer!\n");
            fflush(stdin);
            getchar();
            system("cls");
        }

        break;

    }
    return 1;
}
/*****************************************************/
/* Permet de reprendre une partie deja sauvegardee   */
/*****************************************************/
int reprendrePartie( joueur *p, int mode, int niveau)
{
    int x, y,j=0,i=1,t,z,q=2;
    char c;
    if(p[0].coup==p[1].coup)
    {
        i=0;
    }
    switch(mode)
    {
    case 1:
        do
        {
            do
            {
                system("cls");
                affichageX(p[(i+1)%2].tab);
                printf("joueur %d:\nEntrer la case a attaquer (EX: 5A):\n",i+1);
                scanf("%d%c", &x,&c);
                y=toascii(c)-64;
                j=toucheOuEau(x,y,&p[(i+1)%2]);
                if(p[0].coule==6 || p[1].coule==6)
                {
                    j=0;
                }

                printf("Appuyez sur la touche ECHAP pour quitter ou sur une autre touche pour continuer!\n");
                fflush(stdin);
                if(getch()==27)
                {
                    system("cls");
                    printf("voulez vous vraiment quitter la partie?\n1.Oui\n2.Non\n");
                    scanf("%d", &q);
                    if(q==1)
                    {
                        system("cls");
                        printf("voulez vous sauvegarder la partie avant de quitter?\n1.Oui\n2.Non\n");
                        scanf("%d", &q);
                        if(q==1)
                        {
                            save(p,mode,niveau);
                            printf("Fichier sauvegarde\n");
                        }
                        return 0;
                    }

                }
            }
            while(j!=0);
            i++;
            i%=2;
        }
        while(p[0].coule<6 && p[1].coule<6);
        printf("Vainqueur: Joueur %d\n",i);
        break;

    case 2:
        do
        {
            do
            {
                system("cls");
                affichageX(p[(i+1)%2].tab);


                if(i==0)
                {
                    printf("joueur :\nEntrer la case a attaquer (EX: 5A):\n");
                    scanf("%d%c", &x,&c);
                    y=toascii(c)-64;
                    j=toucheOuEau(x,y,&p[(i+1)%2]);

                }

                else
                {
                    printf("Ordinateur: ");
                    switch(niveau)
                    {
                    case 1:

                        do
                        {
                            hasard1(&x, &y);
                        }
                        while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');
                        break;

                    case 2:

                        if(j==0)
                        {
                            do
                            {
                                hasard1(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }

                        else
                        {
                            do
                            {
                                hasard2(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }
                        break;

                    case 3:

                        if(j!=1)
                        {
                            do
                            {

                                hasard1(&x, &y);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C');

                        }

                        else if(j==1)
                        {
                            do
                            {
                                z=x;
                                t=y;
                                hasard2(&z, &t);
                            }
                            while(p[(i+1)%2].tab[x-1][y-1]=='X' || p[(i+1)%2].tab[x-1][y-1]=='C' || p[(i+1)%2].placement[x-1][y-1]==0);

                        }
                        break;


                    }

                    printf("%d%c ",x,y+64);
                    j=toucheOuEau(x,y,&p[(i+1)%2]);

                }
                if(p[0].coule==6 || p[1].coule==6)
                {

                    j=0;
                }
                printf("Appuyez sur la touche ECHAP pour quitter ou sur une autre touche pour continuer!\n");
                fflush(stdin);
                if(getch()==27)
                {
                    system("cls");
                    printf("voulez vous vraiment quitter la partie?\n1.Oui\n2.Non\n");
                    scanf("%d", &q);
                    if(q==1)
                    {
                        system("cls");
                        printf("voulez vous sauvegarder la partie avant de quitter?\n1.Oui\n2.Non\n");
                        scanf("%d", &q);
                        if(q==1)
                        {
                            printf("ok\n");
                            save(p,mode,niveau);
                            printf("Fichier sauvegarde\n");
                        }
                        return 0;
                    }

                }
                p[i].coup++;




            }
            while(j!=0);
            i++;
            i%=2;
        }
        while(p[0].coule<6 && p[1].coule<6);
        if(i==0)
        {

            printf("Vous avez perdu!\n");
        }
        else
        {
            printf("Bravo!\n");
            printf("Nombre de coups: %d\nAppuyer sur La touche Entree pour continuer!\n", p[0].coup);
            meilleurScore(&p[0]);
            printf("Appuyez sur la touche Entrée pour continuer!\n");
            fflush(stdin);
            getchar();
            system("cls");
        }

        break;

    }

    return 1;
}
/*****************************************************/

/*****************************************************/
int main()
{
    int i,menup=0,mode=1,niveau,choix;
    char str[200];
    FILE *fic=NULL;
    joueur p[2];


    printf("Bienvenue dans le jeu de la bataille navale!\n\n");

    do
    {

        printf("----------------MENU----------------\n1. Jouer\n2. Aide\n3. Meilleur score\n0. Quitter\n");
        scanf("%d", &menup);
        switch(menup)
        {
        case 1:



            do
            {
                system("cls");
                printf("1. Reprendre partie\n2. Nouvelle Partie\n0. Precedent\n");
                scanf("%d", &choix);
                switch(choix)
                {


                case 2:
                    do
                    {
                        system("cls");

                        printf("----------------Mode de jeu----------------\n1. 1 vs 1\n2. 1 vs IA\n0. Precedent\n");

                        scanf("%d",&mode);
                        switch(mode)
                        {
                        case 1:
                            for(i=0; i<2; i++)
                            {
                                printf("Joueur %d",i+1);
                                creationPartie(&p[i],0);
                                printf("Appuyez sur la touche Entrée pour continuer!\n");
                                fflush(stdin);
                                getchar();
                                system("cls");
                            }

                            partie( p, mode,0);
                            break;

                        case 2:

                            do
                            {
                                system("cls");

                                printf("------------Niveau------------\n 1. Facile\n 2. Moyen\n 3. Difficile\n 0. Precedent\n");
                                scanf("%d", &niveau);
                                creationPartie(&p[1],1);
                                switch(niveau)
                                {
                                case 1:
                                    creationPartie(&p[0], 0);
                                    printf("Appuyez sur la touche Entree pour continuer!\n");
                                    fflush(stdin);
                                    getchar();
                                    system("cls");
                                    partie( p, mode, 1);
                                    break;
                                case 2:
                                    creationPartie(&p[0], 0);
                                    printf("Appuyez sur la touche Entree pour continuer!\n");
                                    fflush(stdin);
                                    getchar();
                                    system("cls");
                                    partie( p, mode, 2);
                                    break;
                                case 3:
                                    creationPartie(&p[0], 0);
                                    printf("Appuyez sur la touche Entree pour continuer!\n");
                                    fflush(stdin);
                                    getchar();
                                    system("cls");
                                    partie( p, mode, 3);
                                    break;
                                }

                            }
                            while(niveau!=0);
                            break;
                        }
                    }
                    while(mode !=0);
                    break;

                case 1:
                    chargerPartie(p,&mode, &niveau);
                    printf("Ok!\n");
                    n=reprendrePartie(p, mode,niveau);
                    if(n!=0)
                    {
                        remove("sauvegarde");
                        remove("j1");
                        remove("j2");

                    }
                    break;
                }
            }
            while(choix!=0);
            break;

        case 2:
            system("cls");
            fic=fopen("Notice.txt","r");
            if(fic==NULL)
            {
                printf("Impossible d'ouvrir le fichier");
            }
            else
            {
                while(fgets(str,200,fic)!=NULL)
                {
                    printf("%s", str);
                }
            }
            printf("Appuyez sur la touche Entree pour continuer!\n");
            fflush(stdin);
            getchar();

            break;

        case 3:
            system("cls");
            fic=fopen("mscore.txt", "r");
            if(fic==NULL)
            {
                printf("Pas de score enregistre!");
            }
            else
            {
                fgets(str,100,fic);
                fclose(fic);
            }
            printf("%s\n",str);
            break;
        }
        system("cls");
    }
    while(menup!=0);
    return 0;
}
