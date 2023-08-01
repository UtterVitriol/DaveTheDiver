#pragma once
#include <windows.h>
#include "GameData.h"

//struct ObscuredIntFields
//{
//	int32_t cryptokey;
//	int32_t hiddenvalue;
//	bool inited;
//	int32_t fakevalue;
//	bool fakeValueActive;
//};
//struct ObscuredInt
//{
//	struct ObscuredIntFields fields;
//};

/// <summary>
/// void PlayerCharacter$$Update(PlayerCharacter_o *__this,MethodInfo *method)
/// </summary>
typedef void* (*tPlayerCharacter$$Update)(void*, void*);
void hPlayerCharacter$$Update(void* player, void* method);

/// <summary>
/// void PlayerBreathHandler$$Update(PlayerBreathHandler_o *__this,MethodInfo *method)
/// </summary>
typedef void* (*tPlayerBreathHandler$$Update)(void*, void*);
void hPlayerBreathHandler$$Update(void* player, void* method);


// bool LootBox$$CheckOverloadedState(LootBox_o *__this,int32_t tid,MethodInfo *method)
typedef bool (*tLootBox$$CheckOverloadedState)(void*, int, void*);
bool hLootBox$$CheckOverLoadedState(void* box, int tid, void* method);

// void StaffDave$$Update(StaffDave_o *__this,MethodInfo *method)
typedef void* (*tStaffDave$$Update)(void*,void*);
void hStaffDave$$Update(void* dave, void* method);

// bool LootBox$$Add(LootBox_o *__this,int32_t id,int32_t count,int32_t bonusGrade,int32_t liftType, bool bUpdateMissionCnt, MethodInfo* method)
typedef bool (*tLootBox$$Add)(void*, int, int, int, int, bool, void*);
bool hLootBox$$Add(void* box, int id, int count, int bonusgrade, int lifttype, bool updatemissioncount, void* method);


int init_hooks();

// CharacterStatus_SO 0x98
// PlayerMoveProperty 0x80