
/**
\mainpage
Laboratorium 3. \n
Rozne implementacje stosu i kolejki.
Pomiar zlozonosci obliczeniowek wstawiania elementow do stosu
zaimplentowanego na tablicy.

\author Jakub Chmiel 200314
**/

/**
\file TestStosowIKolejek.cpp
**/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "definicje.h"
#include "StosTab1.h"
#include "StosTabx2.h"
#include "StosLista.h"
#include "KolejkaLista.h"
#include "KolejkaTablica.h"

/** \brief nazwa pliku z danymi wejsciowymi, takze dla wyjscia generowanych liczb. **/
#define PLIK_DANYCH "dane3.txt"
/** \brief ilosc powtorzen pomiaru czasu dla kazdego rozmiaru problemu.**/
#define LICZBA_POWTORZEN 10
/** \brief ilosc roznych rozmiarow problemu.**/
#define LICZBA_WIELKOSCI 9
/** \brief tablica zawierajaca wszystkie mierzone rozmiary problemu.**/
#define WIELKOSCI_PROBLEMU {10, 100, 1000, 2000, 3000, 4000, 6000, 8000, 10000}
/** \brief ilosc danych do wygenerowania.**/
#define WIELKOSC_GENEROWANYCH_DANYCH 10000

using namespace std;

/**
\brief Testowany algorytm dla stosu tablicowego z powiekszeniem 1
\param zrodlo tablica danych do wrzucenia na stos
\param rozmiar ilosc danych
\return czas wykonywania
**/
double algorytm1 (TYP* zrodlo, int rozmiar) {
	StosTab1 stos;
	double czas_koniec;
	double czas_start = (double)clock()/CLOCKS_PER_SEC;
	for (int i=0; i<rozmiar; i++) {
		StosTab1::push(stos, zrodlo[i]);
	}
	czas_koniec= (double)clock()/CLOCKS_PER_SEC;
	return czas_koniec - czas_start;
}
/**
\brief Testowany algorytm dla stosu tablicowego z powiekszeniem x2
\param zrodlo tablica danych do wrzucenia na stos
\param rozmiar ilosc danych
\return czas wykonywania
**/
double algorytm2 (TYP* zrodlo, int rozmiar) {
	StosTabx2 stos;
	double czas_koniec;
	double czas_start = (double)clock()/CLOCKS_PER_SEC;
	for (int i=0; i<rozmiar; i++) {
		StosTabx2::push(stos, zrodlo[i]);
	}
	czas_koniec= (double)clock()/CLOCKS_PER_SEC;
	return czas_koniec - czas_start;
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
///*
//\brief wypisuje tablice na standardowe wyjscie
//\param *tablica tablica
//\param rozmiar rozmiar tablicy
//**/
//void wypisz_dane(TYP *tablica, int rozmiar) {
//	if (tablica == NULL)
//		return;
//	for (int i = 0; i<rozmiar; i++) {
//		cout << tablica[i] << endl;
//	}
//}
///*
//\brief kopiuje n elementow tablicy do innej
//\param *tab_z tablica wyjsciowa
//\param *tab_do tablica docelowa
//\param ile ilosc elementow do skopiowania
//**/
//void kopiuj(TYP *tab_z, TYP *tab_do, int ile) {
//	if (tab_z == NULL || tab_do == NULL)
//		return;
//	for (int i=0; i<ile; i++) {
//		tab_do[i] = tab_z[i];
//	}
//}
/**
\brief wykonuje testy czasu algorytmu dla przygotowanych parametrow
zmierzone czasu zapisuje do pliku
\param double(*algorytm) funkcja z algorytmem do testowania
\param *tablica dane dla algorytmu
\param rozmiar rozmiar tablicy
\param *plik_wyjsciowy nazwa pliku do zapisu zmierzonych czasow
**/
void testuj_algorytm(double(*algorytm)(TYP* zrodlo, int rozmiar), TYP *tablica, int rozmiar, const char *plik_wyjsciowy) {
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
			continue;
		}
		for(int j=0; j<LICZBA_POWTORZEN; j++) {
			int index = i*LICZBA_POWTORZEN + j;
			
			col_rozmiar_problemu[i*LICZBA_POWTORZEN + j] = aktualny_rozmiar;
			//cout << czas_koniec-czas_koniec << endl;

			col_czas[i*LICZBA_POWTORZEN + j] = algorytm(tablica, aktualny_rozmiar);
			cout << "Postep: " << i*LICZBA_POWTORZEN+j+1  << "/" << LICZBA_POWTORZEN * LICZBA_WIELKOSCI << endl;
		}
	}
	zapisz_dane(plik_wyjsciowy, col_rozmiar_problemu, col_czas, liczba_col);
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
\brief funkcja sprawdza poprawnosc dzialania struktur danych.
**/
void sprawdz_poprawnosc() {
	TYP a = 0;
	StosTab1 stos1;
	for (int i=0; i<10; i++) {
		StosTab1::push(stos1, i*i);
	}
	cout << "size(): " << StosTab1::size(stos1) << ", isempty(): " << StosTab1::isempty(stos1) << endl;
	while (StosTab1::pop(stos1, a)) {
		cout << a << ", ";
	}
	cout << endl;

	StosTabx2 stos2;
	for (int i=0; i<10; i++) {
		StosTabx2::push(stos2, i*i);
	}
	cout << "size(): " << StosTabx2::size(stos2) << ", isempty(): " << StosTabx2::isempty(stos2) << endl;
	while (StosTabx2::pop(stos2, a)) {
		cout << a << ", ";
	}
	cout << endl;

	StosLista stos3;
	for (int i=0; i<10; i++) {
		StosLista::push(stos3, i*i);
	}
	cout << "size(): " << StosLista::size(stos3) << ", isempty(): " << StosLista::isempty(stos3) << endl;
	while (StosLista::pop(stos3, a)) {
		cout << a << ", ";
	}
	cout << endl;

	KolejkaLista kolejka1;
	for (int i=0; i<10; i++) {
		KolejkaLista::enqueue(kolejka1, i*i);
	}
	cout << "size(): " << KolejkaLista::size(kolejka1) << ", isempty(): " << KolejkaLista::isempty(kolejka1) << endl;
	while (KolejkaLista::dequeue(kolejka1, a)) {
		cout << a << ", ";
	}
	cout << endl;

	KolejkaTab kolejka2;
	for (int i=0; i<10; i++) {
		KolejkaTab::enqueue(kolejka2, i*i);
	}
	cout << "size(): " << KolejkaTab::size(kolejka2) << ", isempty(): " << KolejkaTab::isempty(kolejka2) << endl;
	while (KolejkaTab::dequeue(kolejka2, a)) {
		cout << a << ", ";
	}
	cout << endl;
}
/**
\brief funkcja main
**/
int main() {
	sprawdz_poprawnosc();
	/*
	generuj_dane();
	int *tab = NULL;
	int rozmiar;
	wczytaj_dane(PLIK_DANYCH, tab, rozmiar);
	testuj_algorytm(algorytm1, tab, rozmiar, "wyjscie3 tab1.csv");
	testuj_algorytm(algorytm2, tab, rozmiar, "wyjscie3 tabx2.csv");
	*/
	cin.get();
	return 0;
}