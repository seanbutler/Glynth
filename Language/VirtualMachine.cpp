//
// Created by sean on 27/06/2020.
//

#include "Instructions.h"
#include "VirtualMachine.h"

//#define DEBUG

void VM::Execute(unsigned int slice) {
    running = slice;
    if ( ! done ) {
        while (running > 0) {
            running--;
    #ifdef DEBUG
            std::cout << "pc = " << programCounter << " instr = " << instructionNames[getCurrentInstruction()] << std::endl;

            std::cout << "instr = ";
            for(auto E : this->instructions) {
                std::cout << E << " ";
            }
            std::cout << std::endl;

            std::cout << "data = ";
            for(auto E : this->data) {
                std::cout << E << " ";
            }
            std::cout << std::endl;

            std::cout << "stacktop = " ;

            if ( stack.size() )
                std::cout << stack.top();
            else
                std::cout << "(unknown)";

            std::cout << std::endl;
    #endif
            switch ((INS)getCurrentInstruction()) {

                case INS::NOP : {
                    // Do Nothing
                    break;
                }

                case INS::HALT : {
                    // Finish Running
                    running = false;
                    done = true;
                    break;
                }

                case INS::YIELD : {
                    // Stop Running to Restart again next iteration
                    running = false;
                    done = false;
                    break;
                }

                case INS::PUSH : {
                    incrProgramCounter();
                    stack.push(getCurrentInstruction());
                    break;
                }

                case INS::POP : {
                    stack.pop();
                    break;
                }

                case INS::ADD: {
                    int a = stack.top();
                    stack.pop();
                    int b = stack.top();
                    stack.pop();
                    stack.push(b + a);
                    break;
                }

                case INS::SUB: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    stack.pop();
                    stack.push(b - a);
                    break;
                }

                case INS::MUL: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    stack.pop();
                    stack.push(b * a);
                    break;
                }

                case INS::DIV: {
                    int a = stack.top();
                    stack.pop();
                    int b = stack.top();
                    stack.pop();
                    stack.push(b / a);
                    break;
                }

                case INS::EQU: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b == a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::NE: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b != a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::LT: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b < a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::LTE: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b <= a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::GT: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b > a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::GTE: {
                    int a = stack.top();
                    this->stack.pop();
                    int b = stack.top();
                    this->stack.pop();
                    if (b >= a)
                        this->stack.push(1);
                    else
                        this->stack.push(0);
                    break;
                }

                case INS::RAND : {
                    int param = this->stack.top();
                    this->stack.pop();
                    int result = (int) (rand() % param);
                    this->stack.push(result);
                    break;
                }

                case INS::OUTPUT : {
                    std::cout << "out... " << this->stack.top() << std::endl;
                    this->stack.pop();
                    break;
                }

                case INS::INPUT : {
                    std::cout << "INPUT - not implemented" << std::endl;
                    break;
                }

                case INS::MOVE : {
                    int dir = this->stack.top() % 4;

                    if (dir == 0) {
                        this->alien[1] -= 1;
                    }
                    else if (dir == 1) {
                        this->alien[0] += 1;
                    }
                    else if (dir == 2) {
                        this->alien[1] += 1;
                    }
                    else if (dir == 3) {
                        this->alien[0] -= 1;
                    }

                    this->stack.pop();
                    break;
                }

                case INS::TURN : {
                    int dir = this->stack.top();

                    if (dir == 0) {
                        this->alien[2] += 1;
                    }

                    if (dir == 1) {
                        this->alien[2] -= 1;
                    }

                    this->stack.pop();
                    break;
                }

                case INS::SAVEALIEN: {
                    int val = stack.top();
                    stack.pop();
                    incrProgramCounter();
                    int addr = getCurrentInstruction();
                    alien[addr] = (val%32)+1;
                    break;
                }

                case INS::LOADALIEN: {
                    incrProgramCounter();
                    int addr = getCurrentInstruction();
                    int val = alien[addr];
                    stack.push(val);
                    break;
                }

                case INS::SAVE: {
                    int val = stack.top();
                    stack.pop();
                    incrProgramCounter();
                    int addr = getCurrentInstruction();
                    data[addr] = val;
                    break;
                }

                case INS::LOAD: {
                    incrProgramCounter();
                    int addr = getCurrentInstruction();
                    int val = data[addr];
                    stack.push(val);
                    break;
                }

                case INS::JMP: {
                    incrProgramCounter();
                    int addr = getCurrentInstruction();
                    programCounter = addr-1;
                    break;
                }

                case INS::BRT: {
                    int a = stack.top();
                    this->stack.pop();

                    incrProgramCounter();
                    int addr = getCurrentInstruction();

//                    std::cout << "INS::BRT " << a << " " << addr << std::endl;

                    if (a!=0) {
                        programCounter = addr-1;
                    }
                    break;
                }

                case INS::BRF: {
                    int a = stack.top();
                    this->stack.pop();

                    incrProgramCounter();
                    int addr = getCurrentInstruction();

                    if (a==0) {
                        programCounter = addr-1;
                    }
    //                std::cout << " " << programCounter << std::endl;
                    break;
                }

                case INS::END_OF_FILE: {
                    running = 0;
                    done = true;
                    break;
                }

                default: {
                    std::cerr << "Unknown Instruction pc = " << programCounter << " instr = " << getCurrentInstruction() << std::endl;
                    running = 0;
                    done = true;
                }

            }

            incrProgramCounter();
        }

    }

}
