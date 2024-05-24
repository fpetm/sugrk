#pragma once
#include "color.hpp"
#include "log.hpp"

#include <GL/gl.h>

namespace sugrk {
template <typename color_t,
          std::enable_if_t<std::is_base_of<Color, color_t>::value> * = nullptr>
class Image {
public:
  // TODO Implement image file loading (maybe make resource manager)
  // Image(std::string path);
  Image(int width, int height) : m_Width(width), m_Height(height) {
    m_Data = new color_t[m_Width * m_Height];
    m_RGBAData = (float *)malloc(sizeof(float) * m_Width * m_Height * 4);

    glGenTextures(1, &m_GLTexture);
    glBindTexture(GL_TEXTURE_2D, m_GLTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // This is required on WebGL for non
                                       // power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA,
                 GL_FLOAT, m_RGBAData);
  }
  ~Image() {
    free(m_RGBAData);
    delete[] m_Data;
  }

  void Set(int x, int y, color_t c) {
    m_Data[m_Width * y + x] = c;
    RGBAf rgba_c = c;
    m_RGBAData[(m_Width * y + x) * 4 + 0] = rgba_c.R;
    m_RGBAData[(m_Width * y + x) * 4 + 1] = rgba_c.G;
    m_RGBAData[(m_Width * y + x) * 4 + 2] = rgba_c.B;
    m_RGBAData[(m_Width * y + x) * 4 + 3] = rgba_c.A;
  }
  color_t &At(int x, int y) {
    const int offset = (m_Width * y + x) * 4;
    SG_INFO("{} {} {}", m_RGBAData[offset + 0], m_RGBAData[offset + 0],
            m_RGBAData[offset + 1], m_RGBAData[offset + 2]);
    return m_Data[m_Width * y + x];
  }
  color_t At(int x, int y) const { return m_Data[m_Width * y + x]; }
  int Width() { return m_Width; }
  int Height() { return m_Height; }

  void UpdateTexture() const {
    glBindTexture(GL_TEXTURE_2D, m_GLTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA,
                 GL_FLOAT, m_RGBAData);
  };
  GLuint GetGLTexID() { return m_GLTexture; }

private:
  int m_Width, m_Height;
  float *m_RGBAData;
  color_t *m_Data;

  GLuint m_GLTexture;
};
}; // namespace sugrk
