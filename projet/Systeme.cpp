#include "Systeme.h"
#include "SupportADessin.h"
#include "ContrainteSpherique.h"
#include <cmath>
#include <typeindex>
#include <iostream>

void Systeme::ajouter_objet(PointMateriel& point) {
    objets.emplace_back(&point);
}

void Systeme::ajouter_contrainte(Contrainte& contrainte) {
  if (std::type_index(typeid(contrainte)) == std::type_index(typeid(ContrainteSpherique))) {
    spherique = true;
    whereSpherique = contraintes.size();
    reference = contrainte.getCentre();
  }
  contraintes.emplace_back(&contrainte);
}

void Systeme::ajouter_champforces(ChampForces& champ) {
    champs.emplace_back(&champ);
}

void Systeme::ajouter_contrainte_locale(const size_t& i, const size_t& j) {
  if (i < contraintes.size() && j < objets.size())
    objets[j]->setContrainte(contraintes[i]);
  else
    std::cout << "Cette opération ne peut pas être effectuée.\n";
}

void Systeme::ajouter_champforces_local(const size_t &i, const size_t &j) {
  if (i < champs.size() && j < objets.size())
    objets[j]->setChamp(champs[i]);
  else
    std::cout << "Cette opération ne peut pas être effectuée.\n";
}

void Systeme::afficher(std::ostream& sortie) const {
  size_t i = 1;
  sortie << "Systeme à t = " << t << "\n\n";
  if (!spherique) {
    for (const auto& objet : objets) {
      if (objet != nullptr) {
        sortie << "Objet No " << i;
        objet->getCharge() == 0 ? sortie << " de type PointMateriel\n" : sortie << " de type ParticuleChargee\n";
        sortie << *objet << '\n';
      }
      i++;
    }
  } else {
    for (const auto& objet : objets) {
      if (objet != nullptr) {
        sortie << "Objet No " << i;
        objet->getCharge() == 0 ? sortie << " de type PointMateriel\n" : sortie << " de type ParticuleChargee\n";
        sortie << "Masse # " << objet->getMasse();
        sortie << "\nPosition # " << getPositionSpherique(objet) << " (en coordonnées sphériques)\n\n";
      }
      i++;
    }
  }
  for (const auto& contrainte: contraintes)
    if (contrainte != nullptr)
      sortie << *contrainte << '\n';
  for (const auto& champ: champs)
    if (champ != nullptr)
      sortie << *champ << '\n';
  if (tracker != -1 && compteur != 0)
    sortie << "\nNombre de perturbations subies par l'objet No " << tracker + 1 << " : " << compteur << "\n\n";
}

void Systeme::dessine_sur(SupportADessin& support) {
  support.dessine(*this);
}

void Systeme::evolue(const double& tinit, const double& tfin, const double& dt) {
  t = tinit;
  do {
    for (auto& objet: objets)
      if (objet != nullptr)
        if (objet->getContrainte() != nullptr) {
          objet->relaxer();
          objet->setChampForces(objet->getContrainte()->applique_force(objet, objet->force(), t));
          objet->setPosition(objet->getContrainte()->position(objet, t));
        }
    std::vector<Vecteur> nouvelles_vitesses;
    nouvelles_vitesses.reserve(objets.size());
    for (auto& objet: objets)
      if (objet != nullptr) {
        if (objet->getContrainte() != nullptr)
          nouvelles_vitesses.emplace_back(objet->getContrainte()->vitesse(objet, t));
        else
          nouvelles_vitesses.emplace_back(objet->vitesse());
      }
    for (size_t i = 0; i < objets.size(); i++)
      if (objets[i] != nullptr)
        objets[i]->setVitesse(nouvelles_vitesses[i]);
    std::vector<Vecteur> nouvelles_positions;
    nouvelles_positions.reserve(objets.size());
    for (auto& objet: objets)
      if (objet != nullptr)
        nouvelles_positions.emplace_back(integrateur->integre(objet, t, dt));
    for (size_t i = 0; i < objets.size(); i++)
      if (objets[i] != nullptr)
        objets[i]->setPosition(nouvelles_positions[i]);
    t += dt;
    if (tracker != -1)
      if (objets[tracker] != nullptr)
        if (objets[tracker]->perturbation() == true)
          compteur++;
    for (auto& objet: objets)
      if (objet != nullptr)
        if (objet->getContrainte() != nullptr)
          objet->setPosition(objet->getContrainte()->position(objet, t));
  } while (t < tfin);
}

