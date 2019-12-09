#include <string.h>
#include <stdio.h>

void Dodaj5spacji(char t[])
{
  //przesuniecie wszystkich liter o 5 pozycji w prawo
  memmove( t+5, t, strlen(t)+1 );

  //wypełnienie wolnych miejsc spacjami
  for(int i=0; i<5; i++)
    t[i]=32;
}

int main() {
    char str1[] = "AAAABBBBCCCCDDD";
    char str2[] = "this should not change";

    Dodaj5spacji(str1);

    puts(str1);
    puts(str2);
}
