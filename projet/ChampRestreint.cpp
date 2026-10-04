#include "ChampRestreint.h"
#include "PointMateriel.h"
#include "constantes.h"
#include <cmath>

bool ChampRestreint::contient(const Vecteur& position) const {
  bool effectue(true);
  for (size_t i(0); i < 6; ++i)
    if (bornes[i])
      if (pow(-1, i) * position.get_coord(i / 2) <= pow(-1, i) * coords[i])
        effectue = false;
  return effectue;
}

Vecteur ChampRestreint::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr && enclosed == contient(point->position()))
    return champ->force(point, t);
  return constantes::vecnul;
}

/* Pas de vérification si champ est nullptr parce qu'il ne peut pas l'être. */

void ChampRestreint::affiche(std::ostream& sortie) const {
  sortie << "Champ restreint : " << *champ << '\n' << "Bords (depuis l\'";
  sortie << (enclosed ? "intérieur" : "extérieur") << ") : ";
  for (size_t i(0); i < 6; i++)
    if (bornes[i])
      sortie << " " << bords[i] << " = " << coords[i];
}

/* Pas de vérification si champ est nullptr parce qu'il ne peut pas l'être. */