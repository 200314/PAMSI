#include "StosTabx2.h"

/**
\file StosTabx2.h
**/

void StosTabx2::zwieksz_rozmiar() {
	TYP* stara_tablica = tablica;
	tablica = new TYP[rozmiar_tablicy*2];
	for (int i=0; i<ilosc_elementow; i++) {
		tablica[i] = stara_tablica[i];
	}
	rozmiar_tablicy*=2;
	delete stara_tablica;
}
void StosTabx2::zmniejsz_rozmiar() {
	if (ilosc_elementow > rozmiar_tablicy/2)
		return;
	TYP* stara_tablica = tablica;
	tablica = new TYP[rozmiar_tablicy/2];
	for (int i=0; i<ilosc_elementow; i++) {
		tablica[i] = stara_tablica[i];
	}
	rozmiar_tablicy/=2;
	delete stara_tablica;
}
bool StosTabx2::push(StosTabx2& cel, TYP element) {
	if (cel.ilosc_elementow >= cel.rozmiar_tablicy)
		cel.zwieksz_rozmiar();
	cel.tablica[cel.ilosc_elementow++] = element;
	return true;
}
bool StosTabx2::pop(StosTabx2& cel, TYP& element) {
	if (cel.ilosc_elementow < 1)
		return false;
	element = cel.tablica[--cel.ilosc_elementow];
	if (cel.ilosc_elementow*4 < cel.rozmiar_tablicy)
		cel.zmniejsz_rozmiar();
	return true;
}
bool StosTabx2::isempty(StosTabx2& cel) {
	return (cel.ilosc_elementow == 0);
}
int StosTabx2::size(StosTabx2& cel) {
	return cel.ilosc_elementow;
}