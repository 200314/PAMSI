#ifndef DEPTHSEARCH
#define DEPTHSEARCH

/**
\file DepthSearch.h
**/

#include <stack>
#include "Definicje.h"
#include "Graf.h"

using namespace std;

/**
\brief Algorytm szukania wszerz.
**/
class DepthSearch
{
public:
  static bool szukaj(Graf& graf, int W1, int W2, list<int>& sciezka);
};

#endif