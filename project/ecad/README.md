# Conception électronique

Un dossier par projet KiCad, contenant au minimum les fichiers `.kicad_pro`,
`.kicad_sch` et `.kicad_pcb`.

| Carte | Dossier | Rôle |
|---|---|---|
| Carte principale, rev A (2 couches) | `projet maker/` | XIAO ESP32S3, écran TFT, joystick, 2 boutons, LED, connecteur I2C |
| Carte principale, rev B (1 couche) | `projet maker bis/` | Même schéma, routage sur une seule face, dessous = plan de masse, 0 via |

Le projet a été fait avec **KiCad 10**. Les bibliothèques ajoutées (XIAO de Seeed Studio,
joystick, bibliothèque du Makerspace) sont dans le dossier `libs/` de chaque projet, donc
le projet s'ouvre directement sans rien installer.

## Affichage sur le site

Pas besoin de recopier les fichiers dans `docs/assets/kicad/` : à chaque push qui
modifie `project/ecad/`, la publication du site copie automatiquement tous les
`.kicad_sch` et `.kicad_pcb` de ce dossier (les espaces des noms deviennent des tirets,
par exemple `projet maker bis.kicad_pcb` devient `projet-maker-bis.kicad_pcb`), puis le
site se met à jour. Le schéma et les deux PCB sont affichés sur la page
**Conception → Électronique → Carte principale**.

## Fichiers à ne pas mettre sur le repo

Les sauvegardes (`*-backups/`), les fichiers de verrou (`*.lck`), `*.kicad_prl` et
les `.bak` sont propres à chaque ordinateur. Ils sont déjà ignorés par `.gitignore`
quand on passe par GitHub Desktop, mais il ne faut pas les glisser à la main sur le
site GitHub.
