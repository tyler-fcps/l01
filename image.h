namespace image
{
    class Image
    {
    public:
        Image(int, int, std::string);
        void print();
        void output();
        void write(int, int, int, int, int);

    private:
        int width;
        int height;
        std::string name;
        std::vector<unsigned int> imageData;
    };
}