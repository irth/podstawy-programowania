/*
	Autor: Marcel Guzik
	Grupa: środa parzysta 15:15
	Data: Mon 11 Nov 17:54:19 CET 2019
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#ifndef __unix__
    #include <conio.h>
#endif

// cross platform getch, falling back to getchar on linux
// only use this for linux compatibility
// on windows, use getch directly
char xgetch() {
    #ifdef __unix__
        return getchar();
    #else
        return getch();
    #endif
}

void print_centered_line(char text, int width, int padding) {
    for(int i = 0; i < padding; i++) {
            printf(" ");
        }
        for(int i = 0; i < width; i++) {
            printf("%c", text);
        }
        for(int i = 0; i < padding; i++) {
            printf(" ");
        }
        printf("\n");
}

void print_xmas_tree(unsigned int height) {
    int width = 2 * (height-1) + 1;
    for(unsigned int j = 0; j < height; j++) {
        int currentWidth = 2 * j + 1;
        int padding = (width - currentWidth) / 2;
        print_centered_line('*', currentWidth, padding);
    }
    print_centered_line('#', 1, (width - 1) / 2);
}

void zad1() {
    printf("podaj wysokosc: ");
    unsigned int height;
    scanf("%d", &height);
    print_xmas_tree(height);
}

void zad2() {
    printf("podaj: liczba_wierszy libcza_kolumn (separowane spacja): ");
    int rows, columns;
    scanf(" %d %d", &rows, &columns);

    int x_label_width = snprintf(nullptr, 0, "%d", columns);
    int y_label_width = snprintf(nullptr, 0, "%d", rows);
    int max_width = snprintf(nullptr, 0, "%d", rows * columns);

    printf(" %*c |", y_label_width, ' ');
    for(int i = 1; i <= columns; i++) {
        printf("%*d", max_width + 1, i);
    }
    printf("\n");
    for(int i = 0; i < (columns + 1) * (max_width + 1) + 1; i++) {
        printf("=");
    }
    printf("\n");
    for(int y = 1; y <= rows; y++) {
        printf(" %*d |", y_label_width, y);
        
        for(int x = 1; x <= columns; x++) {
            printf("%*d", max_width + 1, x * y);
        }
        printf("\n");
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    int max = a > b ? a : b;
    while(max % a != 0 || max % b != 0) {
        max++;
    }
    return max;
}

void zad3() {
    printf("Podaj a, b (separowane spacja): ");
    int a, b;
    scanf(" %d %d", &a, &b);
    printf("nwd: %d\n", gcd(abs(a), abs(b)));
    printf("nww: %d\n", lcm(abs(a), abs(b)));
}

int digit_sum(unsigned long num) {
    int sum = 0;
    while(num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void zad4() {
    printf("podaj liczbe: ");
    unsigned long num;
    scanf(" %ld", &num);
    printf("suma cyfr: %d\n", digit_sum(num));
}

void zad5() {
    // "hashmap" for amount of occurences of chars in the key
    // implemented as key/value pairs
    char keys[] = "aeiouy";
    int values[6] = { 0 };
    printf("Wpisuj litery: ");
    char input;
    int chars_written = 0;
    do {
        input = tolower(xgetch()); // getch(); -- not available in linux
        // co zrobic jezeli podany znak to newline albo spacja?
        if(input != ' ' && input != '\n') {
            chars_written++;
        }
        
        for(int i = 0; i < 6; i++) {
            if(keys[i] == input) {
                values[i]++;
                break;
            }
        }
    } while(input != 'k');

    printf("Wpisano ogolem %d znakow w tym:\n", chars_written);
    for(int i = 0; i < 6; i++) {
        printf("litera %c  %d ", toupper(keys[i]), values[i]);
        for(int j = 0; j < values[i]; j++) {
            printf("#");
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    printf("Autor: Marcel Guzik\n");

    void (*funcs[])() = { zad1, zad2, zad3, zad4, zad5 };
    int funcsLen = sizeof(funcs) / sizeof(void*);

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
            printf("wybierz zadanie (1-%d). 'E' zeby wyjsc: ", funcsLen);
            // https://stackoverflow.com/questions/5240789/scanf-leaves-the-new-line-char-in-the-buffer
            scanf(" %c", &choice);
            offset = choice - '0' - 1;
        }
        if(offset >= 0 && offset <= funcsLen - 1) {
            funcs[offset]();
        }
    } while(choice != 'e' && choice != 'E');

    return 0;
}
