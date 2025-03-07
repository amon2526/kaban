#ifndef STATIC_ARRAY_HPP
#define STATIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T> class array {
public:
  array<T>(size_t size) {
    m_data = malloc(size * sizeof(T));
    if (!m_data)
      throw(std::runtime_error("Malloc failed"));
    m_size = size;
  }

  void resize(size_t newSize) {
    m_data = realloc(m_data, newSize * sizeof(T));
    if (!m_data)
      throw(std::runtime_error("Realloc failed"));
    m_size = newSize;
  }

  T& operator[](size_t index) {
    if (index > m_length || index < 0) {
      throw(std::out_of_range("Element out of range"));
    }
    return m_data[index];
  }

  size_t length() const { return m_length; }
  size_t size() const { return m_size; }

private:
  T *m_data;
  size_t m_length;
  size_t m_size;
};


#endif