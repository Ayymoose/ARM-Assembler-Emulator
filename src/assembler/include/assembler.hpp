#include <fstream>
#include <iostream>
#include <unordered_map>
#include <functional>


class Assembler {

    public:
   
    // Assembles the source file and writes it
    bool assemble(std::string output_file);

    // Creates the symbol table from a (.s) file
    bool create_symbol_table(std::string file_name);

    private:

        // Hash table for opcode to functions
        // Using C++11 lambda expressions
        std::unordered_map<std::string,std::function<uint32_t(std::vector<std::string>)>> opcode_map =
        {
         {"add",[this](std::vector<std::string> instruction){ return assemble_add(instruction);}},
         {"sub",[this](std::vector<std::string> instruction){ return assemble_sub(instruction);}},
         {"rsb",[this](std::vector<std::string> instruction){ return assemble_rsb(instruction);}},
         {"and",[this](std::vector<std::string> instruction){ return assemble_and(instruction);}},
         {"eor",[this](std::vector<std::string> instruction){ return assemble_eor(instruction);}},
         {"orr",[this](std::vector<std::string> instruction){ return assemble_orr(instruction);}},
         {"mov",[this](std::vector<std::string> instruction){ return assemble_mov(instruction);}},
         {"tst",[this](std::vector<std::string> instruction){ return assemble_tst(instruction);}},
         {"teq",[this](std::vector<std::string> instruction){ return assemble_teq(instruction);}},
         {"cmp",[this](std::vector<std::string> instruction){ return assemble_cmp(instruction);}},
         {"mul",[this](std::vector<std::string> instruction){ return assemble_mul(instruction);}}, 
         {"mla",[this](std::vector<std::string> instruction){ return assemble_mla(instruction);}},
         {"ldr",[this](std::vector<std::string> instruction){ return assemble_ldr(instruction);}},  
         {"str",[this](std::vector<std::string> instruction){ return assemble_str(instruction);}},
         {"beq",[this](std::vector<std::string> instruction){ return assemble_beq(instruction);}}, 
         {"bne",[this](std::vector<std::string> instruction){ return assemble_bne(instruction);}},
         {"bge",[this](std::vector<std::string> instruction){ return assemble_bge(instruction);}},
         {"blt",[this](std::vector<std::string> instruction){ return assemble_blt(instruction);}},
         {"bgt",[this](std::vector<std::string> instruction){ return assemble_bgt(instruction);}},
         {"ble",[this](std::vector<std::string> instruction){ return assemble_ble(instruction);}},
         {"b",  [this](std::vector<std::string> instruction){ return assemble_b(instruction);}},
         {"lsl",[this](std::vector<std::string> instruction){ return assemble_lsl(instruction);}}, 
         {"andeq",[this](std::vector<std::string> instruction){ return assemble_andeq(instruction);}}
        };

        // Internal symbol table
        std::map<std::string,int> symbol_table;

        // Vector of array of string tokens 
        std::vector<std::vector<std::string>> instructions;

        // Assemble a single instruction
        bool assemble_instruction(std::vector<std::string> instruction);

        // Separate instruction types
        uint32_t assemble_ldr(std::vector<std::string> instruction);
        uint32_t assemble_str(std::vector<std::string> instruction);

        uint32_t assemble_mul(std::vector<std::string> instruction);
        uint32_t assemble_mla(std::vector<std::string> instruction);

        uint32_t assemble_add(std::vector<std::string> instruction);
        uint32_t assemble_sub(std::vector<std::string> instruction);
        uint32_t assemble_rsb(std::vector<std::string> instruction);
        uint32_t assemble_and(std::vector<std::string> instruction);
        uint32_t assemble_eor(std::vector<std::string> instruction);
        uint32_t assemble_orr(std::vector<std::string> instruction);
        uint32_t assemble_mov(std::vector<std::string> instruction);
        uint32_t assemble_tst(std::vector<std::string> instruction);
        uint32_t assemble_teq(std::vector<std::string> instruction);
        uint32_t assemble_cmp(std::vector<std::string> instruction);

        uint32_t assemble_beq(std::vector<std::string> instruction);
        uint32_t assemble_bne(std::vector<std::string> instruction);
        uint32_t assemble_bge(std::vector<std::string> instruction);
        uint32_t assemble_blt(std::vector<std::string> instruction);
        uint32_t assemble_bgt(std::vector<std::string> instruction);
        uint32_t assemble_ble(std::vector<std::string> instruction);
        uint32_t assemble_b(std::vector<std::string> instruction);

        uint32_t assemble_lsl(std::vector<std::string> instruction);
        uint32_t assemble_andeq(std::vector<std::string> instruction);
};


