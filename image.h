#pragma once

namespace image
{
    class Image
    {
    public:
        Image(int width, int height, std::string name);
        void print();
        void output();
        void write(int x, int y, int r, int g, int b);

    private:
        int width;
        int height;
        std::string name;
        std::vector<unsigned int> imageData;
    };
}