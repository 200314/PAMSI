#ifndef	SORTOWANIESCALANIE
#define	SORTOWANIESCALANIE

/**
\file SortowanieScalanie.h
**/

#include "StrukturaDanych.h"

/**
\brief Klasa implementuje algorytm sortowania przez scalanie (mergesort).
**/
class SortowanieScalanie {
private:
	static void podsortowanie_scalanie(StrukturaDanych &do_sortowania, int index_od, int index_do);
	static void scalanie(StrukturaDanych& tablica, int index_od, int index_srodek, int index_do);
public:
	static void sortuj(StrukturaDanych &do_sortowania);
};

#endif