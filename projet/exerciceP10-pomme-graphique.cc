#include <QApplication>
#include "glwidget.h"
#include "Vecteur.h"
#include "Dessinable.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "PlanImmobile.h"
#include "Integrateurs.h"

int main(int argc, char* argv[]) {

  /* La chute d'une pomme dans un champ gravitationnel. Cette fois-ci avec l'affichage graphique. */

  /// Affichage graphique

  QApplication a(argc, argv);

  /// Constantes pour l'initialisation

  constexpr double massePomme(0.1);
  constexpr double masseTerre(5.972e24);
  constexpr double rayonTerre(6371000.0);
  constexpr double altitude(3.0);
  const Vecteur pos_init({0.0, rayonTerre + altitude, 0.0});
  const Vecteur pos_sol({0.0, altitude, 0.0});
  const Vecteur normale_sol({0.0, -1.0, 0.0});

  /// Points materiels

  PointMateriel pomme(constantes::vecnul, massePomme);
  PointMateriel terre(pos_init, masseTerre);

  /// Champs de forces

  ChampNewtonien champTerre(terre);

  /* Pour l'instant, on ignore l'effet gravitationnel qu'exerce la pomme sur la terre,
   * donc il n'est pas nécessaire d'initialiser ce champ-là. Une future simulation
   * servira d'observer comment deux objets célestes s'influencent l'un l'autre. */

  /// Contraintes

  PlanImmobile sol(pos_sol, normale_sol);

  /// Intégrateur

  RungeKuttaOr4 Rung;

  /// Initialisation du système

  Systeme sys;
  sys.setExercice(Pomme);
  sys.ajouter_objet(pomme);
  sys.ajouter_objet(terre);
  sys.ajouter_champforces(champTerre);
  sys.ajouter_contrainte(sol);
  sys.ajouter_integrateur(Rung);

  /// Édition des liens

  sys.ajouter_champforces_local(0, 0);
  sys.ajouter_contrainte_locale(0, 0);
  pomme.modifParam({{0, 3.19, 0}, {0, -1, 0}, {0, 0, 0, 0}, {0.2}, {false, true}, true, Pomme});
  terre.modifParam({{0, 3.19, 0}, {0, -1, 0}, {0, 0, 0, 0}, {0.2}, {false, true}, false, Pomme});
  sol.modifParam({{0, -0.3, 0}, {0, -1.0/4.5, 0}, {0, 0, 0, 0}, {1}, {false, true}, true, Pomme});
  champTerre.modifParam({{4, 1, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0.6}, {false, true}, true, Gravitation});
  sys.setDT(0.0025);

  /// Affichage graphique

  GLWidget w(sys);
  w.show();
  return QApplication::exec();
}
