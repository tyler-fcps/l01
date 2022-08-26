#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"
using namespace std;

int main() {
    cout << "This is my first C++ project!" << endl;

    Image* image = new Image(800, 800, "output.ppm");
    image->print();

    return 0;
}