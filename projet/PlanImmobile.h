#ifndef PLANIMMOBILE_H
#define PLANIMMOBILE_H

#include "constantes.h"
#include "Contrainte.h"

class PlanImmobile final : public Contrainte {

  /// Attributs

  private:

  Vecteur pointReference = constantes::vecnul;
  Vecteur normal = constantes::vecnul;
  double restitution{};

  /// Constructeurs

  public:

  explicit PlanImmobile(const Vecteur& pointReference, const Vecteur& normal)
    : pointReference(pointReference), normal(normal.unitaire()), restitution(1.0) {}

  explicit PlanImmobile(const Vecteur& pointReference, const Vecteur& normal, const double& restitution)
  : pointReference(pointReference), normal(normal.unitaire()), restitution(restitution) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~PlanImmobile() override = default;

  /// Méthodes

  Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;

  Vecteur position(PointMateriel*& objet, const double& t) override;

  void afficher(std::ostream& sortie) const override;

  [[nodiscard]] Vecteur getPosition() const;

  [[nodiscard]] Vecteur getNormal() const;

  [[nodiscard]] double getRestitution() const;

  void setRestitution(const double& restitution);

  void setPointReference(const Vecteur& pointReference);

  void setNormal(const Vecteur& normal);

  void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, const PlanImmobile& planImmobile);

#endif //PLANIMMOBILE_H