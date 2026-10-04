#include "ChampsEM.h"
#include "PointCharge.h"
#include <iostream>

Vecteur ChampElectrique::champMagnitude(PointMateriel*& autre) const {
  if (autre != nullptr)
    return (-1) * k * source->getCharge() * quadratique_inverse(*autre);
  return constantes::vecnul;
}

/* Pas de vérification si source est un nullptr parce qu'elle ne peut pas l'être. */

Vecteur ChampElectrique::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getCharge() * champMagnitude(point);
  return constantes::vecnul;
}

double ChampElectrique::potentiel(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return k * source->getCharge() * inverse(*point);
  return 0.0;
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */

double ChampElectrique::energiePotentielle(PointMateriel *&point, const double &t) const {
  if (point != nullptr)
    return point->getCharge() * potentiel(point, t);
  return 0.0;
}

/* Pas de vérification si source est nullptr parce qu'elle ne peut pas l'être. */

void ChampElectrique::setK(const double& k) {
  this->k = k;
}

void ChampElectrique::affiche(std::ostream& sortie) const {
  sortie << "Champ électrique avec source de charge " << source->getCharge() << " à position " << source->position();
}

/* Pas de vérification si source est un nullptr parce qu'elle ne peut pas l'être. */

std::ostream& operator<<(std::ostream& sortie, const ChampElectrique& champ) {
  champ.affiche(sortie);
  return sortie;
}

Vecteur ChampMagnetique::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getCharge() * (point->vitesse() ^ champ_externe);
  return constantes::vecnul;
}

void ChampMagnetique::affiche(std::ostream& sortie) const {
  sortie << "Champ magnétique d'intensité " << champ_externe;
}

std::ostream& operator<<(std::ostream& sortie, const ChampMagnetique& champ) {
  champ.affiche(sortie);
  return sortie;
}

Vecteur ChampElectriqueConstant::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getCharge() * champ_externe;
  return constantes::vecnul;
}

void ChampElectriqueConstant::affiche(std::ostream& sortie) const {
  sortie << "Champ électrique constant d'intensité " << champ_externe;
}

std::ostream& operator<<(std::ostream& sortie, const ChampElectriqueConstant& champ) {
  champ.affiche(sortie);
  return sortie;
}