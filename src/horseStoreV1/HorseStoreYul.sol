// SPDX-License-Identifier: MIT

pragma solidity ^0.8.19;

contract HorseStoreYul{
    uint256 numberOfHorses;
    

    function updateHorseNumber(uint256 horseNumber) external {
        assembly{
            sstore(numberOfHorses.slot , horseNumber)
        }
        
    }
    function readNumberOfHorses() external view returns(uint256){
        assembly {
            let num := sload(numberOfHorses.slot)
            mstore(0, num)
            return(0 , 0x20)
        }
    }
}