#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include "Systeme.h"
#include "vue_opengl.h"

class GLWidget : public QOpenGLWidget {

  /// Constructeurs

  public:

  GLWidget(const Systeme& sys, QWidget* parent = nullptr);

  GLWidget(QWidget *parent = nullptr);

  virtual ~GLWidget() = default;

  /// Méthodes

  void ajouter_dessinable(Dessinable* dessinable);

  private:

  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter

  virtual void initializeGL() override;

  virtual void resizeGL(int width, int height) override;

  virtual void paintGL() override;

  // Méthodes de gestion d'évènements

  virtual void keyPressEvent(QKeyEvent* event) override;

  virtual void timerEvent(QTimerEvent* event) override;

  virtual void mousePressEvent(QMouseEvent* event) override;

  virtual void mouseMoveEvent(QMouseEvent* event) override;

  // Méthodes de gestion interne

  void pause();

  /// Attributs

  VueOpenGL vue; // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  int timerId;
  QElapsedTimer chronometre;
  QPoint lastMousePosition; // souris
  Systeme systeme;
};