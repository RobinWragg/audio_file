#include "audio_file.h"
#include <string>

struct WaveHeader {
  // RIFF chunk
  char riff_id[4]; // = "RIFF"
  uint32_t file_size_minus_8; // = Total file size minus the data for riff_id and this variable
  char wave_id[4]; // = "WAVE"
  
  // Format chunk
  char format_id[4]; // = "fmt "
  uint32_t format_chunk_size; // = 16 for PCM
  uint16_t audio_format; // = 1 for PCM
  uint16_t channel_count; // = 1 for mono, 2 for stereo
  uint32_t sample_rate; // = 1 for mono, 2 for stereo
  uint32_t byte_rate; // = sample_rate * full_sample_size
  uint16_t full_sample_size; // = channel_count * bits_per_mono_sample / sizeof(uint8_t)
  uint16_t bits_per_mono_sample; // = 16 for 16bit
  
  // Data chunk
  char data_id[4]; // = "data"
  uint32_t data_size; // = full_sample_size * number of full samples
};

static void floats_to_ints(uint32_t count, float floats[], int16_t ints_out[]) {
  for (uint32_t i = 0; i < count; i++) {
    ints_out[i] = floats[i] * 32767;
  }
}

void create_wave_file_data(uint32_t ints_count, int16_t ints[], uint32_t sample_rate, bool stereo, uint32_t *file_size_out, uint8_t **file_data_out) {
  
  *file_size_out = sizeof(WaveHeader) + ints_count * sizeof(int16_t);
  *file_data_out = (uint8_t*)malloc(*file_size_out);
  
  WaveHeader *header = (WaveHeader*)*file_data_out;
  int16_t *data = (int16_t*)*file_data_out + sizeof(WaveHeader);
  
  // RIFF chunk
  header->riff_id[0] = 'R';
  header->riff_id[1] = 'I';
  header->riff_id[2] = 'F';
  header->riff_id[3] = 'F';
  header->file_size_minus_8 = (*file_size_out) - 8;
  header->wave_id[0] = 'W';
  header->wave_id[1] = 'A';
  header->wave_id[2] = 'V';
  header->wave_id[3] = 'E';
  
  // Format chunk
  header->format_id[0] = 'f';
  header->format_id[1] = 'm';
  header->format_id[2] = 't';
  header->format_id[3] = ' ';
  header->format_chunk_size = 16;
  header->audio_format = 1;
  header->channel_count = stereo ? 2 : 1;
  header->sample_rate = sample_rate;
  header->bits_per_mono_sample = 16;
  header->full_sample_size = header->channel_count * header->bits_per_mono_sample;
  header->byte_rate = sample_rate * header->full_sample_size;
  
  // Data chunk
  header->data_id[0] = 'd';
  header->data_id[1] = 'a';
  header->data_id[2] = 't';
  header->data_id[3] = 'a';
  header->data_size = ints_count * sizeof(int16_t);
  
  memcpy(data, ints, header->data_size);
}










