#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "PointMateriel.h"
#include "PointCharge.h"
#include "Contrainte.h"

class Collision : public Contrainte{

  /// Attributs

  private:

  double restitution{};

  protected:

  double tolerance = constantes::moins3;
  PointMateriel* autre = nullptr;

  /// Constructeurs

  public:

  explicit Collision(PointMateriel& objet)
    : autre(&objet) {}

  explicit Collision(PointCharge& objet)
    : autre(&objet) {}

  /* Pas de polymorphisme pour que l'attribut autre ne soit pas initialisé à nullptr. */

  explicit Collision(const double& tolerance, PointMateriel& objet)
    : tolerance(tolerance), autre(&objet) {}

  explicit Collision(const double& tolerance, PointCharge& objet)
    : tolerance(tolerance), autre(&objet) {}

  explicit Collision(const double& restitution, const double& tolerance, PointMateriel& objet)
    : restitution(restitution), tolerance(tolerance), autre(&objet) {}

  explicit Collision(const double& restitution, const double& tolerance, PointCharge& objet)
    : restitution(restitution), tolerance(tolerance), autre(&objet) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~Collision() override = default;

  /// Méthodes

  [[nodiscard]] double getRestitution() const;

  void setRestitution(const double& restitution);

  [[nodiscard]] PointMateriel* getAutre() const;

  void setAutre(PointMateriel& autre);

  [[nodiscard]] double getTolerance() const;

  void setTolerance(const double& tolerance);
  
  void afficher(std::ostream& sortie) const override;

  Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) override;

  Vecteur position(PointMateriel*& objet, const double& t) override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;
};

std::ostream& operator<<(std::ostream& sortie, const Collision& collision);

class Elastique final : public Collision {

  /// Constructeurs

  public:

  explicit Elastique(const double& tolerance, PointMateriel& objet)
    : Collision(1, tolerance, objet) {}

  explicit Elastique(PointMateriel& objet)
    : Collision(objet) {
    setRestitution(1);
  }

  /* Pas de constructeur par défaut parce que la classe parente Collision n'en dispose pas. */

  ~Elastique() override = default;
  
  /// Méthodes

  void afficher(std::ostream& sortie) const override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;
};

std::ostream& operator<<(std::ostream& sortie, const Elastique& elastique);

class Plastique final : public Collision {

  /// Constructeurs

  public:

  explicit Plastique(const double& tolerance, PointMateriel& objet)
    : Collision(0, tolerance, objet) {}

  explicit Plastique(PointMateriel& objet)
    : Collision(objet) {
    setRestitution(0);
  }

  /* Pas de constructeur par défaut parce que la classe parente Collision n'en dispose pas. */

  ~Plastique() override = default;

  /// Méthodes

  void afficher(std::ostream& sortie) const override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;
};

std::ostream& operator<<(std::ostream& sortie, const Plastique& plastique);

#endif //COLLISIONS_H