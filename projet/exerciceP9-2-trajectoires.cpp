#include "constantes.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include <iostream>

int main() {

  /* Il s'agit ici d'un programme permettant de faire simuler l'orbite de la Terre autour du Soleil,
   * les deux se déplaçant à cause de l'influence de l'autre. */

  /// Constantes pour l'initialisation

  constexpr double t_init(0);
  constexpr double t_fin(3.3e7);
  constexpr double masse_etoile(2e30);
  constexpr double masse_planete(6e24);
  const Vecteur position_etoile(constantes::vecnul);
  const Vecteur position_planete({1.5e11, 0});
  const Vecteur vitesse_etoile(constantes::vecnul);
  const Vecteur vitesse_planete({0, 3e4});

  /// Points matériels

  PointMateriel etoile(position_etoile, vitesse_etoile, masse_etoile);
  PointMateriel planete(position_planete, vitesse_planete, masse_planete);

  /// Champs de forces

  ChampNewtonien champ_etoile(etoile);
  ChampNewtonien champ_planete(planete);

  /// Intégrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme shuga;
  shuga.ajouter_objet(etoile);
  shuga.ajouter_objet(planete);
  shuga.ajouter_champforces(champ_etoile);
  shuga.ajouter_champforces(champ_planete);
  shuga.ajouter_integrateur(Oily);

  /// Édition des liens

  shuga.ajouter_champforces_local(0, 1);
  shuga.ajouter_champforces_local(1, 0);

  /// Affichage

  std::cout << "Avant l'évolution :\n\n";
  shuga.afficher(std::cout);
  std::cout << "\nDistance : " << (etoile.position()-planete.position()).norme1() << "\n\n";
  shuga.afficheIntegrales(std::cout);

  /// Simulation

  shuga.evolue(t_init, t_fin, 60);

  /// Affichage

  std::cout << "\n\nAprès l'évolution :\n\n";
  shuga.afficher(std::cout);
  std::cout << "\nDistance : " << (etoile.position()-planete.position()).norme1() << "\n\n";
  shuga.afficheIntegrales(std::cout);

  return 0;
}