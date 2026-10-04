cmake_minimum_required(VERSION 3.20)
project(poo_projet)

set(CMAKE_CXX_STANDARD 20)

add_executable(testVecteur
Vecteur.cpp
testVecteur.cpp
)

add_executable(testPointMateriel
testPointMateriel.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
Contrainte.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
)

add_executable(testIntegrateurs
testIntegrateurs.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
Contrainte.cpp
PlanImmobile.cpp
Integrateurs.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
)

add_executable(testSysteme
testSysteme.cpp
Vecteur.cpp
Systeme.cpp
Integrateurs.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ChampForces.cpp
Contrainte.cpp
ContrainteSpherique.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
)

add_executable(testDessinableText
testDessinableText.cpp
Vecteur.cpp
Dessinable.cpp
TextViewer.cpp
SupportADessin.h
Systeme.cpp
PointMateriel.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
ChampForces.cpp
Contrainte.cpp
PlanImmobile.cpp
ContrainteSpherique.cpp
Integrateurs.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
)

add_executable(testPomme
        exerciceP7-testPomme.cpp
Vecteur.cpp
PointMateriel.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
ChampForces.cpp
Contrainte.cpp
ContrainteSpherique.cpp
PlanImmobile.cpp
Integrateurs.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
Systeme.cpp
)

add_executable(PommeSysteme
exerciceP9-pomme.cpp
Vecteur.cpp
Systeme.cpp
PointMateriel.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
ChampForces.cpp
Contrainte.cpp
ContrainteSpherique.cpp
PlanImmobile.cpp
Integrateurs.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
)

add_executable(CompterPi
exerciceP11-compter-pi.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
Contrainte.cpp
PlanImmobile.cpp
ContrainteSpherique.cpp
Integrateurs.cpp
Collisions.cpp
Systeme.cpp
)

add_executable(Trajectoires
exerciceP9-2-trajectoires.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
Contrainte.cpp
ContrainteSpherique.cpp
Integrateurs.cpp
Collisions.cpp
Systeme.cpp
)

add_executable(Cyclotron
exerciceP11-2-cyclotron.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
ContrainteSpherique.cpp
PointMateriel.cpp
PointCharge.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
ChampsEM.cpp
ChampRestreint.cpp
Contrainte.cpp
Collisions.cpp
Integrateurs.cpp
Systeme.cpp
)

add_executable(Pendule
exerciceP11-6-pendule.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ChampForces.cpp
GravitationConstante.h
Contrainte.cpp
ContrainteSpherique.cpp
Integrateurs.cpp
Systeme.cpp
)

add_executable(Orbite
exerciceP9-2-orbite.cpp
Vecteur.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ContrainteSpherique.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
Contrainte.cpp
Integrateurs.cpp
Systeme.cpp
)

add_executable(ThreeBodyProblem
exerciceP11-three-body-problem.cpp
Vecteur.cpp
ContrainteSpherique.cpp
ObjetMobile.cpp
ObjetPhysique.cpp
PointMateriel.cpp
ChampForces.cpp
ForceCentrale.cpp
ChampNewtonien.cpp
Contrainte.cpp
Integrateurs.cpp
Systeme.cpp
)

target_include_directories(testPointMateriel PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(testIntegrateurs PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(testDessinableText PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(testPomme PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(testSysteme PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(PommeSysteme PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(CompterPi PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Trajectoires PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Cyclotron PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Pendule PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Orbite PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(ThreeBodyProblem PRIVATE ${CMAKE_SOURCE_DIR})

set(OpenGL_GL_PREFERENCE GLVND)

find_package(Qt5
COMPONENTS
Core
Gui
Widgets
REQUIRED)

find_package(Qt5
COMPONENTS
Core
Widgets
OpenGL
REQUIRED)

find_package(OpenGL REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

qt5_add_resources(RESOURCE_FILES resource.qrc)

message(STATUS "Resources générées : ${RESOURCE_FILES}")

set(SOURCES
glsphere.cpp
glwidget.cc
vue_opengl.cc
Systeme.cpp
Integrateurs.cpp
PointMateriel.cpp
ObjetPhysique.cpp
Dessinable.cpp
Vecteur.cpp
ChampForces.cpp
ChampNewtonien.cpp
ForceCentrale.cpp
ContrainteSpherique.cpp
ObjetMobile.cpp
Contrainte.cpp
SupportADessin.h
PlanImmobile.cpp
${CMAKE_BINARY_DIR}/qrc_resource.cpp
${RESOURCE_FILES}
)

set(HEADERS
glwidget.h
vertex_shader.h
constantes_graphique.h
)

add_executable(PommeSystemeGL ${SOURCES} ${HEADERS}
exerciceP10-pomme-graphique.cc
)

target_link_libraries(PommeSystemeGL
Qt5::Core
Qt5::Widgets
Qt5::OpenGL
OpenGL::GL
)

add_executable(ThreeBodyProblemGL ${SOURCES} ${HEADERS}
exerciceP11-three-body-problem-graphique.cpp
)

target_link_libraries(ThreeBodyProblemGL
Qt5::Core
Qt5::Widgets
Qt5::OpenGL
OpenGL::GL
)

add_executable(OrbiteGL ${SOURCES} ${HEADERS}
exerciceP10-2-orbite-graphique.cpp
)

target_link_libraries(OrbiteGL
Qt5::Core
Qt5::Widgets
Qt5::OpenGL
OpenGL::GL
)

add_executable(PenduleGL ${SOURCES} ${HEADERS}
exerciceP11-6-pendule-graphique.cpp
)

target_link_libraries(PenduleGL
Qt5::Core
Qt5::Widgets
Qt5::OpenGL
OpenGL::GL
)

add_executable(CompterPiGL ${SOURCES} ${HEADERS}
exerciceP11-compter-pi-graphique.cpp
configurationsCompterPi.h
Collisions.cpp
)

target_link_libraries(CompterPiGL
Qt5::Core
Qt5::Widgets
Qt5::OpenGL
OpenGL::GL
)