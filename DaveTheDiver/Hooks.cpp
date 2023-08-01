#include "Hooks.h"
#include "MinHook.h"
#include "Game.h"
#include <iostream>

extern MyGame g_Game;

tPlayerCharacter$$Update oPlayerCharacter$$Update = NULL;
uintptr_t PlayerCharacter$$UpdateOffset = 0x244A640;

tPlayerBreathHandler$$Update oPlayerBreathHandler$$Update = NULL;
uintptr_t PlayerBreathHandler$$UpdateOffset = 0x242CF90;

tStaffDave$$Update oStaffDave$$Update = NULL;
uintptr_t StaffDave$$UpdateOffset = 0x2A72A90;

tLootBox$$CheckOverloadedState oLootBox$$CheckOverLoadedState = NULL;
uintptr_t LootBox$$CheckOverLoadedStateOffset = 0x2FD3D00;


tLootBox$$Add oLootBox$$Add = NULL;
uintptr_t LootBox$$AddOffset = 0x2FD37A0;


void hPlayerCharacter$$Update(void* player, void* method)
{
	static bool bInited = false;
	//printf("Player: %p\n", player);

	PlayerCharacterData* PlayerCharacter = (PlayerCharacterData*)player;
	if (!bInited)
	{
		g_Game.playerCharacter.swimSpeed = PlayerCharacter->swimSpeed;
		bInited = true;
	}
	PlayerCharacter->swimSpeed = g_Game.playerCharacter.swimSpeed;
	g_Game.playerCharacter.swimSpeed = PlayerCharacter->swimSpeed;

	oPlayerCharacter$$Update(player, method);
}

void hPlayerBreathHandler$$Update(void* handler, void* method)
{
	static bool bInited = false;
	PlayerBreathHandlerData* breathHandler = (PlayerBreathHandlerData*)handler;
	if (!bInited)
	{
		g_Game.breathHandler.oxygen = breathHandler->oxygen;
		bInited = true;
	}
	breathHandler->oxygen = g_Game.breathHandler.oxygen;
	g_Game.breathHandler.oxygen = breathHandler->oxygen;
	oPlayerBreathHandler$$Update(handler, method);
}

bool hLootBox$$CheckOverLoadedState(void* box, int tid, void* method)
{
	printf("Box: %p\n", box);

	//return oLootBox$$CheckOverLoadedState(box, tid, method);
	return false;
}


void hStaffDave$$Update(void* dave, void* method)
{
	printf("Dave: %p\n", dave);
	oStaffDave$$Update(dave, method);
}


bool hLootBox$$Add(void* box, int id, int count, int bonusgrade, int lifttype, bool updatemissioncount, void* method)
{
	return oLootBox$$Add(box, id, count * g_Game.itemCountMutiply, bonusgrade, lifttype, updatemissioncount, method);
}

int init_hooks()
{
	uintptr_t moduleBase = (uintptr_t)GetModuleHandleA("GameASsembly.dll");
	int status = 0;

	if ((status = MH_CreateHook((LPVOID)(moduleBase + PlayerCharacter$$UpdateOffset), hPlayerCharacter$$Update, (LPVOID*)&oPlayerCharacter$$Update)) != MH_OK)
	{
		return status;
	}

	if ((status = MH_CreateHook((LPVOID)(moduleBase + PlayerBreathHandler$$UpdateOffset), hPlayerBreathHandler$$Update, (LPVOID*)&oPlayerBreathHandler$$Update)) != MH_OK)
	{
		return status;
	}

	if ((status = MH_CreateHook((LPVOID)(moduleBase + LootBox$$CheckOverLoadedStateOffset), hLootBox$$CheckOverLoadedState, (LPVOID*)&oLootBox$$CheckOverLoadedState)) != MH_OK)
	{
		return status;
	}

	if ((status = MH_CreateHook((LPVOID)(moduleBase + StaffDave$$UpdateOffset), hStaffDave$$Update, (LPVOID*)&oStaffDave$$Update)) != MH_OK)
	{
		return status;
	}

	if ((status = MH_CreateHook((LPVOID)(moduleBase + LootBox$$AddOffset), hLootBox$$Add, (LPVOID*)&oLootBox$$Add)) != MH_OK)
	{
		return status;
	}

	if ((status = MH_EnableHook(MH_ALL_HOOKS)) != MH_OK)
	{
		return status;
	}
}