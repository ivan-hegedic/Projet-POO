#include "constantes.h"
#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "PlanImmobile.h"
#include "Integrateurs.h"
#include <iostream>

int main() {

  /* Il s'agit ici de la reprise du testPomme, cette fois-ci avec l'implémentation de la classe Systeme. */

  /// Constantes

  constexpr double t_fin(0.4);
  constexpr double massePomme(0.1);
  constexpr double masseTerre(5.972e24);
  constexpr double rayonTerre(6371000);
  constexpr double altitude(0.5);
  const Vecteur pos_init({rayonTerre + altitude});
  const Vecteur pos_sol({altitude});
  const Vecteur normale_sol({-1.0});

  /// Points materiels

  PointMateriel pomme(constantes::vecnul, massePomme);
  PointMateriel terre(pos_init, masseTerre);

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
  sys.trackObjet(0);

  /// Édition des liens

  sys.ajouter_champforces_local(0, 0);
  sys.ajouter_contrainte_locale(0, 0);

  /// Affichage

  std::cout << "Avant l'évolution:\n\n";
  sys.afficher(std::cout);

  /// Simulation

  sys.evolue(0.0, t_fin, constantes::moins3);

  /// Affichage

  std::cout << "\n\nAprès l'évolution:\n\n";
  sys.afficher(std::cout);

  return 0;
}
