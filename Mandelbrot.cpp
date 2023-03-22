//
// Created by Phineas on 3/20/23.
//

#include <iostream>
#include <vector>
#include "ComplexNumber.h"
#include "SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/include/SFML/Window.hpp"

void step(ComplexNumber& z, ComplexNumber& c);
int iterate(ComplexNumber& c, int max_it);
void print(std::vector<std::vector<int>>& img, int max_it);
std::vector<std::vector<int>> get_img(uint16_t w, uint16_t h, double left, double right, double bottom, double top, uint16_t max_it);
std::vector<ComplexNumber> simulate(sf::Vector2i pos, uint16_t max_it);

int main() {
    uint16_t w = 2560, h = 1440;

    sf::RenderWindow window(sf::VideoMode(w, h), "Mandelbrot");
    window.setFramerateLimit(15);

    double left = -0.85, right = -0.65;
    double bottom = 0.05, top = 0.18;

    uint16_t max_it = 255;

    auto img = get_img(w, h, left, right, bottom, top, max_it);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto pixels = new sf::Vertex[w * h];

        sf::VertexBuffer pixel_buffer;
        pixel_buffer.create(w * h);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int pixel = img[i][j];
                const sf::Vertex vert(sf::Vector2f((float) j, (float) i), sf::Color(pixel * 1, pixel * 1, pixel * 1));

                pixels[i * w + j] = vert;
            }
        }

        pixel_buffer.update(pixels, w * h, 0);

        auto trace = new sf::Vertex[max_it];

        std::vector<ComplexNumber> traced = simulate(sf::Mouse::getPosition(), max_it);
        for (int i = 0; i < max_it; i++) {
            const sf::Vertex vert(sf::Vector2f((float) traced[i].a, (float) traced[i].b), sf::Color(127, 0, 0, 255));

            trace[i] = vert;
        }

        window.draw(pixel_buffer);
        window.draw(trace, max_it, sf::Lines);

        window.display();
    }
}

std::vector<ComplexNumber> simulate(sf::Vector2i pos, uint16_t max_it) {
    std::vector<ComplexNumber> out(max_it);

    ComplexNumber z(0.0, 0.0);
    ComplexNumber c((double) pos.x, (double) pos.y);
    for (int i = 0; i < max_it; i++) {
        out[i] = z;

        z = z * z + c;
    }

    return out;
}

std::vector<std::vector<int>> get_img(uint16_t w, uint16_t h, double left, double right, double bottom, double top, uint16_t max_it) {
    std::vector<std::vector<int>> img(h, std::vector<int>(w, max_it));

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            double x = left + i * (right - left) / w;
            double y = bottom + j * (top - bottom) / h;

            ComplexNumber c(x, y);
            int res = iterate(c, max_it);

            img[h - j - 1][i] = res;
        }
    }

    return img;
}

int iterate(ComplexNumber& c, int max_it) {
    ComplexNumber z = ComplexNumber(0.0, 0.0);

    for (int i = 0; i < max_it; i++) {
        if (z.magnitude() > 2) {
            return i;
        } else {
            step(z, c);
        }
    }

    return max_it;
}

void step(ComplexNumber& z, ComplexNumber& c) {
    z = z * z + c;
}

void print(std::vector<std::vector<int>>& img, int max_it) {
    std::string out;

    for (int i = 0; i < img[0].size() + 2; i++) {
        out += "_";
    }

    out += "\n";

    for (const std::vector<int>& row : img) {
        out += "|";

        for (int pixel : row) {
            out += pixel == max_it ? "M" : (pixel == max_it / 4 ? "." : " ");
        }
        out += "|\n";
    }

    for (int i = 0; i < img[0].size() + 2; i++) {
        out += "⎻";
    }

    std::cout << out << std::endl;
}
