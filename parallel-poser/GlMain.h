#pragma once

#include <string>
#include <vector>
#include <assimp\scene.h>

class GlMain
{
public:
	GlMain(void);
	~GlMain(void);
	GlMain(int argc, char **argv, std::string filename, const aiScene* scene);

	void UpdateDisplay();
	void Render();

	const aiScene* scene;
};