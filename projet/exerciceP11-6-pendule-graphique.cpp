#include "constantes.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "GravitationConstante.h"
#include "Contrainte.h"
#include "ContrainteSpherique.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include "glwidget.h"
#include "constantes_graphique.h"
#include <iostream>
#include <cmath>
#include <QApplication>

int main(int argc, char* argv[]) {

  /* Le programme ci-dessous permet de simuler et afficher graphiquement le mouvement
   * d'une pendule dans un champ gravitationnel uniforme et constant. */

  /// Constantes pour l'initialisation

  QApplication a(argc, argv);

  constexpr double longueur_pendule(0.05);
  constexpr double masse_pendule(1.0);
  constexpr double theta(M_PI-0.01);
  constexpr double phi(0.0);
  const Vecteur position_centre({0.0, 0.0, 0.0});
  const Vecteur vitesse_pendule({0.0, 0.0, 0.0});
  const Vecteur gravitation(constantes::gravitation);

  /// Contraintes

  ContrainteSpherique contrainte_pendule(position_centre, longueur_pendule);

  /// Pendule

  PointMateriel pendule(theta, phi, vitesse_pendule, masse_pendule, contrainte_pendule);
  modif param_pendule={{0,-10,-6},{1e4,1,1e2},{45,0,1,0},{1},{true, false}, true, Rien, 0};
  for (auto& c : param_pendule.couleurs) c = randomColor();
  pendule.modifParam(param_pendule);
  contrainte_pendule.modifParam(param_pendule);

  /// Champs de forces

  GravitationConstante champ_gravitation(gravitation);
  champ_gravitation.modifParam({{4,0,-6},{0,0,0},{0,0,0,0},{0.6},{false, true}, true, Gravitation, 0, {0,0,0,0,0,0}});

  /// Intégrateur

  RungeKuttaOr4 Rofl;

  /// Initialisation du système

  Systeme yoyo;
  yoyo.setExercice(Pendule);
  yoyo.ajouter_objet(pendule);
  yoyo.ajouter_champforces(champ_gravitation);
  yoyo.ajouter_contrainte(contrainte_pendule);
  yoyo.ajouter_integrateur(Rofl);

  /// Édition des lies

  yoyo.ajouter_champforces_local(0, 0);
  yoyo.ajouter_contrainte_locale(0, 0);
  yoyo.setDT(0.001);

  /// Affichage graphique

  GLWidget w(yoyo);
  w.show();
  return QApplication::exec();
}