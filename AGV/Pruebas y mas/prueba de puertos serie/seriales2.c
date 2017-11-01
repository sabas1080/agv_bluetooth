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

#use delay(crystal=20000000) //clock=5000000

//-----------------Se le pde a picc que no mueva los TRIS de los puertos
#use FAST_IO(A)
#use FAST_IO(B)
#use FAST_IO(C)
#use FAST_IO(D)
#use FAST_IO(E)

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8, stream=COM_A)
#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B0,bits=8,stream=COM_B)

char posicion;

#int_EXT
void  EXT_isr(void) 
{
   
   disable_interrupts(INT_EXT);
   disable_interrupts(GLOBAL);
   posicion=fgetc(COM_B);     //Se lee la posicion inicial del brazo
 
}





void CPU()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_PWM);       //PWM1 activo
   setup_ccp2(CCP_PWM);       //PWM2 Activo
   setup_comparator(NC_NC_NC_NC);
   enable_interrupts(INT_EXT);   //Interrupcion del puerto B(encoder)
   enable_interrupts(GLOBAL);    //Interrupciones Globales
   enable_interrupts(INT_RDA);   //Interrupcion del serial (Bluetooth)
   ext_int_edge(H_TO_L);         //Interrupcion por flanco de bajada
   set_pwm1_duty(0);             //Motor derecho
   set_pwm2_duty(0);             //Motor Izquierdo
   SET_TRIS_B(0B00000001);       //RB0.-Rx y RB1.-Tx
   SET_TRIS_C(0B10000000);       //RC7.-Rx y RC6.-Tx
}

void main()
{
   
   CPU();
   
   fprintf(COM_B,"%c",'c');   //Se pide al picencoder posicion del encoder
   disable_interrupts(INT_EXT);  //Se desactiva la interrupcion ya teniendo la posicion
   
   while(1){


   //fprintf(COM_A,"%c",recibido);    //putc(recibido); // Envia mensaje por serial COM1
   
   }
}
