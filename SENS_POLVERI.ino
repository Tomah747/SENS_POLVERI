/*******************************************************************
 * 
 *        INIZIO PROGRAMMA E DICHIARAZIONE LIBRERIE AGGIUNTIVE
 * 
*******************************************************************/
#define BLYNK_PRINT Serial  //Libreria per applicazione BLYNK.
#include <WiFi.h> //Libreria per protocollo WI-FI.
#include <WiFiClient.h> //Libreria per protocollo WI-FI_CLIENT.
#include <BlynkSimpleEsp32.h> //Libreria per applicazione BLYNK con ESP32.
#include <sps30.h> //Libreria per sensore di polvere sensirion Modello SP30.
float a; //Variabile per polveri PM 1.
float b; //Variabile per polveri PM 2.5.
float c; //Variabile per polveri PM 4.0.
float d; //Variabile per polveri PM 10.0.
/********************************************************
 * 
 *             IMPOSTAZIONI WI-FI
 * 
********************************************************/
char auth[] = "AUTH"; //Codice di autenticazione APP BLYNK.
char ssid[] = "SSID"; //Nome del WI-FI a cui ci stiamo connettendo. 
char pass[] = "PASSWORD"; //Password del WI-FI a cui ci stiamo connettendo.
/*********************************************************
 * 
 *             FINE IMPOSTAZIONI WI-FI
 *             
**********************************************************/
BlynkTimer timer; //Funzione per app BLYNK.
void setup()
{
  Serial.begin(9600); //Inizio comunicazione seriale tra pc e ESP32.
  Blynk.begin(auth, ssid, pass); //Inzio connessione con i server tramite WI-FI.
  int16_t ret; //Settaggio variabile.
  uint8_t auto_clean_days = 4; //Settaggio tempo di pulitura del sensore ogni 4 giorni.
  uint32_t auto_clean; //Settaggio tempo di pulitura del sensore ogni 4 giorni.
  sensirion_i2c_init(); //Inizio protocollo I2C per parlare con il sensore Sensirion SP30.
  //FUNZIONE PER LA VERIFICA DELLA CORRETTA INSERZIONE DEI PIN.
  while (sps30_probe() != 0) {
    Serial.print("SENSORE NON COLLEGATO CORRETAMMENTE\n");
    delay(500);
  }
  sps30_set_fan_auto_cleaning_interval_days(auto_clean_days); //Settaggio tempo di pulitura del sensore ogni 4 giorni.
  sps30_start_measurement(); //Iniziazzazione sensore.
  timer.setInterval(1000L, sendSensor); //Funzione per app BLYNK per determinare tempo di invio dati.
}
void loop()
{  
  struct sps30_measurement m; //Settaggio variabile.
  char serial[SPS30_MAX_SERIAL_LEN]; //Settaggio variabile.
  uint16_t data_ready; //Settaggio variabile.
  int16_t ret; //Settaggio variabile.
  sps30_read_measurement(&m); //Inizo lettura sensore.
    // STAMPO SUL MONITOR SERIALE LA MASSA DI PARTICELLE PER SCALA DI GRANDEZZA CRESCENTE.
    Serial.print("PM  1.0: "); //Stampa sul monitor seriale "PM  1.0:".
    Serial.println(m.mc_1p0); //Stampa sul monitor seriale il valore di massa del particolato spesso 1.0μm in un cm3.
    Serial.print("PM  2.5: "); //Stampa sul monitor seriale "PM  2.5:".
    Serial.println(m.mc_2p5); //Stampa sul monitor seriale il valore di massa del particolato spesso 2.5μm in un cm3.
    Serial.print("PM  4.0: "); //Stampa sul monitor seriale "PM  4.0:".
    Serial.println(m.mc_4p0); //Stampa sul monitor seriale il valore di massa del particolato spesso 4.0μm in un cm3.
    Serial.print("PM 10.0: "); //Stampa sul monitor seriale "PM 10.0:".
    Serial.println(m.mc_10p0); //Stampa sul monitor seriale il valore di massa del particolato spesso 10.0μm in un cm3.
/*******************************************************************************************************************    
 *     
 *     STAMPA SUL MONITOR SERIALE IL NUMERO DI PARTICELLE PER SCALA DI GRANDEZZA CRESCENTE.
 *     
*******************************************************************************************************************/    
    Serial.print("NC  0.5: "); //Stampa sul monitor seriale "NC  0.5:".
    Serial.println(m.nc_0p5); //Stampa sul monitor seriale il numero di particolato spesso 0.5μm in un cm3.
    Serial.print("NC  1.0: "); //Stampa sul monitor seriale "NC  1.0:".
    Serial.println(m.nc_1p0); //Stampa sul monitor seriale il numero di particolato spesso 1.0μm  in un cm3.
    Serial.print("NC  2.5: "); //Stampa sul monitor seriale "NC  2.5:".
    Serial.println(m.nc_2p5); //Stampa sul monitor seriale il numero di particolato spesso 2.5μm in un cm3.
    Serial.print("NC  4.0: "); //Stampa sul monitor seriale "NC  4.0:".
    Serial.println(m.nc_4p0); //Stampa sul monitor seriale il numero di particolato spesso 4.0μm in un cm3.
    Serial.print("NC 10.0: "); //Stampa sul monitor seriale "NC 10.0:".
    Serial.println(m.nc_10p0); //Stampa sul monitor seriale il numero di particolato spesso 10.0μm in un cm3.
    Serial.print("Sezione media di una particella: "); //Stampa sul monitor seriale "Sezione media di una particella:".
    Serial.println(m.typical_particle_size); //Stampa sul monitor seriale il valore medio di spessore del particolato.
    Serial.println(); //Torna a capo.
  //COPIO VALORI NEGLI SPAZI DI MEMORIA.
    a = m.nc_1p0; //Copio valore delle polveri PNC 1.0 ricevuto dal sensore nello spazio di memoria "a";
    b = m.nc_2p5; //Copio valore delle polveri PNC 2.5 ricevuto dal sensore nello spazio di memoria "b";
    c = m.nc_4p0; //Copio valore delle polveri PNC 4.0 ricevuto dal sensore nello spazio di memoria "c";
    d = m.nc_10p0; //Copio valore delle polveri PNC 10.0 ricevuto dal sensore nello spazio di memoria "d";
  delay(1000); //Aspetta 1 secondo.
  Blynk.run(); //Funzione per app BLYNK.
  timer.run(); //Funzione per app BLYNK.
}
/**********************************************************************************************************************
 * 
 *                       FUNZIONE PER INVIARE I DATI ALL'APP BLYNK.
 * 
**********************************************************************************************************************/
void sendSensor()
{

  Blynk.virtualWrite(V9,a); //Valore delle polveri PM 1.0 ricevuto dal sensore nello spazio di memoria "a" viene mandato all'app sottoforma di pin virtuale "V9".
  Blynk.virtualWrite(V10,b); //Valore delle polveri PM 2.5 ricevuto dal sensore nello spazio di memoria "b" viene mandato all'app sottoforma di pin virtuale "V10".
  Blynk.virtualWrite(V11,c); //Valore delle polveri PM 4.0 ricevuto dal sensore nello spazio di memoria "c" viene mandato all'app sottoforma di pin virtuale "V11".
  Blynk.virtualWrite(V12,d); //Valore delle polveri PM 10.0 ricevuto dal sensore nello spazio di memoria "d" viene mandato all'app sottoforma di pin virtuale "V12".
}
/***********************************************************************************************************************************************************************
 * 
 *                                FINE PROGRAMMA
 * 
*************************************************************************************************************************************************************************/
