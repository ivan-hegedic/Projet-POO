#include "Integrateurs.h"
#include "PointMateriel.h"
#include "constantes.h"
#include <iostream>

Vecteur EulerCromer::integre(ObjetMobile& objet, const double& t, const double& dt) const {
  const Vecteur vit_courante(objet.vitesse());
  objet.setVitesse(objet.vitesse() + objet.acceleration() * dt);
  return objet.position() + vit_courante * dt;
}

Vecteur EulerCromer::integre(PointMateriel*& point, const double& t, const double& dt) const {
  if (point != nullptr) {
    if (point->getChamp() != nullptr)
      point->setChampForces(point->getChamp()->force(point, t));
    point->setAcceleration(point->evolution(t));
    Vecteur const vitNew = point->vitesse() + point->acceleration().mult(dt);
    point->setVitesse(vitNew);
    return point->position() + vitNew.mult(dt);
  }
  return constantes::vecnul;
}

void EulerCromer::evolue(ObjetMobile& objet, double& tinit, const double& tfin, double const& dt) const {
  while (tinit < tfin) {
    objet.setPosition(integre(objet, tinit, dt));
    tinit += dt;
  }
}

void EulerCromer::evolue(PointMateriel*& point, double& tinit, const double& tfin, const double& dt) const {
  unsigned int compteur(0);
  while (tinit < tfin) {
    if (compteur % 100 == 0) {
      std::cout << std::fixed << std::setprecision(5) << tinit << "   " << point->position() << '\n';
    }
    if (point->getContrainte() != nullptr) {
      point->setChampForces(point->getContrainte()->applique_force(point, point->acceleration(), tinit));
      point->setVitesse(point->getContrainte()->vitesse(point, tinit));
      point->setPosition(point->getContrainte()->position(point, tinit));
    }
    point->setPosition(integre(point, tinit, dt));
    if (point->getContrainte() != nullptr)
      point->setPosition(point->getContrainte()->position(point, tinit));
    compteur++;
    tinit += dt;
  }
}

std::string EulerCromer::getNom() const{
  return "Euler-Cromer";
}

Vecteur Newmark::integre(ObjetMobile& objet, const double& t, const double& dt) const {
  const Vecteur s = objet.acceleration();
  Vecteur q = objet.position();
  {
    const Vecteur r = objet.acceleration();
    objet.setVitesse(objet.vitesse() + (r + s).mult(dt / 2));
    objet.setPosition(objet.position() + objet.vitesse().mult(dt) + (r.mult(0.5) + s).mult(dt * dt / 3));
    q = objet.position();
  } while ((objet.position() + q.opposee()).norme1() >= 1.0e-1);
  return objet.position();
}

Vecteur Newmark::integre(PointMateriel*& point, const double& t, const double& dt) const {
  if (point != nullptr) {
    if (point->getChamp() != nullptr)
      point->setChampForces(point->getChamp()->force(point, t));
    const Vecteur position_courante(point->position());
    const Vecteur vitesse_courante(point->vitesse());
    const Vecteur r(point->evolution(t));
    const EulerCromer Oily;
    Oily.integre(point, t, dt);
    const Vecteur s(point->evolution(t + dt));
    point->setAcceleration((r + s) / 2.0);
    point->setVitesse(vitesse_courante + point->acceleration() * dt);
    return position_courante + vitesse_courante * dt + point->acceleration() * dt * dt / 2.0;
  }
  return constantes::vecnul;
}

void Newmark::evolue(PointMateriel*& point, double &tinit, const double &tfin, const double &dt) const {
  unsigned int compteur(0);
  while (tinit < tfin) {
    if (compteur % 100 == 0) {
      std::cout << std::fixed << std::setprecision(5) << tinit << "   " << point->position() << '\n';
    }
    if (point->getContrainte() != nullptr) {
      point->setChampForces(point->getContrainte()->applique_force(point, point->acceleration(), tinit));
      point->setVitesse(point->getContrainte()->vitesse(point, tinit));
      point->setPosition(point->getContrainte()->position(point, tinit));
    }
    point->setPosition(integre(point, tinit, dt));
    compteur++;
    tinit += dt;
  }
}

std::string Newmark::getNom() const{
  return "Newmark";
}

Vecteur RungeKuttaOr4::integre(ObjetMobile &objet, const double &t, const double &dt) const {
  const Vecteur vit_courante(objet.vitesse());
  objet.setVitesse(objet.vitesse() + objet.acceleration() * dt);
  return objet.position() + vit_courante * dt;
}

Vecteur RungeKuttaOr4::integre(PointMateriel*& point, const double& t, const double& dt) const {
  if (point != nullptr) {
    if (point->getChamp() != nullptr)
      point->setChampForces(point->getChamp()->force(point, t));
    point->setAcceleration(point->evolution(t));
    const Vecteur pos_courante(point->position());
    const Vecteur k1(point->vitesse());
    const Vecteur g1(point->evolution(t));
    const Vecteur k2(k1 + g1 * (dt / 2.0));
    const EulerCromer Oily;
    point->setVitesse(k2);
    point->setPosition(Oily.integre(point, t, dt / 2.0));
    const Vecteur g2(point->evolution(t + dt / 2.0));
    const Vecteur k3(k1 + g2 * (dt / 2.0));
    point->setVitesse(k3);
    point->setPosition(Oily.integre(point, t + dt / 2.0, dt / 2.0 ));
    const Vecteur g3(point->evolution(t + dt / 2.0));
    const Vecteur k4(k1 + g3 * dt);
    point->setVitesse(k4);
    point->setPosition(Oily.integre(point, t + dt, dt / 2.0));
    const Vecteur g4(point->evolution(t + dt));
    point->setVitesse(k1 + (g1 + 2.0 * g2 + 2.0 * g3 + g4) * dt / 6.0);
    return pos_courante + (k1 + 2.0 * k2 + 2.0 * k3 + k4) * dt / 6.0;
  }
  return constantes::vecnul;
}

std::string RungeKuttaOr4::getNom() const{
  return "Runge-Kutta d'ordre 4";
}