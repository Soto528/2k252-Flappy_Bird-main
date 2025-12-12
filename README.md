Controles
---------

- Espacio: Saltar / Iniciar / Reiniciar tras perder.
- ESC: Pausar el juego.
- Enter: Reanudar desde pausa.

Requisitos
---------

- Windows 10/11 (o equivalente) para las versiones binarias incluidas.
- SFML (bibliotecas dinámicas .dll incluidas en `assets/`).
- `cl.exe` (MSVC) o `g++` (MinGW) si deseas compilar desde el código fuente.

Cómo compilar
-------------

Con MSVC (Developer Command Prompt):

```powershell
cl.exe /Zi /EHsc /nologo /Fe"bin\\flappy.exe" assets\flappy.cpp /I assets
```

Con MSBuild (Visual Studio):

```powershell
msbuild assets\flappy.vcxproj /p:Configuration=Release
```

Con MinGW (g++):

```powershell
g++ -std=c++17 -O2 -Iassets -o bin/flappy.exe assets/flappy.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Solución de problemas
---------------------

- Si faltan archivos de audio (`musica_fondo.ogg`, `game_over.wav`, `point_score.wav`) el juego seguirá arrancando pero mostrará advertencias y no reproducirá sonido.
- Si la fuente `arial.ttf` no está disponible en `assets/`, el juego intentará cargarla desde `C:\Windows\Fonts`.
- Asegúrate de ejecutar `bin/flappy.exe` desde la carpeta raíz del repositorio (o copiar las dependencias `*.dll` a la misma carpeta del ejecutable).


2k252-FLAPPY_BIRD-MAIN
======================

Estructura principal del repositorio (lista exacta del contenido):

├── .github/
│   └── workflows/
│       └── publish.yml
├── .vscode/                      ← Carpeta local de VSCode (ignorada por .gitignore)
│   └── tasks.json
├── assets/
│   ├── arial.TTF
│   ├── arialbd.ttf
│   ├── arialbi.ttf
│   ├── ariali.ttf
│   ├── ariblk.ttf
│   ├── background.png
│   ├── flappy.exe
│   ├── flappy.pdb
│   ├── flappy.vcxproj
│   ├── flappy.vcxproj.filters
│   ├── flappy.vcxproj.user
│   ├── flappy.cpp
│   ├── openal32.dll
│   ├── pipe_0.png
│   ├── Player_Rainbow.png
│   ├── screenshots/               ← Carpeta de capturas (vacía actualmente)
│   ├── sfml-audio-2.dll
│   ├── sfml-audio-d-2.dll
│   ├── sfml-graphics-2.dll
│   ├── sfml-graphics-d-2.dll
│   ├── sfml-network-2.dll
│   ├── sfml-network-d-2.dll
│   ├── sfml-system-2.dll
│   ├── sfml-system-d-2.dll
│   ├── sfml-window-2.dll
│   └── sfml-window-d-2.dll
├── bin/
│   └── flappy.exe                 ← Ejecutable precompilado
├── gallery/
│   └── cover.png                  
├── screenshots/
│   ├── screenshot1.PNG
│   ├── screenshot2.PNG
│   └── screenshot3.PNG
├── video/
│   └── demo.mp4
├── README.md
└── .gitignore

Descripción breve
-----------------

Proyecto del juego tipo "Flappy Bird". Los recursos y binarios para jugar
están incluidos; el código fuente principal del juego está dentro de `assets/`
(archivo `flappy.cpp` y proyecto de Visual Studio `flappy.vcxproj`).

Cómo ejecutar
-------------

- Ejecutar la versión ya compilada: `bin/flappy.exe` o `assets/flappy.exe`.
- Si quieres compilar el proyecto en Windows con la línea de comandos:

```powershell
cl.exe /Zi /EHsc /nologo /Fe"bin\\flappy.exe" assets\flappy.cpp
```

O con MSBuild / Visual Studio:

```powershell
msbuild assets\flappy.vcxproj /p:Configuration=Release
```

Nota sobre VSCode
-----------------

- En realese encontraras todos los recursos para jugar el juego sin problemas


