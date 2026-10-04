#include <iostream>
#include <vector>
#include "PointMateriel.h"
#include "Vecteur.h"

#include "GravitationConstante.h"
#include "constantes.h"

int main() {

  /* Ici, il s'agit simplement d'un test afin de voir si le code écrit jusque-là est correct ou non. */

  /// Constantes pour l'initialisation

  const std::vector<double> pos1({1, 2, 3});
  const std::vector<double> pos2({4, 5, 6});
  const std::vector<double> vit1({1, 0, 0});
  const std::vector<double> vit2({0, 1, 0});
  const Vecteur position1(pos1);
  const Vecteur position2(pos2);
  const Vecteur vitesse1(vit1);
  const Vecteur vitesse2(vit2);
  constexpr double masse1(0.1);
  constexpr double masse2(2);

  GravitationConstante gravitation(constantes::gravitation);

  /// Points Materiels

  const PointMateriel point1(position1, vitesse1, masse1, gravitation);
  const PointMateriel point2(position1, vitesse1, masse2, gravitation);

  /// Affichage et marche d'exécution

  std::cout << "Nous avons : \n\nUn champ de force : \n";
  gravitation.affiche(std::cout);
  std::cout << "\n\nUn point matériel : \n";
  point1.affiche();
  point1.affiche_force();
  std::cout << "\net un autre point matériel : \n";
  point2.affiche();
  point1.affiche_force();
  return 0;
}