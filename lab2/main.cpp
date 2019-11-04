/*
	Autor: Marcel Guzik
	Grupa: środa parzysta 15:15
	Data: śro, 30 paź 2019, 15:28:22 CET
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

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
    printf("podaj: min_obwod max_obwod ilosc_wierszy\n");
    float min, max;
    unsigned int rows;
    scanf("%f %f %d", &min, &max, &rows);
    if(max < min) { // swap
        float buf = min;
        min = max;
        max = buf;
    }

    if(min <= 0 || max <= 0 || rows <= 0) {
        printf("zle dane\n");
    }

    printf("+=======================================+\n");
    printf("| Lp | promien | obwod kola | pole kola |\n");
    printf("+=======================================+\n");
    for(unsigned int i = 1; i <= rows; i++) {
        float current_radius = min + (max - min) / (rows - 1) * (i - 1);
        float circumference = 2 * current_radius * M_PI;
        float area = current_radius * current_radius * M_PI;
        printf("| %2d | %7.2f | %10.2f | %9.2f |\n", i, current_radius, circumference, area);
    }
    printf("+=======================================+\n");
}

void zad4() {
    printf("n0 = ");
    int n0;
    scanf(" %d", &n0);

    int n = n0;
    for(unsigned int i = 1; n != 1; i++) {
        int next_n;

        if(n % 2 == 0) {
            next_n = n / 2;
            printf("%d, %d, %s, %d\n", i, n, "parzyste", next_n);
        } else {
            next_n = 3 * n + 1;
            printf("%d, %d, %s, %d\n", i, n, "nieparzyste", next_n);
        }
        n = next_n;
    }
}

void zad5a() {
    printf("podaj liczby calkowite: a b\n");
    int min, max;
    scanf(" %d %d", &min, &max);
    if(max < min) {
        int buf = max;
        max = min;
        min = buf;
    }

    int randomised = min + rand() % (max - min + 1);
    int sum = randomised;
    int smallest = randomised, biggest = randomised;

    for(unsigned int i = 1; i < 20; i++) {
        int randomised = min + rand() % (max - min + 1);

        if(randomised < smallest) {
            smallest = randomised;
        }
        else if(randomised > biggest) {
            biggest = randomised;
        }

        sum += randomised;
    }

    double avg = (double)sum / 20.0;
    printf("najmniejsza: %d\nnajwieksza: %d\nsrednia: %f\n", smallest, biggest, avg);
}

void zad5b() {
    printf("podaj liczby rzeczywiste: a b\n");
    double min, max;
    scanf(" %lf %lf", &min, &max);
    if(max < min) {
        double buf = max;
        max = min;
        min = buf;
    }

    int randomised = min + (max - min) * rand() / ((double)RAND_MAX);
    double sum = randomised;
    double smallest = randomised, biggest = randomised;

    for(unsigned int i = 1; i < 20; i++) {
        double randomised = min + (max - min) * rand() / ((double)RAND_MAX);

        if(randomised < smallest) {
            smallest = randomised;
        }
        else if(randomised > biggest) {
            biggest = randomised;
        }

        sum += randomised;
    }

    double avg = sum / 20.0;
    printf("najmniejsza: %f\nnajwieksza: %f\nsrednia: %f\n", smallest, biggest, avg);
}

void zad5() {
    printf("(a/b): ");
    char choice;
    do {
        scanf(" %c", &choice);
        if(choice == 'a') {
            zad5a();
        }
        else if(choice == 'b') {
            zad5b();
        }
    } while(choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B');
}

int main(int argc, char** argv) {
    srand(time(NULL));
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
}
