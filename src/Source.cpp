﻿#include "pch.h"
#include <iostream>

typedef sf::Event sfe;
typedef sf::Keyboard sfk;

struct Spherical
{
    float distance, theta, fi;
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance), theta(gtheta), fi(gfi) { }
    float getX() { return distance * cos(theta) * cos(fi); }
    float getY() { return distance * sin(theta); }
    float getZ() { return distance * cos(theta) * sin(fi); }
};

Spherical camera(3.0f, 0.2f, 1.2f);
sf::Vector3f pos(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rot(0.0f, 0.0f, 0.0f); //new

void initOpenGL(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Spherical north_of_camera(camera.distance, camera.theta + 0.01f, camera.fi);
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
        0.0, 0.0, 0.0,
        north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());

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

    //transformacje
    glTranslatef(pos.x, pos.y, pos.z);   //new
    glRotatef(rot.x, 1, 0, 0);           //new
    glRotatef(rot.y, 0, 1, 0);           //new
    glRotatef(rot.z, 0, 0, 1);           //new
    glScalef(scale.x, scale.y, scale.z); //new

    glLineWidth(2.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (unsigned char i = 0; i < 2; i++)
        for (unsigned char j = 0; j < 2; j++)
        {
            glVertex3f(-0.3f + 0.6f * (i ^ j), -0.3f + 0.6f * j, -0.3f); glVertex3f(-0.3f + 0.6f * (i ^ j), -0.3f + 0.6f * j, 0.3f);
            glVertex3f(-0.3f, -0.3f + 0.6f * (i ^ j), -0.3f + 0.6f * j); glVertex3f(0.3f, -0.3f + 0.6f * (i ^ j), -0.3f + 0.6f * j);
            glVertex3f(-0.3f + 0.6f * (i ^ j), -0.3f, -0.3f + 0.6f * j); glVertex3f(-0.3f + 0.6f * (i ^ j), 0.3f, -0.3f + 0.6f * j);
        }
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.3f, 0.3f, 0.3f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.3f, -0.3f, 0.3f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.3f, 0.3f, -0.3f);
    glEnd();
}

int main()
{
    bool running = true;
    sf::ContextSettings context(24, 0, 0, 4, 5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Michal Stefaniuk projekt", 7U, context);
    int shift_key_state = 1;

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
        if (sfk::isKeyPressed(sfk::Left)) camera.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::Right)) camera.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::Up)) camera.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::Down)) camera.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::LShift)) shift_key_state = -1;        //new
        if (sfk::isKeyPressed(sfk::Q)) pos.x += 0.01f * shift_key_state;   //new
        if (sfk::isKeyPressed(sfk::A)) pos.y += 0.01f * shift_key_state;   //new
        if (sfk::isKeyPressed(sfk::Z)) pos.z += 0.01f * shift_key_state;   //new
        if (sfk::isKeyPressed(sfk::W)) scale.x += 0.01f * shift_key_state; //new
        if (sfk::isKeyPressed(sfk::S)) scale.y += 0.01f * shift_key_state; //new
        if (sfk::isKeyPressed(sfk::X)) scale.z += 0.01f * shift_key_state; //new
        if (sfk::isKeyPressed(sfk::E)) rot.x += 0.5f * shift_key_state;    //new
        if (sfk::isKeyPressed(sfk::D)) rot.y += 0.5f * shift_key_state;    //new
        if (sfk::isKeyPressed(sfk::C)) rot.z += 0.5f * shift_key_state;    //new
        shift_key_state = 1;

        drawScene();
        window.display();
    }
    return 0;
}