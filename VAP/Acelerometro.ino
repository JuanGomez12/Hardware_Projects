#include <math.h>

#define SLP 7 //Defino nombres por si tengo que cambiar los pines usados mas adelante
#define SENSE 6
#define Alarma 8

//Defino los pines para la lectura analogica en x, y, z
#define An0 A3
#define An1 A4
#define An2 A5
#define led 13

double x=0; //Para obtener los grados con decimales, se puede poner int para quitarle los decimales por si no interesan
double xg=0; //Para leer el ADC
double y=0;
double yg=0;
double z=0;
double zg=0;
int n=1; //Control de menus, esta en 1 para el debug

double cuadx=0; //Valores en donde se almacenan las potencias
double cuady=0;
double cuadz=0;
double cuad4=0;

double res1=0; //Valor para almacenar la resultante 1;
double res2=0; //Valor para almacenar la resultante 2;
double angulo=0; //Valor para almacenar el angulo obtenido;




void setup() {
pinMode(SLP,OUTPUT); //Pin para el conector SLEEP
pinMode(SENSE,OUTPUT); //Pin para la seleccion de la sensibilidad (1.5g, 6g)
pinMode(led, OUTPUT);
digitalWrite(SLP, LOW); //Apago acelerometro
digitalWrite(SENSE,LOW); //Configuro sensibilidad a 1.5g
Serial.begin(9600);
delay(50);
}

void loop() {
  while(n=0){
        //Menu principal
        digitalWrite(SLP,LOW); //Apago acelerometro
        
    }
    
  while (n=1){ 
   digitalWrite(led,LOW); //Control de si el acel esta funcionando
   //Para obtener datos y guardarlos
  digitalWrite(SLP, HIGH);//Enciendo acelerometro
  delay(100);
  xg=analogRead(An0); // Uso ADC para encontrar el valor del acelerometro
  delay(50); //Pausa para dejar que el ADC se recupere
  yg=analogRead(An1);
  delay(50);
  zg=analogRead(An2);
  delay(50);
    Serial.println("Valores crudos acelerometro");
    Serial.println(xg);
    Serial.println(yg);
    Serial.println(zg);
    delay(1000);
    
  x=(xg/675)*3.3; //Convierto el valor de analogico a voltaje, en arduino UNO el VRef es 5V, por lo que tenemos que ajustarlo a nuestro maximo de 3.3V del acelerometro.
  x=(x-1.65)/0.8; //Ajuste segun funcionamiento (positivo es en direccion del eje del acelerometro y negativo en el otro eje)
   
  
  
  y=(yg/675)*3.3;
  y=(y-1.65)/0.8;
  
    
  z=(zg/675)*3.3;
  z=(1.65-z)/0.8;
  
  
    
    Serial.println("Valores en G de x, y, z");
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    delay(1000);
    
 //A partir de aqui cambia el codigo dependiendo de como se ubique el dispositivo, asumo eje Y en direccion cabeza-pies del paciente (positivo hacia los pies del paciente), y z en direccion piso-techo (positivo hacia el techo)

 cuadx=x*x;
 cuady=y*y;
 cuadz=z*z;
      
 res1=cuadx+cuadz;
 res1=sqrt(res1);

 res2=y/res1;
 
 //angulo=atan(res2); //Este es el angulo en radianes
 //angulo=angulo*57.3; //Angulo en grados
 angulo=round( atan2 (y, res1) * 180/3.14159265 ); 
 
 Serial.println("Valores resultantes");
 Serial.println(res1);
 Serial.println(res2);
 Serial.println("Angulo");
 Serial.println(angulo);
 delay(1200);
 
  if (angulo<30){
   digitalWrite(Alarma,LOW)
 }
 
 if (angulo>30){
   digitalWrite(Alarma,HIGH)
 }
 
 
 //Analizar si se deben guardar estos datos, y como guardarlos para que no se pierda su fecha/hora
        if (z>0){
            if (z<5){
                digitalWrite(led,HIGH); //Control de si el acelerometro esta funcionando
            delay(100);
          }
        }
 }
    
 while (n=2){
        //Aqui va la lectura de datos guardados
        digitalWrite(SLP,LOW); //Apago acelerometro


    }

 while (n=3){
        //Configuracion de la fecha y hora
        digitalWrite(SLP,LOW); //Apago acelerometro
    }
}
