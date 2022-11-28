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

const QString acpi_ec_file = "/dev/ec";
const QString ec_sys_file = "/sys/kernel/debug/ec/ec0/io";
QString ioFile = ec_sys_file;

ReadWrite::ReadWrite() = default;

QByteArray ReadWrite::readFromFile() const {
    if (QFile file(ioFile); file.open(QIODevice::ReadOnly))
        return file.readAll();
    return {};
}

void ReadWrite::writeToFile(const int pos, BYTE value) const {
    std::ofstream file(ioFile.toStdString(), std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(pos);
        file << value;
    }
}

bool ReadWrite::isAcpiEc() const {
    if (QFile::exists(acpi_ec_file)) {
        ioFile = acpi_ec_file;
        return true;
    }
    return false;
}

bool ReadWrite::isEcSys() const {
    if (QFile::exists(ec_sys_file)) {
        ioFile = ec_sys_file;
        return true;
    }
    return false;
}
