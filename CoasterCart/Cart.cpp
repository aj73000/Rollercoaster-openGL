//
// Created by arthur on 4/10/24.
//
#include "Cart.h"

void Cart::resolveCollision(float& deltaTime, Object *obj)
{
    CameraManager::setCamera(this->cam);
    CameraManager::setInCart(true);
}
