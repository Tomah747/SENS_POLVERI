# SENS_POLVERI  
Il programma SENS_POLVERI,serve per la misurazione della concentrazione numerica delle polveri(Da 10μm a 1μm in un cm cubo)tramite un sensore Sensirion, modello SPS30,e riportarle,tramite scheda wireless ESP32,sul server di BLYNK.com che provedera allo storing,al processing e all'interfecing dei sudetti dati su APP BLYNK.
Si nota che per lo svolgimento del programma OPEN-SOURCE vi è bisogno dell'app BLYNK versione OLD,già configurata,perchè richiede codici di autenticazione generati dall'app.
Inoltre,si può osservare,viste le carateristiche del sensore,che esso possa misurare i PNC o Particle Number Concentration da 0.5μm a 10 μm per cm3, i PM o Particle Matter da 1.0μm a 10μm per cm3,e la grandezza media di una particella.
Il programma prende i dati dal sensore tramite questo comando: "m.nc_10p0" specificamente,esso,va a richiedere la quantità di PNC,di grandezza 10μm,nell'aria analizzata.
Se si vuole mandare al server i dati dei PM,invece che dei NPC(ATTENZIONE! è necessario fare alcune modifiche per la ricezione dei PM all'APP BLYNK),modificare i seguenti comandi (Riga 81 a 84) nel programma:

    a = m.nc_1p0; //Copio valore delle polveri PNC 1.0 ricevuto dal sensore nello spazio di memoria "a";
    b = m.nc_2p5; //Copio valore delle polveri PNC 2.5 ricevuto dal sensore nello spazio di memoria "b";
    c = m.nc_4p0; //Copio valore delle polveri PNC 4.0 ricevuto dal sensore nello spazio di memoria "c";
    d = m.nc_10p0; //Copio valore delle polveri PNC 10.0 ricevuto dal sensore nello spazio di memoria "d";
    
Modificati in:

    a = m.mc_1p0; //Copio valore delle polveri PM 1.0 ricevuto dal sensore nello spazio di memoria "a";
    b = m.mc_2p5; //Copio valore delle polveri PM 2.5 ricevuto dal sensore nello spazio di memoria "b";
    c = m.mc_4p0; //Copio valore delle polveri PM 4.0 ricevuto dal sensore nello spazio di memoria "c";
    d = m.mc_10p0; //Copio valore delle polveri PM 10.0 ricevuto dal sensore nello spazio di memoria "d";
    
  Dopodichè compilare e caricare il programma nel M5-Stack-Basic.
  P.S.In caso si vogliano vedere tutti i dati descritti finora,aprire il monitor seriale,in Arduino IDE,(Icona a forma di lente di ingrandimento in alto a destra)in cui verrano     elencati ogni 2 secondi tutti i dati raccolti.(ATTENZIONE!Il monitor seriale non funzionera se il microcontrollore è staccato dalla porta USB)
