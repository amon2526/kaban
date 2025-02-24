#define STB_IMAGE_IMPLEMENTATION
#include <error_handler.hpp>
#include <gl/gl.h>
#include <stb_image.h>
#include <texture_loader.hpp>


GLuint TextureLoader::loadTexture(const std::string &filename) {
  int width, height, channels;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &channels, 4);

  if (!data) {
    handleError(1, "Failed to load a texture");
    return 0;
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_image_free(data);
  return texture;
}