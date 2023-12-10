#include "Application.h"
#include "ModuleTexture.h"
#include "glew.h"
#include "DirectXTex.h"


ModuleTexture::ModuleTexture()
{
    
}

ModuleTexture::~ModuleTexture()
{

}

const wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    size_t zSice;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs_s(&zSice, wc, cSize, c, cSize -1);

    return wc;
}

//unsigned solo recoge valores positivos, nunca recoge signo.

unsigned int ModuleTexture::LoadTexture(const char* path)
{
    DirectX::ScratchImage image;
    const wchar_t* pathTex = GetWC(path);

    // every texture have one format, if the format its not the correct it use another method for load
    HRESULT hr = DirectX::LoadFromDDSFile(pathTex, DirectX::DDS_FLAGS_NONE, nullptr, image);
    if (FAILED(hr))
    {
        hr = DirectX::LoadFromTGAFile(pathTex, DirectX::TGA_FLAGS_NONE, nullptr, image);

        if (FAILED(hr))
        {
            hr = DirectX::LoadFromWICFile(pathTex, DirectX::WIC_FLAGS_NONE, nullptr, image);

            if (FAILED(hr))
            {
                LOG("texture failed to load");
                //HASTA LUEGO!
            }
        }
    }

    switch (image.GetMetadata().format) // for get all information of the texture and see the parameters it have
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_BGRA;
        type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B5G6R5_UNORM:
        internalFormat = GL_RGB8;
        format = GL_BGR;
        type = GL_UNSIGNED_BYTE;
        break;
    default:
        assert(false && "Unsupported format");
    }

    unsigned int createTex;

    glGenTextures(1, (GLuint*)&createTex); //asignate a number and get texture
    glBindTexture(GL_TEXTURE_2D, createTex); //bind texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, image.GetMetadata().mipLevels - 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    widthTex = image.GetMetadata().width;
    widthTex = image.GetMetadata().height;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, widthTex, heightTex, 0, format, type, image.GetPixels());

    for (size_t i = 0; i < image.GetMetadata().mipLevels; ++i)
    {
        const DirectX::Image* mip = image.GetImage(i, 0, 0);
        glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    return createTex;
}

bool ModuleTexture::Init()
{
   
	return true;
}

update_status ModuleTexture::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleTexture::Update()
{
 
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTexture::CleanUp()
{
	return true;
}