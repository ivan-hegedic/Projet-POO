# Projet POO

***

## Introduction et contenu

Parmi ce qui nous a été suggéré de faire dans le cadre du projet, nous avons implémenté tout,
y compris l'affichage graphique, toutefois sauf l'affichage gnuplots. En raison de vous faciliter le
parcours à travers notre rendu, tout fichier est nommé selon le format proposé suivi d'une courte
description : par exemple, les exécutables accordés d'un affichage graphique sont suivis du
mot-clé `GL`, tandis que les noms des fichiers `.cpp` leurs correspondants finissent par
`graphique`.

Le projet offre la possibilité de faire simuler et également de visualiser les systèmes
physiques de notre choix dont :

- `PommeSysteme`, exemple primitif d'une chute libre dans un champ gravitationnel,

- `PommeSystemeGL`, version graphique de PommeSysteme,

- `testPomme`, test de comparaison d'intégrateurs et d'affichage,

- `Pendule`, simulation du mouvement d'une pendule dans un champ gravitationnel
uniforme,

- `PenduleGL`, version grqphique de Pendule,

- `Orbite`, simulation primitive du problème à deux corps, la Terre et un satellite
(dont seulement le satellite bouge), intéragissant gravitationnellement,

- `OrbiteGL`, version graphique d'Orbite,

- `Trajectoires`, simulation du problème à deux corps interagissant gravitationnellement 
dont le Soleil et la Terre (l'un influant le mouvement de l'autre),

- `ThreeBodyProblem`, collection de simulations non-triviales du problème à trois corps
intéragissant gravitationnellement,

- `ThreeBodyProblemGL`, version graphique de ThreeBodyProblem,

- `CompterPi`, simulation d'une séquence de collision qui permet de compter les
chiffres de pi,

- `CompterPiGL`, version graphique de CompterPi,

- `Cyclotron`, simulation du fonctionnement d'un cyclotron.

Toute simulation dispose de resources afin de la faire visualiser au moyen de la bibliothèque
graphique Qt (version 5.15). Le développement entier du projet, y compris la conceptualisation,
l'écriture du code, la journalisation et l'enregistrement du progrès, a pris en moyenne 10 heures
par semaine par personne.

Nous vous invitons de bien faire connaissance avec les fichiers PDF
suivants : `JOURNAL`, `REPONSES`, `CONCEPTION` et enfin `RAPPORT` où l'on explique davantage certains
exercices plus complexes et non triviaux.

## Configuration et exécution

Merci de suivre les étapes suivantes afin de bien lancer notre rendu. Lors de la configuration,
vous créerez un dossier `build` contenant les exécutables générés par CMake. De plus, nous avons
fourni un script `run.sh` pour compiler et lancer les exécutables plus facilement.

### Configuration de tous les exécutables à la fois

1. Accéder au dossier `projet-g039` via le terminal.
2. Continuer vers le dossier `projet` en entrant `cd projet`.
3. Configurer le projet en entrant `cmake .`.
4. Lancer le script `run.sh` fourni avec `chmod +x run.sh`, puis `./run.sh`.

Tous les exécutables seront affichés dans le terminal. Pour en choisir un,
entrer le nombre affiché correspondant. Après la première exécution du script,
seule la dernière commande est nécessaire pour exécuter un autre programme.

```bash
  cd projet
  cmake .
  chmod +x run.sh
  ./run.sh
```

### Configuration des exécutables un par un

1. Accéder au dossier `projet-g039` via le terminal.
2. Continuer vers le dossier `projet` en entrant `cd projet`.
3. Compiler l'exécutable souhaité avec `cmake --build . --target nom_executable`.
4. Lancer l'exécutable une fois la compilation terminée avec `./nom_executable`.

```bash
  cd projet
  cmake --build . --target nom_executable
  ./nom_executable
```

### Termination du projet

Exécuter ceci pour supprimer le dossier `build` et tout ce qu'il contient :

```bash
  rm -rf build
```