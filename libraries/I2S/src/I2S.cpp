#include "I2S.h"
#include "esp_now.h"
#include "driver/i2s.h"



I2SClass::I2SClass()
{
  
}

I2SClass::~I2SClass()
{

}
void I2SClass::setI2Sformat(i2s_comm_format_t i2s_format)
{
	_i2s_format = i2s_format;
}
void I2SClass::begin(int channels, long sampleRate)
{
  // I2S mode
//  Serial.println("Setup I2S...");
i2s_channel_fmt_t t_channel;
if (channels == 1)
	{
		t_channel = I2S_CHANNEL_FMT_ONLY_LEFT;
	}	
else{
		t_channel = I2S_CHANNEL_FMT_RIGHT_LEFT;
	}
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = sampleRate, 
    .bits_per_sample = (i2s_bits_per_sample_t)_sampleBit,   //I2S_BITS_PER_SAMPLE_16BIT,         
    .channel_format = t_channel,                     
//    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S |I2S_COMM_FORMAT_I2S_MSB),
//   .communication_format = (i2s_comm_format_t)( I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB ),
//	.communication_format = (i2s_comm_format_t)( I2S_COMM_FORMAT_I2S ),
	 .communication_format = _i2s_format,
    .intr_alloc_flags = 0,// ESP_INTR_FLAG_LEVEL1,  
    .dma_buf_count = 128,
    .dma_buf_len = 64,
//    .use_apll = true,
//    .tx_desc_auto_clear = false,
//    .fixed_mclk = 0,
  };
//	Serial.printf("_sampleBit:%d \r\n",_sampleBit);
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK, // Bit Clock.
    .ws_io_num = I2S_LRC,    // Word Select.
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN, // Data-out of the mic.
  };
  if (ESP_OK != i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL))
  {
    Serial.println("i2s_driver_install: error");
  }
  if (ESP_OK != i2s_set_pin(I2S_NUM_1, &pin_config))
  {
    Serial.println("i2s_set_pin: error");
  }
 if(channels==1)
 	{
	  i2s_set_clk(I2S_NUM_1, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, (i2s_channel_t)I2S_CHANNEL_MONO);//
 	}
 else
 	{
      i2s_set_clk(I2S_NUM_1, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, (i2s_channel_t)I2S_CHANNEL_STEREO);//
 	} 
  i2s_zero_dma_buffer(I2S_NUM_1);
  i2s_stop(I2S_NUM_1);
  i2s_start(I2S_NUM_1);
  _i2s_state = true;
}
void I2SClass::clearDMA(void)
{
	i2s_zero_dma_buffer(I2S_NUM_1);
}
void I2SClass::begin(int channels, long sampleRate,uint8_t bit)
{
  // I2S mode
//  Serial.println("Setup I2S...");
i2s_channel_fmt_t t_channel;
if (channels == 1)
	{
		t_channel = I2S_CHANNEL_FMT_ONLY_LEFT;
	}	
else{
		t_channel = I2S_CHANNEL_FMT_RIGHT_LEFT;
	}

  _sampleBit = bit;
 switch(bit)
 	{

		case 16:
			_sampleBit = I2S_BITS_PER_SAMPLE_16BIT;
		break;
		case 24:
			_sampleBit = I2S_BITS_PER_SAMPLE_24BIT;
		break;
		case 32:
			_sampleBit = I2S_BITS_PER_SAMPLE_32BIT;
		break;
		default:
			_sampleBit = I2S_BITS_PER_SAMPLE_16BIT;
		break;

 	}


  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = sampleRate, 
    .bits_per_sample = (i2s_bits_per_sample_t)_sampleBit,                 
    .channel_format = t_channel,                     
 //   .communication_format = (i2s_comm_format_t)( I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB ),
    .communication_format = _i2s_format,	//(i2s_comm_format_t)( I2S_COMM_FORMAT_STAND_I2S ),
    .intr_alloc_flags = 0,// ESP_INTR_FLAG_LEVEL1,  
    .dma_buf_count = 128,
    .dma_buf_len = 64,

  };
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK, // Bit Clock.
    .ws_io_num = I2S_LRC,    // Word Select.
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN, // Data-out of the mic.
  };
  if (ESP_OK != i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL))
  {
    Serial.println("i2s_driver_install: error");
  }
  if (ESP_OK != i2s_set_pin(I2S_NUM_1, &pin_config))
  {
    Serial.println("i2s_set_pin: error");
  }
 if(channels==1)
 	{
	  i2s_set_clk(I2S_NUM_1, sampleRate, (i2s_bits_per_sample_t)_sampleBit, (i2s_channel_t)I2S_CHANNEL_MONO);//
 	}
 else
 	{
      i2s_set_clk(I2S_NUM_1, sampleRate, (i2s_bits_per_sample_t)_sampleBit, (i2s_channel_t)I2S_CHANNEL_STEREO);//
 	} 
// Serial.printf("_sampleBit:%d \r\n",_sampleBit);
  i2s_zero_dma_buffer(I2S_NUM_1);
  i2s_stop(I2S_NUM_1);
  i2s_start(I2S_NUM_1);
  _i2s_state = true;

}
int I2SClass::setSampleBit(uint8_t bit)
{
	_sampleBit = bit;
	return _sampleBit;
}
int I2SClass::write(void* buffer, size_t size) 
{
  size_t byteWrite;
	i2s_write(I2S_NUM_1, buffer, size, &byteWrite, portMAX_DELAY);
  return byteWrite;
}

int I2SClass::read(void* buffer, size_t size)
{
  size_t byteRead;
	i2s_read(I2S_NUM_1, buffer, size, &byteRead, portMAX_DELAY);
  return byteRead;
}
int I2SClass::start(void)
{
	if(_i2s_state == false)
	{		
		i2s_start(I2S_NUM_1);
		_i2s_state = true;
	}
	return 0;
}
int I2SClass::stop(void)
{
	if(_i2s_state == true)
	{
		i2s_stop(I2S_NUM_1);
		_i2s_state = false;
	}
	return 0;
}
int I2SClass::end(void)
{
	_i2s_state = false;
	return (i2s_driver_uninstall(I2S_NUM_1));	
}

I2SClass I2S;