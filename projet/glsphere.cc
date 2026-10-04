#define  _USE_MATH_DEFINES
#include "glsphere.h"
#include <cmath>
#include "vertex_shader.h"

void GLSphere::setGradient(QVector3D base, QVector3D top) {
  baseColor = base;
  topColor = top;
}

void GLSphere::initialize(GLuint slices, GLuint stacks) {
  QVector<GLfloat> positions;
  QVector<GLfloat> colors;
  QVector<GLfloat> vertexData;

  QVector<GLuint> indices0;
  QVector<GLuint> indices1;
  QVector<GLuint> indices2;

  GLuint size = 2+slices*(stacks-1);

  positions.reserve(3*size);
  colors.reserve(3*size);
  vertexData.reserve(6*size); // 3 positions + 3 couleurs

  const double alpha = M_PI/double(stacks);
  const double beta = 2.0*M_PI/double(slices);

  positions << 0.0 << 0.0 << 1.0;
  colors << topColor.x() << topColor.y() << topColor.z();

  for (GLuint i = 1; i < stacks; ++i) {
    for (GLuint j = 0; j < slices; ++j) {
      float r = sin(i*alpha);
      float z = cos(i*alpha);
      float y = sin(j*beta)*r;
      float x = cos(j*beta)*r;
      positions << x << y << z;
      float t = (z+1.0f)/2.0f; // normalisé à [0.0,1.0]
      QVector3D c = (1.0f-t)*baseColor+t*topColor; // nous créons un dégradé avec une interpolation linéaire
      colors << c.x() << c.y() << c.z();
    }
  }

  positions << 0.0 << 0.0 << -1.0;
  colors << baseColor.x() << baseColor.y() << baseColor.z();

  // Enlacer les positions et les couleurs
  for (int i = 0; i < size; ++i)
    vertexData << positions[3*i+0] << positions[3*i+1] << positions[3*i+2] << colors[3*i+0] << colors[3*i+1] << colors[3*i+2];

  //Initialise le « triangle fan » du pôle Nord
  indices0.reserve(slices + 2);
  indices0 << 0;
  for (GLuint i = 0; i <= slices; ++i)
    indices0 << 1+(i%slices);

  indices1.reserve((stacks - 2) * 4 * slices);
  for (GLuint i = 0; i < stacks - 2; ++i) {
    for (GLuint j = 0; j < slices; ++j) {
      indices1 << 1+i*slices+j << 1+(i+1)*slices+j << 1+(i+1)*slices+(j+1)%slices << 1+i*slices+(j+1)%slices;
    }
  }

  //Initialise le « triangle fan » du pôle Sud
  indices2.reserve(slices + 2);
  GLuint start = 1 + (stacks - 2) * slices;
  for (GLuint i = 0; i < slices; ++i) {
    indices2 << size-1;                          
    indices2 << start+i;                         
    indices2 << start+(i+1)%slices;          
  }
  
  vbo_sz = 6 * size * sizeof(GLfloat);
  vbo.create();
  vbo.bind();
  vbo.allocate(vertexData.constData(), vbo_sz);
  vbo.release();

  ibo_sz[0] = indices0.size() * sizeof(GLuint);
  ibo_sz[1] = indices1.size() * sizeof(GLuint);
  ibo_sz[2] = indices2.size() * sizeof(GLuint);

  ibo.create();
  ibo.bind();
  ibo.allocate(ibo_sz[0] + ibo_sz[1] + ibo_sz[2]);
  ibo.write(0, indices0.constData(), ibo_sz[0]);
  ibo.write(ibo_sz[0], indices1.constData(), ibo_sz[1]);
  ibo.write(ibo_sz[0] + ibo_sz[1], indices2.constData(), ibo_sz[2]);
  ibo.release();
}


void GLSphere::draw(QOpenGLShaderProgram& program, int attributeLocation) {
  bind();
  program.setAttributeBuffer(attributeLocation, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
  program.enableAttributeArray(attributeLocation);
  program.setAttributeBuffer(CouleurId, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
  program.enableAttributeArray(CouleurId);
  #define BUFFER_OFFSET(a) ((char*)nullptr + (a))
  glDrawElements(GL_TRIANGLE_FAN, ibo_sz[0] / sizeof(GLuint), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  glDrawElements(GL_QUADS, ibo_sz[1] / sizeof(GLuint), GL_UNSIGNED_INT, BUFFER_OFFSET(ibo_sz[0]));
  glDrawElements(GL_TRIANGLE_FAN, ibo_sz[2] / sizeof(GLuint), GL_UNSIGNED_INT, BUFFER_OFFSET(ibo_sz[0] + ibo_sz[1]));
  program.disableAttributeArray(attributeLocation);
  program.disableAttributeArray(CouleurId);
  release();
}


void GLSphere::bind() {
  vbo.bind();
  ibo.bind();
}

void GLSphere::release() {
  ibo.release();
  vbo.release();
}