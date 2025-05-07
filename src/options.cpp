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

Options::Options()
    :cli(false), cooler_boost(std::nullopt)
{}

void Options::print_help(std::string program_name)
{
    fprintf(stdout, R"(Description
Syntax: %s [options]

    -B, --coolerboost STATE             toggle fan cooler boost
    -M, --usermode MODE                 change user mode
    -h                                  show help

Arguments:
    STATE: can be 'ON', 'OFF' or 'TOGGLE'
    MODE: can be 'PERFORMANCE', 'BALANCED', 'SILENT', 'BATTERY', 'NEXT'
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

                if(std::string(optarg) =="ON"){
                    cooler_boost = std::optional<Options::State>{Options::State::ON};
                }
                else if(std::string(optarg) == "OFF")
                {
                    cooler_boost = std::optional<Options::State>{Options::State::OFF};
                }
                else if(std::string(optarg) == "TOGGLE")
                {
                    cooler_boost = std::optional<Options::State>{Options::State::TOGGLE};
                }
                else{
                    fprintf(stderr, "Wrong TOGGLE value for coolerboost option.\n");
                    print_help(argv[0]);
                }
            
            break;
            
            case 'M':
                cli = true;

                if(strcmp(optarg, "BALANCED") == 0){
                    user_mode = std::optional<Options::Mode>{Options::Mode::BALANCED};
                }
                else if(strcmp(optarg, "PERFORMANCE") == 0)
                {
                    user_mode = std::optional<Options::Mode>{Options::Mode::PERFORMANCE};
                }
                else if(strcmp(optarg, "SILENT") == 0)
                {
                    user_mode = std::optional<Options::Mode>{Options::Mode::SILENT};
                }
                else if(strcmp(optarg, "BATTERY") == 0)
                {
                    user_mode = std::optional<Options::Mode>{Options::Mode::BATTERY};
                }
                else if(strcmp(optarg, "NEXT") == 0)
                {
                    user_mode = std::optional<Options::Mode>{Options::Mode::NEXT};
                }
                else{
                    fprintf(stderr, "Wrong MODE value for usermode option.\n");
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
