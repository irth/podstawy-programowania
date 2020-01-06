#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Towar {
    char* nazwa;
    int cena;
    int ilosc;
};

Towar* towary_new(size_t *size) {
    *size = 0;
    return (Towar *)calloc(sizeof(Towar), 0);
}

void towary_print(Towar* towary, size_t size) {
    if(towary == NULL) {
        printf("Brak tablicy\n");
        return;
    }

    printf("Nazwa | Cena | Ilosc\n");
    printf("======+======+======\n");
    for(int i = 0; i < size; i++) {
        Towar t = towary[i];
        printf("%s | %d | %d\n", t.nazwa, t.cena, t.ilosc);
    }
}

size_t towary_append(Towar* towary, size_t size, Towar t) {
    // nie musimy sprawdzac czy towary == nullptr bo (z dokumentacji):
    //      In case that ptr is a null pointer, the function behaves like malloc, assigning a new block of size bytes
    //      and returning a pointer to its beginning.
    Towar* new_towary = (Towar *)realloc(towary, sizeof(Towar) * (size + 1));
    if(new_towary == NULL) {
        return size;
    }
    towary = new_towary;
    towary[size] = t;
    return size + 1;
}

size_t towary_remove(Towar* towary, size_t size, int idx) {
    if(idx >= size) {
        printf("error: Nieprawidlowy element! Tablica ma tylko %d elementow (0-%d); wybrany element: %d",
            size, size-1, idx);
        return size;
    }

    free(towary[idx].nazwa);
    size--;
    memmove(towary + idx, towary + idx + 1, (size - idx) * sizeof(Towar));
    towary = (Towar *)realloc(towary, size);
    return size;
}

void towary_free(Towar* towary, size_t size) {
    if(towary == NULL) {
        printf("error: Brak tablicy\n");
        return;
    }

    for(int i = 0; i < size; i++) {
        free(towary[i].nazwa);
    }

    free(towary);
}

void print_help() {
    printf("KOMENDY:\n");
}

void exec_cmd(char* cmd) {
    return;
}

int main() {
    size_t Rozmiar = 0;
    Towar* Tab = towary_new(&Rozmiar);

    char input[256];
    print_help();
    do {
        printf("(towary): ");
        scanf("%s", &input);
        exec_cmd(input);
    } while(true);
    
    towary_free(Tab, Rozmiar);
    
    return 0;
}
