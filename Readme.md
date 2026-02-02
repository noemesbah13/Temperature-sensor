# Temperature sensor

Ce projet lit la température avec un capteur TMP36 connecté à l'entrée analogique [`Temp`](src/main.cpp) (A0), l'affiche sur un écran LCD 16x2 et envoie la valeur sur le port série toutes les 5 secondes.

Fichiers clés :
- Code principal : [src/main.cpp](src/main.cpp)
- Réception / envoi Google Sheets : [src/main.py](src/main.py)
- Affichage web : [src/temp.html](src/temp.html)
- Librairie LCD : [`LiquidCrystal`](.pio/libdeps/uno/LiquidCrystal/src/LiquidCrystal.h)

Résumé du fonctionnement (dans [`setup()`](src/main.cpp) et [`loop()`](src/main.cpp)) :
- Initialisation de la liaison série (`Serial.begin(9600)`) et du LCD (`lcd.begin(16, 2)`).
- Le LCD est déclaré par `LiquidCrystal lcd(10,11,8,7,6,5)` (broches de contrôle et données).
- À chaque itération, on lit la valeur ADC via `analogRead(Temp)` et on calcule la température :
  - Formule utilisée : `tempReal = ((tempRead/1024.0)*5.0 - 0.5) * 100`
  - Contexte : ADC 0–1023 pour 0–5V, TMP36 ≈ 750 mV à 25 °C et ≈ 10 mV/°C.
- Mise à jour de l'affichage LCD toutes les 5 secondes (contrôle via [`tpsMillis`](src/main.cpp)).
- Envoi série : `Serial.println((int)(tempReal*100));` — la valeur envoyée est un entier en centièmes de degrés (ex. `2345` → 23.45 °C). Le script [src/main.py](src/main.py) lit ces valeurs et peut les poster vers Google Sheets.

Variables importantes (dans [src/main.cpp](src/main.cpp)) :
- [`Temp`](src/main.cpp) — pin analogique du capteur (A0).
- [`tempRead`](src/main.cpp) — valeur brute ADC.
- [`tempReal`](src/main.cpp) — température calculée en °C.
- [`tpsMillis`](src/main.cpp) — temporisation pour la mise à jour toutes les 5 s.