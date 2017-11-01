#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B2,rcv=PIN_B1,bits=8)

char CAR;
long a;


#int_RDA
void res_isr()
{
   disable_interrupts(int_RDA);
   disable_interrupts(GLOBAL);
   disable_interrupts(INT_EXT);
   delay_ms(100);
   CAR=getc();
   if(CAR=='c')
   {
   putc(a);
   }
}

#int_EXT
void posicion()
{
   disable_interrupts(int_RDA);
   a++;
   
}

void cpu(void)
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   enable_interrupts(int_RDA);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
 }

void main(){
   
   CPU();
   
   while(1)
   {
   enable_interrupts(int_RDA);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   output_high(PIN_A0);
   delay_ms(1000);
   output_low(PIN_A0);
   }
}
