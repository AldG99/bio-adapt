# Simulador de Tardígrados

Una aplicación educativa interactiva desarrollada en C++ con Qt5 que
simula el comportamiento de los tardígrados en diferentes ambientes
extremos.

---

## Características

- **Simulación Visual**: Animación del tardígrado en entornos como
  agua, hielo, radiación y espacio.
- **Simulación Científica**: Control de parámetros ambientales
  mediante sliders.
- **Cálculo de Supervivencia**: Algoritmo basado en literatura
  científica.
- **Gráficos en Tiempo Real**: Usando QtCharts.
- **Base de Conocimiento**: Información educativa integrada.

---

## Requisitos del Sistema

- CMake \>= 3.16
- Qt5 (Core, Widgets, Charts)
- Compilador C++17
- macOS / Linux / Windows

---

## Instalación y Compilación

### En macOS (Homebrew)

```bash
brew install qt@5
cd bio-adapt
mkdir build && cd build
export PATH="/opt/homebrew/Cellar/qt@5/5.15.17/bin:$PATH"
export CMAKE_PREFIX_PATH="/opt/homebrew/Cellar/qt@5/5.15.17"
cmake ..
make -j4
./bin/TardigradeSimulator
```

### En Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential cmake qtbase5-dev libqt5charts5-dev
mkdir build && cd build
cmake ..
make -j4
./bin/TardigradeSimulator
```

---

## Uso de la Aplicación

### Simulación Visual

- Selección de ambientes.
- Animación reactiva del tardígrado.
- Estado de supervivencia en tiempo real.

### Simulación Científica

- Ajuste de parámetros:
  - Temperatura (-200 °C a +150 °C)
  - Radiación (0 a 10 000 Gy)
  - Presión (0 a 1000 atm)
  - Hidratación (0% a 100%)
- Gráficos dinámicos de factores.

### Base de Conocimiento

- Sección informativa sobre anatomía, hábitats y resistencia.

---

## Algoritmo de Supervivencia

El modelo considera: - Temperatura - Radiación - Presión - Hidratación

Cada factor contribuye con un peso específico al índice final.

---

## Estructura del Proyecto (Vertical)

    tardigrade-sim/
    src/
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/VisualSimWidget.cpp
    src/VisualSimWidget.h
    src/ScienceSimWidget.cpp
    src/ScienceSimWidget.h
    src/Tardigrade.cpp
    src/Tardigrade.h
    src/KnowledgeBase.cpp
    src/KnowledgeBase.h
    src/ChartsWidget.cpp
    src/ChartsWidget.h
    resources/
    resources/sprites/
    resources/backgrounds/
    resources/knowledge.json
    resources/resources.qrc
    build/
    CMakeLists.txt
    README.md

---

## Valor Educativo

- Estudiantes de biología
- Educadores
- Divulgación científica
- Investigadores

---

## Base Científica

El simulador se basa en investigaciones sobre: - Tolerancia térmica

- Resistencia a radiación ionizante
- Presión extrema
- Criptobiosis / anhidrobiosis

---

## Contribuciones

- Mejoras en el algoritmo
- Nuevas animaciones visuales
- Ampliación del contenido educativo
- Corrección de errores

---

## Créditos

- Programación en C++ con Qt5
- Simulación científica interactiva
- Diseño de interfaces educativas
- Integración de conocimiento biológico y computacional

---

## Ejecución Rápida

```bash
cd build
./bin/TardigradeSimulator
```
