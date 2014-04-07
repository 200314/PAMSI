#ifndef	SORTOWANIESZYBKIE2
#define	SORTOWANIESZYBKIE2

/**
\file SortowanieSzybkie2.h
**/

#include "StrukturaDanych.h"
#include <time.h>

/**
\brief Klasa implementuje algorytm sortowania szybkiego (quicksort) z losowym wyborem elementu dzielacego.
**/
class SortowanieSzybkie2 {
private:
	static void podsortowanie_szybkie(StrukturaDanych &do_sortowania, int index_od, int index_do);
public:
	static void sortuj(StrukturaDanych &do_sortowania);
};

#endif