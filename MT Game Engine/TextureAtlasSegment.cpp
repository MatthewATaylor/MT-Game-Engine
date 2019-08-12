#include "TextureAtlasSegment.h"

//Constructor
TextureAtlasSegment::TextureAtlasSegment(const unsigned int START_FACE_INDEX_S, const unsigned int START_FACE_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T) :
	OFFSET_S((float)START_FACE_INDEX_S / (float)ATLAS_SIZE_S), 
	OFFSET_T((float)START_FACE_INDEX_T / (float)ATLAS_SIZE_T), 
	STEP_S(1.0f / (float)ATLAS_SIZE_S), 
	STEP_T(1.0f / (float)ATLAS_SIZE_T)
{}