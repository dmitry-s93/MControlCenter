/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MControlCenter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MControlCenter. If not, see <https://www.gnu.org/licenses/>.
 */

#include "readwrite.h"
#include <fstream>
#include <vector>

const char* ioFile = "/sys/kernel/debug/ec/ec0/io";

ReadWrite::ReadWrite()
{

}

typedef unsigned char BYTE;

std::vector<ReadWrite::BYTE> ReadWrite::readFile()
{
    if (!fileExists(ioFile))
    {
        return std::vector<BYTE>();
    }
    std::streampos fileSize;
    std::ifstream file(ioFile, std::ios::binary);
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<BYTE> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

std::vector<ReadWrite::BYTE> ReadWrite::readFileWithPos(const int startPos, const int size)
{
    if (!fileExists(ioFile))
    {
        return std::vector<BYTE>();
    }
    std::ifstream file(ioFile, std::ios::binary);
    file.seekg(startPos);
    std::vector<BYTE> fileData(size);
    file.read((char*) &fileData[0], size);
    return fileData;
}

void ReadWrite::writeToFile(const int pos, const int value)
{
    std::ofstream file(ioFile, std::ios::in | std::ios::out | std::ios::binary);
    file.seekp(pos);
    file << BYTE(value);
}

bool ReadWrite::fileExists(const std::string &name)
{
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}
