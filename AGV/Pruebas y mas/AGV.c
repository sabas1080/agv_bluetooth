//***************************************************************************************************
//---------------------Programa de un AGV Electronica y Mecanica----------------
//-------------------------31 de Octubre del 2011------------------------------
//---------------Programacion: Andres Eduardo Sabas Jimenez--------------------
//-----------------Dise�o:                                           ------------
//-----------------------Objetivo: Lograr un vehiculo no tripulado-------------- 
//-----------------con opcion hibrida automatica y manual, con comunicacion bluethoot-----------
//----------------------asi como poder soportar una pantalla touch--------------
//****************************************************************************************************
//#include <AGV.h>
#include <18F4550.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES PUT                      //Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES MCLR                     //Master Clear pin enabled
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PLL12                    //Divide By 12(48MHz oscillator input)
#FUSES CPUDIV4                  //System Clock by 4
#FUSES USBDIV                   //USB clock source comes from PLL divide by 2
#FUSES VREGEN                   //USB voltage regulator enabled
#FUSES ICPRT                    //ICPRT enabled

#use delay(crystal=20000000,  clock=3000000)


//---------- Configuro el uso del puerto serial-------
#use rs232(baud=19200, xmit=PIN_C6,rcv=PIN_C7,RESTART_WDT)

//--------------Configuro el uso de I2C------------------

#use i2c(MASTER, SDA=PIN_D0, SCL=PIN_D1,FAST,FORCE_HW)

//-----------------Se le pide a picc que no mueva los TRIS de los puertos
#use FAST_IO(A)
#use FAST_IO(B)
#use FAST_IO(C)
//#use FAST_IO(D)
#use FAST_IO(E)

//----------------Seccionde definicion de bits utlizados------------------------
#bit LED=0xF82.0   //Direccion logica del led   

//------------------------ Variables globales-----------------------------------
   long VAL_ADC;
   unsigned char cmd, blue;
   int a, com;
   
//******************************************************************************
//------------------------- Interrupciones--------------------------------------
//******************************************************************************
//------------------------Subrutina de encoder---------------------------------
/*#int_EXT
void  EXT_isr(void) 
{
   a++;
}
//---------------------Interrupciondel rs232-----------------------------------
#int_RDA
void  RDA_isr(void) 
{
 if(com=0)
   {
   cmd=getc(); //Espera de instruccion manual o automatico
   }
  else
  {
   blue=getc(); //Comunicacion con el bluetooht
  }
 
}*/
//******************************************************************************

//-----------------Subrutina que enciende y me apaga un led---------------------
void FLASHEO(unsigned char TIE)
{
   LED=1;
   delay_ms(TIE);
   LED=0;
   delay_ms(TIE);
   LED=1;
   delay_ms(TIE);
   LED=0;
   delay_ms(TIE);
 
   return;

}
//******************SUBRUTINAS DEL GIRO DEL MOTOR********************************
//----------Subrutina de Giro a la derecha---------
void DERECHA(void)
{

}

//----------Subrutina de Giro a la Izquierda---------
void IZQUIERDA(void)
{

}
//***********************SUBRUTINAS DEL BRAZO**********************************
//----------Subrutina de cierre de pinza---------
void CIERRE(void)
{

}
//----------Subrutina de levantamiento de la pinza---------
void ALTURA(void)
{

}

//********************SUBRUTINAS MAESTRAS**************************************
//*****************************************************************************
//------------------Subrutina de modo manual
void manual()
{
   com=1; //Se a seleccionado el modo y ahora se enviaran comandos del bluethoot
 
}
//-----------------Subrutina de modo automatico
void automatico()
{
   com=1; //Se a seleccionado el modo y ahora se enviaran comandos del bluethoot
}
//---  Subrutina de configuracion----------
void INI_CPU(void)
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_1,74,1);
   //setup_ccp1(CCP_PWM_FULL_BRIDGE|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(0);// Motor derecho
   set_pwm2_duty(0);// Motor Izquierdo
   setup_comparator(NC_NC_NC_NC);
   
   //0x00 Salida
   //0xFF Entrada
   set_tris_A(0B11111001); //Se configura el puerto para que RA1 y RA2 Salida
   SET_TRIS_B(0XFF); //El puerto B es entrada para el teclado matricial
   SET_TRIS_C(0X00);
   //SET_TRIS_D(0X00);
   SET_TRIS_E(0x00); //Se configuran las direcciobnes de los buses
   
   
   return;

}

//-------------Programa Principal------------------------
void main()
{

      
      INI_CPU();
      FLASHEO(100);
      
      while(1)
      {
               i2c_start();      //condicion de inicio
               i2c_write(0x08);  //direccion del esclavo con el que haremos la comunicacion

               i2c_write(5);  //enviamos un dato, p.e el entero 5
               i2c_stop();    //finalizacion de la comunicacion

               delay_ms(1000);   //introducimos retardo para que no este constantemte escribiendo

     
         /*//Eleccion del modo de trabajo
         if(cmd!=0)
         {
            switch (cmd) {

            case 0:printf("Manual");
            manual();

            break;

            case 1:printf("Automatico");
            automatico();

           break;

           default:printf("Bad cmd");

           break; }
      }
      else
      {
      
      }

      }*/
      
}
