#include "Vecteur.h"
#include "constantes.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

void Vecteur::augmente(const double& valeur) {
  vecteur.push_back(valeur);
}

void Vecteur::set_coord(const size_t& coordonnee, const double& valeur) {
  if (vecteur.size() <= coordonnee)
    for (size_t i = vecteur.size(); i <= coordonnee; i++)
      vecteur.push_back(0);
  vecteur[coordonnee] = valeur;
}

double Vecteur::get_coord(const size_t& coordonnee) const {
  if (coordonnee >= vecteur.size())
    return 0.0;
  return vecteur[coordonnee];
}

void Vecteur::affiche() const {
  std::cout << std::setprecision(15);
  for(const auto& i : vecteur)
    std::cout << i << ' ';
}

bool Vecteur::empty() const {
  return vecteur.empty();
}

std::ostream& Vecteur::afficher(std::ostream& sortie) const {
  sortie << std::setprecision(15);
  for(const auto& i : vecteur)
    sortie << i << ' ';
  return sortie;
}

bool Vecteur::compare(const Vecteur& v) const {
  if(vecteur.size() != v.vecteur.size())
    return false;
  for(size_t i = 0; i < vecteur.size(); i++)
    if(std::abs(vecteur[i] - v.vecteur[i]) > constantes::precision)
      return false;
  return true;
}

bool Vecteur::compare_dimension(const Vecteur &v) const {
  return vecteur.size() == v.vecteur.size();
}

Vecteur Vecteur::addition(const Vecteur& v) const {
  Vecteur result;
  if (vecteur.size() < v.vecteur.size()) {
    result.vecteur = vecteur;
    plongement(result, getDimMax(v, vecteur) - getDimMin(v, vecteur), 0);
    size_t j = 0;
    for (const auto& i : v.vecteur) {
      result.vecteur[j] += i;
      j++;
    }
  } else {
    result.vecteur = v.vecteur;
    plongement(result, getDimMax(v, vecteur) - getDimMin(v, vecteur), 0);
    size_t j = 0;
    for (const auto& i : vecteur) {
      result.vecteur[j] += i;
      j++;
    }
  }
  return result;
}

Vecteur Vecteur::opposee() const {
  Vecteur result(vecteur);
  for (size_t i = 0; i < vecteur.size(); i++) {
    result.vecteur[i] = -vecteur[i];
  }
  return result;
}

Vecteur Vecteur::mult(const double& valeur) const {
  Vecteur result(vecteur);
  for (size_t i = 0; i < vecteur.size(); i++)
    result.vecteur[i] *= valeur;
  return result;
}

double Vecteur::prod_scal(const Vecteur& v) const {
  double result(0.0);
  for (size_t i = 0; i < getDimMin(v, *this); i++)
    result += vecteur[i] * v.vecteur[i];
  return result;
}

Vecteur Vecteur::prod_vect(Vecteur& autre) {
  if (vecteur.size() > 3 || autre.vecteur.size() > 3)
    throw std::invalid_argument("Les vecteurs doivent être au plus de dimension 3 afin de bien effectuer leur produit vectoriel.");
  if (vecteur.size() < 3 || autre.vecteur.size() < 3) {
    plongement(*this, 3 - vecteur.size(), 0);
    plongement(autre, 3 - autre.vecteur.size(), 0);
  }
  Vecteur result({0, 0, 0});
  result.vecteur[0] = vecteur[1] * autre.vecteur[2] - vecteur[2] * autre.vecteur[1];
  result.vecteur[1] = -vecteur[0] * autre.vecteur[2] + vecteur[2] * autre.vecteur[0];
  result.vecteur[2] = vecteur[0] * autre.vecteur[1] - vecteur[1] * autre.vecteur[0];
  return result;
}

double Vecteur::norme2 () const {
  double norme2(0.0);
  for (const auto& i : vecteur)
    norme2 += i * i;
  return norme2;
}

double Vecteur::norme1 () const {
  return sqrt(norme2());
}

