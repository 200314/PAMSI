#ifndef STOSLISTA
#define STOSLISTA

/**
\file StosLista.h
**/

#include "definicje.h"
#include <stdlib.h>

using namespace std;

/**
\brief Struktura pojedynczego elementu przechowywanego w stosie.
**/
struct ElementStosu {
	/** \brief Wskaznik do nastepnego elementu. **/
	ElementStosu* nastepny;
	/** \brief Wlasciwy zapamietany element. **/
	TYP elem;

	/** \brief Konstruktor. **/
	ElementStosu():
		nastepny(NULL) {};
	/** \brief Destruktor. **/
	~ElementStosu() { if (nastepny != NULL) delete nastepny; }
};
/**
\brief Implementacja stosu na liscie.
**/
class StosLista{
private:
	/** \brief Wskaznik na pierwszy element stosu. **/
	ElementStosu *pierwszy;
	/** \brief Ilosc elementow na stosie. **/
	int ilosc_elementow;
public:
	/** \brief Konstruktor. **/
	StosLista():
		pierwszy(NULL),
		ilosc_elementow(0) {};
	/** \brief Destruktor. **/
	~StosLista() { if (pierwszy != NULL) delete pierwszy; };
	/** \brief Wstawia element na szczyt stosu.
	\param cel docelowy stos.
	\param element do wstawienia na stos docelowy.
	\return powodzenie wykonania funkcji. **/
	static bool push(StosLista& cel, TYP element);
	/** \brief Usuwa element ze szczytu stosu.
	\param cel docelowey stos.
	\param element sciagniety ze stosu.
	\return powodzenie wykonania funkcji. **/
	static bool pop(StosLista& cel, TYP& element);
	/** \brief Sprawdza czy stos nie ma zadnych elementow.
	\param cel docelowy stos.
	\return true - jesli pusty.
	false - jesli nie pusty. **/
	static bool isempty(StosLista& cel);
	/** \brief Sprawdza ile elementow jest na stosie. 
	\param cel docelowy stos.
	\return ilosc elementow. **/
	static int size(StosLista& cel);
};

#endif