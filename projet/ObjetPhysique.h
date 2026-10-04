#ifndef OBJETPHYSIQUE_H
#define OBJETPHYSIQUE_H

#include "ObjetMobile.h"
#include "Contrainte.h"
#include "ChampForces.h"

class ObjetPhysique : public ObjetMobile {

  /// Attributs

  protected:

  Vecteur champForces = constantes::vecnul;
  Contrainte* contrainte = nullptr;
  ChampForces* champ = nullptr;

  public:

  /// Constructeurs

  explicit ObjetPhysique(const Vecteur& position)
    : ObjetMobile(position) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse)
    : ObjetMobile(position, vitesse) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse, const Vecteur& acc)
    : ObjetMobile(position, vitesse, acc) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse, const Vecteur& acc, const Vecteur& force)
    : ObjetMobile(position, vitesse, acc), champForces(force) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse, Contrainte& contrainte)
    : ObjetMobile(position, vitesse), contrainte(&contrainte) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse, ChampForces& champ)
    : ObjetMobile(position, vitesse), champ(&champ) {}

  explicit ObjetPhysique(const Vecteur& position, const Vecteur& vitesse, ChampForces& champ, Contrainte& contrainte)
    : ObjetMobile(position, vitesse), contrainte(&contrainte), champ(&champ) {}

  ObjetPhysique(const ObjetPhysique& autre)
    : ObjetMobile(autre), champForces(autre.champForces), contrainte(autre.contrainte), champ(autre.champ) {}

  ObjetPhysique(ObjetPhysique&& autre) noexcept
    : ObjetMobile(std::move(autre)), champForces(autre.champForces), contrainte(autre.contrainte), champ(autre.champ) {}

  ObjetPhysique() = default;

  ~ObjetPhysique() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur force() const;

  virtual void affiche_force() const;

  std::ostream& affiche_force(std::ostream& sortie) const;

  void dessine_sur(SupportADessin& support) override;

  std::ostream& affiche(std::ostream& sortie) const override;

  void setChampForces(const Vecteur& champForces);

  virtual void setContrainte(Contrainte*& contrainte);

  virtual void setChamp(ChampForces*& champ);

  [[nodiscard]] virtual Contrainte* getContrainte() const;

  [[nodiscard]] virtual ChampForces* getChamp() const;

  void affiche_contrainte(std::ostream& sortie) const;

  void affiche_champ(std::ostream& sortie) const;

};

std::ostream& operator<<(std::ostream& sortie, const ObjetPhysique& objet);

#endif //OBJETPHYSIQUE_H