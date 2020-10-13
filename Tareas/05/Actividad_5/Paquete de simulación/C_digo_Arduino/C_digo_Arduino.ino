int LED0 = 22;
int LED1 = 23;
int LED2 = 24;
int PULSADOR0 =18;
int PULSADOR1 =19;
int PULSADOR2 =20;
volatile int estado0 = HIGH;
volatile int estado1 = HIGH;
volatile int estado2 = HIGH;
int dato0= 0;

void setup(){
  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (PULSADOR0, INPUT);
  pinMode (PULSADOR0, INPUT);
  pinMode (PULSADOR0, INPUT);
  digitalWrite (LED0, estado0);
  digitalWrite (LED1, estado1);
  digitalWrite (LED2, estado2);
  attachInterrupt (digitalPinToInterrupt(PULSADOR0), manejadorPulsador0, FALLING);
  attachInterrupt (digitalPinToInterrupt(PULSADOR1), manejadorPulsador1, FALLING);
  attachInterrupt (digitalPinToInterrupt(PULSADOR2), manejadorPulsador2, FALLING);
}

void manejadorPulsador0(){
  estado0 = !estado0;
  dato0 = 1;
}
void manejadorPulsador1(){
  estado1 = !estado1;
}
void manejadorPulsador2(){
  estado2 = !estado2;
}

void loop (){
  digitalWrite(LED0, estado0);
  digitalWrite(LED1, estado1);
  digitalWrite(LED2, estado2);
  /*if (dato0 == 0){
    estado0 = !estado0;
  }*/
}
