#pragma once

class TextureLoader
{
public:
    static GLuint Load(const std::string& path);

private:
    static std::unordered_map<std::string, GLuint> s_cache;
    static GLuint LoadInternal(const std::string& path);
};
