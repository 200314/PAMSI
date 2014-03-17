#ifndef KOLEJKATABLICA
#define KOLEJKATABLICA

/**
\file KolejkaTablica.h
**/

#include "definicje.h"
#include <stdlib.h>

using namespace std;

/**
\brief Implementacja kolejki na tablicy.
**/
class KolejkaTab{
private:
	/** \brief Tablica elementow. **/
	TYP *tablica;
	/** \brief Rozmiar tablicy. **/
	int rozmiar;
	/** \brief Ilosc elementow w kolejce. **/
	int ilosc_elementow;
	/** \brief Index pierwszego elementu. **/
	int start;
	/** \brief Index ostatniego elementu. **/
	int koniec;

	/** \brief Funkcja tworzy nowa tablice o zadanym rozmiarze.
	Tylko jesli wszystkie elementy sie zmieszcza.
	\param nowy_rozmiar zadany rozmiar tablicy. **/
	void przepisz_do_nowej_tablicy(int nowy_rozmiar);
public:
	/** \brief Konstruktor. **/
	KolejkaTab():
		tablica(new TYP[1]),
		rozmiar(1),
		ilosc_elementow(0),
		start(0),
		koniec(0) {};
	/** \brief Destruktor. **/
	~KolejkaTab() { if (tablica != NULL) delete tablica; };
	/** \brief Wstawia element na poczatek kolejki.
	\param cel docelowa kolejka.
	\param element do wstawienia na kolejke docelowa.
	\return powodzenie wykonania funkcji. **/
	static bool enqueue(KolejkaTab& cel, TYP element);
	/** \brief Usuwa element z konca kolejki.
	\param cel docelowa kolejka.
	\param element sciagniety z kolejki.
	\return powodzenie wykonania funkcji. **/
	static bool dequeue(KolejkaTab& cel, TYP& element);
	/** \brief Sprawdza czy kolejka nie ma zadnych elementow.
	\param cel docelowkolejka.
	\return true - jesli pusty.
	false - jesli nie pusty. **/
	static bool isempty(KolejkaTab& cel);
	/** \brief Sprawdza ile elementow jest w kolejce. 
	\param cel docelowa kolejka.
	\return ilosc elementow. **/
	static int size(KolejkaTab& cel);
};

#endif