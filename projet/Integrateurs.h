#ifndef INTEGRATEURS_H
#define INTEGRATEURS_H

#include "Vecteur.h"

class ObjetMobile;
class PointMateriel;

class Integrateur {

  /// Méthodes et constructeurs

  public:

  Integrateur() = default;

  virtual ~Integrateur() = default;

  virtual Vecteur integre(ObjetMobile& objet, const double& t, const double& dt) const = 0;

  virtual Vecteur integre(PointMateriel*& point, const double& t, const double& dt) const = 0;

  virtual std::string getNom() const = 0;
};

class EulerCromer final : public Integrateur {

  /// Constructeurs

  public:

  EulerCromer() = default;

  ~EulerCromer() override = default;

  /// Méthodes

  Vecteur integre(ObjetMobile& objet, const double& t, const double& dt) const override;

  Vecteur integre(PointMateriel*& point, const double& t, const double& dt) const override;

  /* Les deux méthodes suivantes nous servent dans testPomme où l'on n'avait pas encore introduit
   * la classe Systeme. Du coup, il fallait créer une méthode d'évolution appropriée. */

  void evolue(ObjetMobile& objet, double& tinit, const double& tfin, const double& dt) const;

  void evolue(PointMateriel*& point, double& tinit, const double& tfin, const double& dt) const;

  std::string getNom() const override;
};

class Newmark final : public Integrateur {

  /// Constructeurs

  public:

  Newmark() = default;

  ~Newmark() override = default;

  /// Méthodes

  Vecteur integre(ObjetMobile& objet, const double& t, const double& dt) const override;

  Vecteur integre(PointMateriel*& point, const double& t, const double& dt) const override;

  /* La méthode suivante nous sert dans testPomme où l'on n'avait pas encore introduit
     * la classe Systeme. Du coup, il fallait créer une méthode d'évolution appropriée. */

  void evolue(PointMateriel*& point, double& tinit, const double& tfin, const double& dt) const;

  std::string getNom() const override;
};

class RungeKuttaOr4 final : public Integrateur {

  /// Constructeurs

  public:

  RungeKuttaOr4() = default;

  ~RungeKuttaOr4() override = default;

  /// Méthodes

  Vecteur integre(ObjetMobile& objet, const double& t, const double& dt) const override;

  /* On n'implémente pas l'algorithme de Runge-Kutta dans la méthode integre pour les ObjetMobiles
   * parce que son algorithme est réduit en celui de EulerCromer. */

  Vecteur integre(PointMateriel*& point, const double& t, const double& dt) const override;

  std::string getNom() const override;
};

#endif //INTEGRATEURS_H