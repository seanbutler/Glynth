//
// Created by sean on 27/06/2020.
//

#include "Instructions.h"
#include "VirtualMachine.h"

void VM::Execute() {
    bool running = true;

    while (running) {

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

        switch ((INS)getCurrentInstruction()) {

            case INS::NOP : {
                // Do Nothing
                break;
            }

            case INS::HALT : {
                // Stop Running
                running = false;
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
                std::cout << "OUTPUT " << this->stack.top() << std::endl;
                this->stack.pop();
                break;
            }

            case INS::INPUT : {
                std::cout << "INPUT - not implemented" << std::endl;
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

                std::cout << "INS::BRT " << a << " " << addr << std::endl;

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

                std::cout << "INS::BRF " << a << " " << addr;

                if (a==0) {
                    programCounter = addr-1;
                }
                std::cout << " " << programCounter << std::endl;
                break;
            }

            case INS::END_OF_FILE: {
                running = false;
                break;
            }

            default: {
                std::cerr << "Unknown Instruction pc = " << programCounter << " instr = " << getCurrentInstruction() << std::endl;
                running = false;
            }

        }

        incrProgramCounter();
        std::cout << std::endl;
    }
}
