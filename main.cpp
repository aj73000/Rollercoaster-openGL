#include <iostream>
#include <memory>
using namespace std;

#include <cmath>     //sin and cos included in this header file.
#include <ctime>

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
#include "Physics/boundaries.h"
#include "Shadows/DepthMap.h"


//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

int screenWidth=800, screenHeight=800;

float Angle2 = 0.0f;

float pathTime = 0;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::mat4 ProjectionMatrix;

Shader* shader;

cubeMap map;

Shader* skyBox;

Shader* heightMapShader;
Shader* heightMapShaderGrass;
Shader* depthMapShader;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

glm::vec4 treePositions[3] = {{0,0,0.5f,10},{0,0,-0.5f,200},{-0.5f,0,0.5f,45}};

Plane* plane;

Model* obj;

Model* tree;

Cart* cart;

DepthMap* shaderMap;

double lastX,lastY;
bool rideActive = false;

Cube* lightCube;

std::vector<Vertex> curvePositions;

Player*  player;

Camera worldCam(glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(-1.347193,0.25059,-0.774781)));
Camera groundLookAtCam(glm::vec3(-5,0.1,-20));

int positionPointer = 0;


/**************** END OPENGL FUNCTIONS *************************/

void renderScene(Shader* shader);

void reshape(GLFWwindow * window,int width, int height)		// Resize the OpenGL window
{
    screenWidth = width;
    screenHeight = height;

    glViewport(0,0,screenWidth,screenHeight);// set Viewport dimensions
    //Calculate a projection matrix based on perspective viewing for 3d geometry
    ProjectionMatrix = glm::perspective(glm::radians(CameraManager::getCamera().Zoom), (float)width / static_cast<float>(height), 0.1f, 200.0f);
}

