#include "configurationsThreeBodyProblem.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include "constantes_graphique.h"
#include "glwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {

  /* Ce programme permet de faire simuler et afficher graphiquement le fameux problème à trois corps interagissant
   * gravitationnellement. À l'exécution du programme, vous serez demandé d'entrer un nombre de la configuration
   * souhaitée dont il y a 4. La première est un exemple réel du système du Soleil, de la Terre et d'une satellite
   * quelconque, tandis que l'on avait trouvé les trois autres en ligne dans une bibliothèque de configurations
   * stables du problème. Nous vous invitons de lire le document Rapport, attaché avec les autres documents, où
   * l'on explique en davantage de détails le fonctionnement du programme et les configurations mentionnées. */

  /// Affichage graphique

  QApplication a(argc, argv);

  /// Choisir la configuration du système

  const unsigned int n(demander_config());
  const std::array config_doubles(doubles(n));
  const std::array config_vecteurs(vecteurs(n));

  /// Points materiels

  PointMateriel etoile(config_vecteurs[0], config_vecteurs[3], config_doubles[3]);
  PointMateriel planete(config_vecteurs[1], config_vecteurs[4], config_doubles[4]);
  PointMateriel satellite(config_vecteurs[2], config_vecteurs[5], config_doubles[5]);

  modif param_etoile;
  modif param_planete;
  modif param_satellite;

  if (n != 1) {
    param_etoile = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
    param_planete = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
    param_satellite = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
  } else {
    param_etoile = {{0, 0, 0}, {3 * 1e-11, 3 * 1e-11, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
    param_planete = {{0, 0, 0}, {3 * 1e-11, 3 * 1e-11, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
    param_satellite = {{0, 0, 0}, {3 * 1e-11, 3 * 1e-11, 1}, {0, 0, 0, 0}, {0.2}, {true, false}, true, Threebod, 0};
  }

  for (double &c: param_etoile.couleurs) {
    c = randomColor();
  }
  for (double &c: param_planete.couleurs) {
    c = randomColor();
  }
  for (double &c: param_satellite.couleurs) {
    c = randomColor();
  }
  etoile.modifParam(param_etoile);
  planete.modifParam(param_planete);
  satellite.modifParam(param_satellite);


  /// Champs de forces

  ChampNewtonien champ_etoile(etoile);
  champ_etoile.setG(config_doubles[0]);
  ChampNewtonien champ_planete(planete);
  champ_planete.setG(config_doubles[0]);
  ChampNewtonien champ_satellite(satellite);
  champ_satellite.setG(config_doubles[0]);

  /// Champs composés

  ChampCombine champ_sur_etoile;
  champ_sur_etoile.ajouter(champ_planete);
  champ_sur_etoile.ajouter(champ_satellite);
  ChampCombine champ_sur_planete;
  champ_sur_planete.ajouter(champ_etoile);
  champ_sur_planete.ajouter(champ_satellite);
  ChampCombine champ_sur_satellite;
  champ_sur_satellite.ajouter(champ_etoile);
  champ_sur_satellite.ajouter(champ_planete);

  /// Intégrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme trois;
  trois.ajouter_objet(etoile);
  trois.ajouter_objet(planete);
  trois.ajouter_objet(satellite);
  trois.ajouter_champforces(champ_sur_etoile);
  trois.ajouter_champforces(champ_sur_planete);
  trois.ajouter_champforces(champ_sur_satellite);
  trois.ajouter_integrateur(Oily);
  trois.setReference(trois.evalueCM());

  /// Édition des liens

  trois.ajouter_champforces_local(0, 0);
  trois.ajouter_champforces_local(1, 1);
  trois.ajouter_champforces_local(2, 2);

  trois.setReference(trois.evalueCM());

  if (n == 2) trois.setExercice(ThreebodPapillon);
  else trois.setExercice(Threebod);
  if (n == 1) trois.setDT(300 * 3);
  else trois.setDT(0.005);

  //Affichage graphique

  GLWidget w(trois);
  w.show();
  return QApplication::exec();
}
