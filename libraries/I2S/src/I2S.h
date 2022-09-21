#ifndef I2S_h
#define I2S_h

#include <Arduino.h>
#include "driver/i2s.h"

#define I2S_DOUT      15
#define I2S_BCLK      WB_IO6
#define I2S_LRC       WB_IO5
#define I2S_DIN       18


class I2SClass
{
public:
  I2SClass(void);
  virtual ~I2SClass();
  void setI2Sformat(i2s_comm_format_t i2s_format);
  void clearDMA();
  void begin(int channels, long sampleRate);
  void begin(int channels, long sampleRate,uint8_t bit);
  int write(void* buffer, size_t size);
  int read(void* buffer, size_t size);
  int setSampleBit(uint8_t bit);
  int start(void);
  int stop(void);
  int end(void);
  
 private:
  uint8_t _sampleBit = 16;
  i2s_comm_format_t _i2s_format = i2s_comm_format_t ( I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB );
  bool _i2s_state;
};

extern I2SClass I2S;



#endif
