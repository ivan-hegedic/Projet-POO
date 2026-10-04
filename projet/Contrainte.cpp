#include "Contrainte.h"
#include "SupportADessin.h"
#include "PointMateriel.h"

Vecteur Contrainte::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  if (objet != nullptr)
    return objet->force();
  return constantes::vecnul;
}

Vecteur Contrainte::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->position();
  return constantes::vecnul;
}

Vecteur Contrainte::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->vitesse();
  return constantes::vecnul;
}

void Contrainte::afficher(std::ostream& sortie) const {
  sortie << "Contrainte";
}

Vecteur Contrainte::getCentre() const {
  return constantes::vecnul;
}

void Contrainte::modifParam(const modif& param) {
  this->param = param;
}

const modif& Contrainte::getParam() const {
  return param;
}

std::ostream& operator<<(std::ostream& sortie, const Contrainte& contrainte) {
  contrainte.afficher(sortie);
  return sortie;
}

std::ostream& operator<<(std::ostream& sortie, const Contrainte*& contrainte) {
  if (contrainte != nullptr)
    contrainte->afficher(sortie);
  return sortie;
}

void Contrainte::dessine_sur(SupportADessin& support) {}

void ContrainteCombinee::ajouter(Contrainte& contrainte) {
  contraintes.emplace_back(&contrainte);
}

void ContrainteCombinee::ajouter(Contrainte*& contrainte) {
  if (contrainte != nullptr)
    contraintes.emplace_back(contrainte);
}

void ContrainteCombinee::ajouter(ContrainteCombinee& contrainte) {
  contraintes.emplace_back(&contrainte);
}

void ContrainteCombinee::ajouter(ContrainteCombinee*& contrainte) {
  if (contrainte != nullptr)
    contraintes.emplace_back(contrainte);
}

void ContrainteCombinee::afficher(std::ostream& sortie) const {
  sortie << "Contrainte combinée :";
  for (const auto& contrainte : contraintes)
    if (contrainte != nullptr)
      sortie << '\n' << *contrainte;
}

std::ostream& operator<<(std::ostream& sortie, const ContrainteCombinee& contrainteCombinee) {
  contrainteCombinee.afficher(sortie);
  return sortie;
}

Vecteur ContrainteCombinee::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  Vecteur retour(constantes::vecnul);
  if (objet != nullptr)
    for (const auto& contrainte : contraintes)
      if (contrainte != nullptr)
        retour += contrainte->applique_force(objet, force, t);
  return retour;
}

Vecteur ContrainteCombinee::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    Vecteur retour = objet->position();
    for (const auto& contrainte: contraintes)
      if (contrainte != nullptr)
        retour = contrainte->position(objet, t);
    return retour;
  }
  return constantes::vecnul;
}

std::vector<Contrainte*> ContrainteCombinee::getContraintes() const {
  return contraintes;
}

Vecteur ContrainteCombinee::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    for (const auto& contrainte : contraintes)
      if (contrainte != nullptr)
        if (Vecteur vitcourante = objet->vitesse(), vitnouvelle = contrainte->vitesse(objet, t); vitcourante != vitnouvelle)
          return vitnouvelle;
    return objet->vitesse();
  }
  return constantes::vecnul;
}

void ContrainteCombinee::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

Vecteur ContrainteLibre::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  if (objet != nullptr)
    return objet->force();
  return constantes::vecnul;
}

Vecteur ContrainteLibre::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->position();
  return constantes::vecnul;
}

Vecteur ContrainteLibre::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->vitesse();
  return constantes::vecnul;
}

void ContrainteLibre::afficher(std::ostream& sortie) const  {
  sortie << "Contrainte libre";
}

std::ostream& operator<<(std::ostream& sortie, const ContrainteLibre& libre) {
  libre.afficher(sortie);
  return sortie;
}