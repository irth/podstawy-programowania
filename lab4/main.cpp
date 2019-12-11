/*
	Autor: Marcel Guzik
	Grupa: środa parzysta
	Data: śro, 11 gru 2019, 16:48:08 CET
*/

#include <stdio.h>
#include <string.h>
#include <random>

#define ROZMIAR 5

void init_array(float* arr) {
    for(int i = 0; i < ROZMIAR; i++) {
        printf("Tab[%d] = ", i);
        float val;
        scanf(" %f", &val);
        arr[i] = val;
    }
}

void print_array(float* arr) {
    printf("Tab = [  ");
    for(int i = 0; i < ROZMIAR; i++) {
        printf("%.1f  ", arr[i]);
    }
    printf("]\n");
}

void array_stats(float* arr) {
    int positive = 0, negative = 0;
    float positive_sum = 0, negative_sum = 0;

    bool ascending = true, descending = true;

    for(int i = 0; i < ROZMIAR; i++) {
        if(i > 0) {
            float diff = arr[i] - arr[i - 1];
            if(diff > 0 && (ascending || descending)) {
                descending = false;
            }
            else if(diff < 0) {
                ascending = false;
            }
        }
        if(arr[i] > 0) {
            positive++;
            positive_sum += arr[i];
        }
        else if(arr[i] < 0) {
            negative++;
            negative_sum += arr[i];
        }
    }
    float positive_avg = positive_sum / ROZMIAR;
    float negative_avg = negative_sum / ROZMIAR;

    printf("Dodatnie: %d, ujemne: %d\n", positive, negative);
    printf("Suma dodatnich: %f, suma ujemnych: %f\n", positive_sum, negative_sum);
    printf("Srednia dodatnich: %f, srednia ujemnych: %f\n", positive_avg, negative_avg);
    if(ascending) {
        printf("Elementy tablicy sa uporzadkowane rosnaco\n");
    }
    else if(descending) {
        printf("Elementy tablicy sa uporzadkowane malejaco\n");
    }
}

void sort_insertion(float* arr) {
    int i = 1;
    while(i < ROZMIAR) {
        int j = i;
        while(j > 0 && arr[j-1] > arr[j]) {
            float buf = arr[j-1];
            arr[j-1] = arr[j];
            arr[j] = buf;
            j--;
        }
        i++;
    }
}

// void zad1(float* arr) {
//     init_array(arr);
//     print_array(arr);
//     array_stats(arr);
// }

void zad2(float* arr) {
    printf("podaj zakres (min max): ");
    float min, max;
    scanf("%f %f", &min, &max);
    if(min > max) {
        float buf = min;
        min = max;
        max = buf;
    }
    for(int i = 0; i < ROZMIAR; i++) {
        arr[i] = min + (max - min)*rand()/((double)RAND_MAX);
    }
    print_array(arr);
    array_stats(arr);
}

struct menu_entry {
    char* label;
    void (*func)(float*);
};

menu_entry create_entry(char* label, void (*func)(float*)) {
    return menu_entry {
        .label = label,
        .func = func
    };
}

int main(int argc, char** argv) {
    srand(time(NULL));
    printf("Autor: Marcel Guzik\n");

    menu_entry menu[] = {
        create_entry("Wczytaj elementy tablicy z klawiatury", init_array),
        create_entry("Wypisz tablice", print_array),
        create_entry("Wypisz statystyki tablicy", array_stats),
        create_entry("Wygeneruj nowa tablice", zad2),
        create_entry("Posortuj tablice", sort_insertion),
    };

    int menu_len = sizeof(menu) / sizeof(menu_entry);

    float arr[ROZMIAR];

    char choice;
    do {
        int offset;
        // passing exercise number as command line argument
        if(argc > 1) {
            if(strlen(argv[1]) == 1) {
                offset = *argv[1] - '0' - 1;
            }
            choice = 'e';
        }
        else {
            for(int i = 0; i < menu_len; i++) {
                printf("%d) %s\n", i + 1, menu[i].label);
            }
            printf("wybierz zadanie (1-%d). 'E' zeby wyjsc: \n", menu_len);

            // https://stackoverflow.com/questions/5240789/scanf-leaves-the-new-line-char-in-the-buffer
            scanf(" %c", &choice);
            offset = choice - '0' - 1;
        }
        if(offset >= 0 && offset <= menu_len - 1) {
            menu[offset].func(arr);
        }
    } while(choice != 'e' && choice != 'E');

    return 0;
}
