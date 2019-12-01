#include <memory.h>
#include <string.h>
#include <stdio.h>

// a
void shift_one_up_wrapping(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[(i + 1) % n] = arr[i];
    }
}

// b
bool is_symmetrical(float* arr, int n) {
    for(int i = 0; i < n / 2; i++) {
        if(arr[i] != arr[n - i]) {
            return false;
        }
    }
    return true;
}

// c
float min_positive(float* tab) {
    int n = 100;
    float min = tab[0];
    for(int i = 1; i < n; i++) {
        if(tab[i] > 0 && tab[i] < min) {
            min = tab[i];
        }
    }
    return min;
}

// d
int num_letters_not_unique(char* arr) {
    char keys[] = "abcdefghijklmnopqrstuvwxyz";
    int values[26] = {0};

    int n = 200;
    for(int i = 0; i < n; i++) {
        char* k = strchr(keys, arr[i]);
        if(k == NULL) {
            break;
        }
        int index = (int)(k - keys);
        values[index] += 1;
    }
    
    int not_unique = 0;
    for(int i = 0; i < 26; i++) {
        if(values[i] > 1) {
            not_unique++;
        }
    }
    return not_unique;
}

// e
void print_reverse_idx(int* arr) {
    int n = 20;
    for(int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_reverse_ptr(int* arr) {
    int* head = &arr[20];
    while(head-- != arr) {
        printf("%d ", *head);
    }
    printf("\n");
}

int main() {
    const int n = 20;
    int arr[n];
    for(int i = 0; i < n; i++) {
        arr[i] = i;
    }

    print_reverse_idx(arr);
    print_reverse_ptr(arr);
}