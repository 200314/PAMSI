/**
\file StrukturaDanych.cpp
**/

#include "StrukturaDanych.h"

/**
\brief Konstruktor kopiujacy
\param inna kopiowana StrukturaDanych
*/
StrukturaDanych::StrukturaDanych(StrukturaDanych& inna) {
	
	tablica = new TYP[inna.rozmiar_tablicy];
	rozmiar_tablicy = inna.rozmiar_tablicy;
	aktualna_ilosc = inna.aktualna_ilosc;
	for (int i=0; i<inna.aktualna_ilosc; i++) {
		tablica[i] = inna.element_na(i);
	}
}
/**
\brief zwraca ilosc elementow w strukturze.
\return ilosc elementow.
*/
const int StrukturaDanych::ilosc_elementow() {
	return aktualna_ilosc;
}
/**
\brief zwraca wartosc elementu na danym indeksie
\param i indeks
\return wartosc na i-tym indeksie
*/
const TYP StrukturaDanych::element_na(int i) {
	if (i>=aktualna_ilosc)
		cout << "blad" << endl;
	return tablica[i];
}
/**
\brief dodaje nowy element na koniec tablicy
\param e element do dodania
*/
void StrukturaDanych::pisz_na_koniec(TYP e) {
	if (rozmiar_tablicy <= aktualna_ilosc)
		zwieksz_rozmiar_tablicy();
	tablica[aktualna_ilosc] = e;
	aktualna_ilosc++;
}
/**
\brief wpisuje element na dany indeks
\param e element do wpisania
\param i indeks
*/
void StrukturaDanych::pisz_na(TYP e, int i) {
	if (i > aktualna_ilosc)
		return;
	tablica[i] = e;
}
/**
\brief zwieksza zaalakowana tablice o domyslna ilosc
*/
void StrukturaDanych::zwieksz_rozmiar_tablicy() {
	/*TYP *stara_tablica = tablica;
	tablica = new TYP[rozmiar_tablicy+DODATKOWY_ROZMIAR_TABLICY];
	rozmiar_tablicy += DODATKOWY_ROZMIAR_TABLICY;
	for (int i=0; i<aktualna_ilosc; i++) {
		tablica[i] = stara_tablica[i];
	}
	delete[] stara_tablica;*/
	nowa_tablica(rozmiar_tablicy * 2);
}
/**
\brief tworzy nowa tablice o zadanym rozmiarze i kopiuje poprzednie wartosci.
\param nowy_rozmiar nowy rozmiar tablicy
*/
bool StrukturaDanych::nowa_tablica(int nowy_rozmiar) {
	TYP *stara_tablica = tablica;
	if (tablica == NULL)
		cerr << "blad" << endl;
	tablica = new TYP[nowy_rozmiar];
	if (tablica == NULL) {
		cerr << "Blad" << endl;
		return false;
	}
	rozmiar_tablicy = nowy_rozmiar;
	for (int i=0; i<aktualna_ilosc; i++) {
		tablica[i] = stara_tablica[i];
	}
	delete[] stara_tablica;
	return true;
}
/**
\brief usuwa wszystkie dane i zmienia tablice na poczatkowa.
*/
void StrukturaDanych::usun_wszystko() {
	delete[] tablica;
	tablica = new TYP[1];
	rozmiar_tablicy = 1;
	aktualna_ilosc = 0;
}
/**
\brief Nadpisuje element na danym indeksie.
\param &T Docelowa struktura.
\param index Indeks elementu do nadpisu.
\param e nowy element.
\return Stan powodzenia funkcji.
**/
bool StrukturaDanych::zmien_element(StrukturaDanych &T, int index, TYP e) {
	if (index >= T.ilosc_elementow())
		return false;
	T.tablica[index] = e;
	return true;
}
/**
\brief Dodaje elementy ze struktury zrodlowej do docelowej z indeksow od i_od do i_do.
\param &zrodlo Struktura zrodlowa.
\param &cel Struktura docelowa
\param i_od Indeks pierwszego elementu ktory chcemy kopiowac.
\param i_do Indeks ostatniego elementu ktory chcemy kopiowac.
\return Stan powodzenia funkcji.
*/
bool StrukturaDanych::kopiuj_wycinek(StrukturaDanych &zrodlo, StrukturaDanych &cel, int i_od, int i_do) {
	if (i_do >= zrodlo.ilosc_elementow())
		return false;
	TYP temp;
	for (int i=i_od; i<=i_do; i++) {
		StrukturaDanych::dodaj_element(cel, zrodlo.element_na(i));
	}
	return true;
}
/**
\brief Zamienia kolejnosc dwoch dowolnych elementow
\param T docelowa StrukturaDanych
\param i indeks 1
\param j indeks 2
\return 
- true sukces
- false porazka
*/
bool StrukturaDanych::zamien_elementy(StrukturaDanych &T, int i, int j) {
	if (i>=T.aktualna_ilosc || j>=T.aktualna_ilosc)
		return false;
	TYP temp = T.element_na(i);
	T.pisz_na(T.element_na(j), i);
	T.pisz_na(temp, j);
	return true;
}
/**
\brief Odwraca kolejnosc wszystkich elementow struktury
\param T docelowa StrukturaDanych
\return 
- true sukces
- false porazka
*/
bool StrukturaDanych::odwroc_kolejnosc(StrukturaDanych &T) {
	StrukturaDanych pomocnicza;
	for (int i=T.aktualna_ilosc-1; i>=0; i--) {
		pomocnicza.dodaj_element(pomocnicza, T.element_na(i));
	}
	T = pomocnicza;
	return true;
}
/**
\brief Dodaje element na koniec struktury
\param T docelowa StrukturaDanych
\param e element do dodania
\return 
- true sukces
- false porazka
*/
bool StrukturaDanych::dodaj_element(StrukturaDanych &T,TYP e) {
	T.pisz_na_koniec(e);
	return true;
}
/**
\brief Laczy 2 struktury ze soba
\param T1 pierwsza StrukturaDanych
\param T2 druga StrukturaDanych
\return Struktura bedaca polaczeniem dwoch wejsciowych struktur.
*/
StrukturaDanych StrukturaDanych::dodaj_elementy(StrukturaDanych &T1, StrukturaDanych &T2) {
	StrukturaDanych zwracana;
	for (int i=0; i<T1.aktualna_ilosc; i++) {
		StrukturaDanych::dodaj_element(zwracana, T1.element_na(i));
	}
	for (int i=0; i<T2.aktualna_ilosc; i++) {
		StrukturaDanych::dodaj_element(zwracana, T2.element_na(i));
	}
	return zwracana;
}
/**
\brief Wypisuje dane ze struktury na standardowe wyjscie.
\param T docelowa StrukturaDanych
*/
void StrukturaDanych::wypisz_wszystko(StrukturaDanych &T) {
	cout << T.aktualna_ilosc << " elementow:" << endl;
	for (int i=0; i<T.aktualna_ilosc; i++) {
		cout << T.element_na(i) << endl;
	}
}
/**
\brief Operator przypisania
\param T StrukturaDanych
\return taka sama struktura jak parametr T
*/
StrukturaDanych& StrukturaDanych::operator=( StrukturaDanych &T) {
	usun_wszystko();
	for (int i=0; i<T.aktualna_ilosc; i++) {
		StrukturaDanych::dodaj_element(*this, T.element_na(i));
	}
	return *this;
}
/**
\brief Operator dodawania z przypisaniem
\param T StrukturaDanych
\return Struktura z dodanymi na koniec elementami struktury T
*/
StrukturaDanych& StrukturaDanych::operator+=(StrukturaDanych &T) {
	for (int i=0; i<T.aktualna_ilosc; i++) {
		StrukturaDanych::dodaj_element(*this, T.element_na(i));
	}
	return *this;
}
/**
\brief Laczy 2 struktury ze soba
\param T1 pierwsza StrukturaDanych
\param T2 druga StrukturaDanych
\return Struktura bedaca polaczeniem dwoch wejsciowych struktur.
*/
StrukturaDanych operator+(StrukturaDanych T1, StrukturaDanych &T2) {
	return T1 += T2;
}
/**
\brief Operator porownania
\param T1 pierwsza StrukturaDanych
\param T2 druga StrukturaDanych
\return
- true struktury maja identyczne elementy
- false elementy nie sa identyczne
*/
bool operator==(StrukturaDanych& T1, StrukturaDanych& T2) {
	if (T1.aktualna_ilosc != T2.aktualna_ilosc)
		return false;
	for (int i=0; i<T1.aktualna_ilosc; i++) {
		if (T1.element_na(i) != T2.element_na(i))
			return false;
	}
	return true;
}
