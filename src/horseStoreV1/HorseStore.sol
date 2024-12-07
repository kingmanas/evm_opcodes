// SPDX-License-Identifier: MIT

pragma solidity ^0.8.19;

contract HorseStore{
    uint256 numnberOfHorses;
    

    function updateHorseNumber(uint256 horseNumber) external {
        numnberOfHorses = horseNumber;
        
    }
    function readNumberOfHorses() external view returns(uint256){
        return numnberOfHorses;
    }
}