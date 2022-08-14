/*Enregistrer un bateau en fonction des preferences et le retourner*/
Bateau SaveBato(int c);/*prendre la disposition choisi par le joueur pour un bateau*/

void Verif1Bato(Bateau Bat[MAX],int TGril,int c,int N);/*tester si le bateau peut rester dans limites de la grille*/

void Verif2Bato(char Gril[MAX][MAX], Bateau Bat[MAX],int c,int N);

/*Placer un bateau en fonction des preferences du joueur et en testant si le placement est possible*/
void PlacerBato(char Gril[MAX][MAX], Bateau Bat[MAX],int TGril,int c,int N);/* N: numero de bateau*/
