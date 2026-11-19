---
layout: default
title: Carte principale
parent: Électronique
grand_parent: Conception
nav_order: 1
---

# Carte principale

## Rôle

C'est la carte de la console Pong. Elle accueille la XIAO ESP32S3 (U1) et relie
tous les éléments de la console :

- l'écran TFT, branché sur un connecteur femelle 14 broches (J1) ;
- le joystick (J3) ;
- deux boutons poussoirs (SW1 et SW2) ;
- une LED rouge (D1) ;
- un connecteur I2C 4 broches (J2) pour ajouter un module plus tard.

Toute la carte est alimentée en 3V3 par la XIAO.

## Schéma

Le schéma ci-dessous est toujours à jour : à chaque fois qu'on pousse le projet KiCad
dans `project/ecad/`, le site recopie automatiquement les fichiers et se met à jour
(voir l'étape « Copier les fichiers KiCad » dans `.github/workflows/pages.yml`).

{% include kicad.html src="assets/kicad/projet-maker.kicad_sch" controles="full" hauteur="600px" %}

[📁 Fichiers KiCad]({{ site.gh_edit_repository }}/tree/main/project/ecad){: .btn }

## PCB

Le routage du PCB n'est pas encore commencé. Il s'affichera ici automatiquement dès
que le fichier `.kicad_pcb` sera rempli et poussé.

{% comment %} Enlever les balises comment quand le PCB sera routé :
{% include kicad.html src="assets/kicad/projet-maker.kicad_pcb" controles="full" hauteur="600px" %}
{% endcomment %}

## Nomenclature

| Référence | Composant | Valeur | Empreinte | Quantité |
|---|---|---|---|---|
| U1 | Microcontrôleur Seeed Studio XIAO ESP32S3 | – | `XIAO-ESP32-S3-DIP` | 1 |
| J1 | Connecteur femelle pour l'écran TFT | 1×14, pas 2,54 mm | `PinSocket_1x14_P2.54mm_Vertical` | 1 |
| J2 | Connecteur I2C | 1×4, pas 2,54 mm | `PinHeader_1x04_P2.54mm_Vertical` | 1 |
| J3 | Joystick | – | `Joystick_PTH` (SparkFun) | 1 |
| SW1, SW2 | Bouton poussoir | – | `SW_SPST_B3S-1000` | 2 |
| D1 | LED | rouge | `LED_1206_3216Metric` | 1 |
| C1, C2, C3 | Condensateur | 100 nF | `C_1206_3216Metric` | 3 |
| C4 | Condensateur | 10 µF | `C_1206_3216Metric` | 1 |
| R1 | Résistance | 1 kΩ | `R_1206_3216Metric` | 1 |
| R2, R3 | Résistance | 4,7 kΩ | `R_1206_3216Metric` | 2 |
| R4 | Résistance | 150 Ω | `R_1206_3216Metric` | 1 |
