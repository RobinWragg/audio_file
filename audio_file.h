#pragma once
#include <cinttypes>

// Example usage:
// const int sample_count = 4;
// int16_t samples[sample_count] = {9,8,7,6};
// uint32_t file_size;
// uint8_t *file_data;
// create_wave_file_data(sample_count, samples, 48000, true, &file_size, &file_data);
// ...
// free(file_data);
void create_wave_file_data(uint32_t ints_count, int16_t ints[], uint32_t sample_rate, bool stereo, uint32_t *file_size_out, uint8_t **file_data_out);







