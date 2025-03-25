#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
void ejercicio_1();
void ejercicio_3();
void ejercicio_5();
void ejercicio_7();
void ejercicio_9();
void ejercicio_11();
void ejercicio_13();
void ejercicio_15();
void ejercicio_17();
void ejercicio_19();
void ejercicio_21();
void ejercicio_23();
void ejercicio_25();
void ejercicio_27();
void ejercicio_29();
void problema_1();
void problema_3();
void problema_5();
void problema_7();
void problema_9();
void problema_11();
void problema_13();
void problema_15();
void problema_17();
int num_divisors(int);
int self_power(int);
int mcd(int, int);
bool is_prime(int);

int main()
{
    problema_5();
    return 0;
}

void ejercicio_1() 
{
    int a, b;
    cout << "Escriba un numero: A\n" << endl;
    cin >> a;
    cout << "Escriba un numero: B\n" << endl;
    cin >> b;
    cout << "A % B = " << a % b << '\n';
}

void ejercicio_3() 
{
    int a, b, mayor;
    cout << "Escriba un numero: A\n" << endl;
    cin >> a;
    cout << "Escriba un numero: B\n" << endl;
    cin >> b;
    if (a > b)
        mayor = a;
    else
        mayor = b;

    cout << "El mayor es: " << mayor << endl;
}

void ejercicio_5() 
{
    float a, b;
    cout << "Escriba un numero: A\n" << endl;
    cin >> a;
    cout << "Escriba un numero: B\n" << endl;
    cin >> b;
    cout << a << "/" << b << "= " << round(a / b) << endl;
}

void ejercicio_7() 
{
    int n;
    int sum = 0;
    while(1) {
        cout << "Cuantos numeros quiere sumar?" << endl;
        cin >> n;
        if (n < 0)
            cout << "Como vas a contar una cantidad negativa de numeros?\n" << endl;
        else
            break;
    }

    for (int i = 0; i <= n; i++)
        sum += i;

    cout << "La sumatoria desde " << 0 << " hasta " << n << " es: " << sum << endl;
}

void ejercicio_9() 
{
    float pi = 3.1416;
    float radio;
    float  perimetro = 0.0;
    float area = 0.0;


    while(1) {
        cout << "Cuánto vale el radio?" << endl;
        cin >> radio;
        if (radio < 0)
            cout << "Como vas a tener un radio negativo? \n" << endl;
        else
            break;
    }

    perimetro = 2.0*pi*radio;
    area = pi*radio*radio;
    cout << "Primetro: " << perimetro << endl;
    cout << "Area: " << area << endl;
}

void ejercicio_11() 
{
    int n;

    cout << "Vamos a hacer la tabla del: " << endl;
    cin >> n;

    for (int i = 0; i <= 10; i++)
        cout << i << "x" << n << "=" << i*n << endl;

}

void ejercicio_13() 
{
    int n;
    cout << "Vamos a encontrar los divisores de: " << endl;
    cin >> n;
    for (int i = 1; i <= n; i++)
        if (n % i == 0)
            cout << i << endl;
}

void ejercicio_15() 
{
    int sum = 0, input = -1;
    while (input != 0) {
        cout << "Escriba un número ó 0 para salir: " << endl;
        cin >> input;
        sum += input;
    }
    cout << "La suma de los números es: " << sum << endl;
}

void ejercicio_17() 
{
    int input = -1, mayor;

    cout << "Escriba un número: " << endl;
    cin >> input;
    mayor = input;

    while (input != 0) {
        cout << "Escriba un número: " << endl;
        cin >> input;
        if (input > mayor)
            mayor = input;
    }
    cout << "El mayor número es: " << mayor << endl;
}

void ejercicio_19() 
{
    int numero = 0;
    cout << "Escriba un número: " << endl;
    cin >> numero;
    
    if (is_prime(numero))
        cout << numero << " es primo" << endl;
    else
        cout << numero <<" no es primo" << endl;
}

void ejercicio_21() 
{
    char c;
    cout << "Escriba un caracter: " << endl;
    cin >> c;
    if (c > 96)
        cout << "Letra convertida: " << (char)(c - 32) << endl;
    else 
        cout << "Letra convertida: " << (char)(c + 32) << endl;
}

void ejercicio_23() 
{
    int a, b;
    cout << "Escriba un número: " << endl;
    cin >> a;
    cout << "Escriba un número: " << endl;
    cin >> b;
    cout << "El MCM de: " << a << " y " << b << " es " << (a*b)/mcd(a, b) << endl;
}

int mcd(int a, int b) 
{
    if (b == 0)
        return a;
    return mcd(b, a % b);
}

void ejercicio_25() 
{
    int n, aux;
    int cnt = 0;

    cout << "Escriba un número: " << endl;
    cin >> n;
    aux = n;

    if (aux == 0)
        cnt = 1;
    
    while (aux != 0) {
        aux /= 10;
        cnt++;        
    }
    cout << "El número " << n << " tiene " << cnt << " digitos" << endl;
}

void ejercicio_27() 
{
    float op1, op2;
    char op;
    cout << "Escriba el primer operando: " << endl;
    cin >> op1;
    cout << "Escriba el segundo operando: " << endl;
    cin >> op2;
    cout << "Escriba la operación: " << endl;
    cin >> op;

    switch (op) {
        case '+':
            cout << op1 << " + " << op2 << " = " << op1 + op2 << endl;
            break;
        case '-':
            cout << op1 << " - " << op2 << " = " << op1 - op2 << endl;
            break;
        case '*':
            cout << op1 << " * " << op2 << " = " << op1 * op2 << endl;
            break;
        case '/':         
            if (op2 == 0)
                cout << "No se puede dividir por 0" << endl;
            else
                cout << op1 << " / " << op2 << " = " << op1 / op2 << endl;
            break;
        default:        
            cout << "Operación no válida" << endl;
            break;
    }
}

