#include "ChampNewtonien.h"
#include "SupportADessin.h"
#include "ChampForces.h"
#include "ForceCentrale.h"

Vecteur ChampNewtonien::champMagnitude(PointMateriel*& autre) const {
  if (autre != nullptr)
    return G * source->getMasse() * quadratique_inverse(*autre);
  return constantes::vecnul;
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */

Vecteur ChampNewtonien::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getMasse() * champMagnitude(point);
  return constantes::vecnul;
}

double ChampNewtonien::potentiel(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return (-1) * G * source->getMasse() * inverse(*point);
  return 0.0;
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */

double ChampNewtonien::energiePotentielle(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getMasse() * potentiel(point, t);
  return 0.0;
}

void ChampNewtonien::setG(const double& G) {
  this->G = G;
}

void ChampNewtonien::affiche(std::ostream& sortie) const {
  sortie << "Champ Newtonien avec source de masse " << source->getMasse();
  sortie << " à position " << source->position();
}

/* Pas de vérification si source est un nullptr parce qu'elle ne peut pas l'être. */

void ChampNewtonien::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

std::ostream& operator<<(std::ostream& sortie, const ChampNewtonien& champ) {
  champ.affiche(sortie);
  return sortie;
}