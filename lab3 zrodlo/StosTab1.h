#ifndef STOSTAB1
#define STOSTAB1

/**
\file StosTab1.h
**/

#include <stdlib.h>
#include "definicje.h"

using namespace std;

/**
\brief Implementacja stosu na tablicy.
Wersja z powiekszeniem tablicy o 1 element przy przekroczeniu.
**/
class StosTab1 {
private:
	/** \brief tablica zawierajaca elementy. **/
	TYP *tablica;
	/** \brief rozmiar zaalakowanej tablicy. **/
	int rozmiar_tablicy;
	/** \brief ilosc elementow istniejacych na stosie. **/
	int ilosc_elementow;

	/** \brief Funkcja zwieksza rozmiar zaalokowanej tablicy o 1 **/
	void zwieksz_rozmiar();
public:
	/** \brief Konstruktor. **/
	StosTab1():
		tablica(new TYP[1]),
		rozmiar_tablicy(1),
		ilosc_elementow(0) {};
	/** \brief Destruktor usuwa zaalakowana dynamicznie tablice. **/
	~StosTab1() { if (tablica != NULL) delete tablica; };
	/** \brief Wstawia element na szczyt stosu.
	\param cel docelowy stos.
	\param element do wstawienia na stos docelowy.
	\return powodzenie wykonania funkcji. **/
	static bool push(StosTab1& cel, TYP element);
	/** \brief Usuwa element ze szczytu stosu.
	\param cel docelowey stos.
	\param element sciagniety ze stosu.
	\return powodzenie wykonania funkcji. **/
	static bool pop(StosTab1& cel, TYP& element);
	/** \brief Sprawdza czy stos nie ma zadnych elementow.
	\param cel docelowy stos.
	\return true - jesli pusty.
	false - jesli nie pusty. **/
	static bool isempty(StosTab1& cel);
	/** \brief Sprawdza ile elementow jest na stosie. 
	\param cel docelowy stos.
	\return ilosc elementow. **/
	static int size(StosTab1& cel);
};

#endif