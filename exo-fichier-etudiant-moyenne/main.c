/*programme ecrit par vianney vissoh
Il Enregistre les informations d'etudiants,calcul leur moyenne
et bien d'autres choses*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define MAX2 2000
#include "exo_fem.h"
//fonction de calcul de la moyenne
double Moyenne(double *Notes,int *Coef,int NbNotes)
{
int i=0;
int Scoef=0;
double Total=0;
//calcul de la moyenne
    for(i=1;i<=NbNotes;i++)
    {
        Total+=Notes[i]*Coef[i];
        Scoef+=Coef[i];
    }
return Total/Scoef;
}
//fonction de décison
void Decision(double moy,char d1[MAX],char d2[MAX])
{
    char chaine1[]="Tbien",chaine2[]="Bien",chaine3[]="Abien",chaine4[]="Passable",chaine5[]="Mediocre";
    char chaine6[]="Passe",chaine7[]="Redouble",chaine8[]="Renvoye";

    if(moy<10 && moy>=0)
    {
     strcpy(d1,chaine5);
     strcpy(d2,chaine8);
    }
    else if(moy<12 && moy>=10)
    {
     strcpy(d1,chaine4);
     strcpy(d2,chaine7);
    }
    else if(moy<14 && moy>=12)
    {
     strcpy(d1,chaine3);
     strcpy(d2,chaine6);
    }
    else if(moy<16 && moy>=14)
    {
     strcpy(d1,chaine2);
     strcpy(d2,chaine6);
    }
    else{strcpy(d1,chaine1);strcpy(d2,chaine6);}
}
//Fonction d'ajout et de calcul de la moyenne d'un etudiant
Etudiant AjoutEtudiant()
{
    Etudiant e;
    int i;

    printf("Nous allons ajouter un etudiant\nEntrer le nom,le prenom\n");
    scanf("%s",&e.nom);
    scanf("%s",&e.prenom);
    printf("Entrer le matricule et le nombre de notes(Ne doit pas depasser 8) de l'etudiant\nLe matricule:\n");
    scanf("%d",&e.matricule);
    do{
    printf("Le nombre de notes:");
    scanf("%d",&e.nbrenotes);}while(e.nbrenotes>8);
    printf("Nous allons maintenant prendre les notes en precisant le coefficient\n");
    for(i=1;i<=e.nbrenotes;i++)
    {
      printf("Entrer note %d:",i);
      scanf("%lf",&e.notes[i]);
      printf("Entrer coefficient %d:",i);
      scanf("%d",&e.coef[i]);
    }
//calcul de la moyenne
e.moyenne=Moyenne(e.notes,e.coef,e.nbrenotes);
printf("La moyenne est %f\n",e.moyenne);
//mention et passage
Decision(e.moyenne,e.mention,e.passage);
printf("Mention:%s\nDecision:%s\n",e.mention,e.passage);

    return e;
}
//Fonction pour afficher les informations d'un éléve
/*void AfficherEtudiant(FILE *fichier1,int no)
{
fichier1=fopen("InfosEtudiants.txt","r");
if(fichier1!=NULL)
{
fseek(fichier1,no,SEEK_SET);

}


}
//fonction d'ajout d'une note a un etudiant
void AjouteNote();
*/
int main()
{
Etudiant cppa;
int i=0,ChoixP=1,Choix=0;
FILE *fichier=NULL;//contient la liste des etudiants ajoutés
FILE *sauvegarde=NULL;//contient la sauvegarde des informations des etudiants ajoutes

while(ChoixP==1)
{
printf("Bienvenu(e)\nQuelle operation voulez effectue\n");
printf("1.Ajoute un etudiant\n2.Afficher les informations d'un etudiant\n");
printf("3.Ajouter/Modifier la note d'un etudiant\n");
do
{
    printf("Entrer le numero de choix:");
    scanf("%d",&Choix);}while(Choix==0);
switch(Choix)
{
 case 1:
     system("cls");
     cppa=AjoutEtudiant();
     //sauvegarde infos etudiansts
sauvegarde=fopen("InfosEtudiants.txt","a+");
if(sauvegarde==NULL)
{
    printf("Erreur de sauvegarde des informations\n");
}
else
{
    fprintf(sauvegarde,"Nom:%s\nPrenom:%s\nMatricule:%d\nNombre de notes:%d\nNotes:",cppa.nom,cppa.prenom,cppa.matricule,cppa.nbrenotes);
    for(i=1;i<=cppa.nbrenotes;i++)
    {
        fprintf(sauvegarde,"-%d.",i);
        fprintf(sauvegarde,"%f",cppa.notes[i]);
    }
    fputs("\nCoefficient:",sauvegarde);
    for(i=1;i<=cppa.nbrenotes;i++)
    {
        fprintf(sauvegarde,"-%d.",i);
        fprintf(sauvegarde,"%d",cppa.coef[i]);
    }
    fprintf(sauvegarde,"\nMoyenne:%f\nMention:%s\nDecision:%s\n\n",cppa.moyenne,cppa.mention,cppa.passage);
    fclose(sauvegarde);
}
//mise a jour liste des etudiants
     fichier=fopen("Etudiants.txt","a+");
     if(fichier!=NULL)
     {
        fprintf(fichier,"%s %s\n",cppa.nom,cppa.prenom);
     }
     else{printf("erreur de mise a jour de la liste des etudiants\n");}
     break;

 case 2:
     system("cls");

    break;

 case 3:
    system("cls");
    break;

 default:
    printf("Ce chiffre n'est pas valide\n");
    system("cls");
        break;
}
printf("Voulez-vous effectue une autre oepration\n1.Oui\n2.Non\n");
scanf("%d",&ChoixP);
}




    return 0;
}
