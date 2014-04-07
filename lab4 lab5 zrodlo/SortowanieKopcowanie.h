#ifndef	SORTOWANIEKOPCOWANIE
#define	SORTOWANIEKOPCOWANIE

/**
\file SortowanieKopcowanie.h
**/

#include "StrukturaDanych.h"

/**
\brief Klasa implementuje algorytm sortowania przez kopcowanie (heapsort).
**/
class SortowanieKopcowanie {
private:
	static void zkopcuj(StrukturaDanych& dane);
	static void napraw_kopiec(StrukturaDanych& dane, int start, int koniec);
public:
	static void sortuj(StrukturaDanych &do_sortowania);
};

#endif