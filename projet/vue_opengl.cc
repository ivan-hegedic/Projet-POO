#include "vue_opengl.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <iostream>
#include "ChampNewtonien.h"
#include "Contrainte.h"
#include "ContrainteSpherique.h"
#include "GravitationConstante.h"
#include "PlanImmobile.h"
#include "PointMateriel.h"
#include "Systeme.h"
#include "vertex_shader.h"

void VueOpenGL::dessine(ObjetMobile const& a_dessiner) {}

void VueOpenGL::dessine(Contrainte const& a_dessiner) {}

void VueOpenGL::dessine(PlanImmobile const& a_dessiner) {
  modif param = a_dessiner.getParam();
  if (param.dessinable) {
    QMatrix4x4 matrice;
    matrice.setToIdentity();
    matrice.translate(param.trans.x, param.trans.y, param.trans.z);
    Vecteur pos = a_dessiner.getPosition();
    matrice.translate(param.transcoord.x * pos.get_coord(0), param.transcoord.y * pos.get_coord(1), param.transcoord.z * pos.get_coord(2));
    matrice.rotate(param.rot.angle, param.rot.x, param.rot.y, param.rot.z);
    matrice.scale(param.scale.factor);
    Exercice aufgabe = param.exercice;
    if (param.shape.cube && (aufgabe == Pomme || aufgabe == Collisions))
      dessineCubeTexture(param.tag, param.exercice, matrice);
    else if (param.shape.cube)
      dessineCube(matrice);
    else if (param.shape.sphere)
      dessineSphere(matrice, param.couleurs[0], param.couleurs[1], param.couleurs[2], param.couleurs[3], param.couleurs[4], param.couleurs[5]);
  }
}

void VueOpenGL::dessine(PointMateriel const& a_dessiner) {
  modif param = a_dessiner.getParam();
  if (param.dessinable) {
    QMatrix4x4 matrice;
    matrice.setToIdentity();
    matrice.translate(param.trans.x, param.trans.y, param.trans.z);
    Vecteur pos = a_dessiner.position();
    matrice.translate(param.transcoord.x * pos.get_coord(0), param.transcoord.y * pos.get_coord(1), param.transcoord.z * pos.get_coord(2));
    matrice.rotate(param.rot.angle, param.rot.x, param.rot.y, param.rot.z);
    matrice.scale(param.scale.factor);
    Exercice aufgabe = param.exercice;
    if (param.shape.cube && aufgabe != Collisions)
      dessineCube(matrice);
    else if (param.shape.cube)
      dessineCubeTexture(param.tag, param.exercice, matrice);
    else if (param.shape.sphere)
      dessineSphere(matrice, param.couleurs[0], param.couleurs[1], param.couleurs[2], param.couleurs[3], param.couleurs[4], param.couleurs[5]);
  }
}

void VueOpenGL::dessine(Systeme const& a_dessiner) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 matrice;
  if (a_dessiner.getExercice() == Threebod || a_dessiner.getExercice() == ThreebodPapillon) {
    Vecteur refpoint = a_dessiner.getReference();
    refpoint *= 3 * 1e-11;
    matrice.translate(refpoint.get_coord(0), refpoint.get_coord(1), refpoint.get_coord(2));
  }
  dessineAxes(matrice);
  if (a_dessiner.getExercice()==Pendule)
    glDisable(GL_DEPTH_TEST);
  for (auto& con: a_dessiner.getContraintes())
    con->dessine_sur(*this);
  if (a_dessiner.getExercice()==Pendule)
    glEnable(GL_DEPTH_TEST);
  for (auto& obj: a_dessiner.getObjets())
    obj->dessine_sur(*this);
  for (auto &chm: a_dessiner.getChamps())
    chm->dessine_sur(*this);
}

void VueOpenGL::dessine(ContrainteSpherique const& a_dessiner) {
  Vecteur pos = a_dessiner.getPoint();
  QMatrix4x4 matrice;
  matrice.setToIdentity();
  Vecteur const a = a_dessiner.getCentre();
  Vecteur const b = pos;
  modif par = a_dessiner.getParam();
  Trans tr = par.trans;
  Transcoord tc = par.transcoord;
  Vecteur translation = {tr.x, tr.y, tr.z};
  Vecteur bfin = {b.get_coord(0) * tc.x, b.get_coord(1) * tc.y, b.get_coord(2) * tc.z};
  Vecteur const c = bfin + translation;
  dessineLigne(matrice, a, c);
}

