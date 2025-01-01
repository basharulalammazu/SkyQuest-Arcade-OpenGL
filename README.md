<h1 align="center">✈️ SkyQuest-Arcade-OpenGL ✈️</h1>

<p align="center">
  A thrilling 2D arcade game built with C++ and OpenGL GLUT, featuring dynamic gameplay, interactive transformations, and exciting challenges! 🎮✨
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue" />
  <img src="https://img.shields.io/badge/OpenGL-GLUT-lightgreen" />
    <img src="https://img.shields.io/badge/Game%20Type-Arcade-blueviolet" />
  <img src="https://img.shields.io/badge/Status-In%20Development-orange" />
</p>

---

## 📖 Overview

**SkyQuest-Arcade-OpenGL** is a 2D arcade game that combines vibrant graphics and interactive gameplay to create an engaging experience. The player controls an aircraft, collecting items to earn points while avoiding obstacles and bombs. The game utilizes **translation** and **rotation transformations** to deliver smooth movements and dynamic animations.

### 🎮 Game Highlights
- **Three Challenging Levels**: Progressively harder levels with unique gameplay mechanics.
- **Core Transformations**: Aircraft movement (translation) and dynamic rotating obstacles/collectibles.
- **Dynamic Gameplay**: Smooth transitions, vibrant animations, and increasing difficulty.
- **Interactive Scoring System**: Motivates players to improve and compete for high scores.

---

## 🌟 Features

### Level 1
- Focused on collecting scoring items.
- No obstacles or bombs for easier gameplay.
- Aircraft can only move up and down.

### Level 2
- Adds obstacles between collectibles.
- Players must navigate carefully to avoid obstacles.
- Aircraft movement remains limited to up and down.

### Level 3
- Most challenging level with obstacles, collectibles, and falling bombs.
- Aircraft can move **up**, **down**, **left**, and **right** to dodge bombs and obstacles.

---

## 🛠️ Technologies Used

- **C++**: Core programming language for game development.
- **OpenGL GLUT**: For rendering 2D graphics and animations.
- **Visual Studio** (or equivalent): IDE for compiling and debugging the project.

---

## 🚀 How to Run

Follow these steps to set up and play the game locally:

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/madtanjimrahman/SkyQuest-2D-Arcade-Game.git
```

### 2️⃣ Install Dependencies
Ensure you have OpenGL and GLUT installed on your system. For example:
- **Windows**: Install freeglut via `vcpkg` or download binaries.
- **Linux**: Install using `sudo apt-get install freeglut3-dev`.
- **Mac**: Use `brew install freeglut`.

### 3️⃣ Build and Run
Compile and run the game using your preferred IDE or command line:
```bash
g++ -o SkyQuest main.cpp -lGL -lGLU -lglut
./SkyQuest
```

---

## 🎯 Gameplay Instructions

1. Control the aircraft to collect items and earn points.
2. Avoid obstacles and bombs to survive and progress through levels.
3. Use arrow keys:
   - **Up/Down**: Navigate the aircraft (Levels 1 & 2).
   - **Left/Right**: Additional movement in Level 3.
4. Have fun and try to achieve the highest score!

---

## 📂 Directory Structure

```
SkyQuest-2D-Arcade-OpenGL/
│
├── src/                          # Source code files
│   ├── main.cpp                  # Main game logic
│   ├── utils.cpp                 # Utility functions (if applicable)
│   ├── utils.h                   # Header file for utility functions
│
├── build/                        # Compiled binary and object files
│   ├── Debug/                    # Debug build files
│   │   ├── SkyQuest-Arcade.exe   # Executable game file
│   │   ├── main.o                # Compiled object file
│
├── assets/                       # Game assets (if applicable)
│   ├── textures/                 # Images or textures
│   ├── sounds/                   # Sound effects or background music
│
├── SkyQuest-Arcade.cbp           # Code::Blocks project file
├── SkyQuest-Arcade.depend        # Project dependency file
├── SkyQuest-Arcade.layout        # Project layout configuration
├── LICENSE                       # License information
├── .gitignore                    # Files and directories to be ignored by Git
└── README.md                     # Documentation for the project
```

---

## ✨ Contributors

<table align="center">
  <tr>
        <td align="center">
      <a href="https://github.com/mdtanjimrahman">
        <img src="https://avatars.githubusercontent.com/mdtanjimrahman" width="100px;" alt=""/>
        <br /><sub><b>Md Tanjim Rahman</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/basharulalammazu">
        <img src="https://avatars.githubusercontent.com/basharulalammazu" width="100px;" alt=""/>
        <br /><sub><b>Basharul - Alam - Mazu</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/labanya29">
        <img src="https://avatars.githubusercontent.com/labanya29" width="100px;" alt=""/>
        <br /><sub><b>Rafiha Salsabil Labannya</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/badrunnaharruku">
        <img src="https://avatars.githubusercontent.com/badrunnaharruku" width="100px;" alt=""/>
        <br /><sub><b>Badrunnahar Ruku</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/rajbantee">
        <img src="https://avatars.githubusercontent.com/rajbantee" width="100px;" alt=""/>
        <br /><sub><b>Tatinee Rajbantee</b></sub>
      </a>
    </td>
  </tr>
</table>

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

