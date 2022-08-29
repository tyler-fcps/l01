#pragma once

namespace image
{
    class Image
    {
    public:
        Image(std::string name);
        void output();
        void write(int x, int y, int r, int g, int b);

    private:
        int width;
        int height;
        std::string name;
        unsigned int imageData[800 * 800 * 3];
    };
}