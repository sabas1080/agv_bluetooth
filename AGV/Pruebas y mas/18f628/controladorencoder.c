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


#use i2c(SLAVE, SDA=PIN_A2, SCL=PIN_A3, ADDRESS=0X08, FAST , /*FORCE_HW*/)

int dato;
 

void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   //TODO: User Code 
               
              
      
      
      while(TRUE)
      {
               
           
       dato=i2c_read();
       output_b(dato);        
            
           
      }

}
