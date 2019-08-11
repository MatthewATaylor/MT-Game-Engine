#pragma once

class TextureAtlasSegment {
public:
	const unsigned int OFFSET_S;
	const unsigned int OFFSET_T;
	const unsigned int WIDTH;
	const unsigned int HEIGHT;

	TextureAtlasSegment(const unsigned int OFFSET_S, const unsigned int OFFSET_T, const unsigned int WIDTH, const unsigned int HEIGHT);
};