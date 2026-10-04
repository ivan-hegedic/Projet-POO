#pragma once

#include <vector>
#include <iomanip>

#ifndef VECTEUR_H
#define VECTEUR_H

class Vecteur {

  /// Attributs

  std::vector<double> vecteur;

  public:

  /// Constructeurs

  explicit Vecteur(const size_t& dim) {
    vecteur = std::vector<double>(dim, 0);
  }

  Vecteur(const std::vector<double>& v)
    : vecteur(v) {};

  Vecteur(Vecteur& autre) = default;

  Vecteur(const Vecteur& autre) = default;

  Vecteur(double x,double y, double z)
    : vecteur(std::vector({x,y,z})) {}

  Vecteur(const std::initializer_list<double> v)
    : vecteur(v) {}

  Vecteur() = default;

  /// Méthodes

  void augmente(const double& valeur);

  void set_coord(const size_t& coordonnee, const double& valeur);

  [[nodiscard]] double get_coord(const size_t& coordonnee) const;

  [[nodiscard]] bool compare(const Vecteur& v) const;

  [[nodiscard]] bool compare_dimension(const Vecteur& v) const;

  static void plongement(Vecteur& v, const size_t& n, const double& valeur) {
    for (int i=0; i < n; i++)
      v.augmente(valeur);
  }

  static size_t getDimMin(const Vecteur& a, const Vecteur& b) {
    if (a.vecteur.size() < b.vecteur.size())
      return a.vecteur.size();
    return b.vecteur.size();
  }

  static size_t getDimMax(const Vecteur& a, const Vecteur& b) {
    if (a.vecteur.size() > b.vecteur.size())
      return a.vecteur.size();
    return b.vecteur.size();
  }

  [[nodiscard]] Vecteur addition(const Vecteur& v) const;

  [[nodiscard]] Vecteur opposee() const;

  [[nodiscard]] Vecteur mult(const double& valeur) const;

  [[nodiscard]] double prod_scal(const Vecteur& v) const;

  [[nodiscard]] Vecteur prod_vect(Vecteur& autre);

  [[nodiscard]] double norme2() const;

  [[nodiscard]] double norme1() const;

  [[nodiscard]] Vecteur unitaire() const;

  [[nodiscard]] Vecteur soustraction(const Vecteur& autre) const;

  [[nodiscard]] Vecteur fais_devier(const Vecteur& reference) const;

  void affiche() const;

  [[nodiscard]] bool empty() const;

  std::ostream& afficher(std::ostream& sortie) const;

  /// Surcharge d'opérateurs interne

  void operator+=(const Vecteur& v);

  void operator-=(const Vecteur& v);

  void operator *=(const double& scalaire);

  void operator^=(Vecteur& autre);
};

/// Surcharge d'operateurs externe

Vecteur operator+(Vecteur v1,const Vecteur& v2);

Vecteur operator-(Vecteur v1,const Vecteur& v2);

Vecteur operator^(const Vecteur& v1, const Vecteur& v2);

Vecteur operator*(Vecteur v1, const double& scalaire);

std::ostream& operator<<(std::ostream& sortie, const Vecteur& vecteur);

bool operator!=(const Vecteur& v1, const Vecteur& v2);

bool operator==(const Vecteur& v1, const Vecteur& v2);

Vecteur operator~(const Vecteur& v);

double operator*(const Vecteur& v1, const Vecteur& v2);

Vecteur operator*(const double& scalaire, Vecteur v1);

Vecteur operator/(const Vecteur& v, const double& scalaire);

#endif //VECTEUR_H