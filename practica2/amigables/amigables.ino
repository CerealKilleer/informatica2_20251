unsigned int suma_divisores(unsigned int);
void procesar_entrada(int);
bool get_int();
String num_input = "";

void setup() {
  Serial.begin(115200);
  Serial.println("Ingrese el  número: ");  
}

void loop() {
    unsigned int numero = 0;
    if(get_int()) {
      numero = num_input.toInt();
      num_input = "";
    }
      
    if (numero > 0) {
      procesar_entrada(numero);
    }
}

bool get_int() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c >= '0' && c <= '9') {
      num_input += c;
    }
    else if (c == '\n') {
      return true;
    }
  }
  return false;
}

void procesar_entrada(int numero) {
  unsigned int divisores_b, divisores_3, suma_total;  
  suma_total = 0;
  if(numero > 0) {
      for (unsigned a=1; a < numero; a++) {
          unsigned b = suma_divisores(a);
          if (a == b || b >= numero)
              continue;
          divisores_b = suma_divisores(b);
          if (a == divisores_b)
              suma_total += a;
      }
    }
    Serial.print("El resultado de la suma es: ");
    Serial.println(suma_total);
}

unsigned int suma_divisores(unsigned int numero) {
    unsigned int suma = 0;
    for (unsigned int i = 1; i <= numero/2; i++)
        if (!(numero % i))
            suma += i;
    return suma;
}
