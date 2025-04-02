#pragma once

#include <vector>

namespace utils
{
    std::vector<unsigned char> load_image(const char* filename, int& width, int& height, int& channels);
    void save_image(const char* filename, int width, int height, int channels, const unsigned char* data);
}
