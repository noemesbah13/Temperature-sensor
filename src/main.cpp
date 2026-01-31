#include <Arduino.h>
#include <LiquidCrystal.h>
#define Temp A0

/*  L'objectif de ce projet est d'utiliser un capteur de température sur une carte Arduino UNO R3
    pour afficher la température sur un écran LCD 16x2 et envoyer la valeur sur le port série toutes les 5 secondes.
    Le capteur utilisé est un TMP36 qui fournit une tension proportionnelle à la température ambiante.
    Le code lit la valeur analogique du capteur, calcule la température en degrés Celsius,
    l'affiche sur l'écran LCD et l'envoie sur le port série en centièmes de degrés.
*/


LiquidCrystal lcd(10,11,8,7,6,5); // Ecran LCD
int tempRead;   // Variable de la tension lue pour le capteur de température
float tempReal; // Températue réelle calculée
long tpsMillis; // compteur pour la fonction millis()

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);     // Démarrage du LCD 16 caractères sur 2 lignes
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(Temp,INPUT);    // Capteur de température
  lcd.print("Temperature : ");
  tpsMillis=millis();
}


void loop() {
  tempRead=analogRead(Temp);
  tempReal=((tempRead/1024.0)*5.0-0.5)*100;   // Calcul de la température (tkt ça marche)
  // Actualisation de la température affichée toute les 5 secondes
  if (millis()-tpsMillis > 5000) {
    lcd.setCursor(0,1);
    lcd.print(tempReal);  // Affichage de la température
    lcd.print(" C");      // Affichage de l'unité
    tpsMillis=millis();   
    // La température est discrétisée de O à 1023 (valeur lue par l'ADC) pour des tensions de 0 à 5V
    // Le TMP36 donne une tension de 750mV à 25°C et varie de 10mV par degré Celsius
    Serial.println((int)(tempReal*100));   // Envoi de la température sur le port série en centièmes de degrés
  }
}