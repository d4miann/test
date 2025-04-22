#include <Arduino.h>
#define BOT1 ((PINB >> PB1) & 0x01)
#define ON 1
#define OFF 0
volatile uint64_t multiplicador;
int8_t cont = 0;
uint64_t tiempo = 0;
typedef enum combinaciones
{
  SEC0 = 0,
  SEC1,
  SEC2,
  SEC3
} combinaciones_t;

typedef enum estadobot
{
  UP = 0,
  BAJANDO,
  DOWN,
  RISINg
} estadobot_t;

void MDE_BOT1(void)
{
  switch (estadobot)
  {
  case UP:
    if (BOT1 == OFF)
    {
      estadobot = BAJANDO; // verifico que no sea un falso contacto con la espera
      tiempo = 20;
    }
    break;

  case BAJANDO:
    if (BOT1 == ON)
    {
      estadobot = UP; // vuelve al primer estado si se solto el boton
    }
    if (tiempo == 0 && BOT1 == OFF)
    {
      estadobot = DOWN; // si el tiempo ya decremento pasa al sig estado
    }
    break;

  case DOWN:
    if (BOT1 == ON)
    {
      estadobot = RISINg; // revive el tiempo y pasa al estado sig si se suelta
      tiempo = 20;
    }


    break;

    if (BOT1 == ON)
    {
      estadobot = RISINg;
      tiempo = 20;
    }

    break;

  case RISINg:
    if (BOT1 == ON)
    {
      estadobot = UP; // si se solto y el tiempo es 0 vuelve a up
    }

    if (BOT1 == OFF && tiempo == 0)
    {
      estadobot = DOWN;
    }

    break;

  default:
    estadobot = UP; // por si ocurre algo inesperado se reinicia la mde
  }
}

void ritmo (void)
{
  switch (combinaciones)
  {
  case SEC0:
  if (cont = 0)
  {
    PORTB |=(cont & 0X1F);
  }
  
    
    break;
  case SEC1:
  if (cont>3 || 0>cont)
  {
      PORTB |=(cont & 0X1F);
  }
  

  break;
  case SEC2: 

  default:
    break;
  }
}

void MDE_BOT1(void);



void inicializacion_leds(void)
{
  // Configuración de pines
  DDRD |= 0xFC; // Los pines PD2 a PD7 como salidas 
  DDRB |= (1<<PB0); // Los pines PB0 y  como salidas 
}

void config_TIMER0(void)
{
  TCCR0A = (1 << WGM01);  // Activa el bit CTC (clear timer on compare match)                        // del TCCR0A (timer counter/control register)
  OCR0A = 62;             // valor de comparacion de int cada 1ms
  TCCR0B = (1 << CS02);   // divido por 256 y generar interrupciones cada 1 ms
  TIMSK0 = (1 << OCIE0A); // Habilita las interrupciones entimer compare
}

ISR(TIMER0_COMPA_vect)
{
  tiempo++;
  multiplicador++;
  if (multiplicador > 100)
  {
    PORTB ^= (1 << PORTB5); // me enciende el led del arduino
    multiplicador = 0;
  }

}



int main()
{
  inicializacion_leds();
  config_TIMER0();
  sei();
  while (1)
  {
   
  }
}
//rito harakiri