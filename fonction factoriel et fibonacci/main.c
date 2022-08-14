#include <stdio.h>
#include <stdlib.h>
//creation de la fonction factoriel
 int facto(int n)
 {
     if(n<=1)
     {
         return 1;
     }

     else
     {
         return n*facto(n-1);
     }
 }

//creation de la fonction suite de fibonacci
int fibo(int n)
{
    if(n==0)
    {
        return 0;
    }
    else if(n==1)
    {
        return 1;
    }
    else
    {
        return fibo(n-1)+fibo(n-2);
    }
}
int main()
{
    int n;
    printf("Entrer l'entier dont vous voulez le factoriel et le fibo\n");
    scanf("%d",&n);
    printf("le factoriel de %d est %d et le fibo est %d\n",n,facto(n),fibo(n));
    return 0;
}
