#include <QApplication>
#include "glwidget.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include "constantes_graphique.h"

int main(int argc, char* argv[]) {

  /* Ce programme permet de faire simuler et afficher graphiquement le problème à deux corps
   * de Newton. En particulier, il s'agit d'un satellite orbitant la Terre. */

  QApplication a(argc, argv);

  /// Constantes pour l'initialisation

  constexpr double t_init(0);
  constexpr double t_fin(43200);
  constexpr double masse_satellite(1.0);
  constexpr double masse_terre(6.0e24);
  const Vecteur position_satellite({7.0e6, 0.0, 0.0});
  const Vecteur position_terre({0.0, 0.0, 0.0});
  const Vecteur vitesse_satellite({0.0, 1e4, 0.0});
  const Vecteur vitesse_terre({0.0, 0.0, 0.0});

  /// Points matériels

  PointMateriel satellite(position_satellite, vitesse_satellite, masse_satellite);
  PointMateriel terre(position_terre, vitesse_terre, masse_terre);

  /// Champs de force

  ChampNewtonien champ_terre(terre);

  /// Intégrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme orbite;
  orbite.ajouter_objet(satellite);
  orbite.ajouter_objet(terre);
  orbite.ajouter_champforces(champ_terre);
  orbite.ajouter_integrateur(Oily);

  /// Édition des liens
  orbite.setExercice(Orbite);
  orbite.ajouter_champforces_local(0, 0);
  modif param={{16,5,-21},{0.000001,0.000001,10},{0,0,0,0},{1},{true, false},{true}};
  for (double& c : param.couleurs) {
    c = randomColor();
  }
  satellite.modifParam(param);
  modif param2={{16,0,-21},{0,0,0},{0,0,0,0},{3.5},{true,false},{true}};
  for (double& c : param2.couleurs) {
    c = randomColor();
  }
  terre.modifParam(param2);
  orbite.setDT(15);

  //Affichage graphique

  GLWidget w(orbite);
  w.show();
  return QApplication::exec();
}