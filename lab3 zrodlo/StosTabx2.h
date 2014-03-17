#ifndef STOSTABX2
#define STOSTABX2

/**
\file StosTabx2.h
**/

#include <stdlib.h>
#include "definicje.h"

using namespace std;

/**
\brief Implementacja stosu na tablicy.
Wersja z powiekszeniem tablicy dwukrotnie przy przekroczeniu.
**/
class StosTabx2{
private:
	/** \brief tablica zawierajaca elementy. **/
	TYP *tablica;
	/** \brief rozmiar zaalakowanej tablicy. **/
	int rozmiar_tablicy;
	/** \brief ilosc elementow istniejacych na stosie. **/
	int ilosc_elementow;
	
	/** \brief Funkcja zwieksza rozmiar zaalokowanej tablicy dwukrotnie **/
	void zwieksz_rozmiar();
	/** \brief Funkcja zmniejsza rozmiar zaalokowanej tablicy dwukrotnie.
	Sprawdza czy mniejszy rozmiar pomiesci wszystkie elementy. **/
	void zmniejsz_rozmiar();
public:
	/** \brief Konstruktor. **/
	StosTabx2():
		tablica(new TYP[1]),
		rozmiar_tablicy(1),
		ilosc_elementow(0) {};
	/** \brief Destruktor usuwa zaalakowana dynamicznie tablice. **/
	~StosTabx2() { if (tablica != NULL) delete tablica; };
	/** \brief Wstawia element na szczyt stosu.
	\param cel docelowy stos.
	\param element do wstawienia na stos docelowy.
	\return powodzenie wykonania funkcji. **/
	static bool push(StosTabx2& cel, TYP element);
	/** \brief Usuwa element ze szczytu stosu.
	\param cel docelowey stos.
	\param element sciagniety ze stosu.
	\return powodzenie wykonania funkcji. **/
	static bool pop(StosTabx2& cel, TYP& element);
	/** \brief Sprawdza czy stos nie ma zadnych elementow.
	\param cel docelowy stos.
	\return true - jesli pusty.
	false - jesli nie pusty. **/
	static bool isempty(StosTabx2& cel);
	/** \brief Sprawdza ile elementow jest na stosie. 
	\param cel docelowy stos.
	\return ilosc elementow. **/
	static int size(StosTabx2& cel);
};

#endif