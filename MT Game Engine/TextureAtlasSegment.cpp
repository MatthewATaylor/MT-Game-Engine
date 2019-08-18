#include "TextureAtlasSegment.h"

//Constructor
TextureAtlasSegment::TextureAtlasSegment(const unsigned int ORIGIN_INDEX_S, const unsigned int ORIGIN_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T) :
	OFFSET_S((float)ORIGIN_INDEX_S / (float)ATLAS_SIZE_S),
	OFFSET_T((float)ORIGIN_INDEX_T / (float)ATLAS_SIZE_T),
	STEP_S(1.0f / (float)ATLAS_SIZE_S), 
	STEP_T(1.0f / (float)ATLAS_SIZE_T)
{}

//Public
const float TextureAtlasSegment::getTexCoord_S(const unsigned int faceIndex_S) const {
	return (float)faceIndex_S * STEP_S + OFFSET_S;
}
const float TextureAtlasSegment::getTexCoord_T(const unsigned int faceIndex_T) const {
	return (float)faceIndex_T * STEP_T + OFFSET_T;
}