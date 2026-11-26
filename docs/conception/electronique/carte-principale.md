---
layout: default
title: Carte principale
parent: Électronique
grand_parent: Conception
nav_order: 1
---

# Carte principale

## Rôle

C'est la carte de la console. Elle accueille la XIAO ESP32S3 (U1) et relie tous les
éléments de la console :

- l'écran TFT, branché sur un connecteur femelle 14 broches (J1) ;
- le joystick (SW3) ;
- deux boutons poussoirs (SW1 et SW2) ;
- une LED rouge avec sa résistance (D1 et R3), qui montre que la carte est alimentée ;
- un connecteur I2C 4 broches (J2), avec ses deux résistances de tirage (R1 et R2),
  pour ajouter un module plus tard.

Toute la carte est alimentée en 3V3 par la XIAO.

## Schéma

Le schéma est le même pour les deux révisions du PCB : entre la rev A et la rev B,
on n'a changé aucune broche, seulement le placement et le routage.

Il est toujours à jour : à chaque fois qu'on pousse le projet KiCad dans
`project/ecad/`, le site recopie automatiquement les fichiers et se met à jour
(voir l'étape « Copier les fichiers KiCad » dans `.github/workflows/pages.yml`).

{% include kicad.html src="assets/kicad/projet-maker.kicad_sch" controles="full" hauteur="600px" %}

## PCB

On a fait deux révisions du PCB. La rev A est notre premier routage, sur deux couches.
Au débrief, le prof nous a dit qu'elle n'était pas assez optimisée. On a donc fait une
rev B, routée sur une seule couche.

### Règles communes aux deux révisions

| Règle | Valeur | Pourquoi |
|---|---|---|
| Taille de la carte | 90 × 50 mm | Imposée pour rentrer dans le boîtier |
| Fixations | 4 trous M3 (Ø 3,2 mm) à 4 mm des bords | Visser la carte dans le boîtier |
| Isolement minimum | 0,2 mm | Limite de fabrication, en dessous on risque des courts-circuits |
| Largeur des pistes de signal | 0,25 mm | Au-dessus du minimum (0,2 mm), avec de la marge |
| Largeur des pistes d'alimentation (3V3, GND) | 0,5 mm | Elles portent tout le courant de la carte (pics du Wi-Fi) |
| Angles | 45° | Pas d'angle droit, comme demandé dans le tuto |
| Plan de masse | Oui, avec liaisons thermiques | Masse commune partout, moins de bruit, soudure facile |

### Rev A : routage sur deux couches

Pour la rev A, on a d'abord placé les composants en fonction du boîtier : joystick en
haut à gauche, boutons en bas à gauche sous le pouce, XIAO au milieu avec l'USB vers le
bord du bas, et l'écran à droite.

Le problème, c'est que la XIAO a l'USB vers le bas. Du coup, ses broches de l'écran
(D7 à D10) sont du côté du joystick, et ses broches du joystick et des boutons sont du
côté de l'écran. Les pistes doivent donc se croiser, et on a utilisé les deux faces :

- le bus de l'écran et les fils du joystick passent sur la face arrière (en bleu) ;
- l'alimentation 3V3, les boutons et l'I2C passent sur la face avant (en rouge) ;
- 3 vias pour changer de face là où deux pistes se croisent (SDA, SCL et D0) ;
- 5 vias de masse pour relier les plans de masse du dessus et du dessous.

Résultat : 685 mm de pistes, à peu près moitié dessus, moitié dessous, et 8 vias.

{% include kicad.html src="assets/kicad/projet-maker.kicad_pcb" controles="full" hauteur="600px" %}

### Rev B : routage sur une seule couche

Au débrief, le prof nous a demandé d'optimiser la carte :

- toutes les pistes sur une seule face, le dessous ne sert qu'au plan de masse ;
- décaler l'écran vers la droite ;
- mettre le connecteur I2C entre la XIAO et l'écran ;
- brancher la LED et sa résistance sur le 3V3 du condensateur du joystick.

On s'est imposé en plus de ne pas toucher au schéma (aucune broche changée) et de
laisser la XIAO, le joystick et les boutons à la même place que sur la rev A, pour
rester compatible avec le boîtier.

Sans via, deux pistes ne peuvent jamais se croiser. Il a donc fallu trouver un chemin
pour chaque fil :

- **Le bus de l'écran passe sous la XIAO.** Les fils partent de ses broches vers
  l'intérieur, remontent sous le module et ressortent par le haut, puis vont tout
  droit vers l'écran. Ce sont les pistes les plus rapides de la carte, elles sont
  donc courtes et directes.
- **D10 passe entre les broches 7 et 8 de l'écran.** Sur l'écran, MOSI et SCK sont
  inversés par rapport à la XIAO. D10 traverse le connecteur entre deux broches et
  arrive sur sa broche par la droite, ce qui évite le croisement.
- **Le joystick et les boutons passent aussi sous la XIAO**, mais ils ressortent par le
  bas, sous l'USB, puis partent vers la gauche.
- **Le joystick est tourné de 180° sur lui-même** (même position) pour que ses broches
  arrivent dans le bon ordre. Dans le code, il faut donc inverser le sens des deux axes.
  SW1 est tourné de 90° pour laisser passer les fils du joystick.
- **L'écran est décalé de 10 mm vers la droite** pour faire de la place à J2. L'I2C
  va en ligne droite de la XIAO à J2, avec R1 et R2 juste à côté.
- **La LED et sa résistance** sont branchées sur le 3V3 de C3, le condensateur du
  joystick, juste sous le joystick.
- **La masse des composants CMS** (condensateurs, LED, boutons) rejoint par une petite
  piste une broche GND traversante (XIAO, écran, I2C ou joystick). Comme ces broches
  traversent la carte, elles touchent le plan de masse du dessous : on n'a besoin
  d'aucun via, même pour la masse.
- **C1 et C4**, les condensateurs de la XIAO, sont collés à ses broches 3V3 et GND.
- Le vide de la face du dessus est aussi rempli de masse.

{% include kicad.html src="assets/kicad/projet-maker-bis.kicad_pcb" controles="full" hauteur="600px" %}

### Comparaison des deux révisions

| | Rev A | Rev B |
|---|---|---|
| Faces avec des pistes | 2 (dessus et dessous) | 1 (dessus seulement) |
| Face du dessous | Pistes + plan de masse | Plan de masse plein |
| Vias | 8 (3 de signal, 5 de masse) | 0 |
| Longueur totale des pistes | 685 mm | 765 mm |
| Bus de l'écran | Sur la face arrière, sous la XIAO | Sur la face avant, court et direct |
| Position de l'écran (J1) | x = 153,8 mm | x = 163,8 mm (+10 mm) |
| Connecteur I2C (J2) | Au-dessus de la XIAO | Entre la XIAO et l'écran |
| Joystick | 0° | Tourné de 180° (axes inversés dans le code) |

La rev B est un peu plus longue en pistes. Comme la XIAO ne bouge pas, les fils du
joystick doivent faire le tour des boutons par la gauche. En échange, la carte n'a plus
qu'une face de pistes et aucun via. Elle est plus simple à fabriquer, et le plan de
masse du dessous n'est coupé nulle part.

## Nomenclature

| Référence | Composant | Valeur | Empreinte | Quantité |
|---|---|---|---|---|
| U1 | Microcontrôleur Seeed Studio XIAO ESP32S3 | – | `XIAO-ESP32-S3-DIP` | 1 |
| J1 | Connecteur femelle pour l'écran TFT | 1×14, pas 2,54 mm | `PinSocket_1x14_P2.54mm_Vertical` | 1 |
| J2 | Connecteur I2C | 1×4, pas 2,54 mm | `PinHeader_1x04_P2.54mm_Vertical` | 1 |
| SW3 | Joystick | – | `Joystick` (Makerspace) | 1 |
| SW1, SW2 | Bouton poussoir | – | `SW_Push_KMR2` | 2 |
| D1 | LED | rouge | `LED_1206_3216Metric` | 1 |
| C1, C2, C3 | Condensateur | 100 nF | `C_1206` | 3 |
| C4 | Condensateur | 10 µF | `C_1206` | 1 |
| R1, R2 | Résistance de tirage I2C | 4,7 kΩ | `R_1206` | 2 |
| R3 | Résistance de la LED | 150 Ω | `R_1206` | 1 |
| H1 à H4 | Trou de fixation | M3 | `MountingHole_3.2mm_M3` | 4 |

[📁 Fichiers KiCad]({{ site.gh_edit_repository }}/tree/main/project/ecad){: .btn }
