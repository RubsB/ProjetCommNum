# ProjetCommNum
Projet AEI en Commande numérique de Guillaume Baudouin et Rubens Baudoin pour la commande d'une MCC

Avencement du projet:

PWM: OK
Commande start: OK
Réglage du rapport cyclique: OK


Pinout du connecteur Sub-D 37: (Les pins indiqués sur la carte sont faux)
ISO_RESET: pin 33
CMD_Y_TOP: pin 12
CMD_R_TOP: pin 13
CMD_Y_BOT: pin 30 // Sur notre carte les signaux bottom sont decale d'un cran (31 et 32)
CMD_R_BOT: pin 31 

Mise en route du hacheur:

Commande “start” ou power up sequence:
-Mise sous tension de la carte de commande au préalable connectée au hacheur
-Mise sous tension de l’alimentation DC du hacheur
-"power on" Reset système avec un signal haut sur la ligne ISO-RESET. 

Power down sequence:
-Couper l’alimentation DC du hacheur
-Attendre 5 min le temps que la LED du bus DC s'éteigne
-Couper l’alimentation de la carte si besoin