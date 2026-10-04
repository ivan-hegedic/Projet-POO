#ifndef CONFIGURATIONSTHREEBODYPROBLEM_H
#define CONFIGURATIONSTHREEBODYPROBLEM_H

#include <array>
#include <cmath>
#include <iostream>
#include "Vecteur.h"
#include "constantes.h"

inline unsigned int demander_config() {
  unsigned int config;
  std::cout << "Entrez la configuration (1 - 4) : ";
  std::cin >> config;
  std::cout << '\n';
  return config;
}

/// Configuration No 1 : Triangle tournant

constexpr double dt1(5.0 * 60.0);
constexpr double G1(constantes::G);
constexpr double masse_etoile1(2.0e30);
constexpr double masse_planete1(6.0e24);
constexpr double masse_satellite1(1.0);
constexpr double periode1(365.25 * 86400.0);
const Vecteur position_etoile1({-7.5e10, 0.0});
const Vecteur position_planete1({7.5e10, 0.0});
const Vecteur position_satellite1({0.0, 1.49 * sin(M_PI / 3) * 1.0e11});
const Vecteur position_CM((masse_etoile1 * position_etoile1 + masse_planete1 * position_planete1 + masse_satellite1 * position_satellite1) / (masse_etoile1 + masse_planete1 + masse_satellite1));
const Vecteur vitesse_angulaire({0.0, 0.0, 2.0 * M_PI / periode1});
const Vecteur vitesse_etoile1(vitesse_angulaire ^ (position_etoile1 - position_CM));
const Vecteur vitesse_planete1(vitesse_angulaire ^ (position_planete1 - position_CM));
const Vecteur vitesse_satellite1(vitesse_angulaire ^ (position_satellite1 - position_CM));

/// Configuration No 2 : Croix

constexpr double dt2(1.0e-4);
constexpr double G2(1.0);
constexpr double masse_etoile2(1.0);
constexpr double masse_planete2(1.0);
constexpr double masse_satellite2(1.0);
constexpr double periode2(12.055859);
const Vecteur position_etoile2({-0.1095519101, 0.0000000000});
const Vecteur position_planete2({1.6613533905, 0.0000000000});
const Vecteur position_satellite2({-1.5518014804, 0.0000000000});
const Vecteur vitesse_etoile2({0.0000000000, 0.9913358338});
const Vecteur vitesse_planete2({0.0000000000, -0.1569959746});
const Vecteur vitesse_satellite2({0.0000000000, -0.8343398592});

/// Configuration No 3 : Figure de huit

constexpr double dt3(1.0e-4);
constexpr double G3(1.0);
constexpr double masse_etoile3(1.0);
constexpr double masse_planete3(1.0);
constexpr double masse_satellite3(1.0);
constexpr double periode3(6.324449);
constexpr double p1_3(0.347111);
constexpr double p2_3(0.532728);
const Vecteur position_etoile3({0.0, 0.0});
const Vecteur position_planete3({-1.0, 0.0});
const Vecteur position_satellite3({1.0, 0.0});
const Vecteur vitesse_etoile3({-2 * p1_3, -2 * p2_3});
const Vecteur vitesse_planete3({p1_3, p2_3});
const Vecteur vitesse_satellite3({p1_3, p2_3});

/// Configuration No 4 : Ovales aux fioritures

constexpr double dt4(1.0e-4);
constexpr double G4(1.0);
constexpr double masse_etoile4(1.0);
constexpr double masse_planete4(1.0);
constexpr double masse_satellite4(1.0);
constexpr double periode4(8.094721);
const Vecteur position_etoile4({0.8871256555,0.0000000000});
const Vecteur position_planete4({-0.6530449215,0.0000000000});
const Vecteur position_satellite4({-0.2340807340,0.0000000000});
const Vecteur vitesse_etoile4({0.0000000000,0.9374933545});
const Vecteur vitesse_planete4({0.0000000000,-1.7866975426});
const Vecteur vitesse_satellite4({0.0000000000,0.8492041880});

/// Renvoi de la configuration demandée

constexpr std::array<double, 6> doubles(const unsigned int& n) {
  if (n == 1)
    return {G1, periode1, dt1, masse_etoile1, masse_planete1, masse_satellite1};
  if (n == 2)
    return {G2, periode2, dt2, masse_etoile2, masse_planete2, masse_satellite2};
  if (n == 3)
    return {G3, periode3, dt3, masse_etoile3, masse_planete3, masse_satellite3};
  if (n == 4)
    return {G4, periode4, dt4, masse_etoile4, masse_planete4, masse_satellite4};
  return {};
}

inline const std::array<Vecteur, 6> vecteurs(const unsigned int& n) {
  if (n == 1)
    return {position_etoile1, position_planete1, position_satellite1, vitesse_etoile1, vitesse_planete1, vitesse_satellite1};
  if (n == 2)
    return {position_etoile2, position_planete2, position_satellite2, vitesse_etoile2, vitesse_planete2, vitesse_satellite2};
  if (n == 3)
    return {position_etoile3, position_planete3, position_satellite3, vitesse_etoile3, vitesse_planete3, vitesse_satellite3};
  if (n == 4)
    return {position_etoile4, position_planete4, position_satellite4, vitesse_etoile4, vitesse_planete4, vitesse_satellite4};
  return {};
}

#endif //CONFIGURATIONSTHREEBODYPROBLEM_H