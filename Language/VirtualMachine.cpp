//
// Created by sean on 27/06/2020.
//

#include "Instructions.h"
#include "VirtualMachine.h"

void VM::Execute() {
    bool running = true;

    while (running) {
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
                stack.push(a + b);
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

            case INS::RAND : {
                int param = this->stack.top();
                this->stack.pop();
                int result = (int) (rand() % param);
                this->stack.push(result);
                break;
            }

            case INS::OUTPUT : {
                std::cout << "VMOUT " << this->stack.top() << std::endl;
                this->stack.pop();
                break;
            }

//            case INS::INPUT : {
//                break;
//            }

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

                if (a) {
                    programCounter = addr-1;
                }
                break;
            }

            default: {
                std::cerr << "Unknown Instruction" << std::endl;
                std::cerr << "pc = " << programCounter << " instr = " << getCurrentInstruction() << std::endl;
            }

        }
        incrProgramCounter();
    }
}
