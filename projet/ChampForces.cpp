#include "constantes.h"
#include "ChampForces.h"
#include "PointMateriel.h"
#include "SupportADessin.h"
#include <iostream>

Vecteur ChampForces::force(PointMateriel*& point, const double& t) const {
  return constantes::vecnul;
}

double ChampForces::potentiel(PointMateriel*& point, const double& t) const {
  return 0.0;
}

double ChampForces::energiePotentielle(PointMateriel*& point, const double& t) const {
  return 0.0;
}

void ChampForces::affiche(std::ostream& sortie) const {
  sortie << "Champ de forces";
}

void ChampForces::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

void ChampForces::modifParam(const modif& param) {
  this->param = param;
}

const modif& ChampForces::getParam() const {
  return param;
}

std::ostream& operator<<(std::ostream& sortie, const ChampForces& champ) {
  champ.affiche(sortie);
  return sortie;
}

Vecteur ChampForcesNull::force(PointMateriel*& point, const double& t) const {
  return constantes::vecnul;
}

void ChampForcesNull::affiche(std::ostream& sortie) const {
  sortie << "Champ de forces nilpotent";
}

void ChampCombine::ajouter(ChampForces& champ) {
  champs.emplace_back(&champ);
}

void ChampCombine::affiche(std::ostream& sortie) const {
  sortie << "Champ combiné :";
  for (const auto& champ : champs)
    if (champ != nullptr)
      sortie << '\n' << *champ;
}

Vecteur ChampCombine::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr) {
    Vecteur retour(constantes::vecnul);
    for (const auto& champ : champs)
      if (champ != nullptr)
        retour += champ->force(point, t);
    return retour;
  }
  return constantes::vecnul;
}

double ChampCombine::potentiel(PointMateriel*& point, const double& t) const {
  if (point != nullptr) {
    double somme(0.0);
    for (const auto& champ: champs)
      if (champ != nullptr)
        somme += champ->potentiel(point, t);
    return somme;
  }
  return 0.0;
}

double ChampCombine::energiePotentielle(PointMateriel*& point, const double& t) const {
  if (point != nullptr) {
    double somme(0.0);
    for (const auto& champ: champs)
      if (champ != nullptr)
        somme += champ->energiePotentielle(point, t);
    return somme;
  }
  return 0.0;
}

std::ostream& operator<<(std::ostream& sortie, const ChampCombine& champ) {
  champ.affiche(sortie);
  return sortie;
}