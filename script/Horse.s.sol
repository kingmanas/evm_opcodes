// SPDX-License-Identifier: MIT

pragma solidity ^0.8.20;

import {Script , console} from "lib/forge-std/src/Script.sol";
import {HorseStore} from "src/horseStoreV1/HorseStore.sol";

contract HorseStoreScript is Script {
    function run() public {
        // Start broadcasting transactions
        vm.startBroadcast();

        // Deploy the HorseStore contract
        HorseStore horseStore = new HorseStore();

        // Update the number of horses
        horseStore.updateHorseNumber(10);

        // Read the number of horses
        uint256 horseCount = horseStore.readNumberOfHorses();

        // Log the horse count to verify
        console.log("Number of horses:", horseCount);

        // End broadcasting transactions
        vm.stopBroadcast();
    }
}
