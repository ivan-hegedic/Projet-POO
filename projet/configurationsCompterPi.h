#ifndef CONFIGURATIONSCOMPTERPI_H
#define CONFIGURATIONSCOMPTERPI_H

#include <iostream>
#include <array>
#include "Vecteur.h"

inline unsigned int demander_chiffres() {
  unsigned int chiffres;
  std::cout << "Entrez le nombre de chiffres de pi désiré (1 - 4) : ";
  std::cin >> chiffres;
  std::cout << '\n';
  return chiffres;
}

/// Nombre de chiffres : 1

constexpr double tolerance1(5.0e-3);
constexpr double dt1(1.0e-3);
constexpr double t_fin1(5.0);
constexpr double masse_caillou1(1.0);
constexpr double masse_rocher1(1.0);
const Vecteur position_caillou1({1.0, 0.0, 0.0});
const Vecteur position_rocher1({2.0, 0.0, 0.0});
const Vecteur vitesse_rocher1({-1.0, 0.0, 0.0});

/// Nombre de chiffres : 2

constexpr double tolerance2(5.0e-3);
constexpr double dt2(1.0e-3);
constexpr double t_fin2(40.0);
constexpr double masse_caillou2(1.0);
constexpr double masse_rocher2(1.0e2);
const Vecteur position_caillou2({1.0, 0.0, 0.0});
const Vecteur position_rocher2({1.05, 0.0, 0.0});
const Vecteur vitesse_rocher2({-0.25, 0.0, 0.0});

/// Nombre de chiffres : 3

constexpr double tolerance3(5.0e-2);
constexpr double dt3(5.0e-3);
constexpr double t_fin3(140.0);
constexpr double masse_caillou3(1.0);
constexpr double masse_rocher3(1.0e4);
const Vecteur position_caillou3({1.0, 0.0, 0.0});
const Vecteur position_rocher3({1.06, 0.0, 0.0});
const Vecteur vitesse_rocher3({-5.0e-2, 0.0, 0.0});

/// Nombre de chiffres : 4

constexpr double tolerance4(6.0e-2);
constexpr double dt4(5.0e-3);
constexpr double t_fin4(310.0);
constexpr double masse_caillou4(1.0);
constexpr double masse_rocher4(1.0e6);
const Vecteur position_caillou4({1.0, 0.0, 0.0});
const Vecteur position_rocher4({1.5, 0.0, 0.0});
const Vecteur vitesse_rocher4({-1.0e-2, 0.0, 0.0});

/// Renvoi des valeurs

constexpr std::array<double, 5> doubles(const unsigned int& n) {
  if (n == 1)
    return {tolerance1, dt1, t_fin1, masse_caillou1, masse_rocher1};
  if (n == 2)
    return {tolerance2, dt2, t_fin2, masse_caillou2, masse_rocher2};
  if (n == 3)
    return {tolerance3, dt3, t_fin3, masse_caillou3, masse_rocher3};
  if (n == 4)
    return {tolerance4, dt4, t_fin4, masse_caillou4, masse_rocher4};
  return {};
}

inline const std::array<Vecteur, 3> vecteurs(const unsigned int& n) {
  if (n == 1)
    return {position_caillou1, position_rocher1, vitesse_rocher1};
  if (n == 2)
    return {position_caillou2, position_rocher2, vitesse_rocher2};
  if (n == 3)
    return {position_caillou3, position_rocher3, vitesse_rocher3};
  if (n == 4)
    return {position_caillou4, position_rocher4, vitesse_rocher4};
  return {};
}

#endif //CONFIGURATIONSCOMPTERPI_H