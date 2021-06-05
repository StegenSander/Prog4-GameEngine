#pragma once
///Author: Sander Stegen
///Date of creation: 09 Jan 2021
#include <iostream>
#include <fstream>
class BinaryReader
{
public:
	BinaryReader() =default;
	~BinaryReader() { closeFile(); };

	void openFile(const std::string& filepath)
	{
		closeFile();
		m_File.open(filepath, std::ios::out | std::ios::binary);
	}
	void closeFile()
	{
		if (m_File.is_open()) m_File.close();
	}

	template <typename T>
	void Read(T& data)
	{
		if (!m_File.is_open())
		{
			std::cout << "ERROR: No file was open\n";
			return;
		}

		if (std::is_pod<T>())
		{
			m_File.read((char*)(&data), sizeof(data));
		}
		else
		{
			std::cout << "Data is no Pod, No Case is written to handle this type\n";
		}
	}

	void Read(std::string& data)
	{
		if (!m_File.is_open())
		{
			std::cout << "ERROR: No file was open\n";
			return;
		}

		size_t stringSize{};
		m_File.read((char*)&stringSize, sizeof(stringSize));

		char* cString = new char[stringSize + 1];
		cString[stringSize] = '\0';
		m_File.read(cString, stringSize);

		data = std::string(cString);
		delete[] cString;
	}

private:
	std::ifstream m_File{};
};