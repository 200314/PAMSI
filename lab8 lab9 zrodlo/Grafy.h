/**
\mainpage
Laboratorium 8 i 9. \n
Algorytmy przeszukiwania grafu.

\author Jakub Chmiel 200314
**/

/**
\file Grafy.h
**/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "Definicje.h"
#include "Graf.h"
#include "BreadthSearch.h"
#include "DepthSearch.h"
#include "AStar.h"

/** \brief ilosc powtorzen pomiaru czasu dla kazdego rozmiaru problemu.**/
#define LICZBA_POWTORZEN 100
/** \brief ilosc roznych rozmiarow problemu.**/
#define LICZBA_WIELKOSCI 7
/** \brief tablica zawierajaca wszystkie mierzone rozmiary problemu.**/
#define WIELKOSCI_PROBLEMU {100,150,200,250,300,350,400}

using namespace std;

//bool wczytaj_dane(const char *nazwa_pliku, StrukturaDanych &tablica);
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar);
//void generuj_dane(char *nazwa_pliku);

void testuj_algorytm(bool(*algorytm)(Graf& graf, int W1, int W2, list<int>& sciezka), const char *plik_wyjsciowy);

int main();