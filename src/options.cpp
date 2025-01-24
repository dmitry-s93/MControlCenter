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
#include "options.h"

#include <cstring>

Options::Options()
    :cli(false), cooler_boost(std::nullopt)
{}

void Options::print_help(std::string program_name)
{
    fprintf(stdout, R"(Description
Syntax: %s [options]

    -B, --coolerboost STATE             toggle fan cooler boost
    -h                                  show help

Arguments:
    STATE: can be 'ON', 'OFF' or 'TOGGLE'
)", program_name.c_str());
    exit(1);
}

void Options::process_args(int argc, char** argv)
{
    int option_index;
    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts.data(), long_opts, &option_index);

        if (-1 == opt){
            break;
        }

        switch (opt)
        {
            case 0:
                cli = true;
                // long option without short equivalent
            break;

            case 'B':
                cli = true;

                if(std::strcmp(optarg,"ON") == 0){
                    cooler_boost = std::optional<Options::State>{Options::State::ON};
                }
                else if(std::strcmp(optarg,"OFF") == 0)
                {
                    cooler_boost = std::optional<Options::State>{Options::State::OFF};
                }
                else if(std::strcmp(optarg,"TOGGLE") == 0)
                {
                    cooler_boost = std::optional<Options::State>{Options::State::TOGGLE};
                }
                else{
                    fprintf(stderr, "Wrong TOGGLE value for coolerboost option.\n");
                    print_help(argv[0]);
                }
            break;

            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                print_help(argv[0]);
            break;
        }
    }
}
