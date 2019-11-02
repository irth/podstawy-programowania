/*
	Autor: Marcel Guzik
	Grupa: środa parzysta 15:15
	Data: śro, 30 paź 2019, 15:28:22 CET
*/

#include <stdio.h>
#include <math.h>

void zad1() {
    float a, b, c;
    printf("podaj liczby: a, b, c, oddzielone spacjami\n");
    scanf("%f %f %f", &a, &b, &c);  // TODO: check for bad input

    if(a == 0) {
        printf("rownanie nie jest kwadratowe\n");
        return;
    }

    float delta = b * b - 4 * a * c;
    if(delta < 0) {
        printf("brak pierwiastkow rzeczywistych");
        return;
    }

    // jesli delta == 0, to x1 == x2 wiec nie piszemy
    // osobnego brancha dla delta == 0
    float x1 = (-b - sqrt(delta)) / (2 * a);
    float x2 = (-b + sqrt(delta)) / (2 * a);

    if(x1 == x2) {
        printf("x0 = %f\n", x1);
    } else {
        printf("x1 = %f\nx2 = %f\n", x1, x2);
    }
}

bool is_przestepny(int year) {
    return !((year % 4 != 0) || (year % 100 == 0 && year % 400 != 0));
}

bool is_date_correct(unsigned int day, unsigned int month, unsigned int year) {
    // checking both days and months handled by switch
    // if month <= 12, we return from switch (case hit)
    // if not, we also return from switch (hit default, return false)
    switch(month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return day <= 31;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        return day <= 30;
        break;

    case 2:
        if(is_przestepny(year)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
        break;
    default:
        return false;
        break;
    }
    return true;
}

void zad2() {
    printf("podaj date w formacie (dzien) (miesiac) (rok): ");
    int day, month, year;
    scanf("%d %d %d", &day, &month, &year);
    // evil type hackery: due to how int casts to unsigned int, if int < 0,
    // then unsigned int has its most significant bit set,
    // thus its always bigger than 31
    if(is_date_correct(day, month, year)) {
        printf("data poprawna\n");
    } else {
        printf("data niepoprawna\n");
    }
}

void zad3() {
    float min, max;
    unsigned int rows;
    scanf("%f %f %d", &min, &max, &rows);
    if(max < min) { // swap
        float buf = min;
        min = max;
        max = buf;
    }

    if(min <= 0 || max <= 0 || rows <= 0) {
        printf("bad data\n");
    }

    printf("=========================================\n");
    printf("| Lp | promien | obwod kola | pole kola |\n");
    printf("=========================================\n");
    for(unsigned int i = 1; i <= rows; i++) {
        float current_radius = min + (max - min) / (rows - 1) * (i - 1);
        float obwod = 2 * current_radius * M_PI;
        float area = current_radius * current_radius * M_PI;
        printf("| %2d | %7.2f | %10.2f | %9.2f |\n", i, current_radius, obwod, area);
    }
    printf("=========================================\n");
}

int main() {
    char choice;
    do {
        printf("wybierz zadanie (1-3). 'E' zeby wyjsc: ");
        scanf("%c", &choice);
        switch(choice) {
            case '1':
                zad1();
                break;
            case '2':
                zad2();
                break;
            case '3':
                zad3();
                break;
        }
    } while(choice != 'e' || choice != 'E');
}
