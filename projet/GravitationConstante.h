#ifndef GRAVITATIONCONSTANTE_H
#define GRAVITATIONCONSTANTE_H

#include "constantes.h"
#include "SupportADessin.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include <iostream>

class GravitationConstante final : public ChampForces {

  /// Attributs

  private:

  Vecteur gravitation = constantes::gravitation;

  /// Méthodes

  public:

  explicit GravitationConstante(const Vecteur& gravitation)
    : gravitation(gravitation) {}

  /* Pas de constructeur par défaut. */

  ~GravitationConstante() override = default;

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  void affiche(std::ostream& sortie) const override;

  void dessine_sur(SupportADessin& support) override;
};

inline void GravitationConstante::affiche(std::ostream& sortie) const {
  sortie << "Gravitation constante : " << gravitation << '\n';
}

inline void GravitationConstante::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

inline Vecteur GravitationConstante::force(PointMateriel*& point, const double& t) const {
  if (point != nullptr)
    return point->getMasse() * gravitation;
  return constantes::vecnul;
}

inline std::ostream& operator<<(std::ostream& sortie, const GravitationConstante& gravitation) {
  gravitation.affiche(sortie);
  return sortie;
}

#endif //GRAVITATIONCONSTANTE_H