#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t compter_voyelles(const char* str){
    int c = 0;
    char voy[] = "aeiouyAEIOUY";
    for (int i=0; i< strlen(str); i++){
        if (strchr(voy, str[i])) {
            c+=1;
        }
    }
    return c;
}

void inverser_chaine(char*  str){
    char *p = str;
    int n =  strlen(str);
    char* str2 = str;
    for (int i = 0; i<n ; i++){
        *p = str2[n-i-1];
        p++;
    }
}

int main(){
    char mot[] = "BOUbou";
    int c = compter_voyelles(mot);
    printf("%d\n", c);
    char *p = mot;
    inverser_chaine(mot);
    printf("%s", mot);
    return 0;
}