#ifndef CHAMPRESTREINT_H
#define CHAMPRESTREINT_H

#include <array>
#include <string>
#include "ChampForces.h"

class ChampRestreint final : public ChampForces {

  /// Attributs

  private:

  ChampForces* champ;
  bool enclosed;
  std::array<bool, 6> bornes;
  std::array<double, 6> coords;
  std::array<std::string, 6> bords = {"gauche", "droite", "derriere", "devant", "bas", "haut"};

  /// Constructeurs

  public:

  explicit ChampRestreint(ChampForces& champ, const bool& enclosed, const std::array<bool, 6>& bornes, const std::array<double, 6>& coords)
    : champ(&champ), enclosed(enclosed), bornes(bornes), coords(coords) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~ChampRestreint() override = default;

  /// Méthodes

  [[nodiscard]] bool contient(const Vecteur& position) const;

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  void affiche(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampRestreint& champ);

#endif //CHAMPRESTREINT_H