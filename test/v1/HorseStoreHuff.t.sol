// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

import {Base_TestV1 , IHorseStore} from "./Base_TestV1.t.sol";
import {HuffDeployer} from "lib/foundry-huff/src/HuffDeployer.sol";

contract HorseStoreHuff is Base_TestV1 {

    string public constant HORSE_STORE_HUFF_LOCATION = "HorseStore"; // assumes that every file is in src and without .huff
    function setUp() public override {
        // horseStore = Huff edition
        horseStore = IHorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION));
    }
}