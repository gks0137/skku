#include <stdio.h>
#include <stdlib.h>

int*(*(*f(int(*(*a)[3])[3]))[3])[3] {
    int *(*(*r)[3])[3] = (int *(*(*)[3])[3])malloc(sizeof(int *(*(*)[3])[3]));
    for (int i = 0; i < 3; i++) {
        (*r)[i] = (int*(*)[3])malloc(sizeof(int*[3]));
        for (int j = 0; j < 3; j++) {
            (*(*r)[i])[j] = &(*(*a)[i])[j];
        }
    }


    return r;
}


int main() {
    int a[3] = {1, 2, 3}, b[3] = {4, 5, 6}, c[3] = {7, 8, 9};
    int (*t[3])[3] = {&a, &b, &c};
    int (*(*p)[3])[3] = &t;
    int *(*(*r)[3])[3] = f(p);
    
    if (r != NULL) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", (*(*p)[i])[j]);
                printf("%d ", *(*(*r)[i])[j]);
            }
            printf("\n");
            free((*r)[i]);
        }
        free(r);
    }
    
    
    return 0;
}
