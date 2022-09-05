#pragma once
#include <cstdio>
#include "AL/al.h"
#include <iostream>
#include <vector>
#include <AL/alc.h>

#include "Device.h"

#define alCall(function, ...) nutmeg::alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
#define alcCall(function, device, ...) nutmeg::alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

namespace nutmeg {

 

}