
#include "BatchTextureManager.h"

#include "Core\Log.h"



uint32_t* BatchTextureManager::s_Textures;
int BatchTextureManager::s_TextureSlots;
int BatchTextureManager::s_TextureUnitCount;

void BatchTextureManager::Init(int textureslots)
{
	s_TextureSlots = textureslots;
	s_TextureUnitCount = 1;
	s_Textures = new uint32_t[textureslots];
}

void BatchTextureManager::Shutdown()
{
	delete[] s_Textures;
}
void BatchTextureManager::NewBatch()
{
	s_TextureUnitCount = 1;
}
bool BatchTextureManager::CheckTexture(uint32_t textureid, float* result)
{
	for (int i = 1; i < s_TextureUnitCount; i++) {
		if (s_Textures[i] == textureid) {	
			*result = (float) i;
			return true;
		}
	}
	return false;
}

float BatchTextureManager::AddTexture(uint32_t textureid)
{
	s_Textures[s_TextureUnitCount] = textureid;
	s_TextureUnitCount++;
	return (float) (s_TextureUnitCount - 1);
}

bool BatchTextureManager::IsOccupied()
{
	return s_TextureUnitCount > s_TextureSlots;
}

uint32_t* BatchTextureManager::GetTextureIDs()
{
	return s_Textures;
}
