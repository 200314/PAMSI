#ifndef DEFINICJE
#define DEFINICJE

/**
\file definicje.h
\brief Plik zawiera ogolne instrukcje preprocesora wspolne dla wszystkich plikow zrodlowych.
**/
#include <string>

/** \brief Typ uzyty w strukturze, zawiera klucze do tablic. **/
#define TYP string
/** \brief Typ klucza w tablicach asocjacyjnych. **/
#define TYP_KLUCZ string
/** \brief Typ wartosci w tablicach asocjacyjnych. **/
#define TYP_WARTOSC int
/** \brief Wartosc klucza znaczaca brak klucza. **/
#define KLUCZ_ZERO ""
/** \brief Wartosc domyslna dla typu wartosci. **/
#define WARTOSC_ZERO 0
/** \brief Liczba list w tablicy haszujacej. **/
#define LICZBA_LIST 100000

#endif