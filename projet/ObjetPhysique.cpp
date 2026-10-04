#include "ObjetPhysique.h"
#include "ObjetMobile.h"
#include "ChampForces.h"
#include "Vecteur.h"
#include "SupportADessin.h"
#include <iostream>

void ObjetPhysique::affiche_force() const {
  std::cout << "Force # " << champForces << '\n';
}

[[nodiscard]] Vecteur ObjetPhysique::force() const {
  return champForces;
}

std::ostream& ObjetPhysique::affiche_force(std::ostream& sortie) const {
  sortie << "Force # " << champForces << '\n';
  return sortie;
}

void ObjetPhysique::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

void ObjetPhysique::affiche_contrainte(std::ostream& sortie) const {
  sortie << "Contrainte : ";
  if (contrainte != nullptr)
    sortie << *contrainte;
  else
    sortie << "(null)";
}

void ObjetPhysique::affiche_champ(std::ostream& sortie) const {
  sortie << "Champ de forces : ";
  if (champ != nullptr)
    sortie << *champ;
  else
    sortie << "(null)";
}

std::ostream& ObjetPhysique::affiche(std::ostream& sortie) const {
  sortie << "Position # " << pos << '\n';
  sortie << "Vitesse # " << vit << '\n';
  sortie << "Acceleration # " << acc << '\n';
  sortie << "Force # " << champForces << '\n';
  return sortie;
}

void ObjetPhysique::setChampForces(const Vecteur& champForces) {
  this->champForces = champForces;
}

void ObjetPhysique::setContrainte(Contrainte*& contrainte) {
  if (contrainte != nullptr)
    this->contrainte = contrainte;
}

void ObjetPhysique::setChamp(ChampForces*& champ) {
  if (champ != nullptr)
    this->champ = champ;
}

Contrainte* ObjetPhysique::getContrainte() const {
  return contrainte;
}

ChampForces* ObjetPhysique::getChamp() const {
  return champ;
}

std::ostream& operator<<(std::ostream& sortie, const ObjetPhysique& objet) {
  objet.affiche(sortie);
  return sortie;
}