#include <pruebas.h>




void main()
{

   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
);

   //TODO: User Code

}
