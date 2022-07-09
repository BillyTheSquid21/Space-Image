#pragma once
#ifndef META_READ_H
#define META_READ_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>

namespace SpaceImage
{
	struct ImageMeta
	{
		uint32_t width;
		uint32_t height;
	};

	enum class PngChunkType
	{
		IHDR = 0x49484452, tEXt = 0x74455874, IEND = 0x49454e44, IDAT = 0x49444154
	};
	
	struct PngChunk
	{
		uint32_t length;
		PngChunkType type;
		uint8_t* data;
		uint32_t crc;
	};

	bool ReadImage(const char* path);

	inline static bool ReadHeader(const char* path);
	inline static bool GetNextPngChunk(std::ifstream& infile, PngChunk& chunk);
	inline static void FreePngChunk(PngChunk& chunk);
	inline static bool IsPngChunkUseful(uint32_t type);

	bool ReadImage(const char* path)
	{
		return ReadHeader(path);
	}

	void FreePngChunk(PngChunk& chunk)
	{
		delete chunk.data;
	}

	bool IsPngChunkUseful(uint32_t type)
	{
		switch (type)
		{
		case (uint32_t)PngChunkType::IHDR:
			return true;
		case (uint32_t)PngChunkType::tEXt:
			return true;
		default:
			return false;
		}
	}

	bool GetNextPngChunk(std::ifstream& infile, PngChunk& chunk)
	{
		//Length
		uint8_t lengthBuffer[4];
		infile.read((char*)lengthBuffer, 4);
		uint32_t length = 0;
		for (int i = 0; i < 4; i++)
		{
			length |= lengthBuffer[i] << (3 - i)*8;
		}

		//Type - if not useful return false
		uint8_t typeBuffer[4];
		infile.read((char*)typeBuffer, 4);
		uint32_t type = 0;
		for (int i = 0; i < 4; i++)
		{
			type |= typeBuffer[i] << (3 - i)*8;
		}
		if (!IsPngChunkUseful(type))
		{
			return false;
		}

		//Data
		uint8_t* dataBuffer = new uint8_t[length];
		infile.read((char*)dataBuffer, length);

		//Crc
		uint8_t crcBuffer[4];
		infile.read((char*)crcBuffer, 4);
		uint32_t crc = 0;
		for (int i = 0; i < 4; i++)
		{
			crc |= crcBuffer[i] << 3 - i;
		}

		chunk = {length, PngChunkType::IDAT, dataBuffer, crc};
		return true;
	}

	bool ReadHeader(const char* path)
	{
		//open file
		uint8_t buffer[8];
		std::ifstream infile(path, std::ios::binary);

		//reads the png file header
		infile.read((char*)buffer, 8);

		//Check all png header values are met
		uint8_t check = 0;
		{
			check |= (buffer[0] == 137) << 0;
			check |= (buffer[1] == 80) << 1;
			check |= (buffer[2] == 78) << 2;
			check |= (buffer[3] == 71) << 3;
			check |= (buffer[4] == 13) << 4;
			check |= (buffer[5] == 10) << 5;
			check |= (buffer[6] == 26) << 6;
			check |= (buffer[7] == 10) << 7;
		}
		if (check != 255)
		{
			std::cout << "File is not a PNG!" << std::endl;
			return 0;
		}

		PngChunk chunk;
		GetNextPngChunk(infile, chunk);

		return 1;
	}
}

#endif