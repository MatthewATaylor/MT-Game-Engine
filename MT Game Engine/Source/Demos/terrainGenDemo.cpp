#include <iostream>
#include <string>

#include "Rendering/Shader.h"
#include "Rendering/Texture/Texture.h"
#include "Interaction/Player.h"
#include "Interaction/Camera.h"
#include "Clock.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Interaction/Input.h"
#include "Rendering/Renderer.h"
#include "Rendering/Texture/TextureAtlasSegment.h"
#include "Rendering/Texture/SkyboxTextureContainer.h"
#include "Rendering/Texture/CubeTexture.h"
#include "Rendering/Chunk.h"
#include "Rendering/Skybox.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/PerlinNoise.h"
#include "WorldMap.h"
#include "WorldGenerator.h"
#include "CubeCharacterizer.h"
#include "Rendering/CubeData.h"

const float START_HEIGHT = 0.5f;
const bool USE_EFFECTS = true;

float terrainFunc(float x, float y) {
	return mtge::math::PerlinNoise::get2DWithOctaves(
		x, y, 0.015f, 0.1f, 4
	);
}

mtge::CubeCharacterizer *getCubeCharacterizer() {
	/*
	Texture allocations are used throughout the entire program, so
	they won't need to be freed
	*/

	const unsigned int TEXTURE_ATLAS_ROWS = 1;
	const unsigned int TEXTURE_ATLAS_COLS = 7;

	//Grass texture
	mtge::TextureAtlasSegment *grassCubeSide = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(0, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::TextureAtlasSegment *grassCubeBottom = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(1, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::TextureAtlasSegment *grassCubeTop = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(2, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *grassCubeTexture = new mtge::CubeTexture(grassCubeSide, grassCubeTop, grassCubeBottom);

	//Water texture
	mtge::TextureAtlasSegment *waterCubeAllFaces = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(4, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *waterCubeTexture = new mtge::CubeTexture(waterCubeAllFaces);

	//Rock texture
	mtge::TextureAtlasSegment *rockCubeAllFaces = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(3, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *rockCubeTexture = new mtge::CubeTexture(rockCubeAllFaces);

	//Dirt texture
	mtge::TextureAtlasSegment *dirtCubeAllFaces = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(1, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *dirtCubeTexture = new mtge::CubeTexture(dirtCubeAllFaces);

	//Sand texture
	mtge::TextureAtlasSegment *sandCubeAllFaces = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(5, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *sandCubeTexture = new mtge::CubeTexture(sandCubeAllFaces);

	//Glass texture
	mtge::TextureAtlasSegment *glassCubeAllFaces = new mtge::TextureAtlasSegment(
		mtge::math::Vec<unsigned int, 2>(6, 0),
		mtge::math::Vec<unsigned int, 2>(TEXTURE_ATLAS_COLS, TEXTURE_ATLAS_ROWS)
	);
	mtge::CubeTexture *glassCubeTexture = new mtge::CubeTexture(glassCubeAllFaces);

	//Characterization
	mtge::CubeCharacterizer *cubeCharacterizer = new mtge::CubeCharacterizer;
	cubeCharacterizer->addCubeType('g', grassCubeTexture);
	cubeCharacterizer->addCubeType('w', waterCubeTexture);
	cubeCharacterizer->addCubeType('r', rockCubeTexture);
	cubeCharacterizer->addCubeType('d', dirtCubeTexture);
	cubeCharacterizer->addCubeType('s', sandCubeTexture);
	cubeCharacterizer->addCubeType('l', glassCubeTexture);

	return cubeCharacterizer;
}

int main() {
	if (mtge::ResourceManager::startGLFW(3, 3)) {
		std::cin.get();
		return 1;
	}
	mtge::Window window("MTGE", 1250, 900, true);
	if (mtge::ResourceManager::startGLEW()) {
		std::cin.get();
		return 1;
	}
	mtge::ResourceManager::startOpenGL();

	//Load shader with fog effect
	float fogDensity = 0.07f;
	float fogGradient = 0.5f;
	float fogWeight = 0.0f;
	float fogBias = 1.0f;
	if (USE_EFFECTS) {
		fogWeight = 1.0f;
		fogBias = -0.4f;
	}
	mtge::Shader::loadDefaultShaders(fogDensity, fogGradient, fogWeight, fogBias);

	//Textures
	mtge::Texture::loadTextureAtlas(
		"Resources/Textures/texture_atlas_minimal.png",
		mtge::TextureWrapSetting::REPEAT,
		mtge::TextureWrapSetting::REPEAT,
		mtge::TextureFilterSetting::LINEAR,
		mtge::TextureFilterSetting::LINEAR,
		mtge::TextureColorSetting::RGBA
	);
	if (USE_EFFECTS) {
		std::string skyboxTextureDir = "Resources/Textures/Blue Space/";
		std::string skyboxTextureExt = ".png";
		mtge::SkyboxTextureContainer skyboxTextures(
			skyboxTextureDir + "right" + skyboxTextureExt,
			skyboxTextureDir + "left" + skyboxTextureExt,
			skyboxTextureDir + "top" + skyboxTextureExt,
			skyboxTextureDir + "bottom" + skyboxTextureExt,
			skyboxTextureDir + "front" + skyboxTextureExt,
			skyboxTextureDir + "back" + skyboxTextureExt
		);
		mtge::Texture::loadSkybox(
			&skyboxTextures,
			mtge::TextureWrapSetting::EDGE_CLAMP,
			mtge::TextureWrapSetting::EDGE_CLAMP,
			mtge::TextureWrapSetting::EDGE_CLAMP,
			mtge::TextureFilterSetting::LINEAR,
			mtge::TextureFilterSetting::LINEAR,
			mtge::TextureColorSetting::RGBA
		);
	}
	mtge::CubeCharacterizer *cubeCharacterizer = getCubeCharacterizer();

	//Initial chunk
	mtge::Chunk *centerChunk = new mtge::Chunk(
		cubeCharacterizer, mtge::math::Vec2(0.0f, 0.0f), terrainFunc
	);
	mtge::WorldMap::addChunk(centerChunk);

	//Player setup
	const mtge::math::Vec3 PLAYER_START_POS(0.0f, START_HEIGHT, 0.0f);
	const mtge::math::Vec3 PLAYER_DIMENSIONS(0.03f, 0.13f, 0.03f);
	mtge::Player player(PLAYER_START_POS, PLAYER_DIMENSIONS);
	player.setCanApplyCollisions(true);
	player.setCanApplyGravity(true);
	player.setGravityParams(0.1f, 12.0f, 50.0f);

	mtge::WorldGenerator worldGenerator(&player, terrainFunc);
	mtge::Skybox::init();
	mtge::Clock clock;
	mtge::Input::setCursorType(&window, mtge::CursorType::DISABLED);
	mtge::Input::initCursorInput(&window);

	while (!window.getShouldClose()) {
		//clock.printFPS(1.0f);

		mtge::Input::pollInput();

		if (mtge::Input::keyPressed(&window, mtge::Key::ESCAPE)) {
			window.setShouldClose(true);
		}

		//Player control
		player.controlRotation(mtge::Input::getMouseX(), mtge::Input::getMouseY());
		player.controlMotion(&window, 0.5f, 87, 83, 65, 68);
		player.controlJump(&window, 1.6f, 32);
		player.controlReset(&window, START_HEIGHT);

		if (!mtge::Input::keyPressed(&window, mtge::Key::C)) {
			worldGenerator.generateChunks(cubeCharacterizer, 10, false);
		}
		if (mtge::Input::keyPressed(&window, mtge::Key::G)) {
			player.setCanApplyGravity(false);
		}
		else {
			player.setCanApplyGravity(true);
		}

		//Rendering
		mtge::Renderer::clear(0, 0, 0);
		if (USE_EFFECTS) {
			mtge::Skybox::render(&player, &window);
		}
		mtge::WorldMap::renderScene(&player, &window);
		mtge::Renderer::applyDrawCalls(&window);
	}

	//Cleanup
	mtge::WorldMap::freeResources();
	mtge::ResourceManager::freeResources();
	mtge::Shader::freeResources();
	mtge::Texture::freeResources();

	return 0;
}
