#include <cstdio>
#include <cmath>
#include <complex>
#include <SFML/Graphics.hpp>

std::complex<double> c(0, 1);

const int width   = 640;
const int height  = 480;
const int height_ = 3*height; 
const int width_  = 3*width;

void JuliaSet(sf::VertexArray& vertexarray){
    std::complex<double> x;
    double px,py;
    unsigned char iter;

    for (int i (0), py = -2.1; i < 480; ++i, py += 0.00875)
        for (int j (0), px = -2.0; j < 640; ++j, px += 0.00625){
            iter = 0;
            x = std::complex<double>(px, py);
            while ((abs(x) < 4.0) && (iter < 31)){
                ++iter;
                x = x * x + c;
            }
            vertexarray[i * width + j].position = sf::Vector2f(j, i);
            sf::Color color(8 * iter, 8 * iter, 255 - iter);
            vertexarray[i * width + j].color = color;
        }
}

int main(){
    float angle1 (0.0f); 
    float angle2 (1.0f);
    int cx (0);
    int cy (0);
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(width, height), "Julia Set");
    window.clear();
    sf::VertexArray pointmap(sf::Points, width * height);
 
    while (window.isOpen()){
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        JuliaSet(pointmap); 
        window.draw(pointmap);
        window.display();
    }
    return int(0);
}
