#include "color.h"
#include <iostream>

void Color::errorChecking() {
    if (this->r > 255) { this->r = 255; }
    if (this->r < 0) {this->r = 0; }

    if (this->g > 255) { this->g = 255; }
    if (this->g < 0) { this->g = 0; }

    if (this->b > 255) { this->b = 255; }
    if (this->b < 0) { this->b = 0; }

    if (this->a > 255) { this->a = 255; }
    if (this->a < 0) { this->a = 0; }

    return;
}

Color::Color(int r, int g, int b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = floor(255 * a); // Convert float-based alpha to int for internal representation
    this->errorChecking();
    return;
}

Color::Color(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->errorChecking();
    return;
}

Color::Color(std::string hexCode, float a) {
    // Remove # if present
    if (hexCode[0] == '#') {
        hexCode.erase(0, 1);
    }
    this->r = std::stoi(hexCode.substr(0, 2), nullptr, 16);
    this->g = std::stoi(hexCode.substr(2, 2), nullptr, 16);
    this->b = std::stoi(hexCode.substr(4, 2), nullptr, 16);
    this->a = floor(255 * a);
    this->errorChecking();
    return;
}

Color::Color(std::string hexCode, int a) {
    // Remove # if present
    if (hexCode[0] == '#') {
        hexCode.erase(0, 1);
    }
    //std::cout << hexCode.substr(0, 2) << " " << hexCode.substr(2, 2) << " " << hexCode.substr(4, 2) << "\n";
    //std::cout << std::stoi(hexCode.substr(0, 2), 0, 16) << " " << std::stoi(hexCode.substr(2, 2), 0, 16) << " " << std::stoi(hexCode.substr(4, 2), 0, 16) << "\n";
    this->r = std::stoi(hexCode.substr(0, 2), nullptr, 16);
    this->g = std::stoi(hexCode.substr(2, 2), nullptr, 16);
    this->b = std::stoi(hexCode.substr(4, 2), nullptr, 16);
    this->a = a;
    this->errorChecking();
    return;
}
