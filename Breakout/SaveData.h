#pragma once
#include <cstdint>

struct SaveData
{
public:
	SaveData()
	{
		_data = nullptr;
		_readPos = 0;
		_size = 0;
	}

	SaveData(void* data, uint32_t size)
	{
		_data = data;
		_size = size;
		_readPos = 0;
	}

	template <typename T>
	void write(T data)
	{
		if (_data)
		{
			void* oldData = _data;

			_data = std::malloc(_size + sizeof(T));
			std::memcpy(_data, oldData, _size);
			std::memcpy(static_cast<char*>(_data) + _size, (void*)&data, sizeof(T));
			_size += sizeof(T);

			std::free(oldData);
		}
		else
		{
			_data = malloc(sizeof(T));
			_size = sizeof(T);
			std::memcpy(_data, (void*)&data, _size);
		}
	}

	template <typename T>
	T read()
	{
		T data = *(T*)(static_cast<char*>(_data) + _readPos);
		_readPos += sizeof(T);
		return data;
	}

	void* getData() { return _data; }
	uint32_t getSize() { return _size; }

private:
	uint32_t _readPos;
	uint32_t _size;
	void* _data;
};