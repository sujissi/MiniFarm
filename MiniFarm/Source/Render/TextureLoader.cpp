#include "PCH.h"
#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::unordered_map<std::string, GLuint> TextureLoader::s_cache;

GLuint TextureLoader::Load(const std::string& path)
{
    auto it = s_cache.find(path);
    if (it != s_cache.end())
        return it->second;

    GLuint tex = LoadInternal(path);
    if (tex != 0)
        s_cache[path] = tex;

    return tex;
}

GLuint TextureLoader::LoadInternal(const std::string& path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (!data)
    {
        LOG_E("Texture load failed: %s", path.c_str());
        glDeleteTextures(1, &texture);
        return 0;
    }

    GLenum format = (nrChannels == 4 ? GL_RGBA :
        (nrChannels == 3 ? GL_RGB : GL_RED));

    glTexImage2D(GL_TEXTURE_2D, 0, format,
        width, height, 0,
        format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    LOG("Texture loaded: %s (%dx%d)", path.c_str(), width, height);

    return texture;
}
