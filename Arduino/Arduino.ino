#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522

#define RST_PIN  9      // constante para referenciar pin de reset
#define SS_PIN  10      // constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset

byte LecturaUID[4];         // crea array para almacenar el UID leido
byte Card1[4]= {0x3E, 0xB5, 0xBB, 0x32} ;    // UID de tarjeta para validacion 
byte Card2[4]= {0xFA, 0xD4, 0xBC, 0x12} ;    
byte Card3[4]= {0xFE, 0xBD, 0x34, 0xF8} ;
byte Card4[4]= {0x06, 0x7E, 0xA7, 0x45} ;    
byte Card5[4]= {0x32, 0x9C, 0x96, 0x3F} ;
byte Card6[4]= {0x9F, 0x54, 0x84, 0x2C} ;    
byte Card7[4]= {0xFE, 0xBD, 0x34, 0xF8} ; // MISSING CARD m1
byte Card8[4]= {0xFA, 0xD4, 0xBC, 0x12} ; // MISSING CARD m2
byte Card9[4]= {0xFE, 0xBD, 0x34, 0xF8} ; // MISSING CARD m3

void setup() {
  Serial.begin(9600);     // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();     // inicializa modulo lector
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())   // si no hay una tarjeta presente
    return;           // retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial())     // si no puede obtener datos de la tarjeta
    return;           // retorna al loop esperando por otra tarjeta

        
    for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){   // si el byte leido es menor a 0x10
        Serial.print(" 0");       // imprime espacio en blanco y numero cero
        }
        else{      
          Serial.print(" ");        // imprime un espacio en blanco
          }
          Serial.print(mfrc522.uid.uidByte[i], HEX);    // imprime el byte del UID leido en hexadecimal
          LecturaUID[i]=mfrc522.uid.uidByte[i];     // almacena en array el byte del UID leido      
          }
          
          //Serial.print("\t");         // imprime un espacio de tabulacion             
                    
          if(comparaUID(LecturaUID, Card1))    // llama a funcion comparaUID con Card[n]
            Serial.println("1");         // si retorna verdadero envia al serial el string
          else if(comparaUID(LecturaUID, Card2)) 
            Serial.println("2"); 
          else if(comparaUID(LecturaUID, Card3))
            Serial.println("3");
          else if(comparaUID(LecturaUID, Card4))
            Serial.println("4");
          else if(comparaUID(LecturaUID, Card5))
            Serial.println("5");
          else if(comparaUID(LecturaUID, Card6))
            Serial.println("6");
          else if(comparaUID(LecturaUID, Card7))
            Serial.println("7");
          else if(comparaUID(LecturaUID, Card8))
            Serial.println("8");
          else if(comparaUID(LecturaUID, Card9))
            Serial.println("9");
           else           // si no reconoce la tarjeta 
            Serial.println("f");           
            
                  mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta                
}

boolean comparaUID(byte lectura[],byte card[]) // funcion comparar UID
{
  for (byte i=0; i < mfrc522.uid.size; i++){    // bucle recorre de a un byte por vez el UID
  if(lectura[i] != card[i])        // si byte de UID leido es distinto a usuario
    return(false);          // retorna false
  }
  return(true);           // si los 4 bytes coinciden retorna True
}
