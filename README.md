# Cerno Verdict

Projet personnel de développement d'un système de vision embarquée combinant informatique embarquée, programmation C/C++, Linux, architectures ARM et traitement d'image.

L'objectif est de concevoir progressivement un système capable d'acquérir des images depuis une caméra, de les analyser localement et de prendre une décision en fonction du résultat de l'analyse.

Le système final devra être capable de :

- acquérir une image ou un flux vidéo depuis une caméra
- effectuer un traitement d'image localement
- détecter ou analyser un objet présent dans la scène
- déterminer un état ou une décision à partir de cette analyse
- communiquer cette décision avec un microcontrôleur
- permettre au microcontrôleur de commander des périphériques ou des actionneurs

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
