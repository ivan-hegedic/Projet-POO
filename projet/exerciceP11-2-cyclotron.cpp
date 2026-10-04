#include <iostream>
#include "Vecteur.h"
#include "PointMateriel.h"
#include "PointCharge.h"
#include "ChampForces.h"
#include "ChampsEM.h"
#include "ChampRestreint.h"
#include "Integrateurs.h"
#include "Systeme.h"

int main() {

  /* Ce programme fait simuler le fonctionnement d'un point charge dans un cyclotron ordinaire
   * avec une région à un champ électrique constant et uniforme, où le point charge accélère (ou
   * ralentit, ça dépend de sa direction de mouvement), et deux régions (infinies) à un champ
   * magnétique uniforme et constant, où le point charge circule sans perte d'énergie à cause
   * de la force de Lorentz. Les deux champs mentionnés ci-dessus sont des ChampRestreints
   * (voir Conception).*/

  /// Constantes pour l'initialisation

  constexpr double t_init(0.0);
  constexpr double t_fin(1.0);
  constexpr double dt(1.0e-3);
  constexpr double masse(1.0);
  constexpr double charge(1.0);
  const Vecteur position({1.01, 0.0, 0.0});
  const Vecteur vitesse({1.0, 0.0, 0.0});
  const Vecteur intensite_electrique({0.1, 0.0, 0.0});
  const Vecteur intensite_magnetique({0.0, 0.0, 1.0});

  /// Charge

  PointCharge point(position, vitesse, masse, charge);

  /// Champs

  ChampMagnetique magneto(intensite_magnetique);
  ChampElectriqueConstant elektro(intensite_electrique);

  ChampRestreint magneto_restreint(magneto, false, {true, true, false, false, false, false}, {-1.0, 1.0, 0.0, 0.0, 0.0, 0.0});
  ChampRestreint elektro_restreint(elektro, true, {true, true, false, false, false, false}, {-1.0, 1.0, 0.0, 0.0, 0.0, 0.0});

  ChampCombine cyclotron({&magneto_restreint, &elektro_restreint});

  /// Integrateur

  EulerCromer Oily;

  /// Initialisation du système

  Systeme cyclope;
  cyclope.ajouter_objet(point);
  cyclope.ajouter_champforces(cyclotron);
  cyclope.ajouter_integrateur(Oily);

  /// Édition des liens

  cyclope.ajouter_champforces_local(0, 0);

  /// Affichage

  std::cout << "Avant l'évolution : \n\n" << cyclope;
  std::cout << "Vitesse : " << point.vitesse().norme1() << "\n\n";

  /// Simulation

  cyclope.evolue(t_init, t_fin, dt);

  /// Affichage

  std::cout << "Après l'évolution : \n\n" << cyclope;
  std::cout << "Vitesse : " << point.vitesse().norme1() << '\n';

  return 0;
}