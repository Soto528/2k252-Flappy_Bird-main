
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
│   └── cover.png                  ← Imagen de portada (720x1080)
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

- La carpeta `.vscode/` contiene configuraciones locales y no está pensada para
	estar en el repositorio remoto. Asegúrate de no subir tus ajustes locales.

Contribuciones
--------------

Si quieres mejorar el juego, abre un 'issue' o un 'pull request' con tus cambios.

