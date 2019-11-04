/*
	Autor: Marcel Guzik
	Grupa: środa parzysta
	Data: Mon  4 Nov 16:40:36 CET 2019
*/

#include <stdio.h>
#include <string.h>

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

int main(int argc, char** argv) {
    printf("Autor: Marcel Guzik\n");

    zad2();

    return 0;
}
