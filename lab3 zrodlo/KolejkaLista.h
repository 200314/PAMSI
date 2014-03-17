#ifndef KOLEJKALISTA
#define KOLEJKALISTA

/**
\file KolejkaLista.h
**/

#include "definicje.h"
#include <stdlib.h>

using namespace std;

/**
\brief Struktura pojedynczego elementu przechowywanego w kolejce.
**/
struct ElementKolejki {
	/** \brief Wskaznik do nastepnego elementu. **/
	ElementKolejki* nastepny;
	/** \brief Wskaznik do poprzedniego elementu. **/
	ElementKolejki* poprzedni;
	/** \brief Wlasciwy zapamietany element. **/
	TYP elem;

	/** \brief Konstruktor. **/
	ElementKolejki():
		nastepny(NULL),
		poprzedni(NULL) {};
	/** \brief Destruktor. **/
	~ElementKolejki() { if (nastepny != NULL) delete nastepny;
				 if (poprzedni!= NULL) delete poprzedni; }
};
/**
\brief Implementacja kolejki na liscie.
**/
class KolejkaLista{
private:
	/** \brief Wskaznik na pierwszy element kolejki. **/
	ElementKolejki *pierwszy;
	/** \brief Wskaznik na ostatni element kolejki. **/
	ElementKolejki *ostatni;
	/** \brief Ilosc elementow w kolejce. **/
	int ilosc_elementow;
public:
	/** \brief Konstruktor. **/
	KolejkaLista():
		pierwszy(NULL),
		ostatni(NULL),
		ilosc_elementow(0) {};
	/** \brief Destruktor. **/
	~KolejkaLista() { if (pierwszy != NULL) delete pierwszy;
				   if (ostatni  != NULL) delete ostatni; };
	/** \brief Wstawia element na poczatek kolejki.
	\param cel docelowa kolejka.
	\param element do wstawienia na kolejke docelowa.
	\return powodzenie wykonania funkcji. **/
	static bool enqueue(KolejkaLista& cel, TYP element);
	/** \brief Usuwa element z konca kolejki.
	\param cel docelowa kolejka.
	\param element sciagniety z kolejki.
	\return powodzenie wykonania funkcji. **/
	static bool dequeue(KolejkaLista& cel, TYP& element);
	/** \brief Sprawdza czy kolejka nie ma zadnych elementow.
	\param cel docelowkolejka.
	\return true - jesli pusty.
	false - jesli nie pusty. **/
	static bool isempty(KolejkaLista& cel);
	/** \brief Sprawdza ile elementow jest w kolejce. 
	\param cel docelowa kolejka.
	\return ilosc elementow. **/
	static int size(KolejkaLista& cel);
};

#endif