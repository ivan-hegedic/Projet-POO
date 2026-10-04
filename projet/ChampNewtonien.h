#ifndef CHAMPNEWTONIEN_H
#define CHAMPNEWTONIEN_H

#include "ChampForces.h"
#include "ForceCentrale.h"

class PointMateriel;

class ChampNewtonien final : public ForceCentrale, public ChampForces {

  /// Attributs

  private:

  double G = constantes::G;

  /// Constructeurs

  public:

  explicit ChampNewtonien(PointMateriel& point)
    : ForceCentrale(point) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~ChampNewtonien() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur champMagnitude(PointMateriel*& autre) const;

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double potentiel(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double energiePotentielle(PointMateriel*& point, const double& t) const override;

  void setG(const double& G);

  void affiche(std::ostream& sortie) const override;

  void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampNewtonien& champ);

#endif //CHAMPNEWTONIEN_H