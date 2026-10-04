#include "Dessinable.h"
#include "TextViewer.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "PlanImmobile.h"
#include "Systeme.h"
#include <iostream>

int main() {

  /* Test pour voir si tout le code écrit jusque-là fonctionne. */

  /// Affichage textuel

  TextViewer ecran(std::cout);

  /// Constantes pour l'initialisation

  constexpr double t_fin(9.0);
  constexpr double massePomme(0.1);
  constexpr double masseTerre(5.972e24);
  constexpr double rayonTerre(6371000);
  constexpr double altitude(10);
  const Vecteur pos_init({rayonTerre + altitude});
  const Vecteur pos_sol({rayonTerre});
  const Vecteur normale_sol({1});

  /// Points materiels

  PointMateriel pomme(pos_init, massePomme);
  PointMateriel terre(constantes::vecnul, masseTerre);

  /// Champs de forces

  ChampNewtonien champTerre(terre);

  /* Pour l'instant, on ignore l'effet gravitationnel qu'exerce la pomme sur la terre,
   * donc il n'est pas nécessaire d'initialiser ce champ-là. Une future simulation
   * servira d'observer comment deux objets célestes s'influencent l'un l'autre. */

  /// Contraintes

  PlanImmobile sol(pos_sol, normale_sol);

  /// Intégrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme sys;
  sys.ajouter_objet(pomme);
  sys.ajouter_objet(terre);
  sys.ajouter_champforces(champTerre);
  sys.ajouter_contrainte(sol);
  sys.ajouter_integrateur(Oily);

  /// Édition des liens

  sys.ajouter_champforces_local(0, 0);
  sys.ajouter_contrainte_locale(0, 0);

  /// Affichage

  std::cout << "Avant l'évolution:\n\n";
  sys.dessine_sur(ecran);

  /// Simulation

  sys.evolue(0.0, t_fin, constantes::moins3);

  /// Affichage

  std::cout << "\n\nAprès l'évolution:\n\n";
  sys.dessine_sur(ecran);
  return 0;
}
