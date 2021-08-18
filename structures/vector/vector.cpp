#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {
	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size) 	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_) 	{
		memcpy(memory_, other.memory_, other.size_);
	}

	Vector::Vector(Vector&& other) :
		memory_(other.memory_), size_(other.size_) 	{
		// memory_ = other.memory_;
		// size_ = other.size_;

		other.memory_ = nullptr;
		other.size_ = 0;
	}

	Vector::~Vector() 	{
		free(memory_); // opak funkcie malloc a calloc
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const 	{
		return new Vector(*this);
	}

	size_t Vector::size() const 	{
		return size_;
	}

	Structure& Vector::operator=(const Structure& other) 	{
		if (this != &other) 		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other) 	{
		if (this != &other) 		{
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memcpy(memory_, other.memory_, other.size_);
		}
		return *this;
	}

	Vector& Vector::operator=(Vector&& other) 	{
		if (this != &other) {
			// free(memory_);

			memory_ = other.memory_;
			size_ = other.size_;

			other.memory_ = nullptr;
			other.size_ = 0;
		}
		return *this;
	}

	// porovnanie
	bool Vector::operator==(const Vector& other) const 	{
		// memcmp - ked su obsahy pamati rovnake, vrati 0, ak nie su rovnake, vrati nieco ine
		return (this == &other) || (size_ == other.size_) && (memcmp(memory_, other.memory_, other.size_) == 0);
	}

	// vrati odkaz
	byte& Vector::operator[](const int index) 	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	// vrati kopiu
	byte Vector::operator[](const int index) const 	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) 	{
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid index!");
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length) 	{
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid index!");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid index!");

		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	// vrati adresu
	byte* Vector::getBytePointer(const int index) const 	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return reinterpret_cast<byte*>(memory_) + index;
	}
}