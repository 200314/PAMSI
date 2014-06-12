#ifndef ASTAR
#define ASTAR

/**
\file AStar.h
**/

#include <queue>
#include "Definicje.h"
#include "Graf.h"

using namespace std;

/**
\brief Algorytm szukania A*.
**/
class AStar
{
public:
  static Graf* gr;
  static bool szukaj(Graf& graf, int W1, int W2, list<int>& sciezka);
};

class PorownajWierzcholki {
public:
  bool operator()(int& W1, int& W2)
  {
    return (AStar::gr->wierzcholek(W1).szacowany_koszt > AStar::gr->wierzcholek(W2).szacowany_koszt);
  }
};

#endif