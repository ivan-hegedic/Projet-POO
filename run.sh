#!/bin/bash

BUILD_DIR="build"

mkdir -p "$BUILD_DIR"

if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
  echo "Configuration de CMake du projet..."
  cmake -S . -B "$BUILD_DIR"
  if [ $? -ne 0 ]; then
    echo "Configuration de CMake échouée."
    exit 1
  fi
fi

targets=(
  "PommeSysteme"
  "PommeSystemeGL"
  "Pendule"
  "PenduleGL"
  "Orbite"
  "OrbiteGL"
  "Trajectoires"
  "ThreeBodyProblem"
  "ThreeBodyProblemGL"
  "CompterPi"
  "CompterPiGL"
  "Cyclotron"
  "testVecteur"
  "testPointMateriel"
  "testIntegrateurs"
  "testPomme"
  "testDessinableText"
  "testSysteme"
)

echo "Exécutables disponibles :"
for i in "${!targets[@]}"; do
  printf "%2d: %s\n" $((i+1)) "${targets[i]}"
done

read -p "Entrez le nombre ou le nom de l'exécutable à compiler et lancer : " input

if [[ "$input" =~ ^[0-9]+$ ]]; then
  idx=$((input - 1))
  if [ $idx -ge 0 ] && [ $idx -lt ${#targets[@]} ]; then
    TARGET=${targets[$idx]}
  else
    echo "Nombre de l'exécutable non valable."
    exit 1
  fi
else
  TARGET="$input"
fi

echo "Compilation du '$TARGET'..."
cmake --build "$BUILD_DIR" --target "$TARGET"
if [ $? -ne 0 ]; then
  echo "Compilation échouée pour '$TARGET'."
  exit 1
fi

if [ -x "$BUILD_DIR/$TARGET" ]; then
  echo "Exécution du $TARGET..."
  "$BUILD_DIR/$TARGET"
else
  echo "Exécutable pour '$TARGET' non trouvé ou non exécutable."
fi