void Systeme::ajouter_integrateur(Integrateur& integrateur) {
  this->integrateur = &integrateur;
}

void Systeme::trackObjet(const int& i) {
  if (i >= 0 && i < objets.size())
    tracker = i;
}

double Systeme::getTemps() const {
  return t;
}

std::vector<PointMateriel*> Systeme::getObjets() const {
  return objets;
}

std::vector<Contrainte*> Systeme::getContraintes() const {
  return contraintes;
}

std::vector<ChampForces*> Systeme::getChamps() const {
  return champs;
}

Integrateur* Systeme::getIntegrateur() const {
  return integrateur;
}

double Systeme::evalueEnergie(const size_t& n) {
  if (n <= objets.size()) {
    if (objets[n] != nullptr) {
      double energie = 0;
      energie += objets[n]->getMasse() * 0.5 * objets[n]->vitesse() * objets[n]->vitesse();
      if (objets[n]->getChamp() != nullptr)
        energie += objets[n]->getChamp()->energiePotentielle(objets[n], t);
      return energie;
    }
  }
  return 0;
}

double Systeme::evalueEnergieNet() {
  double somme{};
  for (size_t i = 0; i < objets.size(); i++)
    if (objets[i] != nullptr)
      somme += evalueEnergie(i);
  return somme;
}

void Systeme::setReference(const Vecteur& reference) {
  this->reference = reference;
}

void Systeme::setDT(const double& dt) {
  exercice.dt = dt;
}

void Systeme::setTemps(const double& t) {
  this->t = t;
}
void Systeme::evolueComparaison(const double& t_init, const double& t_fin, const double& dt){
  unsigned int compteur(0);
  t = t_init;
  do {
    if (compteur % 100 == 0) {
      unsigned int i(1);
      for (const auto& objet : objets)
        if (objet != nullptr) {
          std::cout << "Objet No " << i << " à t = " << t << " : " << objet->position() << '\n';
          i++;
        }
    }
    for (auto& objet: objets)
      if (objet != nullptr)
        if (objet->getContrainte() != nullptr) {
          objet->relaxer();
          objet->setChampForces(objet->getContrainte()->applique_force(objet, objet->force(), t));
          objet->setPosition(objet->getContrainte()->position(objet, t));
        }
    std::vector<Vecteur> nouvelles_vitesses;
    nouvelles_vitesses.reserve(objets.size());
    for (auto& objet: objets)
      if (objet != nullptr) {
        if (objet->getContrainte() != nullptr)
          nouvelles_vitesses.emplace_back(objet->getContrainte()->vitesse(objet, t));
        else
          nouvelles_vitesses.emplace_back(objet->vitesse());
      }
    for (size_t i = 0; i < objets.size(); i++)
      if (objets[i] != nullptr)
        objets[i]->setVitesse(nouvelles_vitesses[i]);
    std::vector<Vecteur> nouvelles_positions;
    nouvelles_positions.reserve(objets.size());
    for (auto& objet: objets)
      if (objet != nullptr)
        nouvelles_positions.emplace_back(integrateur->integre(objet, t, dt));
    for (size_t i = 0; i < objets.size(); i++)
      if (objets[i] != nullptr)
        objets[i]->setPosition(nouvelles_positions[i]);
    t += dt;
    compteur++;
  } while (t < t_fin);
}

