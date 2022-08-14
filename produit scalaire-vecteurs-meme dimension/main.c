#include <stdio.h>
#include <stdlib.h>

long ProduitScalaire(int U[],int V[],int dim)
{
long PS=0,H[10];
int i;

for(i=1;i<=dim;i++)
 {
  H[i]=U[i]*V[i];
 }
for (i=1;i<=dim;i++)
{
    PS=PS+H[i];
}
 return PS;
}

int main()
{
    int U[10],V[10],dimension;
    int i;
    long resultat=0;
    //Entrée des données
    printf("Veuillez entrer la dimension des veteurs(inferieur a 10)\nEntrer dimension:");
    scanf("%d",&dimension);
    printf("Maintenant entrer les coordonnees du vecteur U (dans l'ordre svp)\n");
    for (i=1;i<=dimension;i++)
    {
        printf("entrer U[%d]:",i);
        scanf("%d",&U[i]);
    }
    printf("Entrer les coordonnées du vecteur V (dans l'ordre svp)\n");
    for (i=1;i<=dimension;i++)
    {
        printf("entrer V[%d]:",i);
        scanf("%d",&V[i]);
    }
    //Affichage des vecteurs a multiplier
    printf("U---V\n");
    for (i=1;i<=dimension;i++)
    {
        printf("%d---%d\n",U[i],V[i]);
    }

    //Calcul du produit scalaire et présentation des résultats
    resultat=ProduitScalaire(U,V,dimension);
    printf("Le produit scalaire des deux vecteurs est %d\n",resultat);


    return 0;
}
