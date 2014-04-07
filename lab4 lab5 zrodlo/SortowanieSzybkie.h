#ifndef	SORTOWANIESZYBKIE
#define	SORTOWANIESZYBKIE

/**
\file SortowanieSzybkie.h
**/

#include "StrukturaDanych.h"

/**
\brief Klasa implementuje algorytm sortowania szybkiego (quicksort) z wyborem pierwszego elementu jako dzielacego.
**/
class SortowanieSzybkie {
private:
	static void podsortowanie_szybkie(StrukturaDanych &do_sortowania, int index_od, int index_do);
public:
	static void sortuj(StrukturaDanych &do_sortowania);
};

#endif