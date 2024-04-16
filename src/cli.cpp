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

#include "cli.h"
#include "operate.h"

static Operate operate;

CLI::CLI() {
    if (!operate.isEcSysModuleLoaded() && !operate.loadEcSysModule()){
        fprintf(stderr, "Failed to load the ec_sys kernel module\n");
        exit(1);
    }

    if(!operate.updateEcData() || operate.getEcVersion().empty()){
        fprintf(stderr, "Failed to update EC data\n");
        exit(1);
    }

    if (!operate.doProbe()) {
        fprintf(stderr, "Failed probing devices\n");
        exit(1);
    }
}

CLI::~CLI() {
}

void CLI::setCoolerBoost(Options::State state){
    bool on = false;
    if(state == Options::State::TOGGLE){ // TOGGLE
        on = !operate.getCoolerBoostState();
    }
    else{
        on = state;
    }

    if(operate.getCoolerBoostState() != on){
        fprintf(stdout, "%s Cooler Boost\n", ( on ? "Enabling" : "Disabling" ));
        operate.setCoolerBoostState(on);
        operate.updateEcData();
    }
}
