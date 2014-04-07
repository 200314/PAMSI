/**
\file SortowanieSzybkie2.cpp
**/

#include "SortowanieSzybkie2.h"

/**
\brief Sortowanie dla zadanego przedzialu w strukturze.
\param &do_sortowania Struktura ktora chcemy sortowac.
\param index_od Indeks lewej strony przedzialu.
\param index_do Indeks prawej strony przedzialu.
**/
void SortowanieSzybkie2::podsortowanie_szybkie(StrukturaDanych &do_sortowania, int index_od, int index_do) {
	if (index_do <= index_od)
		return;
	srand(clock());
	int index_srodkowy = rand()%(index_do-index_od)+index_od;
	if (index_srodkowy < index_od || index_srodkowy > index_do)
		cerr << "BLAD: " << index_od <<"<"<< index_srodkowy <<"<"<< index_do <<":linia:"<< __LINE__ << endl;
	TYP wartosc_srodkowa = do_sortowania.element_na(index_srodkowy);
	StrukturaDanych::zamien_elementy(do_sortowania, index_srodkowy, index_do);
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
void SortowanieSzybkie2::sortuj(StrukturaDanych &do_sortowania) {
	podsortowanie_szybkie(do_sortowania, 0, do_sortowania.ilosc_elementow() - 1);
}