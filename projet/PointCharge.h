#ifndef PointCharge_H
#define PointCharge_H

#include "PointMateriel.h"

class PointCharge final : public PointMateriel {

  /// Attributs

  private:

  double charge{};

  /// Constructeurs

  public:

  explicit PointCharge(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, const double& charge)
    : PointMateriel(posinit, vitinit, masse), charge(charge) {}

  explicit PointCharge(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, const double& charge, Contrainte& contrainte)
    : PointMateriel(posinit, vitinit, masse, contrainte), charge(charge) {}

  explicit PointCharge(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, const double& charge, ChampForces& champ)
    : PointMateriel(posinit, vitinit, masse, champ), charge(charge) {}

  explicit PointCharge(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, const double& charge, ChampForces& champ, Contrainte& contrainte)
    : PointMateriel(posinit, vitinit, masse, contrainte, champ), charge(charge) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~PointCharge() override = default;

  /// Méthodes

  std::ostream& affiche(std::ostream& sortie) const override;

  void dessine_sur(SupportADessin& support) override;

  [[nodiscard]] double getCharge() const override;
};

std::ostream& operator<<(std::ostream& sortie, const PointCharge& particule);

#endif //PointCharge_H