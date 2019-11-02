/*
	Autor: Marcel Guzik
	Grupa: SR/P 15:15
	Temat: Lab1
	Data: 16.10.2019
*/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

const int CARD_WIDTH = 40;

// WSZYSTKIE ZADANIA W JEDNYM PLIKU
// zadania w osobnych funkcjach

// to make a pretty box with iostream we'd have to use iomanip
void print_card(char* name, char* number, char* address) {
	std::cout << "Imie i nazwisko: " << name << '\n';
	std::cout << "Numer: " << number << '\n';
	std::cout << "Adres: " << address << std::endl;
}

void print_card_row(char* label, char* data, unsigned int width) {
	int data_width = width - strlen(label) - 4; // label + colon + single space
	printf("| %s: %*s |\n", label, data_width, data);
}

// possible errors:
// - too long data (need to detect if above max width and
// resize box accordingly
void print_card_c(char* name, char* number, char* address, unsigned int width) {
	char* labels[] = {"Imie i nazwisko", "Numer", "Adres"};
	
	// apparently printf doesnt have a way to print a character repeatedly
	// https://stackoverflow.com/questions/14678948/how-to-repeat-a-char-using-printf
	printf("+");
	for(unsigned int i = 0; i < width; i++) {
		printf("-");
	}
	printf("+\n");
	print_card_row(labels[0], name, width);
	print_card_row(labels[1], number, width);
	print_card_row(labels[2], address, width);
	printf("+");
	for(unsigned int i = 0; i < width; i++) {
		printf("-");
	}
	printf("+\n");
}

void zad2() {
	int a, b, c;
	std::cin >> a >> b >> c;
	std::cout << "Suma: " << a + b + c
		<< "\nIloczyn: " << a * b * c
		<< "\nSrednia: " << (float)(a+b+c) / 3.0
		<< std::endl;
}

void zad2_c() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf(
		"Suma: %d\nIloczyn: %d\nSrednia: %f\n",
		a + b + c,
		a * b * c,
		(float)(a+b+c) / 3.0
	);
}

void zad3() {
	float r;
	std::cin >> r;
	float area = 4 * M_PI * r * r;
	float volume = (4.0 / 3.0) * M_PI * pow(r, 3);
	std::cout << "pole powierzchni kuli: "<< area
		<< "\nobjetosc kuli: " << volume << std::endl;
}

void zad3_c() {
	float r;
	scanf("%f", &r);
	float area = 4 * M_PI * r * r;
	float volume = (4.0 / 3.0) * M_PI * pow(r, 3);
	printf("pole powierzchni kuli: %f\nobjetosc kuli: %f\n", area, volume);
}

int main()
{	
	char* name = "Marcel Guzik";
	char* number = "012 345 678";
	char* address = "[example address]";
	
	// ask for some data
	char name2[64], address2[64], number2[64];
	printf("Podaj imie: ");
	scanf("%s", &name2);
	printf("Podaj numer: ");
	scanf("%s", &number2);
	printf("Podaj adres: ");
	scanf("%s", &address2);


	print_card(name, number, address);
	print_card_c(name, number, address, CARD_WIDTH);
	
	zad2();
	
	zad3();
}
