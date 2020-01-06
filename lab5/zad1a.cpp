#include <stdio.h>

void CzytajRownanie(float *a, float *b, float *c) {
    printf("Wpisz wspolczynniki a, b, c rownania ax + by = c, oddzielone spacja: ");
    scanf("%f %f %f", a, b, c);
}

float ObliczWyznacznik(float p1, float p2, float p3, float p4) {
    return p1 * p4 - p2 * p3;
}

int ObliczRozwiazanie(float a1, float b1, float c1,
                      float a2, float b2, float c2, float *x, float *y) {
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
    *x = det_x / det_main;
    *y = det_y / det_main;
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
    CzytajRownanie(&a1, &b1, &c1);
    CzytajRownanie(&a2, &b2, &c2);
    // liczba rozwiazan
    int N = ObliczRozwiazanie(a1, b1, c1, a2, b2, c2, &x, &y);
    WypiszRozwiazanie(N, x, y);
}

int main() {
    zad1();
}
