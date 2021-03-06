#include <16F819.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT                      //Power Up Timer
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading

#use delay(clock=4000000)

//---------------------Configuracion del I2C----------------------------

#use i2c(Slave,Slow,sda=PIN_B1,scl=PIN_B4,force_hw,address=0x08)
//-------------------Interrupcion del I2C----------------------------------

#INT_SSP
void ssp_interupt(void)
{
   output_high(PIN_B2);
}

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   enable_interrupts(INT_SSP);
   enable_interrupts(global);
   set_tris_b(0x00);
   //TODO: User Code
   output_b(0x00);
   
   while(1)
   {
   
   }
}
