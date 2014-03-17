#include "KolejkaLista.h"

/**
\file KolejkaLista.cpp
**/

bool KolejkaLista::enqueue(KolejkaLista& cel, TYP element) {
	ElementKolejki* nowy = new ElementKolejki;
	nowy->elem = element;
	if (cel.ilosc_elementow <=0) {
		cel.ostatni = nowy;
	} else {
		nowy->nastepny = cel.pierwszy;
		cel.pierwszy->poprzedni = nowy;
	}
	cel.pierwszy = nowy;
	cel.ilosc_elementow++;
	return true;
}
bool KolejkaLista::dequeue(KolejkaLista& cel, TYP& element) {
	if (KolejkaLista::isempty(cel))
		return false;
	element = cel.ostatni->elem;
	ElementKolejki* stary_ostatni = cel.ostatni;
	if (cel.ilosc_elementow == 1) {
		cel.ostatni = NULL;
		cel.pierwszy = NULL;
	} else {
		cel.ostatni->poprzedni->nastepny = NULL;
		cel.ostatni = cel.ostatni->poprzedni;
	}
	stary_ostatni->nastepny = NULL;
	stary_ostatni->poprzedni = NULL;
	delete stary_ostatni;
	cel.ilosc_elementow--;
	return true;
}
bool KolejkaLista::isempty(KolejkaLista& cel) {
	return (cel.ilosc_elementow <= 0);
}
int KolejkaLista::size(KolejkaLista& cel) {
	return (cel.ilosc_elementow);
}