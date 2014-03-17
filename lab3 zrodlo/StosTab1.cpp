#include "StosTab1.h"

/**
\file StosTab1.cpp
**/

void StosTab1::zwieksz_rozmiar() {
	TYP* stara_tablica = tablica;
	tablica = new TYP[rozmiar_tablicy+1];
	for (int i=0; i<ilosc_elementow; i++) {
		tablica[i] = stara_tablica[i];
	}
	rozmiar_tablicy++;
	delete stara_tablica;
}


bool StosTab1::push(StosTab1& cel, TYP element) {
	if (cel.ilosc_elementow >= cel.rozmiar_tablicy)
		cel.zwieksz_rozmiar();
	cel.tablica[cel.ilosc_elementow] = element;
	cel.ilosc_elementow++;
	return true;
}
bool StosTab1::pop(StosTab1& cel, TYP& element) {
	if (cel.ilosc_elementow < 1)
		return false;
	cel.ilosc_elementow--;
	element = cel.tablica[cel.ilosc_elementow];
	return true;
}
bool StosTab1::isempty(StosTab1& cel) {
	return (cel.ilosc_elementow == 0);
}
int StosTab1::size(StosTab1& cel) {
	return cel.ilosc_elementow;
}