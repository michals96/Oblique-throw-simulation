#include "pch.h"
#include <iostream>

typedef sf::Event sfe;
typedef sf::Keyboard sfk;

//new struct
struct Spherical
{
    float distance, theta, fi;
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance), theta(gtheta), fi(gfi) { }
    float getX() { return distance * cos(theta) * cos(fi); }
    float getY() { return distance * sin(theta); }
    float getZ() { return distance * cos(theta) * sin(fi); }
};

Spherical camera(3.0f, 0.2f, 1.2f); //new

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

    Spherical north_of_camera(camera.distance, camera.theta + 0.01f, camera.fi); //new
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
        0.0, 0.0, 0.0,
        north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ()); //new

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(1.0, 0, 0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, 1.0, 0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1.0);
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(-1.0, 0, 0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, -1.0, 0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, -1.0);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
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
        if (sfk::isKeyPressed(sfk::Left)) camera.fi -= 0.01f;    //new
        if (sfk::isKeyPressed(sfk::Right)) camera.fi += 0.01f;   //new
        if (sfk::isKeyPressed(sfk::Up)) camera.theta += 0.01f;   //new
        if (sfk::isKeyPressed(sfk::Down)) camera.theta -= 0.01f; //new
        drawScene();
        window.display();
    }
    return 0;
}