# Commande Numérique d'une MCC
Projet AEI de Guillaume Baudouin et Rubens Baudoin pour la commande en courant et en tension d'une MCC

###Matériel à disposition:
-Nucléo-G474RE
-Hacheur Microchip dsPICDEM MC1L
-Moteur à courant continu 530W

###Avancement du projet:
-Génération des PWM: OK
-Mise en place de la commande start: OK
-Réglage du rapport cyclique: OK
-Mesure de courant: OK
-Mesure de la vitesse: OK
-Asservissement de la MCC:

##Génération des PWM et première commande de la MCC
Dans cette partie, nous allons:
-Générer les PWM qui permettent la commande en complémentaire du hacheur
-Implémenter des fonctions pour initialiser le hacheur et changer le raport cyclique des PWM

### Configuration du Timer 1:
Pour avoir une commande complémentaire, nous utilisons les channels du timer ainsi:
|channel 1|PWM geneneration CH1 CH1N|
|channel 2|PWM geneneration CH2 CH2N|

Ensuite, nous voulons une fréquence du counter de 16kHz. Le timer étant cadencé à 170MHz cela donne ARR=(170x10^6/16x10^3-1)/2=5312 avec le counter en mode "center align"

##### Counter Settings
![Counter setting](./Images/TIM1_Settings.jpg "Counter setting")

Afin d'éviter que tous les transistors ne conduisent pas en même temps, on introduit un dead time de 2 us et on initialise les PWM avec un rapport cyclique de 50% afin de démarrer avec une vitesse nulle
##### Dead time and PWM Settings
![Dead time and PWM Settings](./Images/TIM1_DT_PWM.jpg "Dead time and PWM Settings")

Nous vérifions notre code sur l'oscilloscope:


##Annexe
Pinout du connecteur Sub-D 37: (Les pins indiqués sur la carte sont faux)
ISO_RESET: pin 33
CMD_Y_TOP: pin 12
CMD_R_TOP: pin 13
CMD_Y_BOT: pin 30 // Sur notre carte les signaux bottom sont décalés d'un cran (31 et 32)
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

esoin