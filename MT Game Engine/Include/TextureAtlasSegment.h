#pragma once

namespace mtge {
	enum class CoordBuffer_S {
		LEFT, RIGHT
	};
	enum class CoordBuffer_T {
		TOP, BOTTOM
	};

	class TextureAtlasSegment {
	private:
		static const float REL_COORD_BUFFER;

		const float OFFSET_S;
		const float OFFSET_T;
		const float STEP_S;
		const float STEP_T;
		const float COORD_BUFFER_S;
		const float COORD_BUFFER_T;

	public:
		TextureAtlasSegment(const unsigned int ORIGIN_INDEX_S, const unsigned int ORIGIN_INDEX_T, const unsigned int ATLAS_SIZE_S, const unsigned int ATLAS_SIZE_T);
		const float getTexCoord_S(const unsigned int faceIndex_S) const;
		const float getTexCoord_T(const unsigned int faceIndex_T) const;
		const float getTexCoord_S(const unsigned int faceIndex_S, const CoordBuffer_S coordBuffer_S) const;
		const float getTexCoord_T(const unsigned int faceIndex_T, const CoordBuffer_T coordBuffer_T) const;
	};
}