/**
\mainpage
Laboratorium 1. \n
Funkcje do pomiaru czasu wykonywania algorytmu.
Algorytm mnozy kazda liczbe przez 2.

\author Jakub Chmiel 200314
**/

/**
\file TestAlgorytmu.cpp
**/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

/** \brief nazwa pliku z danymi wejsciowymi, takze dla wyjscia generowanych liczb. */
#define PLIK_DANYCH "dane1.txt"
/** \brief nazwa pliku wyjsciowego.*/
#define PLIK_WYJSCIOWY "wyjscie1.csv"
/** \brief ilosc powtorzen pomiaru czasu dla kazdego rozmiaru problemu.*/
#define LICZBA_POWTORZEN 50
/** \brief ilosc roznych rozmiarow problemu.*/
#define LICZBA_WIELKOSCI 8
/** \brief tablica zawierajaca wszystkie mierzone rozmiary problemu.*/
#define WIELKOSCI_PROBLEMU {10, 1000, 100000, 1000000, 2000000, 4000000, 6000000, 10000000}
/** \brief ilosc danych do wygenerowania.*/
#define WIELKOSC_GENEROWANYCH_DANYCH 10000000
/** \brief typ danych.*/
#define TYP int

using namespace std;

/**
\brief Testowany algorytm
\param *tablica dane do przetworzenia
\param rozmiar ilosc danych
**/
void algorytm (TYP *tablica, int rozmiar) {
	for (int i=0; i<rozmiar; i++) {
		tablica[i] *= 2;
	}
}
/**
\brief wczytuje dane z pliku
\details
Format: \n
liczba_danych \n
dana1 \n
dana2 \n
. \n
\param *nazwa_pliku nazwa pliku z danymi
\param *&tablica tablica docelowa (usuwana w przypadku !=NULL)
\param &rozmiar rozmiar tablicy docelowej
**/
bool wczytaj_dane(const char *nazwa_pliku, TYP *&tablica, int &rozmiar) {
	ifstream plik;
	plik.open(nazwa_pliku);
	if (plik.good())
		plik >> rozmiar;
	else
		return false;
	if(tablica != NULL)
		delete tablica;
	tablica = new int[rozmiar];
	////
	for (int i=0; i<rozmiar; i++) {
		int temp;
		if(plik.good()) {
			plik >> temp;
			tablica[i] = temp;
		} else
			return false;
	}
	plik.close();
	return true;
}
/**
\brief zapisuje dane do pliku .csv
dane zawieraja:
1 kolumna: wielkosc problemu
2 kolumna: czas potrzebny do zrealizowanego danego problemu
\param *nazwa_pliku nazwa pliku do zapisu
\param *col_rozmiar_problemu tablica z 1 kolumna
\param *col_czas druga kolumna
\param rozmiar rozmiar obu tablic
\return
	- true sukces
	- false blad
**/
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar) {
	ofstream plik;
	plik.open(nazwa_pliku, ios::out | ios::trunc);
	if (!plik.good())
		return false;
	for (int i=0; i<rozmiar; i++) {
		plik << col_rozmiar_problemu[i] << "," << col_czas[i] << endl;
	}
	plik.close();
	return true;
}
/**
\brief wypisuje tablice na standardowe wyjscie
\param *tablica tablica
\param rozmiar rozmiar tablicy
**/
void wypisz_dane(TYP *tablica, int rozmiar) {
	if (tablica == NULL)
		return;
	for (int i = 0; i<rozmiar; i++) {
		cout << tablica[i] << endl;
	}
}
/**
\brief kopiuje n elementow tablicy do innej
\param *tab_z tablica wyjsciowa
\param *tab_do tablica docelowa
\param ile ilosc elementow do skopiowania
**/
void kopiuj(TYP *tab_z, TYP *tab_do, int ile) {
	if (tab_z == NULL || tab_do == NULL)
		return;
	for (int i=0; i<ile; i++) {
		tab_do[i] = tab_z[i];
	}
}
/**
\brief wykonuje testy czasu algorytmu dla przygotowanych parametrow
zmierzone czasu zapisuje do pliku
\param *tablica dane
\param rozmiar rozmiar tablicy
**/
void testuj_algorytm(TYP *tablica, int rozmiar) {
	int tab_wielkosci[] = WIELKOSCI_PROBLEMU;
	
	int liczba_col = LICZBA_POWTORZEN * LICZBA_WIELKOSCI;
	int *col_rozmiar_problemu = new int[liczba_col];
	double *col_czas = new double[liczba_col];

	int aktualny_rozmiar = 0;
	double czas_start = 0;
	double czas_koniec = 0;

	for(int i=0; i<LICZBA_WIELKOSCI; i++) {
		aktualny_rozmiar = tab_wielkosci[i];
		if (aktualny_rozmiar > rozmiar) {
			cerr << "Za malo danych dla wyznaczonych wielkosci problemu" << endl;
		}
		TYP *podtablica = new TYP[aktualny_rozmiar];
		for(int j=0; j<LICZBA_POWTORZEN; j++) {
			int index = i*LICZBA_POWTORZEN + j;
			kopiuj(tablica, podtablica, aktualny_rozmiar);
			czas_start = (double)clock()/CLOCKS_PER_SEC;
			algorytm(podtablica, aktualny_rozmiar);
			czas_koniec= (double)clock()/CLOCKS_PER_SEC;

			col_rozmiar_problemu[i*LICZBA_POWTORZEN + j] = aktualny_rozmiar;
			cout << czas_koniec-czas_koniec << endl;
			col_czas[i*LICZBA_POWTORZEN + j] = czas_koniec-czas_start;
			cout << "Postep: " << i*LICZBA_POWTORZEN+j+1  << "/" << LICZBA_POWTORZEN * LICZBA_WIELKOSCI << endl;
		}
		delete podtablica;
	}
	zapisz_dane(PLIK_WYJSCIOWY, col_rozmiar_problemu, col_czas, liczba_col);
	delete col_rozmiar_problemu;
	delete col_czas;
}
/**
\brief generuje dane jesli ich nie ma
**/
void generuj_dane() {
	ofstream plik;
	plik.open(PLIK_DANYCH, ios::out | ios::trunc);
	if (!plik.good())
		return;
	plik << WIELKOSC_GENEROWANYCH_DANYCH << endl;
	for (int i=0; i<WIELKOSC_GENEROWANYCH_DANYCH; i++) {
		plik << rand() % 100000 << endl;
	}
	plik.close();
	cout << "wygenerowano" << endl;
}
/**
\brief funkcja main
**/
int main() {
	//generuj_dane();
	int *tab = NULL;
	int rozmiar;
	wczytaj_dane(PLIK_DANYCH, tab, rozmiar);
	testuj_algorytm(tab, rozmiar);
	//cin.get();
	return 0;
}