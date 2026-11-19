# Firmware

Le **firmware** est le code qui tourne sur la carte électronique.
Il se développe avec **VSCode** et l'extension **PlatformIO**
(voir [Installation de VSCode et PlatformIO](https://doc.makerspace-amiens.fr/docs/tutorials/software/vscode-platformio/installation-vscode/)).

- **Carte cible :** Seeed Studio XIAO ESP32S3 Plus (framework Arduino)
- **Bibliothèques :** listées dans `platformio.ini` (`lib_deps`), avec leur version
  - `adafruit/DHT sensor library` et `adafruit/Adafruit Unified Sensor` : capteur DHT11
  - `adafruit/Adafruit ST7735 and ST7789 Library` : écran TFT ST7789

Le détail des tests (câblage, résultats, vidéos) est dans le journal de bord :
[TD microcontrôleur : port série, modules et capteurs](../../docs/journal/etudiant-1/2026-09-23.md).

## Organisation

```text
firmware/
└── tests-modules/
    ├── platformio.ini    carte, bibliothèques, un environnement par programme
    ├── include/
    │   └── config.h      brochage de la console (toutes les broches)
    └── src/              un fichier par programme de test
```

Toutes les broches sont dans `include/config.h` : si le câblage change, on ne modifie
que ce fichier.

Le dossier `.pio/` (fichiers de compilation) est ignoré par git : ne le commitez pas.

## Les programmes

Chaque programme est dans son propre fichier de `src/` et a son propre environnement
dans `platformio.ini`. Un environnement ne compile qu'un seul fichier.

| Environnement | Fichier | Ce qu'il fait |
|---|---|---|
| `serie_teleplot` | `src/serie_teleplot.cpp` | Envoie un sinus et un cosinus sur le port série pour TelePlot |
| `bouton_niveau` | `src/bouton_niveau.cpp` | Affiche le niveau du bouton (HIGH relâché, LOW appuyé) |
| `bouton_antirebond` | `src/bouton_antirebond.cpp` | Compte les appuis, un seul événement par appui (anti-rebond 30 ms) |
| `joystick_brut` | `src/joystick_brut.cpp` | Affiche les valeurs brutes x, y (0 à 4095) et le bouton SW |
| `joystick_normalise` | `src/joystick_normalise.cpp` | Calibre le centre et donne x entre -1 et +1 avec une zone morte |
| `buzzer` | `src/buzzer.cpp` | Joue une gamme (buzzer passif) puis un bip HIGH (buzzer actif) |
| `ecran` | `src/ecran.cpp` | Affiche « PONG », un rectangle et un disque sur l'écran ST7789 |
| `test_global` | `src/test_global.cpp` | Test des 4 modules : le point suit le joystick, le bouton fait biper |
| `dht11` | `src/dht11.cpp` | Température et humidité du KY-015 (DHT11), format TelePlot |
| `son_ky037` | `src/son_ky037.cpp` | Volume crête à crête et sortie DO du capteur de son KY-037 |
| `laser_bouton` | `src/laser_bouton.cpp` | Laser KY-008 qui clignote puis s'allume tant que le bouton est appuyé |

## Brochage

| Module | Broche XIAO |
|---|---|
| Bouton `S` | D5 |
| Joystick `VRx` / `VRy` / `SW` | D0 / D1 / D2 |
| Buzzer `S` | D3 (seulement sur breadboard) |
| Écran `SCK` / `MOSI` | D9 / D10 |
| Écran `DC` / `RESET` | D8 / D7 |
| Écran `CS` | GND |
| DHT11 `S`, ou KY-037 `AO` | D4 |
| KY-037 `DO`, ou laser `S` | D6 |
| Tous `VCC` / `GND` | 3V3 / GND (jamais 5V) |

## Compiler et téléverser

1. Dans VSCode, ouvrez le dossier `firmware/tests-modules/` (`File > Open Folder`),
   pas la racine du repo : sinon PlatformIO ne détecte pas le projet.
2. Dans la barre du bas, cliquez sur le nom de l'environnement (`env:...`) et
   choisissez le programme à tester.
3. Branchez la carte en USB.
4. Dans la barre du bas : **✓** pour compiler, **→** pour téléverser, **🔌** pour ouvrir
   le moniteur série (ou **Upload and Monitor** dans le menu PlatformIO).
5. Pour les programmes qui envoient des courbes (`serie_teleplot`, `dht11`,
   `son_ky037`), ouvrez TelePlot sur le port COM à 115200 bauds. Fermez TelePlot
   avant de téléverser, sinon le port est occupé.

Si le téléversement échoue : débrancher la carte, maintenir le bouton **B**, rebrancher,
relâcher **B**, relancer le téléversement, puis appuyer sur **R**.
