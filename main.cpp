#include <iostream>
#include <memory>
using namespace std;

#include <cmath>     //sin and cos included in this header file.

//--- OpenGL --- The OpenGL Extension Wrangler Library
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//--------------
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Model/Model.h"
#include "Cube/Cube.h"
#include "CubeMap/cubeMap.h"
#include "Camera/Camera.h"
#include "Plane/Plane.h"
#include "Spline/Spline.h"
#include "CoasterCart/Cart.h"
#include "Physics/PhysicsCollision.h"
#include "Player/Player.h"
#include "Camera/CameraManager.h"


//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


int screenWidth=800, screenHeight=800;

float Angle2 = 0.0f;

float pathTime = 0;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::mat4 ProjectionMatrix;

std::shared_ptr<Shader> shader;

cubeMap map;

Shader* skyBox;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Plane* plane;

Model* obj;

Cart* cart;
Cart* cart1;

double lastX,lastY;
bool rideActive = false;

Cube* lightCube;

std::vector<Vertex> curvePositions;

Player*  player;

Camera cam(glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(-0.317,0.10059,-0.274781)));

int positionPointer = 0 , positionPointer1 = 0;

/**************** END OPENGL FUNCTIONS *************************/

void reshape(GLFWwindow * window,int width, int height)		// Resize the OpenGL window
{
    screenWidth = width;
    screenHeight = height;

    glViewport(0,0,screenWidth,screenHeight);// set Viewport dimensions

    //Calculate a projection matrix based on perspective viewing for 3d geometry
    ProjectionMatrix = glm::perspective(glm::radians(CameraManager::getCamera().Zoom), width / static_cast<float>(height), 0.1f, 200.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Update the camera position for the given point on the curve

    if(rideActive)
    {
        Spline::spline(curvePositions[positionPointer],curvePositions[positionPointer+1],curvePositions[positionPointer+2],curvePositions[positionPointer+3],pathTime,cart);
        Spline::spline(curvePositions[positionPointer1],curvePositions[positionPointer1+1],curvePositions[positionPointer1+2],curvePositions[positionPointer1+3],pathTime,cart1);
    }

/*
    glm::vec4 camPos = glm::vec4(0,0.08f,0,0);
    glm::mat4 mat = glm::mat4(1);
    mat = glm::rotate(mat, -cart1->Yaw, glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, cart1->Pitch, glm::vec3(0, 0, 1));
    mat = glm::rotate(mat,cart1->Roll,glm::vec3(1,0,0));
    camPos = mat * camPos;
    camPos += glm::vec4(cart1->getPosition(),0);
    PlayerCam.Position = camPos;
    PlayerCam.Pitch = glm::degrees(cart1->Pitch);
    PlayerCam.Yaw = -90-glm::degrees(cart1->Yaw);
    PlayerCam.Roll = glm::degrees(cart1->Roll);
*/

    shader->use();

    shader->setMat4("projection", ProjectionMatrix);

    shader->setVec3("lightColor", 2.0f, 2.0f, 2.0f);
    shader->setVec3("lightPos", lightPos);
    shader->setMat4("view",CameraManager::getCamera().GetViewMatrix());

    glm::mat4 model = glm::mat4(1.0f);

    shader->setMat4("model",model);
    plane->render();

    shader->setMat4("model",cart1->getModelMatrix());
    cart1->Draw(*shader);

    //std::cout << glm::degrees(cart1->Roll) << std::endl;

    shader->setMat4("model",cart->getModelMatrix());
    cart->Draw(*shader);

    shader->setMat4("model", obj->getTranslationMatrix());
    obj->Draw(*shader);

    shader->setMat4("model",player->getModelMatrix(cam));
    player->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    shader->setMat4("model", model);
    lightCube->render();

    skyBox->use();
    skyBox->setInt("skybox",0);
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glm::mat4 view =  glm::mat4(glm::mat3(CameraManager::getCamera().GetViewMatrix()));
    skyBox->setMat4("view", view);
    skyBox->setMat4("projection", ProjectionMatrix);

    //SkyBox:
    map.Render();
    //Update other values
    lightPos = glm::vec3(10*sin(Angle2),10,10*cos(Angle2));

    Angle2 > 360 ? Angle2 = 0 : Angle2 += 0.01f;
    if(rideActive)
    {
        if(pathTime > 1)
        {
            positionPointer == curvePositions.size() - 4 ? positionPointer = 0,rideActive = false : positionPointer += 3;
            positionPointer1 == curvePositions.size() - 4 ? positionPointer1 = 0 :positionPointer1 += 3;
            pathTime = 0;
        }
        else
        {
            pathTime += (0.1f*sin(-cart1->Pitch)+0.1f);
        }
    }
    PhysicsCollision::update(deltaTime);
    PhysicsCollision::detectCollision(deltaTime);
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);

    curvePositions = Spline::setupSpline("../Spline/Points1.txt","../Spline/TrackPoints1.txt");

    positionPointer1 = curvePositions.size() - 13;

    cart = new Cart(curvePositions[positionPointer].Position,"../Object/RollerCoaster/Cart.obj");
    cart1 = new Cart(curvePositions[positionPointer1].Position,"../Object/RollerCoaster/Cart.obj");

    //stbi_set_flip_vertically_on_load(false);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
    model = glm::scale(model,glm::vec3(10,10,10));
    obj = new Model("../Object/RollerCoaster/Rail001.obj");
    obj->setPosition(glm::vec3(0.0f, 0.0f, -20.0f));
    obj->setTranslationMatrix(model);

    shader = std::make_shared<Shader>("../DifferentShaders/basic.vert", "../DifferentShaders/basic.frag");

    skyBox = new Shader("../DifferentShaders/skyBox.vert","../DifferentShaders/skyBox.frag");

    plane = new Plane();

    lightCube = new Cube();
    lightCube->constructGeometry(-1,1,-1,1,-1,1);

    map.innit("../skyBoxTextures/Night/");

    player = new Player("../Object/RollerCoaster/Cart.obj",cam.Position);

    PhysicsCollision::addObject(obj);
    PhysicsCollision::addObject(player);
    PhysicsCollision::addObject(cart);
    PhysicsCollision::addObject(cart1);

    CameraManager::setCamera(player->PlayerCam);
    CameraManager::addCamera(player->PlayerCam);
    CameraManager::addCamera(cam);
    glEnable(GL_DEPTH_TEST);

}

void mouseMovement(GLFWwindow* window, double x, double y)
{
    CameraManager::getCamera().ProcessMouseMovement(lastX-x,lastY-y);
    lastY = y;
    lastX = x;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(FORWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(BACKWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(LEFT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(RIGHT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(UP,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        CameraManager::getCamera().ProcessKeyboard(DOWN,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        std::cout << CameraManager::getCamera().Position.x << std::endl;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        rideActive = true;
}

int main(int argc, char **argv)
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(screenWidth,screenHeight,"Screen", glfwGetPrimaryMonitor(),nullptr);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    reshape(window,screenWidth,screenHeight);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window,reshape);
    glfwSetCursorPosCallback(window, mouseMovement);
    glfwSwapInterval(1);

    init();

    while(!glfwWindowShouldClose(window))
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        display();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
