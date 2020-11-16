#include "pch.h"
#include <iostream>

typedef sf::Event sfe;
typedef sf::Keyboard sfk;

void initOpenGL(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void reshapeScreen(sf::Vector2u size)
{
    glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)size.x / (GLdouble)size.y, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

int main()
{
    bool running = true;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Michal Stefaniuk projekt");

    window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize());
    initOpenGL();

    while (running)
    {
        sfe event;
        while (window.pollEvent(event))
        {
            if (event.type == sfe::Closed || (event.type == sfe::KeyPressed && event.key.code == sfk::Escape)) running = false;
            if (event.type == sfe::Resized) reshapeScreen(window.getSize());
        }
        drawScene();
        window.display();
    }
    return 0;
}