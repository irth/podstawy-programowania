#include <memory.h>
#include <stdio.h>

int* utworz_tablice(int n) {
    return new int[n];
}

void kopiuj_dodatnie(int* src, int size, int* positive, int* dst_size) {
    // we store positive numbers in stack array both to allocate as little as
    // posssible and not to reallocate
    int positive_buf[size];
    int positive_num = 0;
    for(int i = 0; i < size; i++) {
        if(src[i] > 0) {
            positive_buf[positive_num++] = src[i];
        }
    }

    positive = new int[positive_num];
    memcpy(positive, positive_buf, positive_num);
}

int main() {
    int n = 5;
    int* arr = utworz_tablice(n);
    arr[0] = -2;
    arr[1] = -1;
    arr[2] = 0;
    arr[3] = 1;
    arr[4] = 2;

    int* positive = NULL;
    int positive_size;
    kopiuj_dodatnie(arr, n, positive, &positive_size);

    for(int i = 0; i < positive_size; i++) {
        printf("%d ", positive[i]);
    }

}
