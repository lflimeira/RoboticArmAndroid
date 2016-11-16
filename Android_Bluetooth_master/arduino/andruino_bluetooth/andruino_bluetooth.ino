/**
 * =========================================================================
 *
 * App: Andruino
 * Versão: 0.0.1
 * Data: 23 de julho de 2015
 * Developer: Rodrigues F. A. S.
 *
 * ======================================================================*/

 #include <Thread.h>
 #include <ThreadController.h>

 /* Declara uma thread "raiz" um controle que agrupa as thread's filhas.. */
 ThreadController cpu;
 Thread threadRecebeDadosandroid;

 /* Pino que conecta os pinos do LED RGB. */
 const int VERMELHO = 10;
 const int VERDE = 9;
 const int AZUL = 11;

 /* Tempo de cor de transição. */
 const int delayTime = 10;

 /* Definição de variáveis globais. */
 int ValVermelho = 0;
 int ValAzul = 0;
 int ValVerde = 0;

 boolean separador = false;
 const uint8_t BUFFER = 15;
 char dispositivo[BUFFER];
 uint8_t tamDispositivo = 0;
 char valor[5];
 uint8_t tamValor = 0;
 int aux = 0;

/**
 * setup -
 */
 void setup() {
  /* Inicia uma comunicação serial com uma taxa de 9600, para comunicação via Bluetooth.. */
  Serial.begin(9600);

  /* Define o pino digital como saída. */
  pinMode(VERDE, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERMELHO, OUTPUT);

  threadRecebeDadosandroid.setInterval(15);
  threadRecebeDadosandroid.onRun(recebeDadosAndroid);

  /* Adiciona as thread's filhas a thread raiz ou mãe.. */
  cpu.add(&threadRecebeDadosandroid);
}

/**
 * loop -
 */
 void loop() {
  /* Start a thread raiz.. */
  cpu.run();
}

/**
 * recebeDadosAndroid -
 */
 void recebeDadosAndroid() {
  if(Serial.available()) { /* Enquanto houverem bytes disponíveis; */
    char c = Serial.read(); /* Lê byte do buffer serial; */
    
    if (c == '\n') {
      if (tamDispositivo == 0) return;
      dispositivo[tamDispositivo] = 0;
      tamDispositivo = 0;

      valor[tamValor] = 0;
      tamValor = 0;

      aux = atoi(valor);
      separador = false;
      
      if (!strcmp(dispositivo, "led_on") && !strcmp(valor, "1")) led_on();
      else if (!strcmp(dispositivo, "led_off") && !strcmp(valor, "0")) led_off();
      else if (!strcmp(dispositivo, "seekBarR")) analogWrite(VERMELHO, ValVermelho = aux);
      else if (!strcmp(dispositivo, "seekBarG")) analogWrite(VERDE, ValVerde = aux);
      else if (!strcmp(dispositivo, "seekBarB")) analogWrite(AZUL, ValAzul = aux);
      else if (!strcmp(dispositivo, "demoRGB")) demoRGB();
    }
    else if (tamDispositivo < BUFFER - 1) { // Verifica, separa e incrementa os dados.
      if(c != '+' && separador == false){
        dispositivo[tamDispositivo] = c;
        tamDispositivo++;        
      }
      else if(c == '+'){
        separador = true;
      } 
      else {
        valor[tamValor] = c;
        tamValor++;
      }
    }
  }
}

/**
 * led_on -
 */
 void led_on() {
  digitalWrite(VERDE, HIGH); digitalWrite(AZUL, HIGH); digitalWrite(VERMELHO, HIGH);
}

/**
 * led_off -
 */
 void led_off() {
  digitalWrite(VERDE, LOW); digitalWrite(AZUL, LOW); digitalWrite(VERMELHO, LOW);
}

 /**
  * demoRGB - 
  */
  void demoRGB(){
    /** 
  * ==============================================
  * Variação de VERDE para VERMELHO
  * ================================= 
  */
  int ValVermelho = 255;
  int ValAzul = 0;
  int ValVerde = 0;

  for(int i = 0 ; i < 255 ; i += 1) {
    ValVerde += 1;
    ValVermelho -= 1;

    /** 
     * Em cada ciclo de diferença 
     * 255 - ValVerde Redução 
     * 255 - ValVermelho Aumenta
     * Calsando uma transição gradual de VERDE para VERMELHO 
     */

     analogWrite( VERDE, 255 - ValVerde );  
     analogWrite( VERMELHO, 255 - ValVermelho );

     /* Aguardando para perceber cor */
     delay( delayTime );
  } // FIM for

/** 
  * ==============================================
  * Variação de AZUL para VERDE
  * ================================= 
  */

  ValVermelho = 0;  
  ValAzul = 0;  
  ValVerde = 255;

  for(int i = 0 ; i < 255 ; i += 1){
    ValAzul += 1;  
    ValVerde -= 1;

    /** 
     * Em cada ciclo de diferença 
     * 255 - ValAzul Redução 
     * 255 - ValVerde Aumenta 
     * Calsando uma transição gradual de AZUL para VERDE.
     */

     analogWrite( AZUL, 255 - ValAzul );  
     analogWrite( VERDE, 255 - ValVerde );

     /* Aguardando para perceber cor */
     delay( delayTime );  
   }  

/** 
  * ==============================================
  * Variação de VERMELHO para AZUL
  * ================================= 
  */ 
  ValVermelho = 0;  
  ValAzul = 255;  
  ValVerde = 0;  
  
  for( int i = 0 ; i < 255 ; i += 1 ){  
    ValVermelho += 1;  
    ValAzul -= 1;

    /**
     * Em cada ciclo de diferença 
     * 255 - ValVermelho Redução 
     * 255 - ValAzul Aumenta 
     * Calsando uma transição gradual de VERMELHO para AZUL.
     */
     analogWrite( VERMELHO, 255 - ValVermelho );  
     analogWrite( AZUL, 255 - ValAzul );

     /* Aguardando para perceber cor */
     delay( delayTime );  
   }  
 }

