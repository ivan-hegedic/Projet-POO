#pragma once

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <map>
#include <ranges>
#include <string>
#include "SupportADessin.h"
#include "constantes_graphique.h"
#include "glsphere.h"

class VueOpenGL : public SupportADessin, protected QOpenGLFunctions {

  public:

  // méthode(s) de dessin (héritée(s) de SupportADessin)

  void dessine(ObjetMobile const &a_dessiner) override;

  void dessine(Contrainte const &a_dessiner) override;

  void dessine(PlanImmobile const &a_dessiner) override;

  void dessine(PointMateriel const &a_dessiner) override;

  void dessine(Systeme const &a_dessiner) override;

  void dessine(ContrainteSpherique const &a_dessiner) override;

  void dessine(ContrainteCombinee const &a_dessiner) override;

  void dessine(ChampForces const &a_dessiner) override;

  void dessine(ChampNewtonien const &a_dessiner) override;

  void dessine(GravitationConstante const &a_dessiner) override;

  // méthodes de (ré-)initialisation

  void init();

  void initializePosition();

  // méthode set

  void setProjection(QMatrix4x4 const &projection) { prog.setUniformValue("projection", projection); }

  void translate(double x, double y, double z);

  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthodes utilitaires offertes pour simplifier

  void dessineLigne(QMatrix4x4 const &point_de_vue, Vecteur const &a, Vecteur const &b);

  void dessineCube(QMatrix4x4 const &point_de_vue = QMatrix4x4());

  void dessineCubeTexture(size_t pos, Exercice e, QMatrix4x4 const &point_de_vue = QMatrix4x4());

  void dessineAxes(QMatrix4x4 const &point_de_vue, bool en_couleur = true);

  void dessineSphere(QMatrix4x4 const &point_de_vue, double r1 = 1.0, double v1 = 1.0, double b1 = 1.0, double r2 = 1.0, double v2 = 1.0, double b2 = 1.0);

  private:

  // Un shader OpenGL encapsulé dans une classe Qt

  QOpenGLShaderProgram prog;

  modif p;

  GLSphere sphere;

  // Caméra

  QMatrix4x4 matrice_vue;

  //Textures

  /*Comme il n'existe pas de nombre universel de nombres d'objets/cubes à dessiner avec des textures
  * dans une simulation spécifique, une « matrice » avec une taille indéfinie est appropriée. */

  std::map<Exercice, std::vector<std::vector<std::unique_ptr<QOpenGLTexture>>>> textures;
};