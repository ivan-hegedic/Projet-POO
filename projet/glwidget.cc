#include "glwidget.h"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>
#include <iostream>
#include "ChampForces.h"
#include "ChampNewtonien.h"
#include "Integrateurs.h"
#include "PointMateriel.h"
#include "Systeme.h"
#include "Vecteur.h"

GLWidget::GLWidget(const Systeme& sys, QWidget* parent)
  : QOpenGLWidget(parent), systeme(sys) {
  chronometre.restart();
}

GLWidget::GLWidget(QWidget* parent)
  : QOpenGLWidget(parent) {
  chronometre.restart();
}

void GLWidget::initializeGL() {
  vue.init();
  timerId = startTimer(1 / 60);
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  QMatrix4x4 matrice;
  matrice.perspective(90, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  systeme.dessine_sur(vue);
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
  lastMousePosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    constexpr double petit_angle(.4); // en degrés
    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();
    vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);
    update();
  }
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1);
  switch (event->key()) {
    case Qt::Key_Left:
      vue.rotate(petit_angle, 0.0, -1.0, 0.0);
      break;
    case Qt::Key_Right:
      vue.rotate(petit_angle, 0.0, +1.0, 0.0);
      break;
    case Qt::Key_Up:
      vue.rotate(petit_angle, -1.0, 0.0, 0.0);
      break;
    case Qt::Key_Down:
      vue.rotate(petit_angle, +1.0, 0.0, 0.0);
      break;
    case Qt::Key_PageUp:
    case Qt::Key_W:
      vue.translate(0.0, 0.0, petit_pas);
      break;
    case Qt::Key_PageDown:
    case Qt::Key_S:
      vue.translate(0.0, 0.0, -petit_pas);
      break;
    case Qt::Key_A:
      vue.translate(petit_pas, 0.0, 0.0);
      break;
    case Qt::Key_D:
      vue.translate(-petit_pas, 0.0, 0.0);
      break;
    case Qt::Key_R:
      vue.translate(0.0, -petit_pas, 0.0);
      break;
    case Qt::Key_F:
      vue.translate(0.0, petit_pas, 0.0);
      break;
    case Qt::Key_Q:
      vue.rotate(petit_angle, 0.0, 0.0, -1.0);
      break;
    case Qt::Key_E:
      vue.rotate(petit_angle, 0.0, 0.0, +1.0);
      break;
    case Qt::Key_Home:
      vue.initializePosition();
      break;
    case Qt::Key_Space:
      pause();
      break;
  }
  update();
}

void GLWidget::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  chronometre.restart();
  systeme.evolue(systeme.getTemps(), systeme.getTemps() + systeme.getDT(), systeme.getDT());
  update();
}

void GLWidget::pause() {
  if (timerId == 0) {
    timerId = startTimer(0);
    chronometre.restart();
  } else {
    killTimer(timerId);
    timerId = 0;
  }
}