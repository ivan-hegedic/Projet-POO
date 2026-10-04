#include "ObjetMobile.h"
#include "SupportADessin.h"

Vecteur ObjetMobile::position() const {
  return pos;
}

Vecteur ObjetMobile::vitesse() const {
  return vit;
}

Vecteur ObjetMobile::acceleration() const {
  return acc;
}

void ObjetMobile::setPosition(Vecteur const& pos) {
  this->pos = pos;
}

void ObjetMobile::setVitesse(Vecteur const& vit) {
  this->vit = vit;
}

void ObjetMobile::setAcceleration(Vecteur const& acc) {
  this->acc = acc;
}

void ObjetMobile::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

std::ostream &ObjetMobile::affiche(std::ostream& sortie) const {
  sortie << "Position # " << pos << '\n';
  sortie << "Vitesse # " << vit << '\n';
  sortie << "Acceleration # " << acc << '\n';
  return sortie;
}

std::ostream& operator<<(std::ostream& sortie, const ObjetMobile& objet) {
  objet.affiche(sortie);
  return sortie;
}