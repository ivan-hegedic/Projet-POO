#include "constantes.h"
#include "configurationsCompterPi.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "Contrainte.h"
#include "PlanImmobile.h"
#include "Collisions.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include "glwidget.h"
#include "constantes_graphique.h"
#include <QApplication>

int main(int argc, char* argv[]) {

  /* Cette simulation physique permet de simuler et afficher graphiquement le phénomène inattendu
   * du comptage des chiffres de pi au moyen de deux PointMateriels et un mur (PlanImmobile).
   * À l'exécution du programme, vous serez demandés d'entrer le nombre de chiffres souhaités
   * dont les possibles (que l'on avait implémentés) sont de 1 à 4. Toutes les valeurs
   * d'initialisation sont sauvegardées dans un fichier header séparé (en particulier
   * configurationsCompterPi.h). */

  /// Affichage graphique

  QApplication a(argc, argv);

  /// Choisir le nombre de chiffres de pi

  unsigned int n(demander_chiffres());
  const std::array valeurs(doubles(n));
  const std::array vectors(vecteurs(n));

  /// Constantes pour l'initialisation

  constexpr double t_init(0.0);
  const Vecteur position_mur(constantes::vecnul);
  const Vecteur normale_mur({1.0,0,0});

  /// Points matériels

  PointMateriel caillou(vectors[0], {0.0}, valeurs[3]);
  PointMateriel rocher(vectors[1], vectors[2], valeurs[4]);
  caillou.modifParam({{0,0,0},{1,1,1},{0,0,0,0},{0.3},{false,true},true, Collisions, 0});
  rocher.modifParam({{0.79  ,0.227,0},{1,1,1},{0,0,0,0},{0.5},{false,true},true,Collisions,1});

  /// Contraintes

  PlanImmobile mur(position_mur, normale_mur);
  mur.modifParam({{-1.79525,1.3,0},{1,1,1},{0,0,0,0},{1.5},{false,true},true,Collisions,2});
  Elastique elastique_caillou(caillou);
  elastique_caillou.setTolerance(valeurs[0]);
  Elastique elastique_rocher(rocher);
  elastique_rocher.setTolerance(valeurs[0]);

  /// Contraintes composées

  ContrainteCombinee contrainte_caillou;
  contrainte_caillou.ajouter(mur);
  contrainte_caillou.ajouter(elastique_rocher);

  ContrainteCombinee contrainte_rocher;
  contrainte_rocher.ajouter(mur);
  contrainte_rocher.ajouter(elastique_caillou);

  /// Intégrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme brate;
  brate.ajouter_objet(caillou);
  brate.ajouter_objet(rocher);
  brate.ajouter_contrainte(contrainte_caillou);
  brate.ajouter_contrainte(contrainte_rocher);
  brate.ajouter_integrateur(Oily);

  /// Édition des liens

  brate.ajouter_contrainte_locale(0, 0);
  brate.ajouter_contrainte_locale(1, 1);
  brate.trackObjet(0);
  brate.setExercice(Collisions);
  brate.setDT(doubles(n)[1]);

  /// Affichage graphique

  GLWidget w(brate);
  w.show();
  return QApplication::exec();
}