Vecteur Vecteur::unitaire() const {
  Vecteur result(vecteur);
  if (const double norme(norme1()); norme > constantes::precision) {
    for (size_t i = 0; i < vecteur.size(); i++)
      result.vecteur[i] = vecteur[i] / norme;
    return result;
  }
  return constantes::vecnul;
}

Vecteur Vecteur::soustraction(const Vecteur& autre) const {
  return addition(autre.opposee());
}

Vecteur Vecteur::fais_devier(const Vecteur& reference) const {
  return *this + (-2.0) * (vecteur * reference) * reference;
}

Vecteur operator^(Vecteur& v1, Vecteur& v2) {
  Vecteur result = v1.prod_vect(v2);
  return result;
}

Vecteur operator^(const Vecteur& v1, const Vecteur& v2) {
  Vecteur gauche = v1, droite = v2;
  Vecteur result = gauche.prod_vect(droite);
  return result;
}

void Vecteur::operator+=(const Vecteur& v) {
  if (vecteur.size() < v.vecteur.size()) {
    plongement(*this, getDimMax(v, vecteur) - getDimMin(v, vecteur), 0);
    size_t j = 0;
    for (const auto& i : v.vecteur) {
      vecteur[j] += i;
      j++;
    }
  } else {
    size_t j = 0;
    for (const auto& i : v.vecteur) {
      vecteur[j] += i;
      j++;
    }
  }
}

void Vecteur::operator-=(const Vecteur& v) {
  if (vecteur.size() < v.vecteur.size()) {
    plongement(*this, getDimMax(v, vecteur) - getDimMin(v, vecteur), 0);
    size_t j = 0;
    for (const auto& i : v.vecteur) {
      vecteur[j] -= i;
      j++;
    }
  } else {
    size_t j = 0;
    for (const auto& i : v.vecteur) {
      vecteur[j] -= i;
      j++;
    }
  }
}

void Vecteur:: operator*=(const double& scalaire) {
  for (double& val : vecteur)
    val *= scalaire;
}

Vecteur operator*(Vecteur v1, const double& scalaire) {
  v1 *= scalaire;
  return v1;
}

Vecteur operator*(const double& scalaire, Vecteur v1) {
  v1 *= scalaire;
  return v1;
}

Vecteur operator+(Vecteur v1, const Vecteur& v2) {
  v1 += v2;
  return v1;
}

Vecteur operator-(Vecteur v1, const Vecteur& v2) {
  v1 -= v2;
  return v1;
}

std::ostream& operator<<(std::ostream& sortie, const Vecteur& vecteur) {
  vecteur.afficher(sortie);
  return sortie;
}

bool operator!=(const Vecteur& v1, const Vecteur& v2) {
  return !v1.compare(v2);
}

bool operator==(const Vecteur& v1, const Vecteur& v2) {
  return v1.compare(v2);
}

Vecteur operator~(const Vecteur& v) {
  return v.unitaire();
}

double operator*(const Vecteur& v1, const Vecteur& v2) {
  return v1.prod_scal(v2);
}

void Vecteur::operator^=(Vecteur &autre) {
  if (vecteur.size() > 3 || autre.vecteur.size() > 3)
    throw std::invalid_argument("Les vecteurs doivent être au plus de dimension 3 afin de bien effectuer leur produit vectoriel.");
  if (vecteur.size() < 3)
    plongement(*this, 3 - vecteur.size(), 0);
  if (autre.vecteur.size() < 3)
    plongement(autre, 3 - autre.vecteur.size(), 0);
  vecteur[0] = vecteur[1] * autre.vecteur[2] - vecteur[2] * autre.vecteur[1];
  vecteur[1] = -vecteur[0] * autre.vecteur[2] + vecteur[2] * autre.vecteur[0];
  vecteur[2] = vecteur[0] * autre.vecteur[1] - vecteur[1] * autre.vecteur[0];
}

Vecteur operator/(const Vecteur &v, const double& scalaire) {
  return v * (1 / scalaire);
}