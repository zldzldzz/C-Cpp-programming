#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <unordered_set>

// Symbol Table Class
class SymbolTable {
public:
    void addSymbol(const std::string& label, int address) {
        table[label] = address;
    }

    bool hasSymbol(const std::string& label) const {
        return table.find(label) != table.end();
    }

    int getAddress(const std::string& label) const {
        return table.at(label);
    }

    void display() const {
        std::cout << "\nSymbol Table:\n";
        for (const auto& entry : table) {
            std::cout << entry.first << " -> " << std::hex << std::setw(4) << std::setfill('0') << entry.second << "\n";
        }
    }

private:
    std::unordered_map<std::string, int> table;
};

// Instruction Table Class
class InstructionTable {
public:
    struct Instruction {
        std::string operand1;
        std::string operand2;
        std::string size;
        std::string opcode;
        int length;
        std::string binaryPattern;
    };

    void load(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Instruction inst;
            std::string mnemonic;
            iss >> mnemonic >> inst.operand1 >> inst.operand2 >> inst.size >> inst.opcode >> inst.length >> inst.binaryPattern;
            table[mnemonic].push_back(inst);
        }
    }

    const std::vector<Instruction>& getInstructions(const std::string& mnemonic) const {
        return table.at(mnemonic);
    }

    bool hasInstruction(const std::string& mnemonic) const {
        return table.find(mnemonic) != table.end();
    }

private:
    std::unordered_map<std::string, std::vector<Instruction>> table;
};

// Register Table Class
class RegisterTable {
public:
    void load(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string regName, regCode;
            iss >> regName >> regCode;
            table[regName] = regCode;
        }
    }

    bool hasRegister(const std::string& regName) const {
        return table.find(regName) != table.end();
    }

    bool is16BitRegister(const std::string& regName) const {
        static const std::unordered_set<std::string> reg16 = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
        return reg16.find(regName) != reg16.end();
    }

    bool is8BitRegister(const std::string& regName) const {
        static const std::unordered_set<std::string> reg8 = {"AL", "AH", "BL", "BH", "CL", "CH", "DL", "DH"};
        return reg8.find(regName) != reg8.end();
    }

private:
    std::unordered_map<std::string, std::string> table;
};

// Assembler Class
class Assembler {
public:
    Assembler(const InstructionTable& instTable, const RegisterTable& regTable)
        : instructionTable(instTable), registerTable(regTable), addressCounter(0) {}

    void processPass1(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        std::cout << "Pass 1 Output:\n";
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == ';') {
                continue; // Skip empty lines or comments
            }

            int currentAddress = addressCounter;
            std::string output = processLinePass1(line);
            if (!output.empty()) {
                std::cout << std::setw(4) << std::setfill('0') << std::hex << currentAddress << " " << output << "\n";
            }
        }

        symbolTable.display();
    }

private:
    const InstructionTable& instructionTable;
    const RegisterTable& registerTable;
    SymbolTable symbolTable;
    int addressCounter;

    std::string processLinePass1(const std::string& line) {
        std::istringstream iss(line);
        std::string word;
        iss >> word;

        if (word.back() == ':') { // Label definition
            std::string label = word.substr(0, word.size() - 1);
            symbolTable.addSymbol(label, addressCounter);
            return word;
        }

        if (instructionTable.hasInstruction(word)) { // Instruction
            return processInstructionPass1(word, iss);
        }

        return processDataDefinitionPass1(word, iss); // Data definition
    }

    std::string processInstructionPass1(const std::string& mnemonic, std::istringstream& iss) {
        std::string operand1, operand2;
        iss >> operand1;

        if (operand1.back() == ',') {
            operand1.pop_back();
            iss >> operand2;
        }

        for (const auto& inst : instructionTable.getInstructions(mnemonic)) {
            if (matchOperands(inst, operand1, operand2)) {
                int length = inst.length;
                addressCounter += length;
                std::ostringstream oss;
                oss << mnemonic << " " << operand1 << (operand2.empty() ? "" : ", " + operand2);
                oss << "  inst  " << mnemonic << "   " << inst.operand1 << " " << inst.operand2 << " "
                    << inst.size << " " << inst.opcode << " " << inst.length << " " << inst.binaryPattern;
                return oss.str();
            }
        }

        return mnemonic + " (unknown format)";
    }

    std::string processDataDefinitionPass1(const std::string& symbol, std::istringstream& iss) {
        std::string size, value;
        iss >> size >> value;
        int length = (size == "DW") ? 2 : 1;
        symbolTable.addSymbol(symbol, addressCounter);
        addressCounter += length;
        return symbol + " " + size + " " + value;
    }

    bool matchOperands(const InstructionTable::Instruction& inst, const std::string& op1, const std::string& op2) {
    if (inst.operand1 != getOperandType(op1)) return false; // Match first operand
    if (!inst.operand2.empty() && inst.operand2 != getOperandType(op2)) return false; // Match second operand
    return true;
}


    std::string getOperandType(const std::string& operand) {
    if (registerTable.hasRegister(operand)) return "R"; // Register
    if (operand.front() == '[' && operand.back() == ']') return "M"; // Memory reference
    if (std::all_of(operand.begin(), operand.end(), [](char c) { return std::isdigit(c) || c == '-'; })) return "I"; // Immediate
    if (symbolTable.hasSymbol(operand)) return "M"; // Variable or symbol as memory reference
    return "S"; // Default for labels or symbols
}
};

int main() {
    InstructionTable instTable;
    RegisterTable regTable;

    instTable.load("inst.txt");
    regTable.load("reg.txt");

    Assembler assembler(instTable, regTable);
    assembler.processPass1("test1.txt");

    return 0;
}
