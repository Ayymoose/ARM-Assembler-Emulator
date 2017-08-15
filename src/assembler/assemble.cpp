#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <regex>
#include <vector>
#include <cstdint>

#include "include/assembler.hpp"

std::vector<std::string> tokenise(const char *string) {
    std::vector<std::string> tokens;
    do {
        const char *begin = string;
        while(*string != ' ' && *string != ',' && *string) {
            string++;
        }
        std::string token = std::string(begin,string);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    } while (*string++);
    return tokens;
}

// Passing by value requires the copy constructor
bool Assembler::create_symbol_table(std::string file_name) {
    std::ifstream assembly_file(file_name.c_str());
    if (assembly_file.is_open()) {
        std::string line;
        int line_number = 1;
        std::regex label("([a-zA-Z]+[0-9]*:)");
        std::smatch match;
        while (std::getline(assembly_file, line)) {
              if (std::regex_search(line, match, label)) {
                    std::string lbl = match[0];
                    symbol_table.insert(std::pair<std::string,int>(lbl.substr(0,lbl.length()-1),line_number * 4));
              }
              if (!line.empty() && !std::regex_search(line, match, label)) {
                line_number++;
                instructions.push_back(tokenise(line.c_str()));
               // std::cout << line << std::endl;
              }
        }
        assembly_file.close();
        return true;
    } 
    std::cerr << "Unable to open '" << file_name << "'" << std::endl;
    return false;
}

bool Assembler::assemble_instruction(std::vector<std::string> instruction) {
    std::vector<std::string>::iterator token = instruction.begin();
    std::string opcode = *token;
    opcode_map[opcode](instruction);
    return true;
}


bool Assembler::assemble(std::string output_file) {

    std::vector<std::string> tokens;
    for (std::vector<std::vector<std::string>>::iterator instruction = instructions.begin(); instruction != instructions.end(); instruction++) {
        tokens = *instruction; 
        assemble_instruction(tokens);
    }

    return false; 
}

uint32_t Assembler::assemble_ldr(std::vector<std::string> instruction) {return 0;}
uint32_t Assembler::assemble_str(std::vector<std::string> instruction) {return 0;}

uint32_t Assembler::assemble_mul(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_mla(std::vector<std::string> instruction){return 0;}

uint32_t Assembler::assemble_add(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_sub(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_rsb(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_and(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_eor(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_orr(std::vector<std::string> instruction){return 0;}

uint32_t Assembler::assemble_mov(std::vector<std::string> instruction){

    // Set the cond (bits 28-31 to 1110)
    // 1110 00 I Opcode S Rn Rd Operand2
    uint32_t instr = 0xE3A00000;
    uint32_t rn,operand2;
    
    

    return instr;
}
uint32_t Assembler::assemble_tst(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_teq(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_cmp(std::vector<std::string> instruction){return 0;}

uint32_t Assembler::assemble_beq(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_bne(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_bge(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_blt(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_bgt(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_ble(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_b(std::vector<std::string> instruction){return 0;}

uint32_t Assembler::assemble_lsl(std::vector<std::string> instruction){return 0;}
uint32_t Assembler::assemble_andeq(std::vector<std::string> instruction){return 0;}


int main(int argc, char** argv) {

  Assembler assembler;

  switch (argc) {
    case 3:
        // Two pass assembly
        // 1. Create the symbol table
        // 2. Resolve references over second pass assembling instruction
        assembler.create_symbol_table(std::string(argv[1]));
        assembler.assemble(std::string(argv[2]));
    break;
    default:
        std::cerr << "Expecting 2 arguments only: in.s out.s" << std::endl;
        exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

