#pragma once

// Created with ReClass.NET 1.2 by KN4CK3R

class PlayerCharacterData
{
public:
	char pad_0000[512]; //0x0000
	float swimSpeed; //0x0200
	char pad_0204[12]; //0x0204
	float N00000095; //0x0210
	float N000000E9; //0x0214
	float N00000096; //0x0218
	float N000000EB; //0x021C
	char pad_0220[380]; //0x0220
	float someFloat1; //0x039C
	float someFloat2; //0x03A0
}; //Size: 0x03A4
static_assert(sizeof(PlayerCharacterData) == 0x3A4);

class PlayerBreathHandlerData
{
public:
	char pad_0000[148]; //0x0000
	float oxygen; //0x0094
}; //Size: 0x0098
static_assert(sizeof(PlayerBreathHandlerData) == 0x98);