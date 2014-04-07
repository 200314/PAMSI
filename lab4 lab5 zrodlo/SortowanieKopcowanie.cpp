/**
\file SortowanieKopcowanie.cpp
**/

#include "SortowanieKopcowanie.h"


/**
\brief Organizujemy cala strukture w kopiec.
\param &do_sortowania Struktura ktora chcemy zkopcowac.
**/
void SortowanieKopcowanie::zkopcuj(StrukturaDanych& dane) {
	//start start jest na poczatku indexem ostatniego wezla-rodzica
	int start = (dane.ilosc_elementow() - 2) / 2;
    
	while (start >= 0) {
		napraw_kopiec(dane, start, dane.ilosc_elementow()-1);
		//nastepny wezel-rodzic
		start--;
	}
}
/**
\brief Organizujemy kopiec.
\param &dane Struktura ktora chcemy zkopcowac.
\param start Poczatkowy indeks.
\param koniec Koncowy indeks.
**/
void SortowanieKopcowanie::napraw_kopiec(StrukturaDanych& dane, int start, int koniec) {
    int korzen = start;

	//poki korzen ma co najmniej jedno dziecko
    while (korzen * 2 + 1 <= koniec) {
		//lewe
        int dziecko = korzen *2 +1;
        int do_zamiany = korzen;

		if (dane.element_na(do_zamiany) < dane.element_na(dziecko))
			do_zamiany = dziecko;
		//jesli jest prawe dziecko i jest wieksze
		if (dziecko+1 <= koniec && dane.element_na(do_zamiany) < dane.element_na(dziecko+1))
			do_zamiany = dziecko+1;
		if (do_zamiany != korzen) {
			StrukturaDanych::zamien_elementy(dane, korzen, do_zamiany);
			korzen = do_zamiany;
		} else
			return;
	}
}
/**
\brief Sortowanie dla calej struktury.
\param &do_sortowania Struktura ktora chcemy sortowac.
**/
void SortowanieKopcowanie::sortuj(StrukturaDanych &do_sortowania) {
	//organizuje dane w strukture kopca binarnego tak ze wartosc kazdego wezla jest mniejsza niz jego rodzica.
	zkopcuj(do_sortowania);

	//petla za kazdym razem wyrzuca aktualnie najwieksza wartosc z kopca na koniec.
	int index_koniec_kopca = do_sortowania.ilosc_elementow() - 1;
	while (index_koniec_kopca > 0) {
		//pierwszy element kopca jest korzeniem (najwieksza wartosc)
		StrukturaDanych::zamien_elementy(do_sortowania, 0, index_koniec_kopca); 
		//rozmiar kopca sie zmniejsza
		index_koniec_kopca--;
		//utracilismy wlasciwosc kopca wiec go naprawiamy
		napraw_kopiec (do_sortowania, 0, index_koniec_kopca);
	}
}