#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

typedef struct {
	adc_oneshot_unit_handle_t adc_handle;
} AdcInfo;
extern AdcInfo adc_info;

void init_adc_unit(adc_unit_t unit);
void adc_config_chanel(adc_channel_t chan);
int adc_read(adc_channel_t chan);