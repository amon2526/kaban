#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>

template <typename T, size_t N> class Buffer {
public:
  inline void AddArray();
  inline void Clear();
  inline void PopArray();
  void AddElement(const T &element);
  void PopElement();
  T *last();
  T &operator[](size_t index);
  int length() const;

private:
  T m_array[N];
  int m_lastIndex = 0;
  int m_division[1000] = {0};
  int m_divisionLastIndex = 0;
};

template<typename T, size_t N>
inline void Buffer<T, N>::AddArray()
{
	m_division[m_divisionLastIndex++] = m_lastIndex;
}
template<typename T, size_t N>
inline void Buffer<T, N>::Clear()
{
	m_divisionLastIndex = m_lastIndex = 0;
}
template<typename T, size_t N>
inline void Buffer<T, N>::PopArray()
{
	m_lastIndex = m_division[--m_divisionLastIndex];
}
template<typename T, size_t N>
T* Buffer<T, N>::last()
{
	if (m_lastIndex != 0) return &m_array[m_lastIndex-1];
	else return nullptr;
}
template<typename T, size_t N>
T& Buffer<T, N>::operator[](size_t index)
{
	if (m_divisionLastIndex > 0) return m_array[m_division[m_divisionLastIndex-1] + index];
	else return m_array[index];
}
template<typename T, size_t N>
int Buffer<T, N>::length() const
{
	if (m_divisionLastIndex != 0) return m_lastIndex - m_division[m_divisionLastIndex - 1];
	else return m_lastIndex;
}
template<typename T, size_t N>
void Buffer<T, N>::AddElement(const T& element)
{
	m_array[m_lastIndex] = element;
	m_lastIndex++;
}
template<typename T, size_t N>
void Buffer<T, N>::PopElement()
{
	if (m_division[m_divisionLastIndex] < m_lastIndex) {
		m_lastIndex--;
	}
}

#endif