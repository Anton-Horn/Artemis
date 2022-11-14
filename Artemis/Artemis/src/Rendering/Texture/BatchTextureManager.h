#pragma once

#include "Core\Core.h"



class BatchTextureManager
{

private:


	static uint32_t* s_Textures;
	static int s_TextureUnitCount;

	static int s_TextureSlots;

public:

	static void Init(int textureslots);
	static void Shutdown();

	static void NewBatch();

	static bool CheckTexture(uint32_t textureid, float*);
	static float AddTexture(uint32_t textureid);

	static bool IsOccupied();

	static uint32_t* GetTextureIDs();

};