void VueOpenGL::dessine(ContrainteCombinee const& a_dessiner) {
  for (auto& i: a_dessiner.getContraintes())
    i->dessine_sur(*this);
}

void VueOpenGL::dessine(ChampForces const& a_dessiner) {}

void VueOpenGL::dessine(ChampNewtonien const& a_dessiner) {
  modif param = a_dessiner.getParam();
  if (param.dessinable) {
    QMatrix4x4 matrice;
    matrice.setToIdentity();
    matrice.translate(param.trans.x, param.trans.y, param.trans.z);
    matrice.rotate(param.rot.angle, param.rot.x, param.rot.y, param.rot.z);
    matrice.scale(param.scale.factor);
    Exercice aufgabe = param.exercice;
    if (param.shape.cube && aufgabe == Gravitation)
      dessineCubeTexture(param.tag, param.exercice, matrice);
    else if (param.shape.cube)
      dessineCube(matrice);
    else if (param.shape.sphere)
      dessineSphere(matrice, param.couleurs[0], param.couleurs[1], param.couleurs[2], param.couleurs[3], param.couleurs[4], param.couleurs[5]);
  }
}

void VueOpenGL::dessine(GravitationConstante const& a_dessiner) {
  modif param = a_dessiner.getParam();
  if (param.dessinable) {
    QMatrix4x4 matrice;
    matrice.setToIdentity();
    matrice.translate(param.trans.x, param.trans.y, param.trans.z);
    matrice.rotate(param.rot.angle, param.rot.x, param.rot.y, param.rot.z);
    matrice.scale(param.scale.factor);
    Exercice aufgabe = param.exercice;
    if (param.shape.cube && (aufgabe == Gravitation))
      dessineCubeTexture(param.tag, param.exercice, matrice);
    else if (param.shape.cube)
      dessineCube(matrice);
    else if (param.shape.sphere)
      dessineSphere(matrice, param.couleurs[0], param.couleurs[1], param.couleurs[2], param.couleurs[3], param.couleurs[4], param.couleurs[5]);
  }
}

/// Méthode pour initialiser le map des textures

std::vector<std::vector<std::unique_ptr<QOpenGLTexture>>> loadTextures(std::initializer_list<std::vector<QString>> facettes) {
  std::vector<std::vector<std::unique_ptr<QOpenGLTexture>>> result;
  for (const auto &face: facettes) {
    std::vector<std::unique_ptr<QOpenGLTexture>> textures;
    for (const auto &filepath: face) {
      auto img = QImage(filepath);
      if (img.isNull())
        throw std::runtime_error("Chargement de l'image échoué: " + filepath.toStdString());
      textures.push_back(std::make_unique<QOpenGLTexture>(img));
    }
    result.push_back(std::move(textures));
  }
  return result;
}

void VueOpenGL::init() {
  initializeOpenGLFunctions();
  prog.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");
  prog.bindAttributeLocation("sommet", SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);
  prog.bindAttributeLocation("texture", CoordonneeTextureId);
  if (!prog.link())
    qDebug() << "L'édition des liens pour les shaders est échoué: " << prog.log();
  // Activation du shader
  prog.bind();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  sphere.initialize();
  initializePosition();
  //édition des liens
  try {
    textures.emplace(Pomme, loadTextures({{":/grass_above.jpg", ":/grass_lateral.jpg", ":/grass_below.jpg"}}));
    textures.emplace(Gravitation, loadTextures({{":/Empty.png", ":/CodeCogsEqn.png", ":/Empty.png"}}));
    textures.emplace(Collisions, loadTextures({{":/tnt_above.jpg", ":/tnt.jpg", ":/tnt_belo.png"}, {":/lucky_block.jpeg", ":/lucky_block.jpeg", ":/lucky_block.jpeg"}, {":/bedrock.jpg", ":/bedrock.jpg", ":/bedrock.jpg"}}));
  } catch (const std::exception &e) {
    qDebug() << "Erreur lors du chargement des images: " << e.what();
  }
}

