#include <stdlib.h>
#include <stdio.h>


struct Matrix {
    size_t rows;
    size_t cols;
    double *data; // Pointeur vers un tableau de pointeurs
};
typedef struct Matrix Matrix;


Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = malloc(rows * cols * sizeof(int));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    return matrix;
}

void free_matrix(Matrix* mat){
    if (mat != NULL){
        free(mat);
    }
}

void set_value(Matrix* mat, size_t row, size_t col, double value){
    mat->data[col + row * mat->cols] = value;
}

double get_value(const Matrix* mat, size_t row, size_t col){
    return mat->data[col + row * mat->cols];
}

Matrix* product(const Matrix* a, const Matrix* b){
    int n = a->rows;
    int p = a->cols;
    int q = b->rows; 
    int m = b->cols;
    if (p!=q) {   
        printf("produit non définit");
        return NULL;
    }
    Matrix* matrice = create_matrix(n, m);
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            double somme = 0;
            for (int k = 0; k<p; k++){
                somme = somme + get_value(a,i,k)*get_value(b,k,j);
            }
            set_value(matrice,i,j,somme);
        }
    }
    return (matrice);
}


int main(){
    printf("bonjour\n");

    return 0;
}