#include "PointMateriel.h"
#include "SupportADessin.h"
#include <iostream>

[[nodiscard]] double PointMateriel::getMasse() const {
    return masse;
}

void PointMateriel::affiche() const {
  std::cout << "Masse # " << masse << '\n';
  std::cout << "Position # " << pos << '\n';
  std::cout << "Vitesse # " << vit << '\n';
}

[[nodiscard]] Vecteur PointMateriel::evolution(const double& t) const {
  return champForces * (1 / this->getMasse());
}

void PointMateriel::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

bool PointMateriel::perturbation() const {
  return perturbe;
}

void PointMateriel::perturber() {
  perturbe = true;
}

void PointMateriel::relaxer() {
  perturbe = false;
}

double PointMateriel::getCharge() const {
  return 0.0;
}

void PointMateriel::modifParam(const modif& param) {
  this->param = param;
}

const modif& PointMateriel::getParam() const {
  return param;
}

std::ostream& PointMateriel::affiche(std::ostream& sortie) const {
  sortie << "Masse # " << masse;
  sortie << "\nPosition # " << pos;
  sortie << "\nVitesse # " << vit << '\n';
  return sortie;
}

std::ostream& operator<<(std::ostream& sortie, const PointMateriel& point) {
  point.affiche(sortie);
  return sortie;
}