void Systeme::compareIntegrateurs(const std::initializer_list<Integrateur*>& integrateurs, const double& t_init, const double& t_fin, const double& dt){
  std::cout << "Avant l'évolution :\n\n" << *this << '\n';
  std::vector<Vecteur> positions_initiales, vitesses_initiales;
  positions_initiales.reserve(objets.size());
  vitesses_initiales.reserve(objets.size());
  for (const auto& objet : objets)
    if (objet != nullptr) {
      positions_initiales.emplace_back(objet->position());
      vitesses_initiales.emplace_back(objet->vitesse());
    }
  for (const auto& integrateur : integrateurs)
    if (integrateur != nullptr) {
      this->ajouter_integrateur(*integrateur);
      std::cout << std::fixed  << "\nÉvolution avec l'intégrateur " << integrateur->getNom() << " :\n\n";
      evolueComparaison(t_init, t_fin, dt);
      unsigned int i(0);
      for (auto& objet : objets)
        if (objet != nullptr) {
          objet->setPosition(positions_initiales[i]);
          i++;
      }
      i = 0;
      for (auto& objet : objets)
        if (objet != nullptr) {
          objet->setVitesse(vitesses_initiales[i]);
          i++;
        }
    }
}

std::ostream& operator<<(std::ostream& sortie, const Systeme& sys) {
  sys.afficher(sortie);
  return sortie;
}

Vecteur Systeme::evalueMomentCinetique(const size_t& n, const Vecteur& reference) const {
  if (n <= objets.size())
    if (objets[n] != nullptr)
      return objets[n]->getMasse() * ((objets[n]->position() - reference) ^ objets[n]->vitesse());
  return constantes::vecnul;
}
Vecteur Systeme::evalueMomentCinetiqueNet(const Vecteur& reference) const {
  Vecteur somme(constantes::vecnul);
  for (size_t i = 0; i < objets.size(); i++)
    if (objets[i] != nullptr)
      somme += evalueMomentCinetique(i, reference);
  return somme;
}

Vecteur Systeme::evalueMomentCinetique(const size_t& n) const {
  return evalueMomentCinetique(n, reference);
}

Vecteur Systeme::evalueMomentCinetiqueNet() const {
  return evalueMomentCinetiqueNet(reference);
}

void Systeme::afficheIntegrales(std::ostream& sortie) {
  sortie << "Énergie totale du système : " << evalueEnergieNet();
  sortie << "\nMoment cinétique du système : " << evalueMomentCinetiqueNet() << "\n\n";
  for (size_t i = 0; i < objets.size(); i++)
    if (objets[i] != nullptr) {
      sortie << "Énergie totale de l'objet No " << i + 1 << " : " << evalueEnergie(i) << '\n';
      sortie << "Moment cinétique de l'objet No " << i + 1 << " : " << evalueMomentCinetique(i, reference) << '\n';
    }
}

Vecteur Systeme::evalueCM() const {
  Vecteur CM(constantes::vecnul);
  double M(0.0);
  for (auto& objet: objets)
    if (objet != nullptr) {
      CM += objet->getMasse() * objet->position();
      M += objet->getMasse();
    }
  CM = CM / M;
  if (CM != constantes::vecnul)
    return CM;
  return reference;
}

Vecteur Systeme::getReference() const {
  return reference;
}

void Systeme::setExercice(const Exercice& exercice) {
  this->exercice.exercice = exercice;
}

bool Systeme::isSpherique() const {
  return spherique;
}

Exercice Systeme::getExercice() const {
  return exercice.exercice;
}

double Systeme::getDT() const {
  return exercice.dt;
}

Vecteur Systeme::getPositionSpherique(PointMateriel* const& point) const {
  if (spherique)
    if (point != nullptr) {
      const Vecteur retour(point->position() - reference);
      const double r(retour.norme1());
      const double x(retour.get_coord(0));
      const double y(retour.get_coord(1));
      const double z(retour.get_coord(2));
      return {r, acos(z / r), atan2(y, x)};
    }
  return constantes::vecnul;
}