void ejercicio_29() 
{
    cout << "Voy a adivinar tu número de 0 a 100" << endl;
    int upper = 100, lower = 0, guess = 50;
    char c;

    while (lower <= upper) {
        cout << "Adivino: " << guess << endl;
        cin >> c;
        switch (c) {
            case '>':
                lower = guess + 1;
                guess = (upper + lower) / 2;
                break;
            case '<':
                upper = guess - 1;
                guess = (upper + lower) / 2;
                break;
            case '=':
                cout << "Adiviné!" << endl;
                return;
            default:
                cout << "Operación no válida" << endl;
                break;
        }
    }

    if (lower > upper)
        cout << "No se puede adivinar" << endl;
}

void problema_1() 
{
    char c;
    cout << "Escriba un caracter: " << endl;
    cin >> c;

    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
        if (c == 65 || c == 69 || c == 73 || c == 79 || c == 85 || c == 97 
           || c == 101 || c == 105 || c == 111 || c == 117)
            cout << "Es una vocal" << endl;
        else
            cout << "Es una consonante" << endl;
    }
    else {
        cout << "No es ninguna de las dos" << endl;
    }
}

void problema_3() 
{
    int day, month;
    cout << "Escriba el día " << endl;
    cin >> day;
    cout << "Escriba el mes " << endl;
    cin >> month;

    if (day < 1 || day > 31)
        cout << day << " es un día inválido" << endl;
    else if (month < 1 || month > 12)
        cout << month << " es un mes inválido" << endl;
    else if (month == 2 && day > 29)
        cout << day << "/" << month << " es una fecha inválida" << endl;
    else if (month == 2 && day == 29)
        cout << day << "/" << month << " es válida en bisiesto" << endl;
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        cout << day << "/" << month << " es una fecha inválida" << endl;
    else
        cout << day << "/" << month << " es una fecha válida" << endl;
}

void problema_5()
{
    int n, blanks, asterisk;
    cout << "Escriba un número: " << endl;
    cin >> n;
    if (n % 2 == 0) {
        cout << n << " debe ser impar" << endl;
        return;
    } else if (n < 0) {
        cout << n << " debe ser positivo" << endl;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        blanks = abs(n/2 - i);
        asterisk = n - 2*blanks;
        for (int j = 0; j < blanks; j++)
            cout << " ";
        for (int j = 0; j < asterisk; j++)
            cout << "*";
        cout << endl;     
    }
}

void problema_7() 
{
    int fib1 = 1, fib2 = 1, sum = 0, fibn = 1, n;
    cout << "Escriba un número: " << endl;
    cin >> n;

    do {
        if (fibn % 2 == 0)
            sum += fibn;
        fibn = fib1 + fib2;
        fib1 = fib2;
        fib2 = fibn;
    } while (fibn < n);
    cout << "La suma de los números pares de la serie de Fibonacci menores a " << n << " es: " << sum << endl;
}

void problema_9()
{
    int sum = 0, num;
    cout << "Escriba un número positivo: " << endl;
    cin >> num;
    if (num < 0) {
        cout << "Debe ser positivo" << endl;
        return;
    }
    while (num != 0) {
        sum += self_power(num % 10);
        num /= 10;
    }
    cout << "La suma de los digitos al cuadrado es: " << sum << endl;
}

void problema_11()
{
    int n = 1, mcm = 1;
    cout << "Escriba un número natural: " << endl;
    cin >> n;
    if (n < 1) {
        cout << "Debe ser un número natural" << endl;
        return;
    }

    for (int i = 2; i <= n; i++)
        mcm = mcm * i / mcd(mcm, i);

    cout << "El MCM de los números del 1 al " << n << " es: " << mcm << endl;
}

void problema_13()
{   
    int sum = 0, n;
    cout << "Escriba un número: " << endl;
    cin >> n;
    for (int i=0; i < n; i++)
        is_prime(i) ? sum += i : sum;
    cout << "La suma de los números primos menores a " << n << " es: " << sum << endl; 
}

void problema_15()
{
    int n = 5, sum = 0;

    cout << "Escriba la dimensión de la espiral: " << endl;
    cin >> n;

    if (n % 2 == 0) {
        cout << "Debe ser impar" << endl;
        return;
    }

    for (int i = 3; i <= n; i+=2)
        sum += 4*i*i - 6*i + 6;
    
    sum += 1;
    cout << "La suma de los números en la diagonal de una espiral de " << n << "x" << n << " es: " << sum << endl;
}

void problema_17()
{
    int num, i, n;
    cout << "Escriba un número: " << endl;
    cin >> num;

    i = 1;
    n = 1;
    while (num_divisors(n) <= num) {
        n = i*(i+1)/2;
        i++;
    }
    cout << "El primer número triangular con más de " << num << " divisores es: " << n << endl;
}

int num_divisors(int n)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (n % i == 0)
            cnt++;
    return cnt;
}

int self_power(int n) {
    int power = n;
    for (int i = 1; i < n; i++)
        power *= n;

    return power;
}

bool is_prime(int n)
{
    if (n == 2)
        return true;

    if (n < 2 || n % 2 == 0)
        return false;
        
    for (int i = 3; i < n; i++) 
        if (n % i == 0) 
            return false;

    return true;
}