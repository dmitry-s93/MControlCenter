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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>
#include <optional>
#include <string>

class Options{
public:
    Options();
    ~Options() = default;

    enum State {
        OFF = 0,
        ON = 1,
        TOGGLE = 2
    };

    bool cli;
    std::optional<State> cooler_boost;

    void process_args(int argc, char** argv);

private:
    static constexpr std::string_view const short_opts = "B:h";
    static constexpr option long_opts[] = {
        {"coolerboost", required_argument, nullptr, 'B'},
        {"help",        no_argument, nullptr, 'h'},
        {nullptr,       no_argument, nullptr, 0}
    };

    void print_help(std::string program_name);
};

#endif // OPTIONS_H
