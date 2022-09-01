// Loopback test
// We will use task to handle read and write, without DMA interrupt(it is internal function now)

#include <I2S.h>

short read_data[512] = {0};
short write_data[512] = {0};

void reader(void *pvParameters) {

  size_t bytes_read;
  while(1){
    bytes_read = I2S.read((uint8_t *)read_data, 512*2);
    //Serial.println(bytes_read);
    Serial.println(read_data[0],HEX);
    delay(500); // this dealy is decide by the sample rate and dma rate
  }
}

void writer(void *pvParameters) {

  size_t bytes_write;
  memset((uint8_t *)write_data,0x11,512*2);
  while(1){
    bytes_write = I2S.write(write_data, 512*2);
    //Serial.println(bytes_write);
    //delay(500); // this dealy is decide by the sample rate and dma rate
  }
}



void setup() {
  Serial.begin(115200);
  while (!Serial);
  // initialize PDM with:
  // - 2 channel (stereo mode)
  // - a 16 kHz sample rate
  I2S.begin(2, 16000);

  // Create a task that will read the data
  xTaskCreatePinnedToCore(reader, "reader", 2048, NULL, 1, NULL, 1);
  // Create a task that will write the data
  xTaskCreatePinnedToCore(writer, "writer", 2048, NULL, 1, NULL, 1);  
}

void loop() {

}