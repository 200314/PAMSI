#ifndef BREADTHSEARCH
#define BREADTHSEARCH

/**
\file BreadthSearch.h
**/

#include <queue>
#include "Definicje.h"
#include "Graf.h"

using namespace std;

/**
\brief Algorytm szukania wszerz.
**/
class BreadthSearch
{
public:
  static bool szukaj(Graf& graf, int W1, int W2, list<int>& sciezka);
};

#endif