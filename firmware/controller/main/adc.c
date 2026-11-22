#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

#include "joystick.h"
#include "adc.h"

AdcInfo adc_info;

void init_adc_unit(adc_unit_t unit){
	adc_oneshot_unit_init_cfg_t adc_unit = {
		.unit_id = unit,
	};
	adc_oneshot_unit_handle_t adc_unit_handle;
	adc_oneshot_new_unit(&adc_unit, &adc_unit_handle);
	adc_info.adc_handle = adc_unit_handle;
}

void adc_config_chanel(adc_channel_t chan){
    adc_oneshot_chan_cfg_t chan_config = {
        .atten = ADC_ATTEN_DB_0,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    adc_oneshot_config_channel(adc_info.adc_handle, chan, &chan_config);
}

int adc_read(adc_channel_t chan){
	int output;
	adc_oneshot_read(adc_info.adc_handle, chan, &output);
	return output;
}