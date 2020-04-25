#include "Rendering/Texture/TextureAtlasSegment.h"

namespace mtge {
	//Constructor
	TextureAtlasSegment::TextureAtlasSegment(
		const math::Vec<unsigned int, 2> ORIGIN_INDEX, 
		const math::Vec<unsigned int, 2> ATLAS_DIMENS) :
		
		SAMPLE_BUFFER((1.0f / 100.0f) * (1.0f / (float)ATLAS_DIMENS.getS()), (1.0f / 100.0f) * (1.0f / (float)ATLAS_DIMENS.getT())),
		OFFSET((float)ORIGIN_INDEX.getS() / (float)ATLAS_DIMENS.getS(), (float)ORIGIN_INDEX.getT() / (float)ATLAS_DIMENS.getT()),
		SIZE(1.0f / (float)ATLAS_DIMENS.getS(), 1.0f / (float)ATLAS_DIMENS.getT()),
		TOP_LEFT(OFFSET.getS() + SAMPLE_BUFFER.getS(), OFFSET.getT() + SIZE.getT() - SAMPLE_BUFFER.getT()),
		TOP_RIGHT(OFFSET.getS() + SIZE.getS() - SAMPLE_BUFFER.getS(), OFFSET.getT() + SIZE.getT() - SAMPLE_BUFFER.getT()),
		BOTTOM_LEFT(OFFSET.getS() + SAMPLE_BUFFER.getS(), OFFSET.getT() + SAMPLE_BUFFER.getT()),
		BOTTOM_RIGHT(OFFSET.getS() + SIZE.getS() - SAMPLE_BUFFER.getS(), OFFSET.getT() + SAMPLE_BUFFER.getT())
	{}
}