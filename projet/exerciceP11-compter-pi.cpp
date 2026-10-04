#include "constantes.h"
#include "configurationsCompterPi.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "Contrainte.h"
#include "PlanImmobile.h"
#include "Collisions.h"
#include "Integrateurs.h"
#include "Systeme.h"

int main() {

  /* Cette simulation physique permet de simuler le phénomène à première vue inattendu
   * du comptage des chiffres de pi au moyen de deux PointMateriels et un mur (PlanImmobile).
   * À l'exécution du programme, vous serez demandés d'entrer le nombre de chiffres souhaités
   * dont les possibles (que l'on avait implémentés) sont de 1 à 4. Toutes les valeurs
   * d'initialisation sont sauvegardées dans un fichier header séparé (en particulier
   * configurationsCompterPi.h). */

  /// Choisir le nombre de chiffres de pi

  const unsigned int n(demander_chiffres());
  const std::array valeurs(doubles(n));
  const std::array vectors(vecteurs(n));

  /// Constantes

  constexpr double t_init(0.0);
  const Vecteur position_mur(constantes::vecnul);
  const Vecteur normale_mur({1.0});

  /// Points matériels

  PointMateriel caillou(vectors[0], {0.0}, valeurs[3]);
  PointMateriel rocher(vectors[1], vectors[2], valeurs[4]);

  /// Contraintes

  PlanImmobile mur(position_mur, normale_mur);
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

  Systeme sister;
  sister.ajouter_objet(caillou);
  sister.ajouter_objet(rocher);
  sister.ajouter_contrainte(contrainte_caillou);
  sister.ajouter_contrainte(contrainte_rocher);
  sister.ajouter_integrateur(Oily);

  /// Édition des liens

  sister.ajouter_contrainte_locale(0, 0);
  sister.ajouter_contrainte_locale(1, 1);
  sister.trackObjet(0);

  /// Affichage

  std::cout << "Avant l'évolution : \n\n";
  std::cout << sister << '\n';

  /// Simulation

  sister.evolue(t_init, valeurs[2], valeurs[1]);

  /// Affichage

  std::cout << "Après l'évolution : \n\n";
  std::cout << sister << '\n';

  return 0;
}