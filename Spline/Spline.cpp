//
// Created by arthur on 3/3/24.
//

#include "Spline.h"



void Spline::spline(const Vertex& p0, const Vertex& p1, const Vertex& p2, const Vertex& p3, float t, Cart* cart,float alpha)
{
    static bool change;
    if(t == 0)
        change = true;

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

    float F1 = ( t1-t )/( t1-t0 )*p0.Pitch + ( t-t0 )/( t1-t0 )*p1.Pitch;
    float F2 = ( t2-t )/( t2-t1 )*p1.Pitch + ( t-t1 )/( t2-t1 )*p2.Pitch;
    float F3 = ( t3-t )/( t3-t2 )*p2.Pitch + ( t-t2 )/( t3-t2 )*p3.Pitch;

    float G1 = ( t2-t )/( t2-t0 )*F1 + ( t-t0 )/( t2-t0 )*F2;
    float G2 = ( t3-t )/( t3-t1 )*F2 + ( t-t1 )/( t3-t1 )*F3;

    cart->Pitch = ( t2-t )/( t2-t1 )*G1 + ( t-t1 )/( t2-t1 )*G2;

    if((( t1-t )/( t1-t0 )))
        cart->Roll = p0.Rotation;
    if((( t2-t )/( t2-t1 )))
        cart->Roll = p1.Rotation;
    if((( t3-t )/( t3-t2 )))
        cart->Roll = p2.Rotation;
    if((( t-t2 )/( t3-t2 )))
        cart->Roll = p3.Rotation;
    /*
    float H1 = ( t1-t )/( t1-t0 )*p0.Rotation + ( t-t0 )/( t1-t0 )*p1.Rotation;
    float H2 = ( t2-t )/( t2-t1 )*p1.Rotation + ( t-t1 )/( t2-t1 )*p2.Rotation;
    float H3 = ( t3-t )/( t3-t2 )*p2.Rotation + ( t-t2 )/( t3-t2 )*p3.Rotation;

    float I1 = ( t2-t )/( t2-t0 )*H1 + ( t-t0 )/( t2-t0 )*H2;
    float I2 = ( t3-t )/( t3-t1 )*H2 + ( t-t1 )/( t3-t1 )*H3;

    cart->Roll = ( t2-t )/( t2-t1 )*I1 + ( t-t1 )/( t2-t1 )*I2;
     */
}