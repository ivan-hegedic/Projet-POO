#ifndef SUPPORTADESSIN_H
#define SUPPORTADESSIN_H

#include "ChampForces.h"
#include "ContrainteSpherique.h"

class GravitationConstante;
class ChampNewtonien;
class ObjetMobile;
class Systeme;
class PointMateriel;
class Contrainte;
class PlanImmobile;

class SupportADessin {

  /// Constructeurs

  public:

  virtual ~SupportADessin() = default;

  // on ne copie pas les Supports

  SupportADessin(SupportADessin const&)            = delete;
  SupportADessin& operator=(SupportADessin const&) = delete;

  // mais on peut les déplacer

  SupportADessin(SupportADessin&&)            = default;
  SupportADessin& operator=(SupportADessin&&) = default;

  SupportADessin() = default;

  // on suppose ici que les supports ne seront ni copiés ni déplacés

  /// Méthodes

  virtual void dessine(PointMateriel const& a_dessiner) = 0;

  virtual void dessine(Systeme const& a_dessiner) = 0;

  virtual void dessine(ObjetMobile const& a_dessiner) = 0;

  virtual void dessine(Contrainte const& a_dessiner) = 0;

  virtual void dessine(PlanImmobile const& a_dessiner) = 0;

  virtual void dessine(ContrainteSpherique const& a_dessiner) = 0;

  virtual void dessine(ContrainteCombinee const& a_dessiner ) = 0;

  virtual void dessine(ChampForces const& a_dessiner) = 0;

  virtual void dessine(ChampNewtonien const& a_dessiner) = 0;

  virtual void dessine(GravitationConstante const& a_dessiner) = 0;
};

#endif //SUPPORTADESSIN_H