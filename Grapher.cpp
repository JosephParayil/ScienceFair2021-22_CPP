/*
This is a tool I developed to convert the raw results into a meaningful stacked area graph
By Joseph Parayil

(Requires SFML to be installed and either statically or dynamically linked.)
*/

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std; //For easy readability
using namespace sf;



int main() {
    //Taking raw input
    float in;
    float mHistory[50];
    float aHistory[50];
    for (int i = 0;i < 50;i++) {
        cin >> in;
        mHistory[i] = in;
        cin >> in;
        aHistory[i] = in;
        mHistory[i] += in;
    }
    
    
    RenderWindow window(VideoMode(588, 500), "Population Results");
    Event event;
    
    
    //Each population data is in the form of a ConvexShape of 52 points.
    ConvexShape blueArea;
    ConvexShape redArea;
    blueArea.setPointCount(52);
    redArea.setPointCount(52);
    blueArea.setFillColor(Color::Blue);
    redArea.setFillColor(Color::Red);
    for (int i = 0;i < 50;i++) {
        blueArea.setPoint(i, Vector2f(i *12.0f, 500.0f-mHistory[i]));
        redArea.setPoint(i, Vector2f(i * 12.0f, 500.0f-aHistory[i]));
    }
    blueArea.setPoint(50, Vector2f(600.0f, 500.0f));
    redArea.setPoint(50, Vector2f(600.0f, 500.0f));
    blueArea.setPoint(51, Vector2f(0.0f, 500.0f));
    redArea.setPoint(51, Vector2f(0.0f, 500.0f));

    
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(blueArea);
        window.draw(redArea);
        window.display();
    }

    return 0;


}
