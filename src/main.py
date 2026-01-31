import serial
import requests
import time

# --- CONFIGURATION ---
arduino_port = 'COM4'  # À vérifier
baud_rate = 9600
# VOTRE URL DE SCRIPT GOOGLE (assurez-vous d'avoir redéployé et mis la nouvelle URL si elle a changé)
google_script_url = "https://script.google.com/macros/s/AKfycbwBpK1SKRkSTubfJKIVzRvNed7-d2069KmHfaYMd3jRtODUed3jG6A98LDoIcI2rtHh-g/exec" 
# ---------------------

try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Connecte a {arduino_port}")
    time.sleep(2)

    while True:
        temps=time.time()
        if ser.in_waiting > 0:
            # Lire la ligne (la température) et nettoyer les espaces/retours à la ligne
            line = ser.readline().decode('utf-8').rstrip()
            
            if line:
                print(f"Temperature reçue de l'Arduino: {line}")
                
                # Plus besoin de split ou de try/catch complexe pour le format
                payload = {'temperature': line}
                
                try:
                    requests.get(google_script_url, params=payload)
                    print(" -> Envoyé au Sheet avec succès")
                except requests.exceptions.RequestException as e:
                    print(f" -> Erreur de connexion : {e}")
                    while dec<5:pass
        dec=time.time()-temps
        
                    
except KeyboardInterrupt:
    print("Arrêt du script.")
    if 'ser' in locals() and ser.is_open:
        ser.close()