// Incluimos las librerías necesarias para la programación
#include <Stepper.h>
#include <Servo.h> 
#include <HX711.h>  
#include <Wire.h> 
//----------------------------------------------------------
// Definición de pines para los motores Nema 17
#define STEP_PIN 13 
#define DIR_PIN 12
#define STEPRIEL 11
#define DIRRIEL 10
//----------------------------------------------------------

/////////////////////////////-Servo de la caja-//////////////////////////////
Servo myservo;  //creamos un objeto servo 
int angulo;
/////////////////////////////////////////////////////////////////////////////

////////////////////////////PINES DE SENSORES/////////////////////

////////////////////////-Capacitivo e inductivo-////////////////////////////
int capacPin = 7;    // sensor capacitivo *
int inducPin = 6;   // sensor inductivo *
////////////////////////-Óptico-////////////////////////////
int optico=A3;  // *
int dig_optico=4; // *
//////////////////////-Celda de carga-////////////////////////////////
#define DT 2          // DT de HX711 a pin digital 2 *
#define SCK 3         // SCK de HX711 a pin digital 3 *
int rango_peso = 10;
HX711 celda;          // crea objeto con nombre celda

////////////////////////-Ultrasónico-////////////////////////////
int TRIG = 40;      // trigger en pin 5 ultrasonico 
int ECO = 41;      // echo en pin 9 ultrasonico
int DURACION;
int DISTANCIA;
////////////////////////-Fotoeléctrico-////////////////////////////

int pinFotoElectrico = 8;



////////////////////////-Inicializaciones-////////////////////////////

const int stepsPerRevolution = 200;
Stepper MotorFaja(stepsPerRevolution, STEP_PIN, DIR_PIN); // Definición de Motor para la faja
Stepper Motor(stepsPerRevolution, STEPRIEL, DIRRIEL); // Definición de Motor para la faja
int i = 0;
bool lafe = false;

void setup() {
  // SETEO DE VELOCIDADES
  MotorFaja.setSpeed(250); // Seteo de velocidad de Faja
  Motor.setSpeed(1200); // Seteo de velocidad de Riel
  Serial.begin(9600);

  // DECLARACIÓN DE PINES
  pinMode(pinFotoElectrico, INPUT);
  pinMode(dig_optico,OUTPUT);
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(capacPin, INPUT);
  pinMode(inducPin, INPUT);
  myservo.attach(5);  // asignamos el pin 5 al servo.

  // INICIALIZACIÓN DE LA CELDA
  celda.begin(DT, SCK);    // inicializa objeto con los pines a utilizar
  celda.set_scale(443.f);  // establece el factor de escala obtenido del primer programa 1084
  celda.tare();            // realiza la tara o puesta a cero

  int angulo = 0;
}

void loop() {

  myservo.write(angulo);

  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(10);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
            // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  //Serial.println(DISTANCIA);

  float peso = obtenerPesoEnGramos(); // Llama a la función para obtener el peso en gramos
  //Serial.print("Valor (gramos): ");    // texto descriptivo
  //Serial.println(peso, 1);    // muestra el valor obtenido con un decimal

  if (lafe == true) {

    delay(2000);
    int capacitivo = digitalRead(capacPin); // Lectura capacitivo
    int inductivo = digitalRead(inducPin);  // Lectura inductivo

    digitalWrite(dig_optico, HIGH); // Lectura óptico
    delay(5);
    int opt_noise = analogRead(optico);
    digitalWrite(dig_optico, LOW);
    delay(5);
    int noise = analogRead(optico);
    int opt_denoise = -1*(opt_noise - noise);
    Serial.println("optico: ");
    Serial.print(opt_denoise);

    if (inductivo == 0){
      Serial.print("casi metal");
      if (capacitivo == 0){ 
        //metalico
        Motor.step(-2600);
        abrircompuerta();
        Motor.step(2600);
        lafe = false;
        Serial.println("es metal");
      } 
    }
    else{      
      Serial.print("no indc");          
      if (capacitivo == 0){
          Serial.print("capacitivo");
          if(peso>70){
            //Vidrio
            Motor.step(-8500);
            abrircompuerta();
            Motor.step(8500);
            lafe = false;
            Serial.println("vidrio");
          }
          else{
            //Orgánicos u otros
            Motor.step(2800);
            abrircompuerta();
            Motor.step(-2800);
            lafe = false;
            Serial.println("otros");
          }
        }
      else{
        //Plásticos
        if(opt_denoise>100 && opt_denoise<200){
          Motor.step(-14500);
          abrircompuerta();
          Motor.step(14500);
          lafe = false;
          Serial.print("plastico");
        }
        if(opt_denoise>200){
          //Papeles
          Motor.step(-19500);
          abrircompuerta();
          Motor.step(19500);
          lafe = false;
          Serial.print("papel");
        }
        if(opt_denoise>200 || opt_denoise<100){
          Motor.step(2800);
          abrircompuerta();
          Motor.step(-2800);
          lafe = false;
        }
      }
    }
      
  }

  if (lafe == false && DISTANCIA < 20) {
    while (digitalRead(pinFotoElectrico) == LOW) {
      
      while (i < 15) {
        MotorFaja.step(80);
        delay(50);
        MotorFaja.step(-80);
        delay(50);
        
        i++; // Incrementar el contador i en cada iteración
      }
      MotorFaja.step(-1);
      lafe = true;
    }
    i = 0;
  }
}
