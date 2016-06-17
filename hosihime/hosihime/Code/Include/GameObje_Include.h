#ifndef _GAMEOBJE_INCLUDE_H_
#define _GAMEOBJE_INCLUDE_H_

#include "GameObject.h"
#include "Star.h"
#include <memory>
typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::shared_ptr<Star> Star_Ptr;
#endif
