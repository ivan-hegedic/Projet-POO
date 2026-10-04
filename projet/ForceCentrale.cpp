#include "constantes.h"
#include "ForceCentrale.h"

Vecteur ForceCentrale::quadratique_inverse(const PointMateriel& autre) const {
  const Vecteur posrel = source->position() - autre.position();
  if (const double r = posrel.norme1(); r < 1.0e-50)
    return constantes::vecnul;
  else
    return posrel * (1.0 / (r * r * r));
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */

double ForceCentrale::inverse(const PointMateriel& autre) const {
  const Vecteur posrel = source->position() - autre.position();
  if (const double r = posrel.norme1(); r < 1.0e-50)
    return 0.0;
  else
    return 1.0 / r;
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */