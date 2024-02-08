#pragma once

#include <string>
#include <vector>
#include <assert.h>

enum class BufferType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Float2x2, Float3x3, Float4x4,
	Int, Int2, Int3, Int4,
	Bool,
	Struct
};

struct BufferElement
{
	std::string Name;
	BufferType Type;

	uint32_t Length; // in case of array or struct
	std::vector<BufferElement> Elements; // in case of struct

	BufferElement()
		: Name(""), Type(BufferType::None), Length(0), Elements()
	{}

	//array constructor
	BufferElement(const std::string& name, BufferType bufferType, uint32_t length = 1)
		: Name(name), Type(bufferType), Length(length), Elements(0)
	{}

	//struct constructor
	BufferElement(const std::string& name, BufferType bufferType, const std::initializer_list<BufferElement>& elements, uint32_t length = 1)
		: Name(name), Type(bufferType), Length(length), Elements(elements)
	{}

	bool operator==(const BufferElement& other) const
	{
		return Type == other.Type && Name == other.Name && Length == other.Length && Elements == other.Elements;
	}
};