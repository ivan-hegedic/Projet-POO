#include "PointCharge.h"
#include "SupportADessin.h"

std::ostream& PointCharge::affiche(std::ostream& sortie) const {
  PointMateriel::affiche(sortie);
  sortie << "Charge # " << charge << '\n';
  return sortie;
}

void PointCharge::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

double PointCharge::getCharge() const {
  return charge;
}

std::ostream& operator<<(std::ostream& sortie, const PointCharge& particule) {
  particule.PointCharge::affiche(sortie);
  return sortie;
}