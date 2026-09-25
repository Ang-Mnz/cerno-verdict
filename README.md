# Cerno Verdict

Cerno Verdict a pour objectif de devenir un système de surveillance et de vision embarquée autonome, distribué entre un microcontrôleur et une plateforme Linux.

Le système final sera organisé autour de plusieurs modules :

Vigile — un microcontrôleurs STM32 chargé de surveiller l'environnement à l'aide de capteurs de mouvement et de communiquer les événements au système principal par liaison wi-fi.
Praetorium — une plateforme Linux embarquée basée sur un Raspberry Pi, chargée de piloter la caméra, d'effectuer le traitement d'image en C++/OpenCV et de produire un verdict à partir des événements détectés.
Senatus — un backend Java/Spring Boot chargé de centraliser les événements, gérer leur stockage, exposer une API REST et assurer la communication avec l'interface utilisateur.
Forum — une interface web développée en Vue.js/TypeScript permettant de consulter les événements, visualiser les informations du système et interagir avec celui-ci.

À terme, le fonctionnement général sera le suivant :
```text
                         Cerno Verdict

 ┌──────────────────┐
 │     Vigiles      │
 │                  │
 │ STM32            │
 │ Wi-Fi            │
 └────────┬─────────┘
          │
          │ Alerte mouvement
          ▼
 ┌──────────────────┐
 │    Praetorium    │
 │                  │
 │ Raspberry Pi     │
 │ C++ / OpenCV     │
 │ Caméra           │
 │ Détection        │
 └────────┬─────────┘
          │
          │ Verdict / événement
          ▼
 ┌──────────────────┐
 │     Senatus      │
 │                  │
 │ Spring Boot      │
 │ REST             │
 │ SQLite           │
 └────────┬─────────┘
          │
          │ Données
          ▼
 ┌──────────────────┐
 │      Forum       │
 │                  │
 │ Vue.js /         │
 │ TypeScript       │
 └──────────────────┘

```

L'objectif n'est pas uniquement de réaliser un système de détection de mouvement, mais de construire progressivement une architecture complète mêlant systèmes embarqués, programmation bas niveau, C++ moderne, Linux, vision par ordinateur, communication inter-processus, backend, base de données et développement web.

Le projet sera développé progressivement, chaque module étant introduit et intégré au fur et à mesure de l'avancement.

## État actuel

Le prototype fonctionne actuellement sur un PC Linux connecté à une carte STM32.

Le système est capable de :

- acquérir un flux vidéo avec OpenCV
- détecter des mouvements entre les images successives
- gérer les événements de mouvement
- enregistrer une image lorsqu'un événement se termine
- organiser les images par date
- limiter le stockage à 100 images
- communiquer avec un STM32 par UART
- commander une LED depuis le STM32 en fonction de l'état du système
- afficher le flux vidéo et le masque de mouvement

Le microcontrôleur utilisé actuellement est une **NUCLEO-G071RB** basée sur un STM32G071RB.

## Architecture actuelle

```text
                    PC Linux
                       │
                       ▼
                    Camera
                       │
                       ▼
                  OpenCV / C++
                       │
                       ▼
                MotionDetector
                       │
                       ▼
                MotionManager
                  │          │
                  │          ▼
                  │      EventStorage
                  │          │
                  │          ▼
                  │       events/
                  │
                  ▼
                  UART
                    │
                    ▼
              STM32G071RB
                    │
                    ▼
                  GPIO
                    │
                    ▼
                   LED
```

## Installation

### Prérequis

Le projet nécessite :

- Linux
- un compilateur C++ compatible C++17
- CMake 3.20 ou supérieur
- OpenCV
- CTest

Sur Fedora :

```bash
sudo dnf install gcc-c++ cmake opencv-devel
```

### Récupération du projet

Cloner le dépôt :

```bash
git clone https://github.com/Ang-Mnz/cerno-verdict.git
```

Puis entrer dans le projet :

```bash
cd cerno-verdict
```
### Compilation et Execution

Créer le répertoire de compilation :

```bash
cmake -S . -B build
```
Compiler le projet :

```bash
cmake --build build
```

L'exécutable principal est alors disponible dans :

```bash
build/cerno_verdict
```

### Tests

Les tests utilisent CTest.

Après compilation :

```bash
ctest --test-dir build --output-on-failure
```
