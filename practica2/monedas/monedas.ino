String input = "";
unsigned int monedas[] = {50000,20000,10000,5000,2000,1000,500,200,100,50};
bool calculate = false;
char in;

void calculadora_cambio(int);

void setup() {
  Serial.begin(9600);  
}

void loop() {
  unsigned int cambio = 0;
  while(Serial.available() > 0)
    input = Serial.readStringUntil('\n');
  
  if(input.length() > 0) {
    cambio = input.toInt();
    input = "";
  }

  if(cambio > 0)
    calculadora_cambio(cambio);
}

void calculadora_cambio(unsigned int cambio) {
  Serial.println("A devolver: " + String(cambio));
  for (int i = 0; i < sizeof(monedas)/sizeof(monedas[0]); i++) {
    Serial.println(String(monedas[i]) + ": " + String(cambio/monedas[i]));
    cambio = cambio % monedas[i];
  }
  Serial.println("Restante: " + String(cambio));
}
