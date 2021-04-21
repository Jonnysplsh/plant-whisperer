/* Definitions */

// SOUND SENSOR definitions

const int OUT_PIN = 8;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

// CO2 SENSOR Definitions

const int pwmpin = 7;
const int range = 5000;

/*________________________________________________*/

// The setup()-function

void setup() {

    pinMode(pwmpin, INPUT);
    Serial.begin(9600)
}

// The loop()-function
void loop() {

  // __SOUND SENSOR Seriel plotter definitions__
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

    if (digitalRead(OUT_PIN) == HIGH) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }

    /*________________________________________________*/

  // __CO2 SENSOR defintions__  
  int ppm_pwm = readCO2PWM();

  // Ausgabe der Werte über die serielle USB-Verbindung
  
  Serial.print("PPM PWM: ");
  Serial.println(ppm_pwm);

  // Messungen alle 3 Sekundn
  
  delay(2000);
  
  /*________________________________________________*/

  if (sampleBufferValue > 50 && ppm_pwm > 800){
      
  }
}

int readCO2PWM() {

  // Es werden die für die Umrechnung der Zeitdauer auf
  // die PPM-Werte benötigten Variablen definiert.
  // Da es sich bei th um große Werte handeln kann - die verwendete
  // Arduino-Funktion gibt Mikrosekunden zurück - wird diese Variable
  // als vorzeichenlose (unsigned) große Ganzzahl (long) definiert.
  
  unsigned long th;
  int ppm_pwm = 0;
  float pulsepercent;

  // Alles, was in der do ... while-Schleife steht, wird
  // solange ausgeführt, bis der Ausdruck nach while, hier
  // th == 0 als zutreffend (wahr) erkannt wird.
  // Da die Arduino-Funktion pulseIn() 0 zurückgibt, solange
  // sie am Messen ist, dient die Schleife dazu, auf den
  // Messwert zu warten.
  
  do {

    // pulseIn gibt die Dauer des am Pin (pwmpin) anliegenden
    // Signals in Mikrosekunden an. Die maximale Signallänge ist
    // 1004ms. Der Timeoutwert der pulseIn-Funktion muss also
    // mindestens 1004000µs betragen. Für ungünstige Fälle wird
    // sicherheitshalber ein größerer Wert von 2500000µs gewählt.
    // Die Ausgabe der pulseIn()-Funktion wird durch 1000 geteilt
    // und ergibt so für th die Signallänge in Millisekunden (ms).
    
    th = pulseIn(pwmpin, HIGH, 2500000) / 1000;

    // Pulslänge in Prozent (%)

    float pulsepercent = th / 1004.0;

    // PPM-Werte bei gegebenem Range
    
    ppm_pwm = range * pulsepercent;
    
  } while (th == 0);
  
  // Der gemessene Wert wird an die loop()-Funktion zurückgegeben,
  // wo er dann ausgegeben wird.
  
  return ppm_pwm; 
}