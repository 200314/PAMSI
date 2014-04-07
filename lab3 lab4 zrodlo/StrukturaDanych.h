#ifndef STRUKTURADANYCH
#define STRUKTURADANYCH

/**
\file StrukturaDanych.h
**/

#include <iostream>
#include "definicje.h"

using namespace std;

/**
\brief Struktura danych o funkcjonalnosci tablicy.
**/
class StrukturaDanych {
private:
	/** \brief Tablica z danymi. **/
	TYP *tablica;
	/** \brief rozmiar zaalakowanej tablicy. **/
	int rozmiar_tablicy;
	/** \brief aktualna ilosc danych zapamietanych. **/
	int aktualna_ilosc;

	void pisz_na_koniec(TYP e);
	void pisz_na(TYP e, int i);
	void zwieksz_rozmiar_tablicy();
	bool nowa_tablica(int nowy_rozmiar);
	void usun_wszystko();
public:
	StrukturaDanych():
		tablica(new TYP[1]),
		rozmiar_tablicy(1),
		aktualna_ilosc(0) {};
	StrukturaDanych(StrukturaDanych& inna);
	~StrukturaDanych() {if (tablica!=NULL) delete[] tablica;};
	const int ilosc_elementow();
	const TYP element_na(int i);
	static bool zmien_element(StrukturaDanych &T, int index, TYP e);
	static bool kopiuj_wycinek(StrukturaDanych &zrodlo, StrukturaDanych &cel, int i_od, int i_do);
	static bool zamien_elementy(StrukturaDanych &T, int i, int j);
	static bool odwroc_kolejnosc(StrukturaDanych &T);
	static bool dodaj_element(StrukturaDanych &T,TYP e);
	static StrukturaDanych dodaj_elementy(StrukturaDanych &T1, StrukturaDanych &T2);
	static void wypisz_wszystko(StrukturaDanych &T);

	StrukturaDanych& operator=(StrukturaDanych &T);
	StrukturaDanych& operator+=(StrukturaDanych &T);
	friend StrukturaDanych operator+(StrukturaDanych T1, StrukturaDanych &T2);
	friend bool operator==(StrukturaDanych &T1, StrukturaDanych &T2);
};

#endif