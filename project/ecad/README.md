# Conception électronique

Un dossier par projet KiCad, contenant au minimum les fichiers `.kicad_pro`,
`.kicad_sch` et `.kicad_pcb`.

| Carte | Dossier | Rôle |
|---|---|---|
| Carte principale de la console Pong | `projet maker/` | XIAO ESP32S3, écran TFT, joystick, 2 boutons, LED, connecteur I2C |

Le projet a été fait avec **KiCad 10**. Les bibliothèques ajoutées (XIAO de Seeed Studio,
joystick SparkFun) sont dans `projet maker/libs/`, donc le projet s'ouvre directement
sans rien installer.

## Affichage sur le site

Pas besoin de recopier les fichiers dans `docs/assets/kicad/` : à chaque push qui
modifie `project/ecad/`, la publication du site copie automatiquement tous les
`.kicad_sch` et `.kicad_pcb` de ce dossier (les espaces des noms deviennent des tirets),
puis le site se met à jour. Le schéma est affiché sur la page
**Conception → Électronique → Carte principale**.

## Fichiers à ne pas mettre sur le repo

Les sauvegardes (`*-backups/`), les fichiers de verrou (`*.lck`), `*.kicad_prl` et
les `.bak` sont propres à chaque ordinateur. Ils sont déjà ignorés par `.gitignore`
quand on passe par GitHub Desktop, mais il ne faut pas les glisser à la main sur le
site GitHub.
