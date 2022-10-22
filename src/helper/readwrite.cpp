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

#include <QFile>

const char *const ioFile = "/sys/kernel/debug/ec/ec0/io";

ReadWrite::ReadWrite() = default;

QByteArray ReadWrite::readFromFile() {
    if (QFile file(ioFile); file.open(QIODevice::ReadOnly))
        return file.readAll();
    return {};
}

void ReadWrite::writeToFile(const int pos, BYTE value) {
    std::ofstream file(ioFile, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(pos);
        file << value;
    }
}
