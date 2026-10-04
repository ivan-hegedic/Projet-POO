#ifndef CONTRAINTE_H
#define CONTRAINTE_H

#include "Vecteur.h"
#include "constantes_graphique.h"
#include "Dessinable.h"

class PointMateriel;

class Contrainte : public Dessinable {

  modif param = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0}, {false, false}, false, Rien, 0};

  /// Constructeurs

  public:

  Contrainte() = default;

  ~Contrainte() override = default;

  /// Méthodes

  [[nodiscard]] virtual Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t);

  virtual Vecteur position(PointMateriel*& objet, const double& t);

  virtual Vecteur vitesse(PointMateriel*& objet, const double& t);

  virtual void afficher(std::ostream& sortie) const;

  void dessine_sur(SupportADessin& support) override;

  [[nodiscard]] virtual Vecteur getCentre() const;

  void modifParam(const modif& p);

  [[nodiscard]] const modif& getParam() const;
};

std::ostream& operator<<(std::ostream& sortie, const Contrainte& contrainte);

class ContrainteCombinee final : public Contrainte {

  /// Attributs

  private:

  std::vector<Contrainte*> contraintes;

  /// Constructeurs

  public:

  ContrainteCombinee(const std::initializer_list<Contrainte*>& contraintes)
    : contraintes(contraintes) {}

  ContrainteCombinee() = default;

  ~ContrainteCombinee() override = default;

  explicit ContrainteCombinee(const ContrainteCombinee& autre) = delete;
  ContrainteCombinee& operator=(const ContrainteCombinee& autre) = delete;
  explicit ContrainteCombinee(ContrainteCombinee&&) = delete;
  ContrainteCombinee& operator=(ContrainteCombinee&&) = delete;

  /* On ne copie pas les ContrainteCombinees en raison que les contraintes y ajoutées puissent avoir des
   * pointeurs en tant qu'attributs dont faire la copie profonde nous paraît trop fastidieux
   * pour nos besoins dans ce projet, mais elles peuvent être ajoutées dans d'autres ContrainteCombinees. */

  /// Méthodes

  void ajouter(Contrainte& contrainte);

  void ajouter(Contrainte*& contrainte);

  void ajouter(ContrainteCombinee& contrainte);

  void ajouter(ContrainteCombinee*& contrainte);

  void afficher(std::ostream& sortie) const override;

  void dessine_sur(SupportADessin& support) override;

  Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;

  Vecteur position(PointMateriel*& objet, const double& t) override;

  [[nodiscard]] std::vector<Contrainte*> getContraintes() const;

};

std::ostream& operator<<(std::ostream& sortie, const ContrainteCombinee& contrainteCombinee);

class ContrainteLibre final : public Contrainte {

  /// Méthodes

public:

  Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) override;

  Vecteur position(PointMateriel*& objet, const double& t) override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;

  void afficher(std::ostream& sortie) const override ;
};

std::ostream& operator<<(std::ostream& sortie, const ContrainteLibre& libre);

#endif //CONTRAINTE_H