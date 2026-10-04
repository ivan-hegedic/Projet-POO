#ifndef POINTMATERIEL_H
#define POINTMATERIEL_H

#include "Vecteur.h"
#include "constantes.h"
#include "Dessinable.h"
#include "ObjetPhysique.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include "ContrainteSpherique.h"
#include "constantes_graphique.h"
#include <cmath>

class PointMateriel : public ObjetPhysique {

  /// Attributs

  private:

  modif param = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0}, {false, false}, false, Rien, 0, {0, 0, 0, 0, 0, 0}};

  protected:

  double masse{};
  bool perturbe = false;

  public:

  /// Constructeurs

  explicit PointMateriel(const Vecteur& posinit, const Vecteur& vitinit, const Vecteur& acc, const double& masse)
    : ObjetPhysique(posinit, vitinit, acc), masse(masse) {}

  explicit PointMateriel(const ObjetPhysique& obj_phys, const double& mas)
    : ObjetPhysique(obj_phys), masse(mas) {}

  explicit PointMateriel(const Vecteur& posinit, const Vecteur& vitinit, const double& masse)
    : ObjetPhysique(posinit, vitinit), masse(masse) {}

  explicit PointMateriel(const Vecteur& posinit, const double& masse)
    : ObjetPhysique(posinit, constantes::vecnul), masse(masse) {}

  explicit PointMateriel(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, Contrainte& contrainte)
    : ObjetPhysique(posinit, vitinit, contrainte), masse(masse) {}

  explicit PointMateriel(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, ChampForces& champ)
    : ObjetPhysique(posinit, vitinit, champ), masse(masse) {}

  explicit PointMateriel(const Vecteur& posinit, const Vecteur& vitinit, const double& masse, Contrainte& contrainte, ChampForces& champ)
    : ObjetPhysique(posinit, vitinit, champ, contrainte), masse(masse) {}

  explicit PointMateriel(const double& theta, const double& phi, const double& masse, ContrainteSpherique& contrainte)
    : ObjetPhysique(), masse(masse) {
    const Vecteur relative({contrainte.getRayon() * sin(theta) * cos(phi), contrainte.getRayon() * sin(theta) * sin(phi), contrainte.getRayon() * cos(theta)});
    this->ObjetMobile::setPosition(relative + contrainte.getCentre());
    contrainte.setPoint(*this);
  }

  explicit PointMateriel(const double& theta, const double& phi, const double& v_theta, const double& v_phi, const double& masse, ContrainteSpherique& contrainte)
    : ObjetPhysique(), masse(masse) {
    const Vecteur relative({contrainte.getRayon() * sin(theta) * cos(phi), contrainte.getRayon() * sin(theta) * sin(phi), contrainte.getRayon() * cos(theta)});
    this->ObjetMobile::setPosition(relative + contrainte.getCentre());
    this->ObjetMobile::setVitesse({v_theta * cos (theta) * cos(phi) - v_phi * sin(phi), v_theta * cos(theta) * cos(phi) + v_phi * cos(phi), -1.0 * v_theta * sin(theta)});
    contrainte.setPoint(*this);
    }

  explicit PointMateriel(const double& theta, const double& phi, const Vecteur& vitesse, const double& masse, ContrainteSpherique& contrainte)
    : ObjetPhysique(), masse(masse) {
    const Vecteur relative({contrainte.getRayon() * sin(theta) * cos(phi), contrainte.getRayon() * sin(theta) * sin(phi), contrainte.getRayon() * cos(theta)});
    this->ObjetMobile::setPosition(relative + contrainte.getCentre());
    this->ObjetMobile::setVitesse(vitesse);
    contrainte.setPoint(*this);
  }

  PointMateriel(const PointMateriel& autre)
    : ObjetPhysique(autre), masse(autre.masse) {}

  PointMateriel(PointMateriel&& autre) noexcept
    : ObjetPhysique(std::move(autre)), masse(autre.masse) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~PointMateriel() override = default;

  /// Méthodes

  [[nodiscard]] double getMasse() const;

  virtual void affiche() const;

  std::ostream& affiche(std::ostream& sortie) const override ;

  [[nodiscard]] virtual Vecteur evolution(const double& t) const;

  void dessine_sur(SupportADessin& support) override;

  [[nodiscard]] bool perturbation() const;

  void perturber();

  void relaxer();

  [[nodiscard]] virtual double getCharge() const;

  void modifParam(const modif& param);

  [[nodiscard]] const modif& getParam() const;
};

std::ostream& operator<<(std::ostream& sortie, const PointMateriel& point_materiel);

#endif //POINTMATERIEL_H