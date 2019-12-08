#include <stdio.h>
#include <math.h>

void print_odd_multiples_of_7(const int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\n", 14 * i + 7);
    }
}

void sum_of_squares_less_than_50(int a, int b) {
    if(a > b) {
        return;
    }
    for(int x = a; x <= b; x++) {
        for(int y = a; y <= b; y++) {
            int result = x * x + y * y;
            if(result <= 50) {
                printf("(%d, %d): %d^2 + %d^2 = %d\n", x, y, x, y, result);
            }
        }
    }
}

void zadc() {
    int num_letters = 0, num_digits = 0;
    char input, prevInput = 0;
    int num_input_same_as_prev = 0;
    do {
        input = (char)getchar();
        if(input == '\n') {
            continue;
        }
        if(input >= '0' && input <= '9') {
            num_digits++;
        }
        else if(input >= 'a' && input <= 'z') {
            num_letters++;
        }

        if(input == prevInput) {
            num_input_same_as_prev++;
        } else {
            num_input_same_as_prev = 0;
        }

        prevInput = input;
    } while(num_input_same_as_prev < 2);

    if(num_letters > num_digits) {
        printf("wiecej liter\n");
    }
    else if(num_digits > num_letters) {
        printf("wiecej cyfr\n");
    }
    else {
        printf("tyle samo\n");
    }
}

void zadd(unsigned int n) {
    for(int i = (-n / 2) * 2 + 1; i <= (int)n; i += 2) {
        printf("%d^2 = %d\n", i, i*i);
    }
}

void zade() {
    int min, max;
    printf("podaj dane w formacie: min[spacja]max\n");
    scanf(" %d %d", &min, &max);
    if(max < min) {
        return;
    }
    int nearest_odd = (min / 2) * 2 + 1;
    long product = nearest_odd;
    for(int i = nearest_odd + 2; i <= max; i += 2) {
        product *= i;
    }
    printf("%ld", product);
}

void zadf(unsigned int n) {
    float sum = 1;
    for(unsigned int i = 1; i < n; i++) {
        sum += sin((float)i);
    }
    printf("%f\n", sum);
}

void zadg() {
    for(int x = 1; x <= 1000; x++) {
        if(x != 50) {
            if((float)(x * x) / (float)(50 - x) - sin((float)x) >= 0) {
                printf("%d ", x);
            }
        }
    }
    printf("\n");
}

int zadh() {
    return 0;
}

void zadi() {
    // we assume charset = lowercase ascii
    // we generate only prefixes, inverted prefixes are suffixes
    for(char i = 'a'; i <= 'z'; i++) {
        for(char j = 'a'; j <= 'z'; j++) {
            printf("%c%c%c%c ", i, j, j, i);
        }
    }
    printf("\n");
}

int main() {
    zadi();
}