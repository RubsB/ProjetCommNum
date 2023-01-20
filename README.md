# Commande Numérique d'une MCC
Projet AEI de Guillaume Baudouin et Rubens Baudoin pour la commande en courant et en tension d'une MCC

### Matériel à disposition
-Nucléo-G474RE
-Hacheur Microchip dsPICDEM MC1L
-Moteur à courant continu 530W

### Avancement du projet
-Génération des PWM: OK
-Mise en place de la commande start: OK
-Réglage du rapport cyclique: OK
-Mesure de courant: OK
-Mesure de la vitesse: OK
-Asservissement de la MCC:

## Génération des PWM et première commande de la MCC
Dans cette partie, nous allons:
-Générer les PWM qui permettent la commande en complémentaire du hacheur
-Implémenter des fonctions pour initialiser le hacheur et changer le raport cyclique des PWM

### Configuration du Timer 1
Pour avoir une commande complémentaire, nous utilisons les channels du timer ainsi:
|Channel|Mode|
|-|-|
|1|PWM geneneration CH1 CH1N|
|2|PWM geneneration CH2 CH2N|

Ensuite, nous voulons une fréquence du counter de 16kHz. Le timer étant cadencé à 170MHz cela donne ARR=(170x10^6/16x10^3-1)/2=5312 avec le counter en mode "center align"

##### Counter Settings
![Counter setting](./Images/TIM1_Settings.jpg "Counter setting")

Afin d'éviter que tous les transistors ne conduisent pas en même temps, on introduit un dead time de 2 us et on initialise les PWM avec un rapport cyclique de 50% afin de démarrer avec une vitesse nulle
##### Dead time and PWM Settings
![Dead time and PWM Settings](./Images/TIM1_DT_PWM.jpg "Dead time and PWM Settings")

Nous vérifions notre code sur l'oscilloscope:

##### Mesures sur l'oscilloscope
![Mesures sur l'oscilloscope](./Images/Oscillo.jpg "Mesures sur l'oscilloscope")

On vérifie que la fréquence, le temps mort et les rapports cycliques sont corrects. 

Sur l'écran on aperçoit aussi une impulsion de 2 us qui correspond à la commande start que l'on va détailler ci-dessous:

### Fonctions de commande simple

Pour reset le hacheur et ses capteurs, il faut lui envoyer une impulsion d'au moins 2 us sur le pin ISO_RESET.
On le réalise avec la fonction motorPowerOn:
##### motorPowerOn
![motorPowerOn](./Images/PowerOn.jpg "motorPowerOn")

Une fois le hacheur initialisé, on créé une fonction qui permet de changer la valeur du rapport cyclique des PWM:
L'argument en entrée doit être compris entre 0 et 100, il y a donc une vérification avant de changer la valeur des rapports cycliques de la sorte:

##### setDutyCycle
![setDutyCycle](./Images/Alpha.jpg "setDutyCycle")

## Connection du hacheur et démarrage de la MCC
Nous nous connectons aux bras Yellow et Red du hacheur car ils posèdent des capteurs à effet hall, utiles pour la suite.

|Signal|Pin du SubD-37|
|-|-|
|ISO_RESET|pin 33|
|CMD_Y_TOP|pin 12|
|CMD_R_TOP|pin 13|
|CMD_Y_BOT|pin 30|
|CMD_R_BOT|pin 31|

Maintenant nous appelons les fonctions à l'aide de commandes shell pour interragir dynamiquement avec le moteur. 
Puisque il n'est pas asservi, lors d'un changement de rapport cyclique trop brusque le hacheur se met en défaut.
Nous décidons alors d'ajouter une ligne à la commande "motorPowerOn" qui remet le rapport cyclique à 50% (Vitesse nulle) et commençons à mettre en place l'asservissement:

## Asservissement de la MCC

Pour réaliser l'asservissement, nous devons traiter les retours capteurs de courants dans un premier temps puis la vitesse.

### Boucle de courant
Nous utilisons l'ADC1,cadencé à 160kHz par le Timer 2 pour mesurer le courant. Les données lues par l'ADC vont être traîtées par des requêtes DMA afin d'optimiser le transfert des données sans charger le CPU.


## Annexe
Pinout du connecteur Sub-D 37: (Les pins indiqués sur la carte sont faux)
ISO_RESET: pin 33
CMD_Y_TOP: pin 12
CMD_R_TOP: pin 13
CMD_Y_BOT: pin 30 
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