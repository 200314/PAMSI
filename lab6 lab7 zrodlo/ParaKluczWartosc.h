#ifndef PARAKLUCZWARTOSC
#define PARAKLUCZWARTOSC

/**
\file ParaKluczWartosc.h
**/

#include "definicje.h"

using namespace std;


/**
\brief Struktura pary klucz i wartosc.
**/
struct ParaKluczWartosc {
  TYP_KLUCZ klucz;
  TYP_WARTOSC wartosc;

  /** \brief Kontruktor z podanymi wartosciami pol. **/
  ParaKluczWartosc(TYP_KLUCZ klucz, TYP_WARTOSC wartosc):
    klucz(klucz), wartosc(wartosc) {};
  /** \brief Kontruktor ustawia pola na oznaczenia braku pary. **/
  ParaKluczWartosc():
    klucz(KLUCZ_ZERO), wartosc(WARTOSC_ZERO) {};
  /** \brief Sprawdza czy dana para istnieje. **/
  bool czy_istnieje() { return (wartosc != WARTOSC_ZERO); }
  /** \brief Sprawdza czy klucz oznacza ze para istenieje i ma sens. **/
  bool czy_zajety() { return (klucz != KLUCZ_ZERO); }
};

#endif