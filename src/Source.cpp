﻿#include "pch.h"
#include <iostream>

typedef sf::Event sfe;
typedef sf::Keyboard sfk;
sf::Texture TEXid;

struct Velocity
{
    float x, y, z;
    Velocity(float gx, float gy, float gz) : x(gx), y(gy), z(gz) {};
};

struct Spherical
{
    float distance, theta, fi;
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance), theta(gtheta), fi(gfi) { }
    float getX() { return distance * cos(theta) * cos(fi); }
    float getY() { return distance * sin(theta); }
    float getZ() { return distance * cos(theta) * sin(fi); }
};

struct Position
{
    float x, y, z;
    Position(float gx, float gy, float gz) : x(gx), y(gy), z(gz) {};
};

Spherical camera(3.0f, 0.2f, 1.2f), light_position(4.0f, 0.2f, 1.2f);
sf::Vector3f pos(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rot(0.0f, 0.0f, 0.0f);

Position position(0., 0., 0.);
Velocity velocity(0., 0., 0.);

unsigned char projection_type = 'p';
float fov = 45.0f;
float timer = 0.0f;
bool animationStarted = false;

void startAnimation()
{
    velocity.x = 0.0;
    velocity.y = 5.0;
    velocity.z = 0.0;
    
    position.x = 0.0;
    position.y = 1.0;
    position.z = 0.0;

    animationStarted = true;

    timer = 0.0;
}

void initOpenGL(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    TEXid.loadFromFile("ground.jpg");

    GLfloat light_ambient_global[4] = { 0.5,0.5,0.5,1 };     
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);
}

void reshapeScreen(sf::Vector2u size)
{
    glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projection_type == 'p') gluPerspective(fov, (GLdouble)size.x / (GLdouble)size.y, 0.1, 100.0);
    else glOrtho(-1.245 * ((GLdouble)size.x / (GLdouble)size.y), 1.245 * ((GLdouble)size.x / (GLdouble)size.y), -1.245, 1.245, -3.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void glVertexsf(sf::Vector3f v)
{
    glVertex3f(v.x, v.y, v.z);
}

void glNormalsf(sf::Vector3f v)
{
    glNormal3f(v.x, v.y, v.z);
}
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Spherical north_of_camera(camera.distance, camera.theta + 0.01f, camera.fi);
    gluLookAt(camera.getX()*20, camera.getY()*20, camera.getZ()*20,
        0.0, 0.0, 0.0,
        north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());
    GLfloat light0_position[4] = { light_position.getX(), light_position.getY(), light_position.getZ(), 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

   // GLUquadricObj* qobj = gluNewQuadric();
   // GLUquadricObj* qobj2 = gluNewQuadric();
    GLUquadricObj* qobj3 = gluNewQuadric();
    //GLUquadricObj* qobj4 = gluNewQuadric();
    //GLUquadricObj* qobj5 = gluNewQuadric();

    gluQuadricDrawStyle(qobj3, GLU_FILL);
    gluQuadricNormals(qobj3, GLU_SMOOTH);

    //gluQuadricDrawStyle(qobj2, GLU_FILL);
    //gluQuadricNormals(qobj2, GLU_SMOOTH);
    
    /*glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);        
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);       
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);      
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);    
    glTranslatef(-20.0, 1.0, 0.0);
    gluSphere(qobj, 1., 15, 10);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
    glTranslatef(-10.0, 1.0, 0.0);
    gluSphere(qobj2, 1., 15, 10);
    glPopMatrix();*/

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
    glTranslatef(position.x, position.y, position.z);
    gluSphere(qobj3, 1., 15, 10);
    glPopMatrix();

    /*glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
    glTranslatef(10.0, 1.0, 0.0);
    gluSphere(qobj4, 1., 15, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
    glTranslatef(20.0, 1.0, 0.0);
    gluSphere(qobj5, 1., 15, 10);
    glPopMatrix();*/

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    sf::Texture::bind(&TEXid);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0, 0.0, 40.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0, 0.0, -40.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-40.0, 0.0, -40.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0, 0.0, 40.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

int main()
{
    bool running = true;
    sf::ContextSettings context(24, 0, 0, 4, 5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Michal Stefaniuk - projekt semestralny", 7U, context);
    int shift_key_state = 1;
    sf::Clock clock;

    window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize());
    initOpenGL();

    while (running)
    {
        sfe event;
        sf::Time elapsed = clock.restart();
        timer += elapsed.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sfe::Closed || (event.type == sfe::KeyPressed && event.key.code == sfk::Escape)) running = false;
            if (event.type == sfe::Resized) reshapeScreen(window.getSize());
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num0) { projection_type = 'o'; reshapeScreen(window.getSize()); }
                if (event.key.code == sf::Keyboard::Num9) { projection_type = 'p'; reshapeScreen(window.getSize()); }
            }
        }
        if (sfk::isKeyPressed(sfk::Left)) camera.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::Right)) camera.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::Up)) camera.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::Down)) camera.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::I)) light_position.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::O)) light_position.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::K)) light_position.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::L)) light_position.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::LShift)) shift_key_state = -1;
        if (sfk::isKeyPressed(sfk::Q)) pos.x += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::A)) pos.y += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::Z)) pos.z += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::W)) scale.x += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::S)) scale.y += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::X)) scale.z += 0.01f * shift_key_state;
        if (sfk::isKeyPressed(sfk::E)) rot.x += 0.5f * shift_key_state;
        if (sfk::isKeyPressed(sfk::D)) rot.y += 0.5f * shift_key_state;
        if (sfk::isKeyPressed(sfk::C)) rot.z += 0.5f * shift_key_state;
        shift_key_state = 1;

        if (sfk::isKeyPressed(sfk::LBracket)) { fov -= 1.0f; reshapeScreen(window.getSize()); }
        if (sfk::isKeyPressed(sfk::RBracket)) { fov += 1.0f; reshapeScreen(window.getSize()); }
        if (sfk::isKeyPressed(sfk::Space)) { startAnimation(); }
        float tmp = 0.0f;
        float g = 0.981f;

        if (animationStarted)
        {
            float dt = timer - tmp;
            velocity.y = velocity.y - g * timer;
            position.x = position.x; //position.x + velocity.x * dt;
            position.y = position.y + velocity.y * dt;
      
            
            std::cout << position.y << std::endl;
            tmp = timer;
        }
        if (position.y < 1.)
        {
           position.y = 1;
           animationStarted = 0;
        }

        drawScene();
        window.display();
    }
    return 0;
}