#include "PointMateriel.h"
#include "SupportADessin.h"
#include "PlanImmobile.h"
#include <iostream>

Vecteur PlanImmobile::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  if (objet != nullptr)
    return objet->force();
  return constantes::vecnul;
}

Vecteur PlanImmobile::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    if ((objet->position() - pointReference) * normal < 0.0) {
      objet->perturber();
      return objet->position() + normal * ((pointReference - objet->position()) * normal);
    }
    return objet->position();
  }
  return constantes::vecnul;
}

Vecteur PlanImmobile::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    if ((objet->position() - pointReference) * normal <= 0.0) {
      objet->perturber();
      return restitution * objet->vitesse().fais_devier(normal);
    }
    return objet->vitesse();
  }
  return constantes::vecnul;
}

void PlanImmobile::afficher(std::ostream& sortie) const {
  sortie << "Plan immobile au point ( " << pointReference << ") avec normal ( " << normal << ")";
}

Vecteur PlanImmobile::getPosition() const {
  return pointReference;
}

Vecteur PlanImmobile::getNormal() const {
  return normal;
}

double PlanImmobile::getRestitution() const {
  return restitution;
}

void PlanImmobile::setRestitution(const double& restitution) {
  this->restitution = restitution;
}

void PlanImmobile::setPointReference(const Vecteur& pointReference) {
  this->pointReference = pointReference;
}

void PlanImmobile::setNormal(const Vecteur& normal) {
  if (normal.norme1() != 0.0)
    this->normal = normal.unitaire();
  else
    std::cout << "Le vecteur normal ne peut pas être nul.\n";
}

void PlanImmobile::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

std::ostream& operator<<(std::ostream& sortie, const PlanImmobile& plan) {
  plan.afficher(sortie);
  return sortie;
}