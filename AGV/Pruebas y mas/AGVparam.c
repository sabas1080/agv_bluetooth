#include <AGVparam.h>




void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_pp(PMP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,77,1);
   setup_ccp1(CCP_PWM_FULL_BRIDGE|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(1023);
   set_pwm2_duty(1023);
   setup_comparator(NC_NC_NC_NC);
);

   //TODO: User Code

}
