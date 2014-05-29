/**
\mainpage
Laboratorium 6 i 7. \n
Implementacja tablic asocjacyjnych na roznych strukturach danych. Wykorzystano: tablice, drzewo binarne, tablice haszujaca.

\author Jakub Chmiel 200314
**/

/**
\file TestTablicAsocjacyjnych.h
**/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "definicje.h"
#include "StrukturaDanych.h"
#include "TablicaAsocjacyjna.h"
#include "DrzewoAsocjacyjne.h"
#include "TablicaHaszujaca.h"

/** \brief nazwa pliku z danymi wejsciowymi, takze dla wyjscia generowanych liczb. **/
#define PLIK_DANYCH "dane.txt"
/** \brief ilosc powtorzen pomiaru czasu dla kazdego rozmiaru problemu.**/
#define LICZBA_POWTORZEN 1000
/** \brief ilosc roznych rozmiarow problemu.**/
#define LICZBA_WIELKOSCI 4
/** \brief tablica zawierajaca wszystkie mierzone rozmiary problemu.**/
#define WIELKOSCI_PROBLEMU {100,1000,10000,100000}
/** \brief ilosc danych do wygenerowania.**/
#define WIELKOSC_GENEROWANYCH_DANYCH 100000
/** \brief Liczba liter w generowanym kluczu.**/
#define DLUGOSC_KLUCZA 6

using namespace std;

TablicaAsocjacyjna tab1;
DrzewoAsocjacyjne tab2;
TablicaHaszujaca tab3;

void algorytm1(TYP_KLUCZ& klucz);
void algorytm2(TYP_KLUCZ& klucz);
void algorytm3(TYP_KLUCZ& klucz);

void zmien_ilosc_elementow1(StrukturaDanych& dane, int ile);
void zmien_ilosc_elementow2(StrukturaDanych& dane, int ile);
void zmien_ilosc_elementow3(StrukturaDanych& dane, int ile);

bool wczytaj_dane(const char *nazwa_pliku, StrukturaDanych &tablica);
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar);
void generuj_dane(char *nazwa_pliku);

void testuj_algorytm(void(*algorytm)(TYP_KLUCZ& klucz), void(*zmien_ilosc_elementow)(StrukturaDanych& dane, int ile), StrukturaDanych &dane, const char *plik_wyjsciowy);
//StrukturaDanych sprawdz_poprawnosc(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych& dane, int ile_liczb);

int main();