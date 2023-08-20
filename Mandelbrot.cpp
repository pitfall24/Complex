//
// Created by Phineas on 3/20/23.
//

#include <iostream>
#include <vector>
#include "ComplexNumber.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void step(ComplexNumber& z, ComplexNumber& c);
int iterate(ComplexNumber& c, int max_it);
void print(std::vector<std::vector<int>>& img, int max_it);
std::vector<std::vector<int>> get_img(u_int16_t w, u_int16_t h, double left, double right, double bottom, double top, u_int16_t max_it);
std::vector<ComplexNumber> simulate(sf::Vector2f pos, u_int16_t max_it);

int main() {
    u_int16_t w = 1920, h = 1080;

    sf::RenderWindow window(sf::VideoMode(w, h), "Mandelbrot");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(3);
    text.setPosition(12.0, (float) h - 36);

    double left = -2.2, right = 1.1;
    double bottom = -1.1, top = 1.1;

    u_int16_t max_it = 512;

    auto img = get_img(w, h, left, right, bottom, top, max_it);

    sf::Vector2f pos(0.0, 0.0);

    std::vector<ComplexNumber> traced = simulate(pos, max_it);
    auto trace = new sf::Vertex[traced.size()];
    auto pixels = new sf::Vertex[w * h];

    for (int i = 0; i < traced.size(); i++) {
        double x = (traced[i].a - left) / ((right - left) / w);
        double y = (traced[i].b - bottom) / ((top - bottom) / h);

        const sf::Vertex vert(sf::Vector2f((float) x, (float) (h - y)), sf::Color(127, 0, 0));

        trace[i] = vert;
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::VertexBuffer pixel_buffer;
        pixel_buffer.create(w * h);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int pixel = img[i][j];
                int val = (int) (255 * std::sqrt((double) pixel / max_it));
                const sf::Vertex vert(sf::Vector2f((float) j, (float) i), sf::Color(val, val, val));

                pixels[i * w + j] = vert;
            }
        }

        pixel_buffer.update(pixels, w * h, 0);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            pos.x = (float) (left + (double) sf::Mouse::getPosition(window).x * (right - left) / (double) w);
            pos.y = (float) (bottom + (double) (h - sf::Mouse::getPosition(window).y) * (top - bottom) / (double) h);

            text.setString(std::to_string(pos.x) + (pos.y >= 0 ? " + " : " - ") + std::to_string(abs(pos.y)) + "i");

            traced = simulate(pos, max_it);

            for (int i = 0; i < traced.size(); i++) {
                double x = (traced[i].a - left) / ((right - left) / w);
                double y = (traced[i].b - bottom) / ((top - bottom) / h);

                const sf::Vertex vert(sf::Vector2f((float) x,(float) (h - y)), sf::Color(127, 0, 0));

                trace[i] = vert;
            }
        }

        window.draw(pixel_buffer);
        window.draw(trace, traced.size(), sf::LinesStrip);
        window.draw(text);

        window.display();
    }

    delete [] trace;
    delete [] pixels;
}

std::vector<ComplexNumber> simulate(sf::Vector2f pos, u_int16_t max_it) {
    std::vector<ComplexNumber> out;

    ComplexNumber z(0.0, 0.0);
    ComplexNumber c((double) pos.x, (double) pos.y);
    for (int i = 0; i < max_it; i++) {
        step(z, c);

        out.push_back(z);

        if (z.magnitude() > 5.0) {
            break;
        }
    }

    return out;
}

std::vector<std::vector<int>> get_img(u_int16_t w, u_int16_t h, double left, double right, double bottom, double top, u_int16_t max_it) {
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
