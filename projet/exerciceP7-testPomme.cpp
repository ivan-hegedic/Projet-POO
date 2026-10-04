#include "constantes.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "PlanImmobile.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include <iostream>

int main() {

  /* Ce programme est une version primitive de la simulation d'une chute d'une pomme sans et avec utilisation
   * de la classe Systeme. Selon notre conceptualisation, ce ne sont pas les Integrateurs qui font évoluer les
   * PointMateriels reçu en paramètres, mais les Systemes eux-mêmes, d'où le besoin d'introduire la méthode
   * evolue dans la classe Integrateur précisément pour faire fonctionner le code ci-dessous. */

  /// Constantes

  double t_init(0.0);
  constexpr double t_fin(1.4);
  constexpr double dt(1.0e-3);
  constexpr double massePomme(0.1);
  constexpr double masseTerre(5.972e24);
  constexpr double rayonTerre(6371000.0);
  constexpr double altitude(10.0);
  const Vecteur pos_pomme({altitude});
  const Vecteur pos_terre({-rayonTerre});
  const Vecteur pos_sol({0.0});
  const Vecteur normale_sol({1.0});

  /// Points materiels

  PointMateriel pomme(pos_pomme, massePomme);
  PointMateriel* pointeurPomme(&pomme);
  PointMateriel terre(pos_terre, masseTerre);

  /// Champs de forces

  ChampNewtonien champTerre(terre);
  ChampForces* pointeurChampTerre(&champTerre);

  /* Le champ de forces que crée la pomme reste constant tandis que la pomme elle-même
  * bouge. À la rigueur, on devrait aussi mettre à jour ce champ-là à chaque nouvel
  * instant que la pomme se trouve sur une nouvelle position, toutefois, vu que l'on
  * ignore l'effet de la pomme sur la Terre, on ne le met pas à jour. */

  /// Contraintes

  PlanImmobile sol(pos_sol, normale_sol);
  Contrainte* pointeurSol(&sol);

  /// Édition des liens

  pomme.setChamp(pointeurChampTerre);
  pomme.setContrainte(pointeurSol);

  /// Affichage et marche d'éxecution du programme

  EulerCromer Oily;
  Oily.evolue(pointeurPomme, t_init, t_fin, dt);

  std::cout << "\nChangement d'intégrateur\n\n";

  /// Réinitialisation de la pomme

  t_init = 0.0;
  pomme.setPosition(pos_pomme);
  pomme.setVitesse(constantes::vecnul);

  Newmark Marcus;
  Marcus.evolue(pointeurPomme, t_init, t_fin, dt);

  pomme.setPosition(pos_pomme);
  pomme.setVitesse(constantes::vecnul);

  t_init = 0.0;
  std::cout << std::setprecision(0) << "\nÀ travers la classe Systeme\n\n";

  Systeme sys;
  sys.ajouter_objet(pomme);
  sys.ajouter_objet(terre);
  sys.ajouter_champforces(champTerre);
  sys.ajouter_contrainte(sol);

  /// Édition des liens

  sys.ajouter_champforces_local(0, 0);
  sys.ajouter_contrainte_locale(0, 0);

  /// Un troisième intégrateur

  RungeKuttaOr4 LaplaceRungeLenz;

  /// Affichage et marche d'éxecution du programme

  std::cout << std::defaultfloat;

  sys.compareIntegrateurs({&Oily, &Marcus, &LaplaceRungeLenz}, t_init, t_fin, dt);

  return 0;
}