#ifndef OBJETMOBILE_H
#define OBJETMOBILE_H

#include "Vecteur.h"
#include "Dessinable.h"
#include "constantes.h"

class SupportADessin;

class ObjetMobile: public Dessinable {

  /// Attributs

  protected:

  Vecteur pos = constantes::vecnul;
  Vecteur vit = constantes::vecnul;
  Vecteur acc = constantes::vecnul;

  /// Constructeurs

  public:

  explicit ObjetMobile(Vecteur const& pos_)
    : pos(pos_) {}

  explicit ObjetMobile(Vecteur const& pos_, Vecteur const& vit_)
    : pos(pos_), vit(vit_) {}

  explicit ObjetMobile(Vecteur const& pos_, Vecteur const& vit_, Vecteur const& acc_)
    : pos(pos_), vit(vit_), acc(acc_) {}

  ObjetMobile(const ObjetMobile& obj_mobile)
    : pos(obj_mobile.pos), vit(obj_mobile.vit), acc(obj_mobile.acc) {}

  ObjetMobile(ObjetMobile&& obj_mobile) noexcept
    : pos(obj_mobile.pos), vit(obj_mobile.vit), acc(obj_mobile.acc) {}

  ObjetMobile() = default;

  ~ObjetMobile() override = default;

  /// Méthodes

  [[nodiscard]] Vecteur position() const;

  [[nodiscard]] Vecteur vitesse() const;

  [[nodiscard]] Vecteur acceleration() const;

  virtual void setPosition(Vecteur const& pos);

  virtual void setVitesse(Vecteur const& vit);

  virtual void setAcceleration(Vecteur const& acc);

  void dessine_sur(SupportADessin& support) override;

  virtual std::ostream& affiche(std::ostream& sortie) const ;
};

std::ostream& operator<<(std::ostream& sortie, const ObjetMobile& objet);

#endif //OBJETMOBILE_H