#include <stdio.h>
#include <string.h>

int moje_strlen(const char* str) {
    int len = 0;
    while(*(str + len++) != '\0') {}
    return len-1;
}

char* moje_strcat(char* dst, const char* src) {
    int offset = moje_strlen(dst);
    for(int i = 0; *(src + i) != '\0'; i++) {
        *(dst + offset + i) = *(src + i);
    }
    return dst;
}

const char* moje_strstr(const char* str1, const char* str2) {
    for(int i = 0; *(str1 + i) != '\0';) {
        for(int j = 0; ; j++) {
            if(*(str2 + j) == '\0') { // caly tekst znaleziony
                return str1 + i - j;
            }
            else if(*(str1 + i) != *(str2 + j)) {
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

// s/(\w*?)\[(.*?)\]/*($1 + $2)/g

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
    for(int i = 0; *(str + i) != '\0'; i++) {
        int diff = 'a' - 'A';
        // is lowercase letter?
        if(*(str + i) >= 97 && *(str + i) <= 122) {
            *(str + i) = *(str + i) - diff;
        }
    }
    return str;
}

char* moje_strlwr(char* str) {
    for(int i = 0; *(str + i) != '\0'; i++) {
        int diff = 'a' - 'A';
        // is uppercase letter?
        if(*(str + i) >= 65 && *(str + i) <= 90) {
            *(str + i) = *(str + i) + diff;
        }
    }
    return str;
}

void zad2() {
    char teststr1[32] = "AAAABBBBCCC";
    char teststr2[32] = "CDDDD";
    printf("strlen(%s) = %d\n", teststr1, moje_strlen(teststr1));
    printf("strcat(%s, %s) = %s\n", teststr1, teststr2, moje_strcat(teststr1, teststr2));

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

int main() {
    zad2();
    return 0;
}
