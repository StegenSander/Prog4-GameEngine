#pragma once
///Author: Sander Stegen
///Date of creation: 09 Jan 2021
#include <iostream>
#include <fstream>
class BinaryWriter
{
public:
	BinaryWriter(){};
	~BinaryWriter() { closeFile(); };

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
	void Write(const T& data)
	{
		if (!m_File.is_open())
		{
			std::cout << "ERROR: No file was open\n";
			return;
		}

		if (std::is_pod<T>())
		{
			m_File.write((const char*)(&data), sizeof(data));
		}
		else
		{
			std::cout << "Data is no Pod, No Case is written to handle this type\n";
		}
	}
	void Write(const std::string& data)
	{
		if (!m_File.is_open())
		{
			std::cout << "ERROR: No file was open\n";
			return;
		}

		size_t size = data.size();
		m_File.write(reinterpret_cast<const char*>(&size), sizeof(size));
		m_File.write(data.c_str(), size);
	}

private:
	std::ofstream m_File{};
};

