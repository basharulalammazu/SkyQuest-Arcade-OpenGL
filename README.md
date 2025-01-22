<h1 align="center">✈️ SkyQuest-Arcade-OpenGL ✈️</h1>

<p align="center">
  A thrilling 2D arcade game built with C++ and OpenGL GLUT, featuring dynamic gameplay, interactive transformations, and exciting challenges! 🎮✨
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue" />
  <img src="https://img.shields.io/badge/OpenGL-GLUT-lightgreen" />
  <img src="https://img.shields.io/badge/Game%20Type-Arcade-blueviolet" />
</p>

---

## 📖 Overview

**SkyQuest-Arcade-OpenGL** is a 2D arcade game that combines vibrant graphics and interactive gameplay to create an engaging experience. The player controls an aircraft, collecting items to earn points while avoiding obstacles and bombs. The game utilizes **translation** and **rotation transformations** to deliver smooth movements and dynamic animations.

### 🎮 Game Highlights
- **Three Progressive Levels**: Increasing complexity with new animations and challenges in each level.
- **Core Transformations**: Aircraft movement (translation) and dynamic rotating obstacles/collectibles.
- **Scoring and Health Mechanisms**: Motivates strategic gameplay while balancing health and earning points.
- **Immersive Audio-Visual Effects**: Engages players with animations and interactive sounds.

---

## ✨ Features

### Level 1: SkyQuest
- **Landscape Animation**: Smooth scrolling background creates a seamless travel effect.
- **Item Animation**: Collectibles move with simple horizontal or vertical translation.
- **Time Limitation**: Adds urgency and competitive scoring.

### Level 2: Enhanced Complexity
- **Hill-scape Animation**: Scrolling hills enhance depth and realism.
- **Item Animation**: Enhanced motion paths and varied speeds increase challenges.
- **Obstacle Animation**: Dynamic side-to-side moving obstacles.
- **Health Mechanism**: Collisions reduce health, increasing difficulty.

### Level 3: Advanced Dynamics and Challenges
- **Wave Animation**: Realistic flowing waves using cyclic translation patterns.
- **Bomb Animation**: Falling bombs add urgency and tension.
- **Health Mechanism**: Instant health loss on bomb collisions creates high-stakes gameplay.

---

## 🔧 Key Functionalities

### Input Handling
- **Keyboard and Mouse**: For menu navigation and gameplay controls.

### Game Mechanics
- Collectibles: Items increase the player’s score upon collection.
- Time Limitation: Competitive scoring for Level 1.
- Health Effects: Collisions with obstacles or bombs trigger health reduction or game-over scenarios.

### Audio and Visuals
- Interactive sound effects for actions like collecting items, colliding, and game-over.
- Translation-based animations for smooth gameplay.

### High Score Tracking
- Scores stored and displayed via text files for competitive replayability.

---

## 🎥 Gameplay Video

Watch the gameplay here:

[![SkyQuest Gameplay](https://img.youtube.com/vi/8ufxCPwY6F8/0.jpg)](https://www.youtube.com/watch?v=8ufxCPwY6F8)

---

## 🚀 How to Run

Follow these steps to set up and play the game locally:

### 1⃣ Clone the Repository
```bash
git clone https://github.com/mdtanjimrahman/SkyQuest-Arcade-OpenGL.git
```

### 2⃣ Install Dependencies
Ensure you have OpenGL and GLUT installed on your system. For example:
- **Windows**: Install freeglut via `vcpkg` or download binaries.
- **Linux**: Install using `sudo apt-get install freeglut3-dev`.
- **Mac**: Use `brew install freeglut`.

### 3⃣ Build and Run
Compile and run the game using your preferred IDE or command line:
```bash
g++ -o SkyQuest main.cpp -lGL -lGLU -lglut
./SkyQuest
```

---

## 🎯 Gameplay Instructions

### Main Menu Controls:
- **W**: Navigate Up
- **S**: Navigate Down
- **Enter**: Select
- **M**: Sound On/Off
- **Esc**: Go Back / Replay
- **C**: To see Cover Page (Displays developer information)

### In-game Controls:
- **Up Arrow**: Move Up
- **Down Arrow**: Move Down
- **Left Arrow**: Move Left
- **Right Arrow**: Move Right

These controls are applicable across all levels.

---

## 📂 Directory Structure

```
SkyQuest-Arcade-OpenGL/
│
├── SkyQuest-Arcade/
│   ├── bin/                             # Binary files and resources
│   │   └── Debug/                       # Debug build output
│   │       ├── background_music.wav     
│   │       ├── bomb_explosion.mp3      
│   │       ├── bomb_explosion.wav      
│   │       ├── coin_collection.mp3     
│   │       ├── coin_collection.wav     
│   │       ├── demo1.mp3               
│   │       ├── game_over.mp3           
│   │       ├── game_over.wav           
│   │       ├── levelSelect.mp3         
│   │       ├── levelSelect.wav         
│   │       ├── levelSelection.wav      
│   │       ├── menu-select.wav         
│   │       ├── obstacle_hit.mp3        
│   │       ├── obstacle_hit.wav        
│   │       └── SkyQuest-Arcade.exe     # Executable file
│   │
│   ├── obj/                             # Compiled object files
│   │   └── Debug/
│   │       └── main.o                   # Compiled object file for the main source
│   │
│   ├── highest_scores.txt               # High scores file
│   ├── main.cpp                         # Main source code file
│   ├── SkyQuest-Arcade.cbp              # Code::Blocks project file
│   ├── SkyQuest-Arcade.depend           # Project dependency file
│   └── SkyQuest-Arcade.layout           # Project layout configuration
│
├── LICENSE                              # License information
├── .gitignore                           # Git ignore rules
└── README.md                            # Project documentation

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
      <a href="https://github.com/rafiahsalsabillabanya">
        <img src="https://avatars.githubusercontent.com/rafiahsalsabillabanya" width="100px;" alt=""/>
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
