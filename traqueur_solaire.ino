/*
  Fabrication d'un traqueur solaire biaxial.
  Le traqueur solaire est libre de tourner dans
  deux dimensions. Il y a un servo moteur pour
  le tangage (yaw) et un autre servo moteur
  pour le lacet (pitch). 

  Le prototype est équipé de 4 LDR (Light 
  dependent resistor). Les LDRs sont séparées
  par un diviseur en forme de croix. IL y a 
  une LDR sur chacun des cadrans. 
*/

#include <Servo.h>
Servo tangage;           // Rotation autour de l'axe des z 
int tangage_max = 180;   
int tangage_min = 0;
int tangage_act = 90;    // tangage actuel (90 = tangage initiale)

Servo lacet;
int lacet_max = 90;      // Balayage vertical 
int lacet_min = 30;
int lacet_act = 60;     

// Position des LDRs sur l'arduino
int ldr_haut_droite = A0;
int ldr_haut_gauche = A1;
int ldr_bas_gauche = A2;
int ldr_bas_droite = A3; 

void setup() {
  Serial.begin(9600);
  tangage.attach(9);
  tangage.write(90);    // Positionnement initial autour de l'axe des z
  lacet.attach(10);
  lacet.write(60);      // Postionnement vertical initial
  delay(500);
}

void loop() {
  // Pour avoir une indication de l'intensité 
  // lumineuse sur chaque capteur
  int cadran1 = analogRead(ldr_haut_droite);
  int cadran2 = analogRead(ldr_haut_gauche);
  int cadran3 = analogRead(ldr_bas_gauche);
  int cadran4 = analogRead(ldr_bas_droite);

  Serial.print("Haut droit : ");
  Serial.print(cadran1);
  Serial.print("\n");
  Serial.print("Haut gauche : ");
  Serial.print(cadran2);
  Serial.print("\n");
  Serial.print("Bas gauche : ");
  Serial.print(cadran3);
  Serial.print("\n");
  Serial.print("Bas droit : ");
  Serial.print(cadran4);
  Serial.print("\n");
  Serial.print("---------------------------");
  Serial.print("\n");
  // Modification du tangage
  int intensite_droite = cadran1 + cadran4;
  int intensite_gauche = cadran2 + cadran3;
  int diff_t = abs(intensite_droite - intensite_gauche);
  int tolerance_t = 60;                            // Tolérance de la différence pour éviter de surcharger le servo (ajustable)
  
  if((intensite_droite > intensite_gauche) & (diff_t > tolerance_t)){  
    if(tangage_act > tangage_min);
      tangage_act -= 1;                                       // Modification de 1 degré (ajustable)
    }
  if((intensite_droite < intensite_gauche) & (diff_t > tolerance_t)){
    if(tangage_act < tangage_max);
      tangage_act += 1;                                       // Modification de 1 degré (ajustable)
    }
  tangage.write(tangage_act);

  // Modification du lacet
  int intensite_haut = cadran1 + cadran2;
  int intensite_bas = cadran3 + cadran4;
  int diff_lac = abs(intensite_haut - intensite_bas);
  int tolerance_lac = 60;                       // Tolérance de la différence pour éviter de surcharger le servo (ajustable)
  
  if((intensite_haut > intensite_bas) & (diff_lac > tolerance_lac)){
    if(lacet_act > lacet_min);
      lacet_act -= 1         ;                               // Modification de 1 degré (ajustable)
    }
    
  if((intensite_haut < intensite_bas) & (diff_lac > tolerance_lac)){
    
    if(lacet_act < lacet_max);
      lacet_act += 1;                                        // Modification de 1 degré (ajustable)
    }
  lacet.write(lacet_act);
  delay(10);
}
