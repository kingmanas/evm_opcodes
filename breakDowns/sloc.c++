// 0x6080604052348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220d1a682d250a4d330ea4b8f6b875e3d0fc4f8de30690c067db78d34022f38c91364736f6c634300081a0033

// 1. Contract creation

// -->> Free memory pointer
PUSH1 0x80          // [0x80]
PUSH1 0x40          //[0x40 , 0x80]
MSTORE              //[]  , Memory 0x40 -> 0x80

//-->> checks for msg.value==0
// Ortherwise jump to continue execution
CALLVALUE           //[msg.value]
DUP1                //[msg.value , msg.value]
ISZERO              //[msg.value==0 , msg.value]
PUSH1 0x0e          //[0xe0 , msg.value==0 , msg.value]
JUMPI               //[msg.value]
PUSH0               //[0x00 , msg.value]
DUP1                //[0x00,0x00 , msg.value]
REVERT              //[msg.value]

// Jump if msg.value==0
// sticking our runtime code on blockchain
JUMPDEST            //[msg.value]
POP                 //[]
PUSH1 0xa5          //[0xa5]
DUP1                //[0xa5,0xa5]
PUSH1 0x1a          //[0x1a , 0xa5,0xa5]
PUSH0               //[0x00 , 0x1a , 0xa5,0xa5]
CODECOPY            //[0xa5]   // memory [runtime_code]
PUSH0               //[0x00 , 0xa5]
RETURN              //[]
INVALID             //

//2. Runtime code
//-->> entryPoint of all calls
//free memory pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

CALLVALUE           //[msg.value]
DUP1                //[msg.value , msg.value]
ISZERO              //[msg.value==0 , msg.value
PUSH1 0x0e          //[0x0e , msg.value==0 , msg.value]
JUMPI               //[msg.value]
//jump to continue

PUSH0               //[0 , msg.value]
DUP1                //[0,0,msg.value]
REVERT              //[msg.value]

// if msgvalue == 0 , jump here
// This is checking if there is enough data for a function selector
JUMPDEST            //[msg.value]
POP                 //[]
PUSH1 0x04          //[0x04]
CALLDATASIZE        //[calldatasize , 0x04]
LT                  //[calldatasize < 0x04]
PUSH1 0x30          //[0x30 , calldatasize < 0x04]
JUMPI               //[]
//if calldatasize <0x40 -->> calldata_jump

//function dispatching for setNumberOfHorses
PUSH0               //[0x00]
CALLDATALOAD        //[32 bytes calldata]
PUSH1 0xe0          //[0xe0 , 32 bytes calldata]
SHR                 //[function_selector]
DUP1                //[function_selctor , function_selector]
PUSH4 0xcdfead2e    //[0xcdfead2e , function_selctor , function_selector]
EQ                  //[0xcdfead2e == function_selctor , function_selector]
PUSH1 0x34          //[0x34 , 0xcdfead2e == function_selctor , function_selector]
JUMPI               //[function_selector]
// jump to set_number_of_horses

// function dispatching for getNumberOfHorses
DUP1                //[function_selector , function_selector]
PUSH4 0xe026c017    //[0xe026c017 , function_selector , function_selector]
EQ                  //[0xe026c017 == function_selector , function_selector]
PUSH1 0x45          //[0x45 , [0xe026c017 == function_selector , function_selector]]
JUMPI               //[function_selector]
// jump to get_number_of_horses

// calldata_jump here
JUMPDEST            //[]
PUSH0               //[0]
DUP1                //[0,0]
REVERT              //[0]

// upateNumberOfHorses dest 1
// jumping 
JUMPDEST            //[function_selector]
PUSH1 0x43          //[0x43 , function_selector]
PUSH1 0x3f          //[0x3f , 0x43 , function_selector]
CALLDATASIZE        //[calldatasize , 0x3f , 0x43 , function_selector]
PUSH1 0x04          //[0x04 , calldatasize , 0x3f , 0x43 , function_selector]
PUSH1 0x59          //[0x59 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
JUMP                //[0x04 , calldatasize , 0x3f , 0x43 , function_selector]

//updateNumberOfHorses dest 4
JUMPDEST            //[calldataload , 0x43 , function_select]
PUSH0               //[0x00 , calldataload , 0x43 , function_select]
SSTORE              //[0x43 , function_select]
JUMP                //[function_selector]
// jump dest 5

//updateNumberOfHorses dest 5
JUMPDEST            //[function_select]
STOP

// getNumberOFHorses jump dest 1
JUMPDEST            //[function_select]
PUSH0               //[0]
SLOAD               //[numHores , function_select]
PUSH1 0x40          //[0x40 , numHorse , function_select]
MLOAD               //[0x80 , numHorses , function_select]  //memeory [0x40 : 0x80] (free memory pointer)
SWAP1               //[numHorses , 0x80 , function_select] 
DUP2                //[0x80 , numHorses , 0x80 , function_select]
MSTORE              //[0x80 , function_select]  //memory 0x80 -> numHorses
PUSH1 0x20          //[0x20 , 0x80 , function_select]
ADD                 //[0x20 + 0x80 , function_select]
PUSH1 0x40          //[0x40 , 0x20 + 0x80 , function_select]
MLOAD               //[0x80 , 0x20 + 0x80 , function_select]
DUP1                //[0x80 , 0x80 , 0xa0 , function_select]
SWAP2               //[0xa0 , 0x80 , 0x80 , function_select]
SUB                 //[0xa0 - 0x80 , 0x80 , function_select]
SWAP1               //[0x80 , 0xa0 - 0x80 , function_select]
RETURN              //[function_select]

// updateNumberOfHorses dest 2
JUMPDEST                //[0x04 , calldatasize , 0x3f , 0x43 , function_selector]
PUSH0                   //[0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
PUSH1 0x20              //[0x20 , 0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
DUP3                    //[0x04 , 0x20 , 0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
DUP5                    //[calldatasize , 0x04 , 0x20 , 0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
SUB                     //[calldatasize - 0x04 , 0x20 , 0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
SLT                     //[calldatasize - 0x04 < 0x20 , 0 , 0x04 , calldatasize , 0x3f , 0x43 , function_selector]
ISZERO                  //[moreCallDataThanSelector , 0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]
PUSH1 0x68              //[0x68 , moreCallDataThanSelector , 0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]
JUMPI                   //[ 0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]
// we will jump if there is more calldata than -->> func selector + 0x20

PUSH0                   //[0 , 0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector ]
DUP1                    //[0 , 0 , 0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]
REVERT                  //[0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]

// updateNumberOfHorses dest 3
JUMPDEST                //[0 ,  0x04 , calldatasize , 0x3f , 0x43 , function_selector]       
POP                     //[0x04 , calldatasize , 0x3f , 0x43 , function_selector]
CALLDATALOAD            //[calldataload , calldatasize , 0x3f , 0x43 , function_selector]
SWAP2                   //[0x3f , calldatasize , calldataload , 0x43 , function_select]
SWAP1                   //[calldatasize , 0x3f , calldataload , 0x43 , function_select]
POP                     //[0x3f , calldataload , 0x43 , function_select]
JUMP                    //[calldataload , 0x43 , function_select]
INVALID                 //[]


// 3. Metadata
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
INVALID
DUP3
INVALID
POP
LOG4
INVALID
ADDRESS
INVALID
INVALID
DUP16
PUSH12 0x875e3d0fc4f8de30690c067d
INVALID
DUP14
CALLVALUE
MUL
INVALID
CODESIZE
INVALID
SGT
PUSH5 0x736f6c6343
STOP
ADDMOD
BYTE
STOP
CALLER