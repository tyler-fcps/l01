#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "This is my first C++ project!" << endl;

    Image* image = new Image(800, 800, "output.ppm");
    image->print();

    return 0;
}

class Image {
public:

    Image(int width, int height, string name) : width(width), height(height), name(name) {}

    void print() {
        cout << this->width << "\n" << this->height << "\n" << this->name << endl;
    }

private:
    int width;
    int height;
    string name;
};