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


//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


int screenWidth=800, screenHeight=800;

float Angle = 0.0f;

float Angle2 = 0.0f;

float pathTime = 0;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::mat4 ProjectionMatrix;

std::shared_ptr<Shader> shader;

cubeMap map;

Shader* skyBox;

Camera cam(glm::vec3(0,0,-20)+    (    glm::vec3(10,10,10)*glm::vec3(-0.347193,0.10059,-0.274781)      )    );

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Plane* plane;

Model* obj;

Cart* cart;
Cart* cart1;

double lastX,lastY;
bool first = true;

Cube* lightCube;

std::vector<Vertex> curvePositions;
std::vector<Vertex> trackPoints;
int positionPointer = 0 , positionPointer1 = 12;

float rollAngle = 0;


/**************** END OPENGL FUNCTIONS *************************/

void reshape(GLFWwindow * window,int width, int height)		// Resize the OpenGL window
{
    screenWidth = width;
    screenHeight = height;

    glViewport(0,0,width,height);						// set Viewport dimensions

    //Calculate a projection matrix based on perspective viewing for 3d geometry
    ProjectionMatrix = glm::perspective(glm::radians(cam.Zoom), width / static_cast<float>(height), 0.1f, 200.0f);
}
void setupSpline(const char* filePath,const char* trackFilePath)
{
    std::string line;
    ifstream file(filePath);
    while (getline (file, line))
    {
        float posX,posY,posZ;
        string temp;
        int point = 0;
        for(char i : line)
        {
            if(i != ' ')
            {
                temp += i;
            }
            else
            {
                switch(point)
                {
                    case 0:
                        posX = stof(temp);
                        break;
                    case 1:
                        posZ = -stof(temp);
                        break;
                    case 2:
                        posY = stof(temp);
                        break;
                        default:
                            break;
                }
                point == 2 ? point = 0 :point += 1;
                temp = "";
            }
        }
        curvePositions.emplace_back(glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(posX,posY,posZ)),0,0,0);
    }
    file.close();
    file.open(trackFilePath);
    while (getline (file, line))
    {
        float posX,posY,posZ;
        string temp;
        int point = 0;
        for(char i : line)
        {
            if(i != ' ')
            {
                temp += i;
            }
            else
            {
                switch(point)
                {
                    case 0:
                        posX = stof(temp);
                        break;
                    case 1:
                        posZ = -stof(temp);
                        break;
                    case 2:
                        posY = stof(temp);
                        break;
                    default:
                        break;
                }
                point == 2 ? point = 0 :point += 1;
                temp = "";
            }
        }
        trackPoints.emplace_back(glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(posX,posY,posZ)),0,0,0);
    }
    file.close();
    for(int i = 1 ; i<curvePositions.size() - 1;i++)
    {
        float distance = sqrt(pow(curvePositions[i + 1].Position.x - curvePositions[i].Position.x, 2)
                              + pow(curvePositions[i + 1].Position.y - curvePositions[i].Position.y, 2) +
                              pow(curvePositions[i + 1].Position.z - curvePositions[i].Position.z, 2));

        curvePositions[i].Pitch = asin((curvePositions[i + 1].Position.y - curvePositions[i].Position.y) / distance);
        curvePositions[i].Yaw = atan2((float) (curvePositions[i + 1].Position.z - curvePositions[i].Position.z),
                                      (float) (curvePositions[i + 1].Position.x - curvePositions[i].Position.x));

        glm::vec4 normal = glm::vec4(0, 1, 0, 0);
        glm::mat4 mat = glm::mat4(1);
        mat = glm::rotate(mat, -curvePositions[i].Yaw, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, curvePositions[i].Pitch, glm::vec3(0, 0, 1));
        normal = mat * normal;
        normal += glm::vec4(trackPoints[i].Position, 0);

        float b = sqrt(pow(curvePositions[i].Position.x - trackPoints[i].Position.x, 2)
                       + pow(curvePositions[i].Position.y - trackPoints[i].Position.y, 2) +
                       pow(curvePositions[i].Position.z - trackPoints[i].Position.z, 2));

        float a = sqrt(pow(curvePositions[i].Position.x - normal.x, 2)
                       + pow(curvePositions[i].Position.y - normal.y, 2) +
                       pow(curvePositions[i].Position.z - normal.z, 2));

        curvePositions[i].Rotation = acos((pow(b, 2) + 1 - pow(a, 2)) / (2 * b));
        glm::vec4 vector = glm::vec4(curvePositions[i].Position,0) - glm::vec4(trackPoints[i].Position,0);
        vector = glm::inverse(mat) * vector;
        curvePositions[i].Rotation = vector.z < 0 ? curvePositions[i].Rotation *= -1 : curvePositions[i].Rotation;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Update the camera position for the given point on the curve

    Spline::spline(curvePositions[positionPointer],curvePositions[positionPointer+1],curvePositions[positionPointer+2],curvePositions[positionPointer+3],pathTime,cart);
    Spline::spline(curvePositions[positionPointer1],curvePositions[positionPointer1+1],curvePositions[positionPointer1+2],curvePositions[positionPointer1+3],pathTime,cart1);

/*
    glm::vec4 camPos = glm::vec4(0,0.08f,0,0);
    glm::mat4 mat = glm::mat4(1);
    mat = glm::rotate(mat, -cart1->Yaw, glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, cart1->Pitch, glm::vec3(0, 0, 1));
    mat = glm::rotate(mat,cart1->Roll,glm::vec3(1,0,0));
    camPos = mat * camPos;
    camPos += glm::vec4(cart1->Position,0);
    cam.Position = camPos;
    cam.Pitch = glm::degrees(cart1->Pitch);
    cam.Yaw = -90-glm::degrees(cart1->Yaw);
    cam.Roll = glm::degrees(cart1->Roll);
*/

    shader->use();

    shader->setMat4("projection", ProjectionMatrix);

    shader->setVec3("lightColor", 2.0f, 2.0f, 2.0f);
    shader->setVec3("lightPos", lightPos);
    shader->setMat4("view",cam.GetViewMatrix());

    glm::mat4 model = glm::mat4(1.0f);

    shader->setMat4("model",model);
    plane->render();

    shader->setMat4("model",cart->getModelMatrix());

    cart->Draw(*shader);

    shader->setMat4("model",cart1->getModelMatrix());

    cart1->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
    model = glm::scale(model,glm::vec3(10,10,10));
    shader->setMat4("model", model);
    //Ride
    obj->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    shader->setMat4("model", model);
    lightCube->render();

    skyBox->use();
    skyBox->setInt("skybox",0);
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glm::mat4 view =  glm::mat4(glm::mat3(cam.GetViewMatrix()));
    skyBox->setMat4("view", view);
    skyBox->setMat4("projection", ProjectionMatrix);

    //SkyBox:
    map.Render();

    //Update other values
    lightPos = glm::vec3(10*sin(Angle2),10,10*cos(Angle2));

    Angle > 360 ? Angle = 0 : Angle += 0.1f;

    Angle2 > 360 ? Angle2 = 0 : Angle2 += 0.01f;

    if(pathTime > 1)
    {
        positionPointer == curvePositions.size() - 4 ? positionPointer = 0 : positionPointer += 3;
        positionPointer1 == curvePositions.size() - 4 ? positionPointer1 = 0 :positionPointer1 += 3;
        pathTime = 0;
    }
    else
    {
        pathTime += 0.2f*(0.5f*sin(-cart1->Pitch)+0.5f);
        //cam.Zoom = 45-(20*(0.5f*sin(-cart1->Pitch)+0.5f));
    }
    rollAngle == 1 ? rollAngle =  0 : rollAngle+=0.1f;
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);

    setupSpline("../Spline/Points1.txt","../Spline/TrackPoints1.txt");

    cart = new Cart("../Object/RollerCoaster/Cart.obj");
    cart1 = new Cart("../Object/RollerCoaster/Cart.obj");

    //stbi_set_flip_vertically_on_load(false);

    obj = new Model("../Object/RollerCoaster/Rail001.obj");

    shader = std::make_shared<Shader>("../DifferentShaders/basic.vert", "../DifferentShaders/basic.frag");

    skyBox = new Shader("../DifferentShaders/skyBox.vert","../DifferentShaders/skyBox.frag");

    plane = new Plane();

    lightCube = new Cube();
    lightCube->constructGeometry(-1,1,-1,1,-1,1);

    map.innit("../skyBoxTextures/Night/");

    glEnable(GL_DEPTH_TEST);

}

void mouseMovement(GLFWwindow* window, double x, double y)
{
    if(!first)
    {
        lastX = x;
        lastY = y;
        first = false;
    }
    cam.ProcessMouseMovement(lastX-x,lastY-y);
    lastY = y;
    lastX = x;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboard(FORWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboard(BACKWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboard(LEFT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboard(RIGHT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.ProcessKeyboard(UP,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.ProcessKeyboard(DOWN,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        std::cout << cam.Roll << std::endl;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam.Roll +=glm::radians(1.0f);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam.Roll -=glm::radians(1.0f);
}

// FREEGLUT WINDOW SET UP
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
