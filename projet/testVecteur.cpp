#include "Vecteur.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {

  /* Ici, il s'agit simplement d'un test afin de voir si le code écrit jusque-là est correct ou non. */

  Vecteur vect1;
  Vecteur vect2;
  Vecteur vect3;

  /* (1) pourrait être écrite autrement, par exemple avec ses manipulateurs (set_coord()) ;
   * (2) sera revue dans 2 semaines (constructeurs, surcharge des opérateurs). */

  vect1.augmente(1.0);
  vect1.augmente(0.0);
  vect1.augmente(-0.1);

  vect1.set_coord(1, 2.0); // test set_coord()

  vect2.augmente(2.6);
  vect2.augmente(3.5);
  vect2.augmente(4.1);

  vect3 = vect1;

  cout << "Vecteur 1 : ( ";
  vect1.affiche();
  cout << ")\nVecteur 2 : ( ";
  vect2.affiche();

  cout << ")\n\nLe vecteur 1 est ";
  vect1.compare(vect2) ? cout << "égal au" : cout << "différent du";
  cout << " vecteur 2,\net est ";
  not vect1.compare(vect3) ? cout << "différent du" : cout << "égal au";
  cout << " vecteur 3.\n\n";

  /// Tests d'addition

  cout << "Tests d'addition\n\n";

  Vecteur vt1({1.0,2.0,-0.1});
  Vecteur vt2({2.6,3.5,4.1});

  vt1.addition(vt2).affiche();
  cout << '\n';

  Vecteur vt_nul({0,0,0});

  vt1.addition(vt_nul).affiche();
  cout << '\n';

  vt1.soustraction(vt2).affiche();
  cout << '\n';

  vt1.soustraction(vt1).affiche();
  cout << '\n';

  vt1.opposee().affiche();
  cout << '\n';

  vt1.mult(3).affiche();
  cout << '\n';

  cout << vt1.prod_scal(vt2);
  cout << '\n';

  vt1.prod_vect(vt2).affiche();

  cout << "\n\nTests de normes\n\n";

  cout << vt1.norme2() << '\n';
  cout << vt2.norme2() << '\n';
  cout << vt_nul.norme2() << '\n';

  /// Tests pour de différentes dimensions

  cout << "\nTests d'addition pour de différentes dimensions\n\n";

  Vecteur vt3({1, 2});
  Vecteur vt7({5});

  vt2.addition(vt3).affiche();
  cout << "\ncheck\n\n";

  vt3.addition(vt2).affiche();
  cout << '\n';

  cout << vt2.norme1() << '\n';
  vt1.prod_vect(vt2).affiche();
  cout << '\n';
  vt2.prod_vect(vt1).affiche(); // produit vectoriel est anticommutatif

  cout << "\n\nTests de surcharge d'opérateurs\n\n( ";
  vt1.affiche();
  cout << ") + ( ";
  vt2.affiche();
  cout << ") = ( ";
  (vt1+vt2).affiche();
  cout << ")\n\n";

  (vt3+vt7).affiche();
  cout << '\n';
  vt3.addition(vt7).affiche();
  cout << "\n\nold ";
  vt3.affiche();
  cout << '\n';
  vt3 += vt7;
  cout << "new ";
  vt3.affiche();
  cout << "\n\n";
  (vt1+vt2).affiche();
  cout << '\n';
  (vt2+vt1).affiche();
  cout << "\n\n";

  /// Nouveaux tests

  Vecteur small({-0.3, 3.3 ,84});
  Vecteur large({666, 69 ,420 ,5444, 90.00003});

  (small+large).affiche();
  cout << '\n';
  (large+small).affiche();
  cout << "\n\n";

  /// Tests de sortie

  cout << vt1 << '\n';
  cout << vt2 << '\n';
  cout << vt3 << '\n';
  cout << vt_nul << '\n';
  cout << vt1 + vt2 << "\n\n";

  /// Un vecteur en 3D :

  Vecteur vect5(1.0, 2.0, -0.1);

  /// Un autre vecteur aussi en 3D :

  Vecteur vect6(2.6, 3.5,  4.1);

  Vecteur vect7(vect5); // copie de V1
  Vecteur vect4(4); // le vecteur nul en 4D
  Vecteur vect_vector({1,2,3,4}); // vecteur avec le constructeur qui prend un std::vector en parametre
  Vecteur vect_nul_3d(3);

  cout << "Vecteur 5 : ( " << vect5;
  cout << ")\nVecteur 6 : ( " << vect6;
  cout << ")\nVecteur 7 : ( " << vect7;
  cout << ")\nVecteur 4 : ( " << vect4;
  cout << ")\nVecteur vect_vector : ( " << vect_vector;
  cout << ")\nVecteur nul en 3d : ( " << vect_nul_3d;

  cout << ")\n\nLe vecteur 5 est ";
  vect5 == vect6 ? cout << "égal au" : cout << "différent du";
  cout << " vecteur 6,\net est ";
  vect5 != vect7 ? cout << "différent du" : cout << "égal au";
  cout << " vecteur 7.";

  /// Tests de surcharge d'opérateurs

  cout << "\n\nTests sur la surcharge des operateurs\n\nSurcharge de +";

  cout << "\nLa somme ( " << vect5 << ") + ( " << vect6 << ") = ( " << vect5 + vect6;
  cout << ")\nLa somme ( " << vect5 << ") + ( " << vect4 << ") = ( " << vect5 + vect4;
  cout << ")\nLa somme ( " << vect6 << ") + ( " << vect5 << ") = ( " << vect6 + vect5;
  cout << ")\nLa somme ( " << vect5 << ") + ( " << vect5 << ") = ( " << vect5 + vect5;
  cout << ")\nLa somme ( " << vect5 << ") + ( " << vect_nul_3d<< ") = ( " << vect5 + vect_nul_3d;

  cout << ")\n\nSurcharge de +=\n";

  Vecteur vect_dummy(1); // vecteur dummy qui a une seule valeur 0
  vect_dummy += vect5;
  cout << vect_dummy << '\n';
  vect_dummy += vect4;
  cout << vect_dummy;

  cout << "\n\nSurcharge de -";

  cout << "\nLa difference ( " << vect5 << ") - ( " << vect6 << ") = ( " << vect5 - vect6;
  cout << ")\nLa difference ( " << vect5 << ") - ( " << vect4 << ") = ( " << vect5 - vect4;
  cout << ")\nLa difference ( " << vect5 << ") - ( " << vect5 << ") = ( " << vect5 - vect5;
  cout << ")\nLa difference ( " << vect4 << ") - ( " << vect5 << ") = ( " << vect4 - vect5;
  cout << ")\nLa difference ( " << vect5 << ") - ( " << vect_nul_3d << ") = ( " << vect5 - vect_nul_3d;

  cout << ")\n\nSurcharge de -=" << '\n';

  vect_dummy = {0}; // vecteur dummy qui a une seule valeur 0
  vect_dummy -= vect5;
  cout << vect_dummy << '\n';
  vect_dummy -= vect4;
  cout << vect_dummy;

  cout << "\n\nSurcharge de * (produit scalaire)\n";

  cout << "\nLe produit scalaire ( " << vect5 << ") * ( " << vect6 << ") = " << vect5 * vect6;
  cout << "\nLe produit scalaire ( " << vect5 << ") * ( " << vect7 << ") = " << vect5 * vect7;
  cout << "\nLe produit scalaire ( " << vect5 << ") * ( " << vect7 << ") = " << vect7 * vect5;
  cout << "\nLe produit scalaire ( " << vect7 << ") * ( " << vect_nul_3d << ") = " << vect7 * vect_nul_3d;
  cout << "\nLe produit scalaire ( " << vect7 << ") * ( " << vect_nul_3d << ") = " << vect_nul_3d * vect7;

  cout << "\n\nSurcharge de * (multiplication par un scalaire)\n( ";

  cout << vect5 << ") * " << 8 << " = ( " << vect5*8 << ")\n( ";
  cout << vect5 << ") * " << 8 << " = ( " << 8*vect5 << ")\n( ";
  cout << vect1 << ") * " << 3 << " = ( ";
  vect1 *= 3;
  cout << vect1;
  cout << ")\n\nOpérateur unitaire\n\n";
  Vecteur a({1., 2.5, -3.4});
  Vecteur direction( ~a ); // utilisation de l'opérateur unitaire ~

  cout << "Le vecteur unitaire de même dimension que ( " << a << ") est : ( " << direction;
  cout << ")\n\nTest du produit vectoriel\n\nLe produit vectoriel de ( " << vect1 << ") ^ ( " << vect6 << ") = ( " << (vect1 ^ vect6);
  cout << ")\n\nTests des normes \n\nLa norme de ( " << vect1 << ") est " << vect1.norme1() << " et sa norme carrée vaut " << vect1.norme2();
  return 0;
}