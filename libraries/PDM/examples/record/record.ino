// Save audio from PDM microphone to SD Card in wav format

/* Microphone has following pins:
    VDD
    GND
    DOUT - connected to DIN I2S pin on ESP32
    CLK  - connected to WS I2S pin on ESP32
    LR   - not connected to ESP32. Microphone has internal pull-down to GND for this pin. */


#include <driver/i2s.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "PDM.h"

File new_audio_file;
// default number of output channels
static const int channels = 2;
// default PCM output frequency
static const int frequency = 16000;
#define BIT_PER_SAMPLE 16
#define RECORD_TIME    8

// Create a file and add wav header to it so we can play it from PC later
bool create_wav_file(const char* song_name, uint32_t duration, uint16_t num_channels, const uint32_t sampling_rate, uint16_t bits_per_sample) {
  // data size in bytes - > this amount of data should be recorded from microphone later
  uint32_t data_size = sampling_rate * num_channels * bits_per_sample * duration / 8;

  new_audio_file = SD.open(song_name, FILE_WRITE);
  if (new_audio_file == NULL) {
    Serial.println("Failed to create file");
    return false;
  }

  /* *************** ADD ".WAV" HEADER *************** */
  uint8_t CHUNK_ID[4] = {'R', 'I', 'F', 'F'};
  new_audio_file.write(CHUNK_ID, 4);

  uint32_t chunk_size = data_size + 36;
  uint8_t CHUNK_SIZE[4] = {chunk_size, chunk_size >> 8, chunk_size >> 16, chunk_size >> 24};
  new_audio_file.write(CHUNK_SIZE, 4);

  uint8_t FORMAT[4] = {'W', 'A', 'V', 'E'};
  new_audio_file.write(FORMAT, 4);

  uint8_t SUBCHUNK_1_ID[4] = {'f', 'm', 't', ' '};
  new_audio_file.write(SUBCHUNK_1_ID, 4);

  uint8_t SUBCHUNK_1_SIZE[4] = {0x10, 0x00, 0x00, 0x00};
  new_audio_file.write(SUBCHUNK_1_SIZE, 4);

  uint8_t AUDIO_FORMAT[2] = {0x01, 0x00};
  new_audio_file.write(AUDIO_FORMAT, 2);

  uint8_t NUM_CHANNELS[2] = {num_channels, num_channels >> 8};
  new_audio_file.write(NUM_CHANNELS, 2);

  uint8_t SAMPLING_RATE[4] = {sampling_rate, sampling_rate >> 8, sampling_rate >> 16, sampling_rate >> 24};
  new_audio_file.write(SAMPLING_RATE, 4);

  uint32_t byte_rate = num_channels * sampling_rate * bits_per_sample / 8;
  uint8_t BYTE_RATE[4] = {byte_rate, byte_rate >> 8, byte_rate >> 16, byte_rate >> 24};
  new_audio_file.write(BYTE_RATE, 4);

  uint16_t block_align = num_channels * bits_per_sample / 8;
  uint8_t BLOCK_ALIGN[2] = {block_align, block_align >> 8};
  new_audio_file.write(BLOCK_ALIGN, 2);

  uint8_t BITS_PER_SAMPLE[2] = {bits_per_sample, bits_per_sample >> 8};
  new_audio_file.write(BITS_PER_SAMPLE, 2);

  uint8_t SUBCHUNK_2_ID[4] = {'d', 'a', 't', 'a'};
  new_audio_file.write(SUBCHUNK_2_ID, 4);

  uint8_t SUBCHUNK_2_SIZE[4] = {data_size, data_size >> 8, data_size >> 16, data_size >> 24};
  new_audio_file.write(SUBCHUNK_2_SIZE, 4);

  // Actual data should be appended after this point later

  new_audio_file.close();
  return true;
}


void microphone_record(const char* song_name, uint32_t duration) {

  // Add wav header to the file so we can play it from PC later
  
  if (!create_wav_file(song_name, duration, channels, frequency, BIT_PER_SAMPLE)) {
    Serial.println("Error during wav header creation");
    return;
  }

  // Buffer to receive data from microphone
  const size_t BUFFER_SIZE = 500;
  uint8_t* buf = (uint8_t*)malloc(BUFFER_SIZE);

  // Open created .wav file in append+binary mode to add PCM data
  File audio_file = SD.open(song_name, FILE_APPEND);
  if (audio_file == NULL) {
    Serial.println("Failed to create file");
    return;
  }


  // data size in bytes - > this amount of data should be recorded from microphone
  uint32_t data_size = frequency * BIT_PER_SAMPLE * duration / 8;

  // Record until "file_size" bytes have been read from mic.
  uint32_t counter = 0;
  Serial.println("Recording started");
  while (counter != data_size) {
    // Check for file size overflow
    if (counter > data_size) {
      Serial.println("File is corrupted. data_size must be multiple of BUFFER_SIZE. Please modify BUFFER_SIZE");
      break;
    }

    // Read data from microphone
    PDM.read(buf, BUFFER_SIZE);


    // Save data to SD card
    audio_file.write( buf, BUFFER_SIZE);

    // Increment the counter
    counter += BUFFER_SIZE;
  }
  Serial.println("Recording finished");
  audio_file.close();
  PDM.end();
  free(buf);
}

void setup() {
  pinMode(WB_IO2,OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  pinMode(LED_GREEN,OUTPUT);
  Serial.begin(115200);
  delay(1000);
  digitalWrite(LED_GREEN, HIGH); 
  if (!SD.begin(SS,SPI,8000000,"/sd",5)){// Start access to the SD.
    Serial.println("Card Mount Failed");
  }
  if (SD.exists("/record.wav")) {
    Serial.println("Remove file first!");
    SD.remove("/record.wav");
  } 
  // Initialize I2S
  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1) yield();
  }
  microphone_record("/record.wav", RECORD_TIME);
}

void loop() {

}
