/*
	Autor: Marcel Guzik
	Grupa: środa parzysta 15:15
	Data: pią, 17 sty 2020, 09:50:22 CET
*/

// UWAGA: podczas pisania kolokwium nie zadzialal fgets, wiec jezeli program nie dziala, problemem moze byc
// fgets w linii 179 (testowane na GCC 8.3.0)

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

    printf("ID | Nazwa | Cena | Ilosc\n");
    printf("===+=======+======+======\n");
    for(size_t i = 0; i < size; i++) {
        Towar t = towary[i];
        printf("%lu  | %s | %d | %d\n", i, t.nazwa, t.cena, t.ilosc);
    }
    printf("\n");
}

// musi zwracac wskaznik poniewaz realloc moze przeniesc tablice w inne miejsce w pamieci
// alternatywa jest przekazanie tablicy jako wskaznik do wskaznika (wtedy moglibysmy zaktualizowac cel wskaznika
// po przeniesieniu tablicy).
Towar* towary_append(Towar* towary, size_t* size, Towar t) {
    // sprawdz czy juz nie ma takiego towaru
    for(size_t i = 0; i < *size; i++) {
        if(strcmp(towary[i].nazwa, t.nazwa) == 0 && towary[i].cena == t.cena) {
            towary[i].ilosc += t.ilosc;
            return towary;
        }
    }

    // nie musimy sprawdzac czy towary == nullptr bo (z dokumentacji):
    //      In case that ptr is a null pointer, the function behaves like malloc, assigning a new block of size bytes
    //      and returning a pointer to its beginning.
    Towar* new_towary = (Towar *)realloc(towary, sizeof(Towar) * (*size + 1));
    if(new_towary == NULL) {
        return towary;
    }
    towary = new_towary;
    towary[(*size)++] = t;
    return towary;
}

// zwraca `Towar*` zeby sygnatura funkcji byla podobna do `towary_append`. Z tego samego powodu przyjmuje rozmiar jako
// wskaznik.
Towar* towary_remove(Towar* towary, size_t* size, size_t idx) {
    if(idx >= *size) {
        printf("error: Nieprawidlowy element! Tablica ma tylko %lu elementow (0-%lu); wybrany element: %lu",
            *size, *size-1, idx);
        return towary;
    }

    free(towary[idx].nazwa);
    memmove(towary + idx, towary + idx + 1, (--(*size) - idx) * sizeof(Towar));
    towary = (Towar *)realloc(towary, *size);
    return towary;
}

Towar* towary_free(Towar* towary, size_t* size) {
    if(towary == NULL) {
        printf("error: Brak tablicy\n");
        return NULL;
    }

    for(size_t i = 0; i < *size; i++) {
        free(towary[i].nazwa);
    }

    free(towary);
    *size = 0;
    return NULL;
}

void print_help() {
    printf("KOMENDY:\n");
    printf("\th\t\tpomoc\n");
    printf("\tp\t\twypisz zawartosc\n");
    printf("\ta TOWAR\t\tdodaj TOWAR do bazy\n");
    printf("\t\t\t\tTOWAR = NAZWA CENA ILOSC\n");
    printf("\t\t\t\tUWAGA: nazwa nie moze zawierac spacji\n");
    printf("\t\t\t\tPrzyklad: a klej 20 10\n");
    printf("\tr INDEKS\tusun towar o indeksie INDEKS z bazy\n");
    printf("\td\t\tusun cala tablice\n");
    printf("\tc\t\tutworz nowa, pusta tablice. zwolnij aktualna jezeli nie usunieto\n");
}

void exec_cmd(char* cmd, Towar** towary, size_t* size) {
    switch(cmd[0]) {
        case 'h':
            print_help();
            break;
        case 'p':
            towary_print(*towary, *size);
            break;
        case 'a': {
            char nazwa[128];
            int cena, ilosc;
            int args = sscanf(cmd + 1, "%s %d %d", nazwa, &cena, &ilosc);
            if(args != 3) {
                printf("Zle argumenty do funkcji a (add)!\n");
                print_help();
                return;
            }
            // kiedy znamy juz dlugosc nazwy, kopiujemy ja do mniejszego bufora na stercie
            char* nazwa2 = (char*)malloc(strlen(nazwa));
            strcpy(nazwa2, nazwa);
            Towar t = {
                .nazwa = nazwa2,
                .cena = cena,
                .ilosc = ilosc
            };
            *towary = towary_append(*towary, size, t);

            towary_print(*towary, *size);
        }
            break;
        case 'r': {
            int idx;
            int args = sscanf(cmd + 1, "%d", &idx);
            if(args != 1) {
                printf("Zle argumenty do funkcji r (remove)!\n");
                print_help();
                return;
            }
            *towary = towary_remove(*towary, size, idx);
            towary_print(*towary, *size);
        }
            break;
        case 'd': {
            *towary = towary_free(*towary, size);
        }
            break;

        case 'c': {
            if(*towary != NULL) {
                *towary = towary_free(*towary, size);
            }
            *towary = towary_new(size);
        }
        break;
        default:
            printf("Nieprawidlowa komenda!\n");
            print_help();
            break;
    }
}

int main() {
    printf("Autor: Marcel Guzik\n");

    size_t Rozmiar = 0;
    Towar* Tab = towary_new(&Rozmiar);

    char input[256];
    print_help();
    do {
        printf("(tab = %p, rozmiar = %lu)> ", Tab, Rozmiar);
        fgets(input, 256, stdin);
        exec_cmd(input, &Tab, &Rozmiar);
    } while(true);
    
    towary_free(Tab, &Rozmiar);

    return 0;
}
