#include "TextViewer.h"
#include "ChampNewtonien.h"
#include "ContrainteSpherique.h"
#include "PlanImmobile.h"
#include "Systeme.h"
#include "GravitationConstante.h"

void TextViewer::dessine(PointMateriel const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(ObjetMobile const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(Systeme const& a_dessiner) {
  a_dessiner.afficher(flot);
}

void TextViewer::dessine(Contrainte const& a_dessiner) {
  flot<< a_dessiner << '\n';
}

void TextViewer::dessine(PlanImmobile const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(ContrainteSpherique const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(ContrainteCombinee const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(ChampForces const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(ChampNewtonien const& a_dessiner) {
  flot << a_dessiner << '\n';
}

void TextViewer::dessine(GravitationConstante const& a_dessiner) {
  flot << a_dessiner << '\n';
}