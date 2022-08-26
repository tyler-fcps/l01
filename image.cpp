#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Image {
public:

    Image(int width, int height, string name) : width(width), height(height), name(name) {
        imageData = (vector<unsigned int>)(width * height * 3, 0);
    }

    void write(int x, int y, int r, int g, int b) {
        int i = (x + y * this->width) * 3;
        this->imageData[i+0] = r;
        this->imageData[i+1] = g;
        this->imageData[i+2] = b;
    }

    void output() {
        // Create and open a text file
        ofstream out(this->name);

        // Write header to file
        out << "P3 " << this->width << " " << this->height << " 255\r\n";

        // Write data
        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                out << this->imageData[(j + i * this->width) * 3] << " ";
            }
            out << "\n";
        }

        // Close the file
        out.close();
    }

    void print() {
        cout << this->width << "\n" << this->height << "\n" << this->name << endl;
    }

private:
    int width;
    int height;
    string name;
    vector<unsigned int> imageData;
};