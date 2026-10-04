#include "constantes.h"
#include "Vecteur.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "GravitationConstante.h"
#include "Contrainte.h"
#include "ContrainteSpherique.h"
#include "Integrateurs.h"
#include "Systeme.h"
#include <iostream>
#include <cmath>

int main() {

  /* Le programme ci-dessous permet de simuler le mouvement d'une pendule dans un champ
   * gravitationnel uniforme et constant. La durée de la simulation ici vaut à peu près
   * une demi-période, mais le mouvement reste stable (ne perd pas d'énergie) peu importe
   * la durée de simulation choisie, comme on peut voir dans la simulation graphique. */

  /// Constantes pour l'initialisation

  constexpr double t_init(0.0);
  constexpr double longueur_pendule(1.0);
  constexpr double masse_pendule(1.0);
  constexpr double theta(M_PI-0.01);
  constexpr double phi(0.0);
  const Vecteur position_centre({0.0, 0.0, 0.0});
  const Vecteur vitesse_pendule({0.0, 0.0, 0.0});
  const Vecteur gravitation(constantes::gravitation);
  constexpr double t_fin(M_PI * std::sqrt(longueur_pendule / 9.81));

  /// Contraintes

  ContrainteSpherique contrainte_pendule(position_centre, longueur_pendule);

  /// Pendule

  PointMateriel pendule(theta, phi, vitesse_pendule, masse_pendule, contrainte_pendule);

  /// Champs de forces

  GravitationConstante champ_gravitation(gravitation);

  /// Intégrateur

  RungeKuttaOr4 Rofl;

  /// Initialisation du système

  Systeme pula;
  pula.ajouter_objet(pendule);
  pula.ajouter_champforces(champ_gravitation);
  pula.ajouter_contrainte(contrainte_pendule);
  pula.ajouter_integrateur(Rofl);

  /// Édition des lies

  pula.ajouter_champforces_local(0, 0);
  pula.ajouter_contrainte_locale(0, 0);

  /// Affichage

  std::cout << "Avant l'évolution\n\n" << pula;
  std::cout << "Longueur du fil : " << (pendule.position()-position_centre).norme1() << '\n';

  /// Simulation

  pula.evolue(t_init, t_fin, constantes::dt);

  /// Affichage

  std::cout << "\nAprés l'évolution\n\n" << pula;
  std::cout << "Longueur du fil : " << (pendule.position()-position_centre).norme1() << '\n';

  return 0;
}