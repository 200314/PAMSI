#include "KolejkaTablica.h"

/**
\file KolejkaTablica.cpp
**/

void KolejkaTab::przepisz_do_nowej_tablicy(int nowy_rozmiar) {
	if (ilosc_elementow > nowy_rozmiar)
		return;
	TYP *nowa_tablica = new TYP[nowy_rozmiar];
	TYP a;
	int nowy_koniec = 0;
	int nowa_ilosc_elementow = ilosc_elementow;
	while (KolejkaTab::dequeue(*this, a)) {
		nowa_tablica[nowy_koniec] = a;
		nowy_koniec++;
	}
	start = 0;
	koniec = nowy_koniec;
	rozmiar = nowy_rozmiar;
	ilosc_elementow = nowa_ilosc_elementow;
	delete tablica;
	tablica = nowa_tablica;
}
bool KolejkaTab::enqueue(KolejkaTab& cel, TYP element) {
	if (cel.ilosc_elementow >= cel.rozmiar)
		cel.przepisz_do_nowej_tablicy(cel.rozmiar * 2);
	if (cel.koniec+1 == cel.rozmiar) {
		cel.koniec = 0;
		cel.tablica[cel.rozmiar-1] = element;
	} else {
		cel.koniec++;
		cel.tablica[cel.koniec-1] = element;
	}
	cel.ilosc_elementow++;
	return true;
}
bool KolejkaTab::dequeue(KolejkaTab& cel, TYP& element) {
	if (cel.ilosc_elementow <= 0)
		return false;
	element = cel.tablica[cel.start];
	if (cel.start+1 == cel.rozmiar)
		cel.koniec = 0;
	else
		cel.start++;
	cel.ilosc_elementow--;
	return true;
}
bool KolejkaTab::isempty(KolejkaTab& cel) {
	return (KolejkaTab::size(cel) <= 0);
}
int KolejkaTab::size(KolejkaTab& cel) {
	return cel.ilosc_elementow;
}