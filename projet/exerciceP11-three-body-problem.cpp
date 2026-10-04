#include "configurationsThreeBodyProblem.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "Systeme.h"

int main() {

  /* Ce programme permet de faire simuler le fameux problème à trois corps interagissant gravitationnellement.
   * À l'exécution du programme, vous serez demandé d'entrer un nombre de la configuration souhaitée dont
   * il y a 4. La première est un exemple réel du système du Soleil, de la Terre et d'une satellite quelconque,
   * tandis que l'on avait trouvé les trois autres en ligne dans une bibliothèque de configurations stables du
   * problème en question. Nous vous invitons de lire le document Rapport, attaché avec les autres documents,
   * où l'on explique en davantage de détails le fonctionnement du programme et les configurations mentionnées. */

  /// Choisir la configuration du système

  const unsigned int n(demander_config());
  const std::array config_doubles(doubles(n));
  const std::array config_vecteurs(vecteurs(n));

  /// Valeurs pour l'initialisation

  constexpr double t_init(0.0);
  const double t_fin(2.0 * config_doubles[1] + t_init);

  /// Points materiels

  PointMateriel etoile(config_vecteurs[0], config_vecteurs[3], config_doubles[3]);
  PointMateriel planete(config_vecteurs[1], config_vecteurs[4], config_doubles[4]);
  PointMateriel satellite(config_vecteurs[2], config_vecteurs[5], config_doubles[5]);

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

  /// Affichage

  std::cout << "Avant l'évolution : \n\n";
  std::cout << trois;
  std::cout << "Distances du centre de masse :\n";
  std::cout << "Étoile : " << (etoile.position()-trois.getReference()).norme1() << '\n';
  std::cout << "Planète : " << (planete.position()-trois.getReference()).norme1() << '\n';
  std::cout << "Satellite : " << (satellite.position()-trois.getReference()).norme1() << "\n\n";
  trois.afficheIntegrales(std::cout);

  /// Simulation

  trois.evolue(t_init, t_fin, config_doubles[2]);
  trois.setReference(trois.evalueCM());

  /// Affichage

  std::cout << "\n\nAprès l'évolution : \n\n";
  std::cout << trois;
  std::cout << "Distances du centre de masse :\n";
  std::cout << "Étoile : " << (etoile.position()-trois.getReference()).norme1() << '\n';
  std::cout << "Planète : " << (planete.position()-trois.getReference()).norme1() << '\n';
  std::cout << "Satellite : " << (satellite.position()-trois.getReference()).norme1() << "\n\n";
  trois.afficheIntegrales(std::cout);

  return 0;
}