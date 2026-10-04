#include "Vecteur.h"
#include "GravitationConstante.h"
#include "Integrateurs.h"
#include <iostream>

int main() {

  /* Un programme test pour voir si le code écrit jusque-là fonctionne. */

  /// Constantes pour l'initialisation

  const std::vector<double> posinit({0, 0, 10});
  const std::vector<double> vitinit({1, 0, 0});
  double tinit(0);
  double constexpr tfin(10);

  /// Objet mobile

  ObjetMobile objet_mobile(posinit, vitinit, constantes::gravitation);

  /// Affichage et marche d'exécution

  const EulerCromer Oily;

  std::cout << "Avant l'évolution (t = " << tinit << ") :\n" << objet_mobile << '\n';
  Oily.evolue(objet_mobile, tinit, tfin, constantes::dt);
  std::cout << "Après l'évolution (t = " << tinit << ") :\n" << objet_mobile;
  return 0;
}