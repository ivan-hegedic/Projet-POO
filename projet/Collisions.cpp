#include "Collisions.h"
#include "PointMateriel.h"
#include <cmath>

double Collision::getRestitution() const {
  return restitution;
}

void Collision::setRestitution(const double& restitution) {
  this->restitution = restitution;
}

PointMateriel *Collision::getAutre() const {
  return autre;
}

void Collision::setAutre(PointMateriel& autre) {
  this->autre = &autre;
}

double Collision::getTolerance() const {
  return tolerance;
}

void Collision::setTolerance(const double& tolerance) {
  this->tolerance = tolerance;
}

void Collision::afficher(std::ostream& sortie) const {
  sortie << "Collision à restitution " << restitution;
}

Vecteur Collision::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  if (objet != nullptr)
    return objet->force();
  return constantes::vecnul;
}

Vecteur Collision::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->position();
  return constantes::vecnul;
}

Vecteur Collision::vitesse(PointMateriel*& objet, const double&t) {
  if (objet != nullptr) {
    if (autre != objet) {
      if (std::abs((autre->position() - objet->position()).norme1()) < tolerance) {
        const double m1(autre->getMasse()), m2(objet->getMasse());
        const Vecteur vitesse_cm((m1 * autre->vitesse() + m2 * objet->vitesse()) / (m1 + m2));
        objet->perturber();
        return (1 + restitution) * vitesse_cm - restitution * objet->vitesse();
      }
    }
    return objet->vitesse();
  }
  return constantes::vecnul;
}

/* Pas de vérification si autre est nullptr parce qu'il ne peut pas l'être. */

std::ostream& operator<<(std::ostream& sortie, const Collision& collision) {
  collision.afficher(sortie);
  return sortie;
}

void Elastique::afficher(std::ostream& sortie) const {
  sortie << "Collision élastique";
}

Vecteur Elastique::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    if (autre != objet) {
      if (std::abs((autre->position() - objet->position()).norme1()) < tolerance) {
        const double m1 = autre->getMasse(), m2 = objet->getMasse();
        const Vecteur vitesse_cm = (m1 * autre->vitesse() + m2 * objet->vitesse()) / (m1 + m2);
        objet->perturber();
        return 2 * vitesse_cm - objet->vitesse();
      }
    }
      return objet->vitesse();
    }
  return constantes::vecnul;
}

/* Pas de vérification si autre est nullptr parce qu'il ne peut pas l'être. */

std::ostream& operator<<(std::ostream& sortie, const Elastique& elastique) {
  elastique.afficher(sortie);
  return sortie;
}

void Plastique::afficher(std::ostream& sortie) const {
  sortie << "Collision plastique";
}

Vecteur Plastique::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr) {
    if (this->autre != objet) {
      if (std::abs((this->autre->position() - objet->position()).norme1()) < tolerance) {
        const double m1 = this->autre->getMasse(), m2 = objet->getMasse();
        objet->perturber();
        return (m1 * this->autre->vitesse() + m2 * objet->vitesse()) / (m1 + m2);
      }
    }
    return objet->vitesse();
  }
  return constantes::vecnul;
}

/* Pas de vérification si autre est nullptr parce qu'il ne peut pas l'être. */

std::ostream& operator<<(std::ostream& sortie, const Plastique& plastique) {
  plastique.afficher(sortie);
  return sortie;
}