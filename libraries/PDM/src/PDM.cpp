#include "PDM.h"
#include "esp_now.h"
#include "driver/i2s.h"


PDMClass::PDMClass()
{

}

PDMClass::~PDMClass()
{

}



int PDMClass::begin(int channels, long sampleRate)
{
	i2s_channel_fmt_t t_channel;
	if (channels == 1)
	{
		t_channel = I2S_CHANNEL_FMT_ONLY_LEFT;
	}	
	else{
		t_channel = I2S_CHANNEL_FMT_RIGHT_LEFT;
	}
	// I2S PDM mode
	Serial.println("Setup PDM...");
	i2s_config_t i2s_config = {
		.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
		.sample_rate = sampleRate, 
		.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,									
		.channel_format = t_channel,
		.communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_PCM | I2S_COMM_FORMAT_PCM_SHORT), //(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_PCM_SHORT),//
		.intr_alloc_flags = 0,		//ESP_INTR_FLAG_LEVEL1,	
		.dma_buf_count = 4,
		.dma_buf_len = 512,
		.use_apll = true,
		.tx_desc_auto_clear = false,
		.fixed_mclk = 0,
	};
  
	i2s_pin_config_t pin_config = {
		.bck_io_num = I2S_PIN_NO_CHANGE, // Bit Clock.
		.ws_io_num = 23,		// Word Select.
		.data_out_num = I2S_PIN_NO_CHANGE,
		.data_in_num = 26, // Data-out of the mic.
	};
	if (ESP_OK != i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL))
	{
		Serial.println("i2s_driver_install: error");
		return 0;
	}
	if (ESP_OK != i2s_set_pin(I2S_NUM_0, &pin_config))
	{
		Serial.println("i2s_set_pin: error");
		return 0;
	}
	if (channels == 1)
	{
		i2s_set_clk(I2S_NUM_0, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);//
	}
	else{
		i2s_set_clk(I2S_NUM_0, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);//
	}
	i2s_stop(I2S_NUM_0);
	i2s_start(I2S_NUM_0);
	return 1;
}

void PDMClass::end()
{
  if (i2s_driver_uninstall(I2S_NUM_0) != ESP_OK) {
    Serial.println("i2s_driver_uninstall() error");
  }
}


int PDMClass::read(void* buffer, size_t size)
{
  size_t byteRead;
  i2s_read(I2S_NUM_0, buffer, size, &byteRead, portMAX_DELAY);
  return byteRead;
}


PDMClass PDM;
