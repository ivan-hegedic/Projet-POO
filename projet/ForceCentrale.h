#ifndef FORCECENTRALE_H
#define FORCECENTRALE_H

#include "PointMateriel.h"
#include "PointCharge.h"

class ForceCentrale{

  /// Attributs

  protected:

  PointMateriel* source = nullptr;

  /// Méthodes

  [[nodiscard]] Vecteur quadratique_inverse(const PointMateriel& autre) const;

  [[nodiscard]] double inverse(const PointMateriel& autre) const;

 public:

  /// Constructeurs

  explicit ForceCentrale(PointMateriel& point)
    : source(&point) {}

  explicit ForceCentrale(PointCharge& charge)
    : source(&charge) {}

  /* Pas de constructeur par défaut (voir Conception). */

  virtual ~ForceCentrale() = default;
};

#endif //FORCECENTRALE_H