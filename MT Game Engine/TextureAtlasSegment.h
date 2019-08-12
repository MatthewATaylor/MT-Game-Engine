#pragma once

class TextureAtlasSegment {
public:
	const float OFFSET_S;
	const float OFFSET_T;
	const float STEP_S;
	const float STEP_T;

	TextureAtlasSegment(const unsigned int START_FACE_INDEX_S, const unsigned int START_FACE_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T);
	//TextureAtlasSegment(const TextureAtlasSegment *)
};