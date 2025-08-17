<p align="center">
    <img src="https://github.com/amaraoussama94/Timber/blob/main/Game.png" height="150"> 
</p>
# 🌲 Timber — A Cross-Platform SFML Game

Timber is a fast-paced arcade-style game built with [SFML](https://www.sfml-dev.org/) and designed for maintainability, modularity, and cross-platform compatibility. Chop wood, dodge branches, and race against the clock — all wrapped in a clean, scalable codebase.

---

## 📦 Features

- 🎮 Classic Timber gameplay with responsive controls
- 🧩 Modular architecture: `Game`, `Player`, `BranchManager`, `SoundManager`, `UI`
- 🖼️ SFML-powered graphics, audio, and input
- 🔊 Sound effects and background music
- 🧠 Annotated code and clean interfaces for easy onboarding
- 🛠️ Cross-platform builds (Linux & Windows) via GitHub Actions

---

## 🎮 Controls

- Press `Enter` to start the game  
- Use `Left key` and `Right key` keys to control the player  
- Press `Escape` to exit the game  


## 🧱 Project Structure

```text
Timber/
├── bin/                  # Compiled binaries
├── external/             # SFML submodule
├── fonts/                # Game fonts
├── graphics/             # Sprites and textures
├── levels/               # Optional level data
├── sounds/               # Sound effects and music
├── src/
│   ├── Game.cpp/.h       # Main game loop and logic
│   ├── Player.cpp/.h     # Player entity and input
│   ├── BranchManager.cpp/.h  # Branch logic and collision
│   ├── SoundManager.cpp/.h   # Audio playback
│   ├── UI.cpp/.h         # Score, timer, and HUD
├── Makefile              # Build system
└── README.md             # Project documentation
```

---

### 🧱 Game Architecture Overview

This project follows a modular design for clarity and scalability. Each gameplay system is split into its own submodule:

| Module           | Responsibility                                      |
|------------------|-----------------------------------------------------|
| `Game`           | Main loop, orchestration of subsystems              |
| `Player`         | Player sprite, position, input handling             |
| `BranchManager`  | Branch logic, falling behavior, collision detection |
| `SoundManager`   | Loads and plays sound effects                       |
| `UIManager`      | Score, time bar, FPS, and messages                  |

All modules are located in `src/` and `include/`, with assets in `graphics/`, `fonts/`, and `sound/`.

---

## 🚀 Automated Build & Release (CI/CD)

Timber uses a unified GitHub Actions workflow to automate building, tagging, and releasing across platforms. This ensures consistent binaries, version tracking, and simplified distribution.

### 🧰 Workflow Overview

The CI/CD pipeline performs the following:

1. **Builds the game** on both Linux and Windows  
2. **Extracts the SFML version** from the submodule (or uses a fallback)  
3. **Generates a semantic tag** like `Timber_SFML-2.5.1_0001`  
4. **Packages binaries and assets** into `.zip` archives  
5. **Publishes a GitHub Release** with platform-specific builds  

---

### 🐧 Linux Build

- **Environment**: Ubuntu (latest)  
- **Dependencies**: SFML build libraries (OpenGL, X11, audio, fonts, etc.)  
- **Build Tool**: GNU Make  
- **Output**: `bin/Timber` uploaded as `Timber-linux`  

```bash
make clean-all
make all
```

### 🪟 Windows Build

- **Environment**: Windows with MSYS2 shell  
- **Toolchain**: MinGW64 (GCC, Make, CMake)  
- **Build Tool**: GNU Make inside MSYS2  
- **Output**: `bin/Timber.exe` + required `.dll`s uploaded as `Timber-windows`  

```bash
make clean-all
make all
```

PS :DLLs are automatically copied from external/SFML/install/bin/ 

### 🏷️ Tagging Strategy

- Tags follow the format:  
  `Timber_SFML-<version>_<build-number>`  
- Example: `Timber_SFML-2.5.1_0001`  
- The tag is auto-incremented based on previous releases  

---

### 📦 Release Packaging

Each release includes:

- ✅ Executable binary (`Timber` or `Timber.exe`)  
- ✅ Fonts, graphics, sounds, and optional levels  
- ✅ Versioned zip archives:  
  - `Timber_SFML-2.5.1_0001-linux.zip`  
  - `Timber_SFML-2.5.1_0001-windows.zip`  

> Assets are bundled from the following folders:  
> `fonts/`, `graphics/`, `sounds/`, `levels/`

---

### 📤 GitHub Release

Once tagged, the workflow:

- Creates a GitHub Release named after the tag  
- Uploads both `.zip` archives as downloadable assets  
- Publishes the release under [Releases](https://github.com/amaraoussama94/Timber/releases)
