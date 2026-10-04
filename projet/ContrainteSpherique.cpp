#include "ContrainteSpherique.h"
#include "SupportADessin.h"
#include "PointMateriel.h"

Vecteur ContrainteSpherique::applique_force(PointMateriel*& objet, const Vecteur& force, const double& t) {
  if (objet != nullptr)
    return objet->force();
  return constantes::vecnul;
}

Vecteur ContrainteSpherique::position(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return centre + rayon * (objet->position()-centre).unitaire();
  return constantes::vecnul;
}

Vecteur ContrainteSpherique::vitesse(PointMateriel*& objet, const double& t) {
  if (objet != nullptr)
    return objet->vitesse() - (objet->vitesse()*(objet->position()-centre).unitaire())*(objet->position()-centre).unitaire();
  return constantes::vecnul;
}

void ContrainteSpherique::afficher(std::ostream& sortie) const {
  sortie << "Contrainte sphérique centré à " << centre << "de rayon " << rayon;
}

double ContrainteSpherique::getRayon() const {
  return rayon;
}

Vecteur ContrainteSpherique::getCentre() const {
  return centre;
}

void ContrainteSpherique::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

void ContrainteSpherique::setPoint(const PointMateriel& point) {
  this->point = &point;
}

Vecteur ContrainteSpherique::getPoint() const {
  return point->position();
}

/* Cette méthode nous sert à dessiner le fil qui est lié au PointMateriel comme c'est le cas dans Pendule. */

std::ostream& operator<<(std::ostream& sortie, const ContrainteSpherique& spherique) {
  spherique.afficher(sortie);
  return sortie;
}