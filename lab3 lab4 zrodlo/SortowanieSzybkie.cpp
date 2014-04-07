/**
\file SortowanieSzybkie.cpp
**/

#include "SortowanieSzybkie.h"

/**
\brief Sortowanie dla zadanego przedzialu w strukturze.
\param &do_sortowania Struktura ktora chcemy sortowac.
\param index_od Indeks lewej strony przedzialu.
\param index_do Indeks prawej strony przedzialu.
**/
void SortowanieSzybkie::podsortowanie_szybkie(StrukturaDanych &do_sortowania, int index_od, int index_do) {
	if (index_do <= index_od)
		return;
	TYP wartosc_srodkowa = do_sortowania.element_na(index_od);
	StrukturaDanych::zamien_elementy(do_sortowania, index_od, index_do);
	int index_do_zamiany = index_od;
	for (int i = index_od; i < index_do; i++) {
		if (do_sortowania.element_na(i) <= wartosc_srodkowa) {
			StrukturaDanych::zamien_elementy(do_sortowania, i, index_do_zamiany);
			index_do_zamiany++;
		}
	}
	StrukturaDanych::zamien_elementy(do_sortowania, index_do_zamiany, index_do);
	podsortowanie_szybkie(do_sortowania, index_od, index_do_zamiany - 1);
	podsortowanie_szybkie(do_sortowania, index_do_zamiany + 1, index_do);
}
/**
\brief Sortowanie dla calej struktury.
\param &do_sortowania Struktura ktora chcemy sortowac.
**/
void SortowanieSzybkie::sortuj(StrukturaDanych &do_sortowania) {
	podsortowanie_szybkie(do_sortowania, 0, do_sortowania.ilosc_elementow() - 1);
}