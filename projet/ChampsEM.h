#ifndef CHAMPSEM_H
#define CHAMPSEM_H

#include "ChampForces.h"
#include "ForceCentrale.h"

class PointCharge;
class PointMateriel;

class ChampElectrique final : public ForceCentrale, public ChampForces {

  /// Attributs

  private:

  double k = constantes::k;

  /// Constructeurs

  public:

  explicit ChampElectrique(PointCharge& charge)
    : ForceCentrale(charge) {}

  explicit ChampElectrique(const double& k, PointCharge& charge)
    : ForceCentrale(charge), k(k) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~ChampElectrique() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur champMagnitude(PointMateriel*& autre) const;

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double potentiel(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double energiePotentielle(PointMateriel*& point, const double& t) const override;

  void setK(const double& k);

  void affiche(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampElectrique& champ);

class ChampMagnetique final : public ChampForces {

  /// Attributs

  private:

  Vecteur champ_externe = constantes::vecnul;

  /// Constructeurs

  public:

  explicit ChampMagnetique(const Vecteur& champ_externe)
    : champ_externe(champ_externe) {}

  ~ChampMagnetique() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  void affiche(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampMagnetique& champ);

class ChampElectriqueConstant final : public ChampForces {

  /// Attributs

  private:

  Vecteur champ_externe = constantes::vecnul;

  /// Constructeurs

  public:

  explicit ChampElectriqueConstant(const Vecteur& champ_externe)
    : champ_externe(champ_externe) {}

  ~ChampElectriqueConstant() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  void affiche(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampElectriqueConstant& champ);

#endif //CHAMPSEM_H