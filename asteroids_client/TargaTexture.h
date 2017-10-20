#pragma once
#include "opengl\Texture.h"
#include "file_input\Targa.h"

class TargaTexture : public opengl::Texture
{
public:
	TargaTexture ( const std::string& file_path );
};