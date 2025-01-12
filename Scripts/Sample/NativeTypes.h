#pragma once

#define _VOID void*
#define _float UINT32

typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef int AnimScene;
typedef int ItemSet;
typedef int Volume;
typedef int PersChar;
typedef int PopZone;
typedef int Prompt;
typedef int PropSet;

typedef unsigned int Hash;

typedef unsigned int Void;
typedef unsigned int Any;
typedef unsigned int uint;


#define ALIGN8 __declspec(align(8))

struct Vector3
{
	ALIGN8 float x;
	ALIGN8 float y;
	ALIGN8 float z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

static_assert(sizeof(Vector3) == 24, "");