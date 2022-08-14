//VISSOH Vianney
#include <stdio.h>
#include <stdlib.h>
#define max 10

//creation de la fonction pour la somme
int SommeTab(int *P,int *N,int *R,int DIM)/*
P:Tableau entiers positifs
N:Tableau entier negatif
R:Tableau resultat
*/
{
 int i;

 for(i=0;i<DIM;i++)
 {
  R[i]=P[i]+N[i];
 }
 return *R;
}

//creation de la fonction pour trier
int Tri(int *R,int DIM)
{
 int i,nn=0,np=0,z=0;

 for(i=0;i<DIM;i++)
 {
     if(R[i]<0)
     {
         nn++;
     }
     else if(R[i]>0)
     {
         np++;
     }
     else
     {
         z++;
     }
 }
printf("La somme des deux tableaux a ete effectue est\n");
printf("Le nombre d'entiers s. négatifs:%d\n",nn);
printf("Le nombre d'entiers s.positifs est %d.\n",np);
printf("Le nombre d'entiers nuls est %d.\n",z);

return 0;

}

//fonction principale
int main()
{

  int TP[max],TN[max],TR[max];
  int i=0;
  const int DIM = 10;

  printf("Bonjour ce programme vous permettra de faire la somme de deux tableaux s.positifs et s. negatifs\n");
//remplissage du tableau négatifs
  printf("Nous allons remplir le tableau d'entiers s. negatifs\n");
  for(i=0;i<DIM;i++)
  {
    do
  {
  printf("entrer valeur %d\n",i+1);
  scanf("%d",&TN[i]);
  }
  while(TN[i]>=0);
  }

//remplissage tableau positifs
printf("Nous allons remplir le tableau d'entiers s. positifs\n");
for(i=0;i<DIM;i++)
  {
    do
  {
  printf("entrer valeur %d\n",i+1);
  scanf("%d",&TP[i]);
  }
  while(TP[i]<=0);
  }

//Affichage des tableaux entrés
printf("\nLe tableau des entiers s. negatifs est:\n");
for(i=0;i<DIM;i++)
{
    printf("%7d",TN[i]);
}
printf("\nLe tableau des entiers s. positifs est:\n");
for(i=0;i<DIM;i++)
{
    printf("%7d",TP[i]);
}

//Somme des tableaux
SommeTab(TP,TN,TR,DIM);

printf("\n");

//Compte des valeurs positifs,négatifs et nulles
Tri(TR,DIM);

//Affichage du tableau somme
printf("\nLa somme des deux tableaux donne:\n");
for(i=0;i<DIM;i++)
{
    printf("%7d",TR[i]);
}

return 0;
}
