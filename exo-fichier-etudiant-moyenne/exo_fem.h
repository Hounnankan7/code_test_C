#ifndef CONSTfem
#define CONSTfem


typedef struct
{
char nom[MAX];
char prenom[MAX];
int matricule;
int nbrenotes;
double notes[9];
int coef[9];
double moyenne;
char mention[MAX];
char passage[MAX];
}Etudiant;

#endif
