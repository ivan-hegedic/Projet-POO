#ifndef CONSTANTES_H
#define CONSTANTES_H

#pragma once

#include <vector>

namespace constantes {
  inline std::vector gravitation({0.0, 0.0, -9.81});
  inline constexpr double tolerance(1.0e-8);
  inline constexpr double precision(1.0e-6);
  inline constexpr double epsilon(1.0e-3);
  inline constexpr double dt(1.0e-4);
  inline std::vector vecnul({0.0});
  inline constexpr double moins3(1.0e-3);
  inline constexpr double G(6.6743015e-11);
  inline constexpr double k(8.9e9);
}

#endif //CONSTANTES_H