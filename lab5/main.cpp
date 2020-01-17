/*
	Autor: Marcel Guzik
	Grupa: środa parzysta 15:15
	Data: nie, 5 sty 2020, 00:51:50 CET
*/

#include <stdio.h>
#include <string.h>

void CzytajRownanie(float &a, float &b, float &c) {
    printf("Wpisz wspolczynniki a, b, c rownania ax + by = c, oddzielone spacja: ");
    scanf("%f %f %f", &a, &b, &c);
}

float ObliczWyznacznik(float p1, float p2, float p3, float p4) {
    return p1 * p4 - p2 * p3;
}

int ObliczRozwiazanie(float a1, float b1, float c1,
                      float a2, float b2, float c2, float &x, float &y) {
    //det = determinant
    float det_main = ObliczWyznacznik(a1, b1, a2, b2);
    float det_x = ObliczWyznacznik(c1, b1, c2, b2);
    float det_y = ObliczWyznacznik(a1, c1, a2, c2);
    if(det_main == 0) {
        if(det_x == 0 && det_y == 0) {
            // nieskonczenie wiele rozwiazan
            return 2;
        }
        else if(det_x != 0 && det_y != 0) {
            // brak rozwiazan (uklad sprzeczny)
            return 0;
        }
    }
    // jedno rozwiazanie (w parametrach x, y)
    x = det_x / det_main;
    y = det_y / det_main;
    return 1;
}

void WypiszRozwiazanie(int N, float x, float y) {
    printf("Rozwiazanie: ");
    switch(N) {
    case 2:
        printf("Nieskonczenie wiele rozwiazan\n");
        break;
    case 0:
        printf("Brak rozwiazan (uklad sprzeczny)\n");
        break;
    case 1:
        printf("x = %f; y = %f\n", x, y);
        break;
    }
}

void zad1() {
    // uklady rownan: a1x + b1y = c1
    //                a2x + b2y = c2;
    // x, y - rozwiazania
    float a1, a2, b1, b2, c1, c2, x, y;
    CzytajRownanie(a1, b1, c1);
    CzytajRownanie(a2, b2, c2);
    // liczba rozwiazan
    int N = ObliczRozwiazanie(a1, b1, c1, a2, b2, c2, x, y);
    WypiszRozwiazanie(N, x, y);
}

int moje_strlen(const char* str) {
    int len = 0;
    while(str[len++] != '\0') {}
    return len-1;
}

char* moje_strcat(char* dst, const char* src) {
    int offset = moje_strlen(dst);
    for(int i = 0; src[i] != '\0'; i++) {
        dst[offset + i] = src[i];
    }
    return dst;
}

const char* moje_strstr(const char* str1, const char* str2) {
    for(int i = 0; str1[i] != '\0';) {
        for(int j = 0; ; j++) {
            if(str2[j] == '\0') { // caly tekst znaleziony
                return str1 + i - j;
            }
            else if(str1[i] != str2[j]) {
                if(j == 0) {
                    i++;
                }
                break;
            }
            i++;
        }
    }
    return 0;   // nullpointer jesli nie znaleziono
}

int moje_strcmp(const char* p1, const char* p2) {
    char c1, c2;
    do {
        c1 = *p1++;
        c2 = *p2++;
        if(c1 == '\0') {
            return c1 - c2;
        }
    } while(c1 == c2);

    return c1 - c2;
}

char* moje_strupr(char* str) {
    for(int i = 0; str[i] != '\0'; i++) {
        int diff = 'a' - 'A';
        // is lowercase letter?
        if(str[i] >= 97 && str[i] <= 122) {
            str[i] = str[i] - diff;
        }
    }
    return str;
}

char* moje_strlwr(char* str) {
    for(int i = 0; str[i] != '\0'; i++) {
        int diff = 'a' - 'A';
        // is uppercase letter?
        if(str[i] >= 65 && str[i] <= 90) {
            str[i] = str[i] + diff;
        }
    }
    return str;
}
void zad2() {
    char teststr1[32] = "AAAABBBBCCC";
    char teststr2[32] = "CDDDD";
    printf("strlen(%s) = %d\n", teststr1, moje_strlen(teststr1));
    printf("strcat(%s, %s) = ", teststr1, teststr2);
    printf("%s\n", moje_strcat(teststr1, teststr2));

    char haystack[] = "substsubstringgg";
    char needle[] = "substring";
    printf("strstr(%s, %s) = %s\n", haystack, needle, moje_strstr(haystack, needle));

    char not_substr[] = "substring not present";
    printf("strstr(%s, %s) = %p\n", haystack, not_substr, moje_strstr(haystack, not_substr));

    printf("strcmp(\"AAAAB\",\"AAAAZ\") = %d\n", moje_strcmp("AAAAB", "AAAAZ"));

    char lower_upper_example[32] = "!@#$% a StRiNg ^&*()";
    char upper[32], lower[32];
    strcpy(upper, lower_upper_example);
    strcpy(lower, lower_upper_example);
    printf("strupr(%s) = %s\n", lower_upper_example, moje_strupr(upper));
    printf("strlwr(%s) = %s\n", lower_upper_example, moje_strlwr(lower));
}


int main(int argc, char** argv) {
    printf("Autor: Marcel Guzik\n");

    void (*funcs[])() = { zad1, zad2 };
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
            scanf(" %c", &choice);
            offset = choice - '0' - 1;
        }
        if(offset >= 0 && offset <= funcsLen - 1) {
            printf("%d\n", offset);
            funcs[offset]();
        }
    } while(choice != 'e' && choice != 'E');


    return 0;
}
