# 🪙 CoinDash
![GitHub repo size](https://img.shields.io/github/repo-size/<rajnsunny>/CoinDash)
![GitHub issues](https://img.shields.io/github/issues/<rajnsunny>/CoinDash)
![GitHub pull requests](https://img.shields.io/github/issues-pr/<rajnsunny>/CoinDash)
![GitHub](https://img.shields.io/github/license/<rajnsunny>/CoinDash)
![Milestone](https://img.shields.io/badge/milestone-V2-blue)

A simple 2D platformer game built using **C++** and **SFML**.  
Currently supports multiple levels, coin collection, and smooth level transitions.  
Future versions (V2) will add a player sprite, sound effects, and a home page.

---

## 🚀 Features
- Procedurally generated platforms and coins
- Coin collection and scoring system
- Level progression with increasing difficulty
- Exit button to complete levels
- Asynchronous preloading of next levels for smooth gameplay

---

## 📦 Setup & Build

### Prerequisites
- C++17 compiler (g++)
- [SFML 2.5+](https://www.sfml-dev.org/download.php)

### Build & Run
```bash
# Clone the repository
git clone https://github.com/rajnsunny/CoinDash.git
cd CoinDash

# Build using Makefile
make

# Run the game
./platformer
````

### Clean build files

```bash
make clean
```

---

## 🎮 Controls

* **Arrow Keys**

  * `←` / `→` : Move left/right
  * `↑` : Jump
* **Close window** : Exit game

---

## 📂 Project Structure

```
CoinDash/
├── assets/              # Fonts, textures, sounds
│   ├── fonts/
│   ├── images/
│   └── sounds/
├── src/                 # Source files
│   ├── Game.cpp
│   ├── Level.cpp
│   ├── Player.cpp
│   └── ...
├── Makefile             # Build configuration
└── README.md
```

---

## 🛠️ Roadmap

### ✅ V1 (Current)

* Basic platformer mechanics
* Coins collection
* Level loading & async preloading

### 🔜 V2 (Milestone)

* [ ] Player sprite (replace box with character)
* [ ] Sound effects (coins, jump, level complete)
* [ ] Home page / main menu

---

## 🤝 Contributing

1. Fork the repo
2. Create a branch (`git checkout -b feature/new-feature`)
3. Commit your changes (`git commit -m "Add new feature"`)
4. Push to the branch (`git push origin feature/new-feature`)
5. Open a Pull Request 🚀

---

## 📜 License

This project is licensed under the MIT License.

