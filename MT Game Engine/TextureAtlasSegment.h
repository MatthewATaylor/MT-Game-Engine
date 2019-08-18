#pragma once

class TextureAtlasSegment {
private:
	const float OFFSET_S;
	const float OFFSET_T;
	const float STEP_S;
	const float STEP_T;

public:
	TextureAtlasSegment(const unsigned int ORIGIN_INDEX_S, const unsigned int ORIGIN_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T);
	const float getTexCoord_S(const unsigned int faceIndex_S) const;
	const float getTexCoord_T(const unsigned int faceIndex_T) const;
};