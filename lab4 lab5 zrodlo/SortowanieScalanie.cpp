/**
\file SortowanieScalanie.cpp
**/

#include "SortowanieScalanie.h"

/**
\brief Sortowanie dla zadanego przedzialu w strukturze.
\param &do_sortowania Struktura ktora chcemy sortowac.
\param index_od Indeks lewej strony przedzialu.
\param index_do Indeks prawej strony przedzialu.
**/
void SortowanieScalanie::podsortowanie_scalanie(StrukturaDanych &do_sortowania, int index_od, int index_do) {
	if (index_do <= index_od)
		return;
	int index_srodkowy = (index_od + index_do) / 2;
	podsortowanie_scalanie(do_sortowania, index_od, index_srodkowy);
	podsortowanie_scalanie(do_sortowania, index_srodkowy + 1, index_do);

	scalanie(do_sortowania, index_od, index_srodkowy, index_do);
}
/**
\brief Scala dwie posortowane czesci w jednej tablicy.
\param &tablica Struktura w ktorej chcemy scalac.
\param index_od Indeks lewej strony przedzialu.
\param index_srodkowy Ostatni indeks pierwszej czesci zakresu.
\param index_do Indeks prawej strony przedzialu.
**/
void SortowanieScalanie::scalanie(StrukturaDanych& do_scalania, int index_od, int index_srodkowy, int index_do) {
	StrukturaDanych kopia_pierwszej_czesci;
	StrukturaDanych::kopiuj_wycinek(do_scalania, kopia_pierwszej_czesci, index_od, index_srodkowy);
	int index_wstawiania = index_od;
	int index_na_kopii = 0;
	int index_na_docelowej = index_srodkowy + 1;
	while (index_wstawiania <= index_do) {
		if (index_na_docelowej > index_do || ( index_na_kopii < kopia_pierwszej_czesci.ilosc_elementow() && 
		kopia_pierwszej_czesci.element_na(index_na_kopii) < do_scalania.element_na(index_na_docelowej)) ) {
			StrukturaDanych::zmien_element(do_scalania, index_wstawiania, kopia_pierwszej_czesci.element_na(index_na_kopii));
			index_na_kopii++;
		} else {
			StrukturaDanych::zmien_element(do_scalania, index_wstawiania, do_scalania.element_na(index_na_docelowej));
			index_na_docelowej++;
		}
		index_wstawiania++;
	}
}
/**
\brief Sortowanie dla calej struktury.
\param &do_sortowania Struktura ktora chcemy sortowac.
**/
void SortowanieScalanie::sortuj(StrukturaDanych &do_sortowania) {
	podsortowanie_scalanie(do_sortowania, 0, do_sortowania.ilosc_elementow() - 1);
}