#define PLUV 5
int count = 0;

void countPluv(){
    count = count + 1;
    Serial.print("Pulsou ");
    Serial.println(count);
    unsigned long i = millis();
    while (i + 200) > millis());
}

void IRAM_ATTR countPluvFunction() {
    noInterrupts();
    countPluv();
    interrupts();
}

void setup() {
  Serial.begin(115200);
  pinMode(PLUV, INPUT);
  attachInterrupt(digitalPinToInterrupt(PLUV), countPluvFunction, FALLING);
}

void loop() {
 delay(20);
}
