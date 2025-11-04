#include <stdio.h>
#include <stdlib.h>

int somme_tableau( int tab[], size_t taille)
{
    int somme = 0;
    for (int i=0 ; i< taille ; i++){
        somme += tab[i];
    }
    return somme;
}

int max_tableau(int tab[], size_t taille)
{
    int max = tab[0];
    for (int i=1; i<taille ; i++){
        int c = tab[i];
        if(max < c){
            max = c;
        }
    }
    return max;
}


int main(){
    int tab[5] = {1,2,3,4,5};
    int taille = 5;
    int somme = somme_tableau(tab, taille);
    int max = max_tableau(tab, taille);
    printf("la somme du tableau est %d\n" , somme);
    printf("le max du tableau est %d\n", max);
    return 0;
}