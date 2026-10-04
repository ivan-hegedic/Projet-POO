#ifndef SYSTEME_H
#define SYSTEME_H
#pragma once

#include "Dessinable.h"
#include "PointMateriel.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include "Integrateurs.h"
#include "constantes_graphique.h"
#include <numeric>
#include <vector>

class SupportADessin;

struct param_gl {
  Exercice exercice;
  double dt;
};

class Systeme final : public Dessinable {

  /// Attributs

  private:

  std::vector<PointMateriel*> objets{};
  std::vector<ChampForces*> champs{};
  std::vector<Contrainte*> contraintes{};
  Integrateur* integrateur = nullptr;

  Vecteur reference = constantes::vecnul;

  double t{};

  int tracker = -1;
  unsigned int compteur{};

  bool spherique = false;
  unsigned int whereSpherique = -1;

  param_gl exercice = {Rien, 0.1};

  /// Méthodes

  [[nodiscard]] Vecteur getPositionSpherique(PointMateriel* const& point) const;

  /// Constructeurs

  public:

  explicit Systeme(std::vector<PointMateriel>& objets, std::vector<ChampForces>& champs, std::vector<Contrainte>& contraintes) {
    this->objets.reserve(objets.size());
    for (auto& objet : objets)
      this->objets.emplace_back(&objet);
    this->champs.reserve(champs.size());
    for (auto& champ : champs)
      this->champs.emplace_back(&champ);
    this->contraintes.reserve(contraintes.size());
    for (auto& contrainte : contraintes)
      this->contraintes.emplace_back(&contrainte);
  }

  explicit Systeme(std::vector<PointMateriel>& objets, std::vector<ChampForces>& champs, std::vector<Contrainte>& contraintes, Integrateur& integrateur_) {
    this->objets.reserve(objets.size());
    for (auto& objet : objets)
      this->objets.emplace_back(&objet);
    this->champs.reserve(champs.size());
    for (auto& champ : champs)
      this->champs.emplace_back(&champ);
    this->contraintes.reserve(contraintes.size());
    for (auto& contrainte : contraintes)
      this->contraintes.emplace_back(&contrainte);
    integrateur = &integrateur_;
  }

  explicit Systeme(std::vector<PointMateriel>& objets) {
    this->objets.reserve(objets.size());
    for (auto& objet : objets)
        this->objets.emplace_back(&objet);
  }

  explicit Systeme(const std::vector<PointMateriel*>& objets) {
    this->objets.reserve(objets.size());
    for (const auto& objet : objets)
      if (objet != nullptr)
        this->objets.emplace_back(&(*objet));
  }

  explicit Systeme(const double& t) : t(t) {}

  Systeme(const std::initializer_list<PointMateriel*>& objets) {
    this->objets.reserve(objets.size());
    for (const auto& objet : objets)
      if (objet != nullptr)
        this->objets.emplace_back(&(*objet));
  }

  Systeme(std::initializer_list<PointMateriel*>& objets, std::initializer_list<ChampForces*>& champs, std::initializer_list<Contrainte*>& contraintes, Integrateur& integrateur_) {
    this->objets.reserve(objets.size());
    for (auto& objet : objets)
      if (objet != nullptr)
        this->objets.emplace_back(&(*objet));
    this->champs.reserve(champs.size());
    for (auto& champ : champs)
      if (champ != nullptr)
        this->champs.emplace_back(&(*champ));
    this->contraintes.reserve(contraintes.size());
    for (auto& contrainte : contraintes)
      if (contrainte != nullptr)
        this->contraintes.emplace_back(&(*contrainte));
    integrateur = &integrateur_;
  }

  Systeme() = default;

  Systeme(Systeme const& cop) {
    objets = cop.objets;
    champs = cop.champs;
    contraintes = cop.contraintes;
    t = cop.t;
    integrateur = cop.integrateur;
    exercice = cop.exercice;
    reference = cop.reference;
    tracker = cop.tracker;
    compteur = cop.compteur;
    spherique = cop.spherique;
    whereSpherique = cop.whereSpherique;
  }

  /* On ne fait pas de copie profonde, car toute instance ne sera effacée
   * qu'à la fin du programme, il n'y aura donc pas de soucis de mémoire. */

  ~Systeme() override = default;

  void ajouter_objet(PointMateriel& point);

  void ajouter_contrainte(Contrainte& contrainte);

  void ajouter_champforces(ChampForces& champ);

  void ajouter_contrainte_locale(const size_t& i, const size_t& j);

  void ajouter_champforces_local(const size_t& i, const size_t& j);

  void afficher(std::ostream& sortie) const;

  void dessine_sur(SupportADessin& support) override;

  void evolue(const double& tinit, const double& tfin, const double& dt);

  void ajouter_integrateur(Integrateur& integrator);

  void trackObjet(const int& i);

  [[nodiscard]] double getTemps() const;

  [[nodiscard]] std::vector<PointMateriel*> getObjets() const;

  [[nodiscard]] std::vector<Contrainte*> getContraintes() const;

  [[nodiscard]] std::vector<ChampForces*> getChamps() const;

  [[nodiscard]] Integrateur* getIntegrateur() const;

  [[nodiscard]] double evalueEnergie(const size_t& n);

  [[nodiscard]] double evalueEnergieNet();

  void setReference(const Vecteur& reference);

  [[nodiscard]] Vecteur evalueMomentCinetique(const size_t& n, const Vecteur& ref) const;

  [[nodiscard]] Vecteur evalueMomentCinetiqueNet(const Vecteur& ref) const;

  [[nodiscard]] Vecteur evalueMomentCinetique(const size_t& n) const;

  [[nodiscard]] Vecteur evalueMomentCinetiqueNet() const;

  void afficheIntegrales(std::ostream& sortie);

  [[nodiscard]] Vecteur evalueCM() const;

  [[nodiscard]] Vecteur getReference() const;

  void setExercice(const Exercice& exercice);

  [[nodiscard]] bool isSpherique() const;

  [[nodiscard]] Exercice getExercice() const;

  [[nodiscard]] double getDT() const;

  void setDT(const double& dt);

  void setTemps(const double& t);

  void evolueComparaison(const double& t_init, const double& t_fin, const double& dt);

  void compareIntegrateurs(const std::initializer_list<Integrateur*>& integrateurs, const double& t_init, const double& t_fin, const double& dt);
};

std::ostream& operator<<(std::ostream& sortie, const Systeme& sys);

#endif //SYSTEME_H