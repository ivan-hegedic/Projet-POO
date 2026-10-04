#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include <iostream>

int main() {

  /* Ce programme permet de faire simuler le problème à deux corps de Newton. En particulier,
   * il s'agit d'un satellite orbitant la Terre. */

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

  orbite.ajouter_champforces_local(0, 0);

  /// Affichage

  std::cout << "Avant l'évolution : " << orbite << '\n';
  orbite.afficheIntegrales(std::cout);

  /// Simulation

  orbite.evolue(t_init, t_fin, 1);

  /// Affichage

  std::cout << "\n\nAprès l'évolution : " << orbite << '\n';
  orbite.afficheIntegrales(std::cout);
  return 0;
}