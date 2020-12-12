#include "pch.h"
#include <iostream>
#include <stdlib.h>   

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

Position position_1(-20.0, 1., 0.);
Velocity velocity_1(0., 0., 0.);

Position position_2(-10., 1., 0.);
Velocity velocity_2(0., 0., 0.);

Position position_3(0., 1., 0.);
Velocity velocity_3(0., 0., 0.);

Position position_4(10., 1., 0.);
Velocity velocity_4(0., 0., 0.);

Position position_5(20., 1., 0.);
Velocity velocity_5(0., 0., 0.);

unsigned char projection_type = 'p';
float fov = 45.0f;
float timer = 0.0f;
bool animationStarted = false;
float firstBallDone, secondBallDone, thirdBallDone, fourthBallDone, fivthBallDone = false;

void startAnimation()
{
    firstBallDone = false;
    secondBallDone = false;
    thirdBallDone = false;
    fourthBallDone = false;
    fivthBallDone = false;

    velocity_1.x = 0.0;
    velocity_1.y = 5.0;
    velocity_1.z = 0.0;

    velocity_2.x = 0.0;
    velocity_2.y = 5.0;
    velocity_2.z = 0.0;

    velocity_3.x = 0.0;
    velocity_3.y = 5.0;
    velocity_3.z = 0.0;

    velocity_4.x = 0.0;
    velocity_4.y = 5.0;
    velocity_4.z = 0.0;

    velocity_5.x = 0.0;
    velocity_5.y = 5.0;
    velocity_5.z = 0.0;

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

    GLUquadricObj* qobj = gluNewQuadric();
    GLUquadricObj* qobj2 = gluNewQuadric();
    GLUquadricObj* qobj3 = gluNewQuadric();
    GLUquadricObj* qobj4 = gluNewQuadric();
    GLUquadricObj* qobj5 = gluNewQuadric();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
    glDisable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(position_1.x, position_1.y, position_1.z);
    gluSphere(qobj, 1., 15, 10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(position_2.x, position_2.y, position_3.z);
    gluSphere(qobj2, 1., 15, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(position_3.x, position_3.y, position_3.z);
    gluSphere(qobj3, 1., 15, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(position_4.x, position_4.y, position_4.z);
    gluSphere(qobj4, 1., 15, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(position_5.x, position_5.y, position_5.z);
    gluSphere(qobj5, 1., 15, 10);
    glPopMatrix();

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

        std::cout << animationStarted << firstBallDone << secondBallDone << thirdBallDone << fourthBallDone << fivthBallDone << std::endl;

        if (animationStarted && !firstBallDone)
        {
            firstBallDone = false;
            float dt = timer - tmp;
            velocity_1.y = velocity_1.y - g * timer;
            position_1.y = position_1.y + velocity_1.y * dt;
            tmp = timer;
        }
        if (position_1.y < 1.0)
        {
            position_1.y = 1.1f;
            firstBallDone = true;
            tmp = 0.0f;
            timer = 0.0;
        }

        if (animationStarted && firstBallDone && !secondBallDone)
        {
            secondBallDone = false;
            float dt = timer - tmp;
            velocity_2.y = velocity_2.y - g * timer;
            position_2.y = position_2.y + velocity_2.y * dt;
            tmp = timer;
        }
        if (position_2.y < 1.0)
        {
            position_2.y = 1.1f;
            secondBallDone = true;
            tmp = 0.0f;
            timer = 0.0;
        }

        if (animationStarted && firstBallDone && secondBallDone && !thirdBallDone)
        {
            thirdBallDone = false;
            float dt = timer - tmp;
            velocity_3.y = velocity_3.y - g * timer;
            position_3.y = position_3.y + velocity_3.y * dt;
            tmp = timer;
        }
        if (position_3.y < 1.0)
        {
            position_3.y = 1.1f;
            thirdBallDone = true;
            tmp = 0.0f;
            timer = 0.0;
        }

        if (animationStarted && firstBallDone && secondBallDone && thirdBallDone && !fourthBallDone)
        {
            fourthBallDone = false;
            float dt = timer - tmp;
            velocity_4.y = velocity_4.y - g * timer;
            position_4.y = position_4.y + velocity_4.y * dt;
            tmp = timer;
        }
        if (position_4.y < 1.0)
        {
            position_4.y = 1.1f;
            fourthBallDone = true;
            tmp = 0.0f;
            timer = 0.0;
        }

        if (animationStarted && firstBallDone && secondBallDone && thirdBallDone && fourthBallDone && !fivthBallDone)
        {
            fivthBallDone = false;
            float dt = timer - tmp;
            velocity_5.y = velocity_5.y - g * timer;
            position_5.y = position_5.y + velocity_5.y * dt;
            tmp = timer;
        }
        if (position_5.y < 1.0)
        {
            position_5.y = 1.1f;
            fivthBallDone = true;
            tmp = 0.0f;
            animationStarted = 0;
        }

        if (!animationStarted && firstBallDone && secondBallDone && thirdBallDone && fourthBallDone && fivthBallDone)
        {
            animationStarted = 0;
        }

        drawScene();
        window.display();
    }

    return 0;
}