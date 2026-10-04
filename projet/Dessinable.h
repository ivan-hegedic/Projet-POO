#ifndef DESSINABLE_H
#define DESSINABLE_H

class SupportADessin;

class Dessinable {

  /// Méthodes

  public:

  virtual void dessine_sur(SupportADessin& support) = 0;

  virtual ~Dessinable() = default;
};

#endif //DESSINABLE_H