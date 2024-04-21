//
// Created by arthur on 4/1/24.
//

#include "Player.h"

void Player::resolveCollision(float& deltaTime,Object* obj)
{
    std::cout << "Player Collision" << std::endl;
}

void Player::ProcessKeyboard(Camera_Movement direction)
{
    if (direction == FORWARD)
        setForce({PlayerCam.Front.x,this->Velocity.y,PlayerCam.Front.z});
    if (direction == BACKWARD)
        setForce({-PlayerCam.Front.x,this->Velocity.y,-PlayerCam.Front.z});
    if (direction == LEFT)
        setForce({-glm::normalize(glm::cross(PlayerCam.Front, PlayerCam.Up)).x,this->Velocity.y,-glm::normalize(glm::cross(PlayerCam.Front, PlayerCam.Up)).z});
    if (direction == RIGHT)
        setForce({glm::normalize(glm::cross(PlayerCam.Front, PlayerCam.Up)).x,this->Velocity.y,glm::normalize(glm::cross(PlayerCam.Front, PlayerCam.Up)).z});
    if (direction == UP)
        setForce({this->Velocity.x,this->Velocity.y,this->Velocity.z});
}
