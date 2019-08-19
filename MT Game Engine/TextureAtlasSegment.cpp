#include "TextureAtlasSegment.h"

namespace mtge {
	const float TextureAtlasSegment::REL_COORD_BUFFER = 1.0f / 1000.0f;

	//Constructor
	TextureAtlasSegment::TextureAtlasSegment(const unsigned int ORIGIN_INDEX_S, const unsigned int ORIGIN_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T) :
		OFFSET_S((float)ORIGIN_INDEX_S / (float)ATLAS_SIZE_S),
		OFFSET_T((float)ORIGIN_INDEX_T / (float)ATLAS_SIZE_T),
		STEP_S(1.0f / (float)ATLAS_SIZE_S),
		STEP_T(1.0f / (float)ATLAS_SIZE_T),
		COORD_BUFFER_S(STEP_S * REL_COORD_BUFFER),
		COORD_BUFFER_T(STEP_T * REL_COORD_BUFFER)
	{}

	//Public
	const float TextureAtlasSegment::getTexCoord_S(const unsigned int faceIndex_S) const {
		return (float)faceIndex_S * STEP_S + OFFSET_S;
	}
	const float TextureAtlasSegment::getTexCoord_T(const unsigned int faceIndex_T) const {
		return (float)faceIndex_T * STEP_T + OFFSET_T;
	}
	const float TextureAtlasSegment::getTexCoord_S(const unsigned int faceIndex_S, const CoordBuffer_S coordBuffer_S) const {
		if (coordBuffer_S == CoordBuffer_S::LEFT) {
			return (float)faceIndex_S * STEP_S + OFFSET_S + COORD_BUFFER_S;
		}
		else {
			return (float)faceIndex_S * STEP_S + OFFSET_S - COORD_BUFFER_S;
		}
	}
	const float TextureAtlasSegment::getTexCoord_T(const unsigned int faceIndex_T, const CoordBuffer_T coordBuffer_T) const {
		if (coordBuffer_T == CoordBuffer_T::TOP) {
			return (float)faceIndex_T * STEP_T + OFFSET_T - COORD_BUFFER_T;
		}
		else {
			return (float)faceIndex_T * STEP_T + OFFSET_T + COORD_BUFFER_T;
		}
	}
}