void VueOpenGL::initializePosition() {
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -5.0);
  dessineAxes(matrice_vue);
}

void VueOpenGL::translate(double x, double y, double z) {
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) {
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

void VueOpenGL::dessineLigne(QMatrix4x4 const& point_de_vue, Vecteur const& a, Vecteur const& b) {
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setUniformValue("mode", 0);
  glBegin(GL_LINES);
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  prog.setAttributeValue(SommetId, a.get_coord(0), a.get_coord(1), a.get_coord(2));
  prog.setAttributeValue(SommetId, b.get_coord(0), b.get_coord(1), b.get_coord(2));
  glEnd();
}

void VueOpenGL::dessineCube(QMatrix4x4 const& point_de_vue) {
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setUniformValue("mode", 0);
  glBegin(GL_QUADS);

  // face X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.2, 0.2);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.9, 0.1, 0.1);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.05, 0.05);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

  prog.setAttributeValue(CouleurId, 0.7, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face X = -1
  prog.setAttributeValue(CouleurId, 0.7, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.05, 0.05);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  prog.setAttributeValue(CouleurId, 0.9, 0.1, 0.1);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  prog.setAttributeValue(CouleurId, 1.0, 0.2, 0.2);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face Y = +1
  prog.setAttributeValue(CouleurId, 0.9, 0.1, 0.1);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.1, 0.1);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  prog.setAttributeValue(CouleurId, 0.7, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

  prog.setAttributeValue(CouleurId, 0.6, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face Y = -1
  prog.setAttributeValue(CouleurId, 0.6, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.7, 0.05, 0.05);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.1, 0.1);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  prog.setAttributeValue(CouleurId, 0.9, 0.15, 0.15);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face Z = +1
  prog.setAttributeValue(CouleurId, 0.7, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, 1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.1, 0.1);
  prog.setAttributeValue(SommetId, +1.0, -1.0, 1.0);

  prog.setAttributeValue(CouleurId, 0.9, 0.2, 0.2);
  prog.setAttributeValue(SommetId, +1.0, +1.0, 1.0);

  prog.setAttributeValue(CouleurId, 1.0, 0.3, 0.3);
  prog.setAttributeValue(SommetId, -1.0, +1.0, 1.0);

  // face Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.3, 0.3);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.9, 0.2, 0.2);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.8, 0.1, 0.1);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  prog.setAttributeValue(CouleurId, 0.7, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

void VueOpenGL::dessineCubeTexture(size_t pos, Exercice e, QMatrix4x4 const& point_de_vue) {
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setUniformValue("mode", 1);
  /// Indique au shader quel numéro de texture il doit utiliser (0,1,2,...)
  prog.setUniformValue("textureId", 0);
  const std::map<Exercice, std::vector<std::vector<std::unique_ptr<QOpenGLTexture>>>> &t = textures;
  t.find(e)->second[pos][1]->bind();
  // Commence le dessin du cube. On dessine le cube en plusieurs étapes pour pouvoir changer de texture.
  // X+
  if (e == Gravitation)
    t.find(e)->second[pos][0]->bind();
  glBegin(GL_QUADS);
  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // X-
  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  glEnd();

  t.find(e)->second[pos][0]->bind();

  glBegin(GL_QUADS);
  // Y+
  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  glEnd();

  t.find(e)->second[pos][2]->bind();

  glBegin(GL_QUADS);
  // Y-
  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  glEnd();

  t.find(e)->second[pos][1]->bind();

  glBegin(GL_QUADS);
  // Z+
  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // Z-
  prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

void VueOpenGL::dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur) {
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setUniformValue("mode", 0);
  glBegin(GL_LINES);
  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (en_couleur)
    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (en_couleur)
    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

  glEnd();
}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue, double r1, double v1, double b1, double r2, double v2, double b2) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"
  glDisable(GL_CULL_FACE);
  QMatrix4x4 model = point_de_vue;
  model.rotate(90, 1, 0, 0);
  prog.setUniformValue("vue_modele", matrice_vue * model);
  prog.setUniformValue("mode", 0);
  sphere.setGradient(QVector3D(r1, v1, b1), QVector3D(r2, v2, b2));
  sphere.initialize(25, 25); // Nouveau dégradé
  sphere.draw(prog, SommetId);
}
