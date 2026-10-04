#ifndef CONSTANTES_GRAPHIQUE_H
#define CONSTANTES_GRAPHIQUE_H

#include <array>
#include <random>

/* Attributs qui aident à dessiner chaque Dessinable de manière personnalisée. */

struct Trans {
   double x;
   double y;
   double z;
};

struct Transcoord {
   double x;
   double y;
   double z;
};

struct Rot {
   double angle;
   double x;
   double y;
   double z;
};

struct Scale {
   double factor;
};

struct Shape {
  bool sphere;
  bool cube;
};

enum Exercice {Rien = 0, Pomme = 1, Orbite = 2, Pendule = 3, Threebod = 4 , ThreebodPapillon = 5, Collisions = 6, Gravitation = 7};

/* Le type de struct suffit pour nos besoins dans le cadre du projet. */

struct modif {
  Trans trans;
  Transcoord transcoord;
  Rot rot;
  Scale scale;
  Shape shape;
  bool dessinable;
  Exercice exercice;
  size_t tag;
  std::array<double, 6> couleurs = {};

  /* Couleurs pour le dégradé des sphères - 2 couleurs en format RVB déterminées par 3 doubles [0.0,1.0]. */
};

inline double randomColor() {
  static std::random_device rd;
  static std::default_random_engine generator(rd());
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  return distribution(generator);
}

/* La méthode ci-dessus génère une valeur [0.0, 1.0] pour interpoler le dégradé sphérique. */

#endif //CONSTANTES_GRAPHIQUE_H