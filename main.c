#include <stdio.h>
#include <stdlib.h>

int table(int);

int main()
{
    int n = 5 ;
    table(n);
    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}


float convertisseur(float celsius)
{
    return (celsius * 9.0 / 5.0) + 32.0;
}

float super_convertisseur()
{
    char temp;
    printf("Celisius : C ou Fahrenheit : F\n");
    scanf(" %c", &temp);

    if (temp == 'C' || temp == 'c'){
        float celsius;
        printf("Entrez la temperature en Celsius : ");
        scanf("%f", &celsius);
        return convertisseur(celsius);
    }

    else if (temp == 'F' || temp == 'f'){
        float fahrenheit;
        printf("Entrez la temperature en Fahrenheit : ");
        scanf("%f", &fahrenheit);
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }

    else {
        printf("Unite non reconnue.\n");
        return 0.0;
    }
}

int addition(int a, int b)
{
    return a + b;
}   

int produit(int a, int b)
{
    return a * b;
}


int difference(int a, int b)
{
    return a - b;
}

int quotient(int a, int b)
{
    if (b == 0) {
        printf("Erreur : Division par zero.\n");
        return 0;
    }
    return a / b;
}

float quotient_float(float a, float b)
{
    if (b == 0.0) {
        printf("Erreur : Division par zero.\n");
        return 0.0;
    }
    return a / b;
}

int table(int n)
{
    for (int i = 1; i<= n; i++) {
        printf("%d x %d = %d\n", n, i, n*i);
    }
}

int table_1_10()
{
    for (int i = 1; i <= 10; i++) {
        table(i);
        printf("\n");
    }
}

int somme(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("La somme des entiers de 1 a %d est %d\n", n, sum);
    int sum2 = n * (n + 1) / 2;
    printf("Verification par formule : %d\n", sum2);
    return sum;
}

  