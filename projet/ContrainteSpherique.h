#ifndef CONTRAINTESPHERIQUE_H
#define CONTRAINTESPHERIQUE_H

#include "constantes.h"
#include "Vecteur.h"
#include "Contrainte.h"

class ContrainteSpherique final : public Contrainte {

  /// Attributs

  private:

  Vecteur centre = constantes::vecnul;
  double rayon{};
  const PointMateriel* point = nullptr;

  /* L'attribut point nous sert dans la partie graphisme (voir Conception). */

  /// Constructeurs

  public:

  explicit ContrainteSpherique(const Vecteur& centre, const double& rayon)
    : centre(centre), rayon(rayon) {}

  /* Pas de constructeur par défaut (voir Conception). */

  ~ContrainteSpherique() override = default;

  /// Méthodes

  Vecteur applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) override;

  Vecteur vitesse(PointMateriel*& objet, const double& t) override;

  Vecteur position(PointMateriel*& objet, const double& t) override;

  void afficher(std::ostream& sortie) const override;

  [[nodiscard]] double getRayon() const;

  [[nodiscard]] Vecteur getCentre() const override;

  void setPoint(const PointMateriel& point);

  [[nodiscard]] Vecteur getPoint() const;

  void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, const ContrainteSpherique& contrainteSpherique);

#endif //CONTRAINTESPHERIQUE_H