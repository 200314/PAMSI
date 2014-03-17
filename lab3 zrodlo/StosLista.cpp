#include "StosLista.h"

/**
\file StosLista.cpp
**/

bool StosLista::push(StosLista& cel, TYP element) {
	ElementStosu* nowy = new ElementStosu;
	nowy->elem = element;
	nowy->nastepny = cel.pierwszy;
	cel.pierwszy = nowy;
	cel.ilosc_elementow++;
	return true;
}
bool StosLista::pop(StosLista& cel, TYP& element) {
	if (StosLista::isempty(cel))
		return false;
	element = cel.pierwszy->elem;
	ElementStosu* stary_pierwszy = cel.pierwszy;
	cel.pierwszy = cel.pierwszy->nastepny;
	stary_pierwszy->nastepny = NULL;
	delete stary_pierwszy;
	cel.ilosc_elementow--;
	return true;
}
bool StosLista::isempty(StosLista& cel) {
	return (cel.ilosc_elementow <= 0);
}
int StosLista::size(StosLista& cel) {
	return (cel.ilosc_elementow);
}
