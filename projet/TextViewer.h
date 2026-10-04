#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "Dessinable.h"
#include "SupportADessin.h"
#include <iosfwd>

class PointMateriel;

class TextViewer : public SupportADessin {

  /// Attributs

  private:

  std::ostream& flot;

  /// Constructeurs

  public:

  explicit TextViewer(std::ostream& sortie)
    : flot(sortie) {}

  /// Méthodes

  void dessine(PointMateriel const& a_dessiner) override;

  void dessine(ObjetMobile const& a_dessiner) override;

  void dessine(Systeme const& a_dessiner) override;

  void dessine(Contrainte const& a_dessiner) override;

  void dessine(PlanImmobile const& a_dessiner) override;

  void dessine (ContrainteSpherique const& a_dessiner) override;

  void dessine (ContrainteCombinee const& a_dessiner) override;

  void dessine(ChampForces const& a_dessiner) override;

  void dessine(ChampNewtonien const& a_dessiner) override;

  void dessine(GravitationConstante const& a_dessiner) override;
};

#endif //TEXTVIEWER_H