void display()
{
//Shadows
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 lightProjection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,1.0f,7.5f);
    glm::mat4 lightView = glm::lookAt(lightPos,glm::vec3(0,0,-20),glm::vec3(0.0,1.0,0.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    depthMapShader->use();
    depthMapShader->setMat4("lightSpaceMatrix",lightSpaceMatrix);

    shaderMap->bindFBO();
    glClear(GL_DEPTH_BUFFER_BIT);
    renderScene(depthMapShader);
    glBindFramebuffer(GL_FRAMEBUFFER,0);

//=========================================================================================================================

    glViewport(0,0,screenWidth,screenHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();

    shader->setMat4("projection", ProjectionMatrix);
    shader->setMat4("view",CameraManager::getCamera().GetViewMatrix());

    shader->setVec3("viewPos",CameraManager::getCamera().Position);
    shader->setVec3("lightPos", lightPos);
    //Lighting add cone/directional lights here
    shader->setVec3("lightColor", 2.0f, 2.0f, 2.0f);
    shader->setMat4("lightSpaceMatrix",lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,shaderMap->depthMap);
    renderScene(shader);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view =   glm::mat4(glm::mat3(CameraManager::getCamera().GetViewMatrix()));
    skyBox->use();
    skyBox->setInt("skybox",0);
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    view =  glm::mat4(glm::mat3(CameraManager::getCamera().GetViewMatrix()));
    skyBox->setMat4("view", view);
    skyBox->setMat4("projection", ProjectionMatrix);

    //SkyBox:
    map.Render();
    //Update other values

    glEnable(GL_CULL_FACE);
    model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(-30,-9.5f,-50));
    heightMapShader->use();
    heightMapShader->setMat4("projection", ProjectionMatrix);
    heightMapShader->setMat4("view",CameraManager::getCamera().GetViewMatrix());
    heightMapShader->setMat4("model",model);
    plane->render();

    heightMapShaderGrass->use();
    heightMapShaderGrass->setMat4("projection", ProjectionMatrix);
    heightMapShaderGrass->setMat4("view",CameraManager::getCamera().GetViewMatrix());
    heightMapShaderGrass->setMat4("model",model);
    plane->render();
    glDisable(GL_CULL_FACE);

    //lightPos = glm::vec3(10*sin(Angle2),10,10*cos(Angle2));


    lightPos = glm::vec3(0,10,-20);
    Angle2 > 360 ? Angle2 = 0 : Angle2 += 0.01f;
    if(rideActive)
    {
        //Update the camera position for the given point on the curve
        Spline::spline(curvePositions[positionPointer],curvePositions[positionPointer+1],curvePositions[positionPointer+2],curvePositions[positionPointer+3],pathTime,cart);
        if(pathTime > 1)
        {
            positionPointer == curvePositions.size() - 4 ? positionPointer = 0,rideActive = false : positionPointer += 3;
            pathTime = 0;
        }
        else
        {
            pathTime += (0.1f*sin(-cart->Pitch)+0.1f);
        }
    }
    if(&CameraManager::getCamera() == &groundLookAtCam )
    {
        float distance = sqrt(pow(cart->getPosition().x - groundLookAtCam.Position.x, 2)
                              + pow(cart->getPosition().y - groundLookAtCam.Position.y, 2) +
                              pow(cart->getPosition().z - groundLookAtCam.Position.z, 2));

        groundLookAtCam.Pitch = glm::degrees(asin((cart->getPosition().y - groundLookAtCam.Position.y) / distance));
        groundLookAtCam.Yaw = glm::degrees(glm::radians(-90.0f)-atan2((float) (cart->getPosition().z - groundLookAtCam.Position.z),
                                                                      (float) (cart->getPosition().x - groundLookAtCam.Position.x)));
    }
    cart->update();
    PhysicsCollision::update(deltaTime);
    PhysicsCollision::detectCollision(deltaTime);

}

void renderScene(Shader* shader1)
{
    glm::mat4 model = glm::mat4(1.0f);

    shader1->setMat4("model",cart->getModelMatrix());
    cart->Draw(*shader1);

    shader1->setMat4("model", obj->getTranslationMatrix());
    obj->Draw(*shader1);
    tree->Draw(*shader1);


    for(glm::vec4 position : treePositions)
    {
        model = glm::translate(tree->getTranslationMatrix(),glm::vec3(position.x,position.y,position.z));
        model = glm::rotate(model,glm::radians(position.w),glm::vec3(0,1,0));
        shader1->setMat4("model", model);
        tree->Draw(*shader1);
    }
    shader1->setMat4("model",player->getModelMatrix());
    player->Draw(*shader1);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    shader1->setMat4("model", model);
    //lightCube->render();

}

void init()
{
    glClearColor(0.1,0.1,0.1,1.0);

    curvePositions = Spline::setupSpline("../Spline/Points1.txt","../Spline/TrackPoints1.txt");

    cart = new Cart(curvePositions[positionPointer].Position,"../Object/RollerCoaster/Cart.obj");

    //stbi_set_flip_vertically_on_load(false);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
    model = glm::scale(model,glm::vec3(10,10,10));
    obj = new Model("../Object/RollerCoaster/Rail001.obj");
    obj->setPosition(glm::vec3(0.0f, 0.0f, -20.0f));
    obj->setTranslationMatrix(model);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
    model = glm::scale(model,glm::vec3(10,10,10));
    tree = new Model("../Object/Tree/source/tree.obj");
    tree->setTranslationMatrix(model);

    depthMapShader = new Shader("../DifferentShaders/simpleDepthShader.vert","../DifferentShaders/simpleDepthShader.frag",0,0,0);

    shader = new Shader("../DifferentShaders/basic.vert", "../DifferentShaders/basic.frag",nullptr,
                                      nullptr, nullptr);

    heightMapShader = new Shader("../DifferentShaders/heightShader.vert","../DifferentShaders/heightShader.frag","../DifferentShaders/heightShader.tesc",
                                 "../DifferentShaders/heightShader.tese", "../DifferentShaders/terrainGeom.geom");

    heightMapShaderGrass = new Shader("../DifferentShaders/heightShader.vert","../DifferentShaders/heightShader.frag","../DifferentShaders/heightShader.tesc",
                                     "../DifferentShaders/heightShader.tese", "../DifferentShaders/heightShader.geom");

    skyBox = new Shader("../DifferentShaders/skyBox.vert","../DifferentShaders/skyBox.frag",nullptr,nullptr,nullptr);

    plane = new Plane(heightMapShader);

    lightCube = new Cube();
    lightCube->constructGeometry(-1,1,-1,1,-1,1);

    shaderMap = new DepthMap(shader);

    map.innit("../skyBoxTextures/Night/");

    player = new Player("../Object/RollerCoaster/Cart.obj",(glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(-0.317193,0.10059,-0.308781))));

    boundaries b1 = {1,1,1,1,1,1};

    boundaries b2 = {1,1,1,1,1,1};

    boundaries b3 = {1,1,1,1,1,1};

    boundaries b4 = {1,1,1,1,1,1};

    PhysicsCollision::addObject(obj);
    PhysicsCollision::addObject(player);
    PhysicsCollision::addObject(cart);

    CameraManager::setCamera(groundLookAtCam);

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
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        rideActive = true;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        CameraManager::setCamera(player->PlayerCam);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        CameraManager::setCamera(worldCam);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        CameraManager::setCamera(cart->cam);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        CameraManager::setCamera(groundLookAtCam);

if(&CameraManager::getCamera() != &groundLookAtCam )
{
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (CameraManager::isInCart() && !rideActive) {
            CameraManager::setCamera(player->PlayerCam);
            CameraManager::setInCart(false);
        }
    }
    if (&CameraManager::getCamera() == &player->PlayerCam) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            player->ProcessKeyboard(FORWARD);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            player->ProcessKeyboard(BACKWARD);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player->ProcessKeyboard(LEFT);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player->ProcessKeyboard(RIGHT);
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            rideActive = true;
    } else {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            CameraManager::getCamera().ProcessKeyboard(DOWN, deltaTime);
    }
}
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

    glEnable(GL_DEPTH_TEST);
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

    free(player);
    free(skyBox);
    free(plane);
    free(cart);
    free(obj);
    return 0;
}
