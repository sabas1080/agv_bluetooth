#include <encoder890.h>

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#use i2c(Slave,Fast,sda=PIN_C4,scl=PIN_C3,force_hw,address=0x08)

#include <LCD.C>


int8 direccion=0,checksum=0,checksumrec=0;
float valor2;
int8 valor,dato;
int contador1;
int16 contador2;

void muestra_datos(void)
   {
   lcd_gotoxy(1,1);
   lcd_putc('\f');
   lcd_gotoxy(1,1);
   lcd_putc("Showing data");

    
    for(contador2=1;contador2<65535;contador2++)
    {
    direccion=1;
    contador1=1;
    for (contador1=1;contador1<=50;contador1++)
    {
    dato=read_eeprom(direccion); 
    output_b(dato);
    delay_ms(1);
    direccion++;
    }
    
    }
       lcd_gotoxy(1,1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("Finish");
      delay_ms(500);
      lcd_gotoxy(1,1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("      Ready     ");

      
   }


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);

   lcd_init();

   lcd_gotoxy(1,1);
   lcd_putc('\f');
   lcd_gotoxy(1,1);
   lcd_putc("      Ready     ");
   
while (true)
{
   
 if(i2c_poll())
 {
   
   valor=i2c_read();
   
   if (direccion>=1)
      {
      write_eeprom(direccion,valor);
      if (direccion<=50)
      {
      checksum=checksum+valor;
      valor2=valor;
      lcd_gotoxy(1,1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Incoming: %3.0f",valor2);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Data #  %2d",direccion);
      }
      
      if (direccion==51)
      {
      checksumrec=valor;
      
      if (checksumrec==checksum)
      {
      delay_ms(750);
      lcd_gotoxy(1,1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("Reception: OK!");
      delay_ms(750);
      muestra_datos();
      }
      
      else if (checksumrec!=checksum)
      {
      delay_ms(750);
      lcd_gotoxy(1,1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("Reception:WRONG!");
      delay_ms(750);
      }
      checksum=0;
      direccion=-1;
      }
      
      }
   direccion++;
      
  }
}  

}
