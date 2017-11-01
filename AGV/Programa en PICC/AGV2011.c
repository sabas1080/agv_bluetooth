//*******************************************************************************
//---------------------Programa de un AGV Electronica y Mecanica----------------
//-------------------------31 de Octubre del 2011------------------------------
//---------------Programacion: Andres Eduardo Sabas Jimenez--------------------
//-----------------Diseño:Josue Isai Luevano Macias-----------------------------
//-----------------------Objetivo: Lograr un vehiculo--------------------------- 
//-------------------con comunicacion bluethoot y control de un brazo-----------
//*******************************************************************************
#include <18F4550.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES PLL1                     //No PLL PreScaler
#FUSES CPUDIV1                  //No System Clock Postscaler
#FUSES USBDIV                   //USB clock source comes from PLL divide by 2
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES VREGEN                   //USB voltage regulator enabled
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES MCLR                     //Master Clear pin enabled
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES ICSP2                    //ICD uses PGC2/PGD2 pins
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads

#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

char CAR;

#int_RDA
void  RDA_isr(void) 
{
CAR=getc();
}

//-----------------Se le pide a picc que no mueva los TRIS de los puertos
#use FAST_IO(A)
#use FAST_IO(B)
#use FAST_IO(C)
#use FAST_IO(D)
#use FAST_IO(E)

//--------------------------Variables Globales--------------------------------
int pwm1,pwm2;    //Variables de control del pwm

//------------Subrutinas de acciones de los motores de avance-----------------
void adelante()
{
   output_high(PIN_B6);
   output_high(PIN_B7);
   output_high(PIN_D0);
   output_high(PIN_D2);
   output_low(PIN_D1);
   output_low(PIN_D3);  
}

void atras()
{
   output_high(PIN_B6);
   output_high(PIN_B7);
   output_high(PIN_D1);
   output_high(PIN_D3);
   output_low(PIN_D0);
   output_low(PIN_D2);
}
void derecha_adelante()
{
   output_high(PIN_B6);
   output_low(PIN_B7);
   output_high(PIN_D0);
   output_low(PIN_D2);
   output_low(PIN_D1);
   output_low(PIN_D3);
}
void izquierda_adelante()
{
   output_low(PIN_B6);
   output_high(PIN_B7);
   output_low(PIN_D0);
   output_high(PIN_D2);
   output_low(PIN_D1);
   output_low(PIN_D3);
}
void derecha_atras()
{
   output_high(PIN_B6);
   output_low(PIN_B7);
   output_high(PIN_D1);
   output_low(PIN_D3);
   output_low(PIN_D0);
   output_low(PIN_D2);
}
void izquierda_atras()
{
   output_low(PIN_B6);
   output_high(PIN_B7);
   output_low(PIN_D1);
   output_high(PIN_D3);
   output_low(PIN_D0);
   output_low(PIN_D2);
}
void stop()
{
   output_low(PIN_B6);
   output_low(PIN_B7);
   output_low(PIN_D1);
   output_low(PIN_D3);
   output_low(PIN_D0);
   output_low(PIN_D2);
}
//-----------------Subrutinas del control del brazo------------------------
void arriba()
{
   set_pwm1_duty(80);
   set_pwm2_duty(0);
   output_high(PIN_D4);
   output_low(PIN_D5);
   output_low(PIN_D6);
   output_low(PIN_D7);
}
void abajo()
{
   set_pwm1_duty(80);
   set_pwm2_duty(0);
   output_low(PIN_D4);
   output_high(PIN_D5);
   output_low(PIN_D6);
   output_low(PIN_D7);
}

void cierre()
{
   set_pwm1_duty(0);
   set_pwm2_duty(80);
   output_low(PIN_D4);
   output_low(PIN_D5);
   output_high(PIN_D6);
   output_low(PIN_D7);
}

void abrir()
{
   set_pwm1_duty(0);
   set_pwm2_duty(80);
   output_low(PIN_D4);
   output_low(PIN_D5);
   output_low(PIN_D6);
   output_high(PIN_D7);
}
void stop_alt()
{
   set_pwm1_duty(0);
   set_pwm2_duty(0);
   output_low(PIN_D4);
   output_low(PIN_D5);
   output_low(PIN_D6);
   output_low(PIN_D7);
}

void stop_cierre()
{
   set_pwm1_duty(0);
   set_pwm2_duty(0);
   output_low(PIN_D4);
   output_low(PIN_D5);
   output_low(PIN_D6);
   output_low(PIN_D7);
}

//--------------------------Configuracion del PIC-----------------------------
void cpu()
{

   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_4,88,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(0);
   set_pwm2_duty(0);
   setup_comparator(NC_NC_NC_NC);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   
   //0x00 Salida
   //0xFF Entrada
   set_tris_A(0xFF); 
   SET_TRIS_B(0b00111111); 
   SET_TRIS_C(0b10111110);
   SET_TRIS_D(0X00);
   SET_TRIS_E(0xFF);
 
}

//Programa Princicpal
void main()
{
   cpu();
   //Led para saber que el progrma inicio
   output_high(PIN_C0);
   delay_ms(100);
   output_low(PIN_C0);
   delay_ms(100);
   
   while(1)
   {

    if(CAR=='a'){
   adelante();
   output_high(PIN_C0);
   delay_ms(100);
   output_low(PIN_C0);
   delay_ms(100);
    }
    if(CAR=='b'){
   atras();
   output_high(PIN_C0);
   delay_ms(100);
   output_low(PIN_C0);
   delay_ms(100);
    }
    if(CAR=='c'){
   stop();
   output_high(PIN_C0);
   delay_ms(100);
   output_low(PIN_C0);
   delay_ms(100);
    }
    if(CAR=='d'){
    derecha_adelante();
    output_high(PIN_C0);
   delay_ms(100);
   output_low(PIN_C0);
   delay_ms(100);
    }
    if(CAR=='e'){
    izquierda_adelante();
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
    //------------Subrutinas del brazo-------------
    if(CAR=='f'){
    arriba()
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
    if(CAR=='g'){
    abajo();
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
    if(CAR=='h'){
    cierre();
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
    if(CAR=='i'){
    stop_alt()
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
    if(CAR=='j'){
    stop_cierre()
    output_high(PIN_C0);
    delay_ms(100);
    output_low(PIN_C0);
    delay_ms(100);
    }
   }
}
