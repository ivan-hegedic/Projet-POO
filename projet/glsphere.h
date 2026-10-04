#ifndef GLSPHERE_H
#define GLSPHERE_H
#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class GLSphere {

  /// Constructeur

  public:

  GLSphere()
    : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer) {}

  /// Méthodes

  void setGradient(QVector3D base, QVector3D top);

  void initialize(GLuint slices = 25, GLuint stacks = 25);

  void draw(QOpenGLShaderProgram& program, int attributeLocation);

  void bind();

  void release();

  /// Attributs

  private:

  QOpenGLBuffer vbo, ibo;
  GLuint vbo_sz;
  GLuint ibo_sz[3];
  QVector3D baseColor;
  QVector3D topColor;
};

#endif //GLSPHERE_H