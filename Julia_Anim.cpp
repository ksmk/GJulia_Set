#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>

const int width   (1280);
const int height  (720);
const int height_ (3 * height); 
const int width_  (3 * width);

void JuliaSet(int cx, int cy, sf::VertexArray& vertexarray){
    int x2, y2;
    int x, y;
    unsigned char c;
    for (int i (-width_), px (0); i < width_; i += 6, ++px)
        for (int j (-height_), py (0); j < height_; j += 6, ++py){
            c = 0;
            x = i;
            y = j;
            x2 = x * x;
            y2 = y * y;
            while (((x2 + y2) < 6000000) && (c < 31)){
                c++;
                y = ((x * y) >> 9) + cy;
                x = ((x2 - y2) >> 10) + cx;
                x2 = x * x;
                y2 = y * y;
            }
            vertexarray[py * width + px].position = sf::Vector2f(px, py);
            sf::Color color(8 * c, 8 * c, 255 - c);
            vertexarray[py * width + px].color = color;
        }
}

int main(){
    float angle1 (0.0f); 
    float angle2 (1.0f);
    int cx (0);
    int cy (0);

    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(width, height), "Julia Set animation");
    window.clear();
    sf::VertexArray pointmap(sf::Points, width * height);
 
    while (window.isOpen()){
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        angle1 += 0.010f;
        angle2 += 0.015f;
        cx = 768 * (sin(angle1));
        cy = 768 * (cos(angle2));
        JuliaSet(cx, cy, pointmap); 
        window.clear();
        window.draw(pointmap);
        window.display();
    }
    return int(0);
}
