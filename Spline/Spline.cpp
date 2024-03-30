//
// Created by arthur on 3/3/24.
//

#include "Spline.h"



void Spline::spline(const Vertex& p0, const Vertex& p1, const Vertex& p2, const Vertex& p3, float t, Cart* cart,float alpha)
{
    static bool change;
    static bool rollChange;
    if(t == 0)
    {
        change = true;
        rollChange = true;
    }
    float t0 = 0.0f;
    float t1 = t0 + pow(distance(p0.Position, p1.Position), alpha);
    float t2 = t1 + pow(distance(p1.Position, p2.Position), alpha);
    float t3 = t2 + pow(distance(p2.Position, p3.Position), alpha);

    // Linear interpolation between points. This is so all points are reached over the tome period
    t = lerp(t0,t3,t);

    glm::vec3 A1 = ( t1-t )/( t1-t0 )*p0.Position + ( t-t0 )/( t1-t0 )*p1.Position;
    glm::vec3 A2 = ( t2-t )/( t2-t1 )*p1.Position + ( t-t1 )/( t2-t1 )*p2.Position;
    glm::vec3 A3 = ( t3-t )/( t3-t2 )*p2.Position + ( t-t2 )/( t3-t2 )*p3.Position;

    glm::vec3 B1 = ( t2-t )/( t2-t0 )*A1 + ( t-t0 )/( t2-t0 )*A2;
    glm::vec3 B2 = ( t3-t )/( t3-t1 )*A2 + ( t-t1 )/( t3-t1 )*A3;

    cart->Position  = ( t2-t )/( t2-t1 )*B1 + ( t-t1 )/( t2-t1 )*B2;

    float F1 = ( t1-t )/( t1-t0 )*p0.Pitch + ( t-t0 )/( t1-t0 )*p1.Pitch;
    float F2 = ( t2-t )/( t2-t1 )*p1.Pitch + ( t-t1 )/( t2-t1 )*p2.Pitch;
    float F3 = ( t3-t )/( t3-t2 )*p2.Pitch + ( t-t2 )/( t3-t2 )*p3.Pitch;

    float G1 = ( t2-t )/( t2-t0 )*F1 + ( t-t0 )/( t2-t0 )*F2;
    float G2 = ( t3-t )/( t3-t1 )*F2 + ( t-t1 )/( t3-t1 )*F3;

    cart->Pitch = ( t2-t )/( t2-t1 )*G1 + ( t-t1 )/( t2-t1 )*G2;

    if(change)
    {
        float temp = cart->Yaw;

        float D1 = ( t1-t )/( t1-t0 )*p0.Yaw + ( t-t0 )/( t1-t0 )*p1.Yaw;
        float D2 = ( t2-t )/( t2-t1 )*p1.Yaw + ( t-t1 )/( t2-t1 )*p2.Yaw;
        float D3 = ( t3-t )/( t3-t2 )*p2.Yaw + ( t-t2 )/( t3-t2 )*p3.Yaw;

        float E1 = ( t2-t )/( t2-t0 )*D1 + ( t-t0 )/( t2-t0 )*D2;
        float E2 = ( t3-t )/( t3-t1 )*D2 + ( t-t1 )/( t3-t1 )*D3;

        cart->Yaw = std::fmod( ( t2-t )/( t2-t1 )*E1 + ( t-t1 )/( t2-t1 )*E2 ,glm::radians(360.0f));

        if(abs(cart->Yaw - temp) > glm::radians(10.0f))
        {
            cart->Yaw = -temp;
            change = false;
        }
    }
    if(rollChange)
    {
        float temp = cart->Roll;

        float H1 = ( t1-t )/( t1-t0 )*p0.Rotation + ( t-t0 )/( t1-t0 )*p1.Rotation;
        float H2 = ( t2-t )/( t2-t1 )*p1.Rotation + ( t-t1 )/( t2-t1 )*p2.Rotation;
        float H3 = ( t3-t )/( t3-t2 )*p2.Rotation + ( t-t2 )/( t3-t2 )*p3.Rotation;

        float I1 = ( t2-t )/( t2-t0 )*H1 + ( t-t0 )/( t2-t0 )*H2;
        float I2 = ( t3-t )/( t3-t1 )*H2 + ( t-t1 )/( t3-t1 )*H3;

        cart->Roll = ( t2-t )/( t2-t1 )*I1 + ( t-t1 )/( t2-t1 )*I2;

        if(abs(cart->Roll - temp) > glm::radians(45.0f))
        {
            cart->Roll = -temp;
            rollChange = false;
        }
    }
}

std::vector<Vertex> Spline::setupSpline(const char* filePath,const char* trackFilePath)
{
    std::vector<Vertex> trackPoints;
    std::vector<Vertex> curvePositions;
    std::string line;
    std::ifstream file(filePath);
    std::string temp;
    while (getline (file, line))
    {
        float posX,posY,posZ;
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
        temp = "";
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


        // Applying cosine rule to get the angle
        curvePositions[i].Rotation = acos((pow(b, 2) + 1 - pow(a, 2)) / (2 * b));

        //Getting the rotational point with respect to the cart position
        //If the value of z is less than 0 it is to the left so inverse the angle as cosine rule only gives the
        //magnitude of the angle not the direction
        glm::vec4 vector = glm::vec4(curvePositions[i].Position,0) - glm::vec4(trackPoints[i].Position,0);
        vector = glm::inverse(mat) * vector;
        curvePositions[i].Rotation = vector.z < 0 ? curvePositions[i].Rotation *= -1 : curvePositions[i].Rotation;
    }

    return curvePositions;
}