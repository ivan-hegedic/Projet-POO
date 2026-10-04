#include "Systeme.h"
#include "PointMateriel.h"
#include "ObjetPhysique.h"
#include "Vecteur.h"
#include "ChampNewtonien.h"
#include "Contrainte.h"
#include <iostream>

int main() {

  /* Un programme test au moyen duquel on vérifie si le code écrit jusque-là fonctionne. */

  /// Constantes pour l'initialisation

  const Vecteur position1({1, 2, 3});
  const Vecteur position2({4, 5, 6});
  const Vecteur vitesse1({1, 0, 0});
  const Vecteur vitesse2({0, 1, 0});
  constexpr double masse1(0.1);
  constexpr double masse2(2);
  const Vecteur gravitation(constantes::gravitation);

  /// Points materiels et le système

  PointMateriel point1(ObjetPhysique(position1, vitesse1), masse1);
  PointMateriel point2(ObjetPhysique(position1, vitesse1), masse2);
  Systeme sys;

  /// Affichage et marche d'exécution

  sys.ajouter_objet(point1);
  sys.ajouter_objet(point2);
  PointMateriel point3(position1, vitesse1, 0);
  sys.ajouter_objet(point3);

  ContrainteLibre libre;

  sys.ajouter_contrainte(libre);
  sys.ajouter_contrainte_locale(0, 0);

  std::cout << sys << '\n';

  ChampNewtonien champ1(point1);
  PointMateriel point4(point1);
  PointMateriel p5 = point2;
  Systeme sys2;
  sys2.ajouter_objet(point1);
  sys2.ajouter_objet(point2);
  sys2.ajouter_champforces(champ1);
  sys2.ajouter_contrainte(libre);
  sys2.ajouter_champforces_local(0, 0);

  std::cout << sys2 << '\n';

  EulerCromer integrateur;

  Systeme sys3;
  sys3.ajouter_objet(p5);
  sys3.ajouter_integrateur(integrateur);
  std::cout << sys3;

  std::cout << "Tests de copies : \n\n";

  Systeme copie(sys);
  Systeme copie2(sys2);
  Systeme copie3(sys3);
  std::cout << copie << '\n' << copie2 << '\n' << copie3;

  return 0;
}