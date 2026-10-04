#ifndef CHAMPFORCES_H
#define CHAMPFORCES_H

#include "Dessinable.h"
#include "Vecteur.h"
#include "constantes_graphique.h"

class PointMateriel;

class ChampForces : public Dessinable{

  /// Attributs

  private:

  modif param = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0}, {false, false}, false, Rien, 0};

  public:

  /// Constructeurs

  virtual ~ChampForces() = default;

  /// Méthodes

  [[nodiscard]] virtual Vecteur force(PointMateriel*& point, const double& t) const;

  [[nodiscard]] virtual double potentiel(PointMateriel*& point, const double& t) const;

  [[nodiscard]] virtual double energiePotentielle(PointMateriel*& point, const double& t) const;

  virtual void affiche(std::ostream& sortie) const;

  void dessine_sur(SupportADessin& support) override;

  void modifParam(const modif& param);

  [[nodiscard]] const modif& getParam() const;
};

std::ostream& operator<<(std::ostream& sortie, const ChampForces& champ);

class ChampForcesNull final : public ChampForces {

    /// Constructeurs

    public:

    ~ChampForcesNull() override = default;

    /// Méthodes

    [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

    void affiche(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampForcesNull& champ);

class ChampCombine final : public ChampForces {

  /// Attributs

  private:

  std::vector<ChampForces*> champs;

  /// Constructeurs

  public:

  ChampCombine(const std::initializer_list<ChampForces*>& champs)
    : champs(champs) {}

  ChampCombine() = default;

  ~ChampCombine() override = default;

  explicit ChampCombine(const ChampCombine& autre) = delete;
  ChampCombine& operator=(const ChampCombine& autre) = delete;
  explicit ChampCombine(ChampCombine &&) = delete;
  ChampCombine& operator=(ChampCombine &&) = delete;

  /* On ne copie pas les ChampCombines en raison que les champs y ajoutés puissent avoir des
   * pointeurs en tant qu'attributs dont faire la copie profonde nous paraît trop fastidieux
   * pour nos besoins dans ce projet, mais ils peuvent être ajoutés dans d'autres ChampCombines. */

  /// Méthodes

  void ajouter(ChampForces& champ);

  void affiche(std::ostream& sortie) const override;

  [[nodiscard]] Vecteur force(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double potentiel(PointMateriel*& point, const double& t) const override;

  [[nodiscard]] double energiePotentielle(PointMateriel*& point, const double& t) const override;
};

std::ostream& operator<<(std::ostream& sortie, const ChampCombine& champ);

#endif //CHAMPFORCES_H