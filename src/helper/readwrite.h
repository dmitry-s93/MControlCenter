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

#ifndef READWRITE_H
#define READWRITE_H


#include <string>
#include <vector>
class ReadWrite
{
    typedef unsigned char BYTE;
public:
    ReadWrite();
    std::vector<BYTE> readFile();
    std::vector<BYTE> readFileWithPos(const int startPos, const int size);
    void writeToFile(const int pos, const int value);
private:
    inline bool fileExists (const std::string &name);
};

#endif // READWRITE_H
