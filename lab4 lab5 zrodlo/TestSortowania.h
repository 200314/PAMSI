/**
\mainpage
Laboratorium 4 i 5. \n
Implementacje algorytmow sortowania: quicksort, mergesort, heapsort.
Porównanie algorytmu quicksort dla zwyk?ego i najgorszego przypadku (sortowanie tablicy posortowanej)
z wykorzystaniem quicksorta, który wybiera pierwszy lub losowy element do dzielenia problemu.

\author Jakub Chmiel 200314
**/

/**
\file TestSortowania.h
**/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "definicje.h"
#include "StrukturaDanych.h"
#include "SortowanieSzybkie.h"
#include "SortowanieSzybkie2.h"
#include "SortowanieScalanie.h"
#include "SortowanieKopcowanie.h"

/** \brief nazwa pliku z danymi wejsciowymi, takze dla wyjscia generowanych liczb. **/
#define PLIK_DANYCH "dane4.txt"
/** \brief ilosc powtorzen pomiaru czasu dla kazdego rozmiaru problemu.**/
#define LICZBA_POWTORZEN 10
/** \brief ilosc roznych rozmiarow problemu.**/
#define LICZBA_WIELKOSCI 8
/** \brief tablica zawierajaca wszystkie mierzone rozmiary problemu.**/
#define WIELKOSCI_PROBLEMU {100, 1000, 5000, 10000, 20000, 40000, 60000, 100000}
/** \brief ilosc danych do wygenerowania.**/
#define WIELKOSC_GENEROWANYCH_DANYCH 1000000

using namespace std;

bool wczytaj_dane(const char *nazwa_pliku, StrukturaDanych &tablica);
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar);
void generuj_dane(char *nazwa_pliku);

void testuj_algorytm(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych &dane, const char *plik_wyjsciowy);
StrukturaDanych sprawdz_poprawnosc(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych& dane, int ile_liczb);

int main();