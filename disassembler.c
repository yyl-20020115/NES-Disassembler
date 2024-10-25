#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char* name;
    int bytes;
} Opcode;

Opcode opcodes[256] = {
    {"BRK", 1}, {"ORA ($%02X,X)", 2}, {"KIL", 1}, {"SLO ($%02X,X)", 2}, {"NOP $%02X", 2}, {"ORA $%02X", 2}, {"ASL $%02X", 2}, {"SLO $%02X", 2},
    {"PHP", 1}, {"ORA #$%02X", 2}, {"ASL A", 1}, {"ANC #$%02X", 2}, {"NOP $%04X", 3}, {"ORA $%04X", 3}, {"ASL $%04X", 3}, {"SLO $%04X", 3},
    {"BPL $%04X", 2}, {"ORA ($%02X),Y", 2}, {"KIL", 1}, {"SLO ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"ORA $%02X,X", 2}, {"ASL $%02X,X", 2}, {"SLO $%02X,X", 2},
    {"CLC", 1}, {"ORA $%04X,Y", 3}, {"NOP", 1}, {"SLO $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"ORA $%04X,X", 3}, {"ASL $%04X,X", 3}, {"SLO $%04X,X", 3},
    {"JSR $%04X", 3}, {"AND ($%02X,X)", 2}, {"KIL", 1}, {"RLA ($%02X,X)", 2}, {"BIT $%02X", 2}, {"AND $%02X", 2}, {"ROL $%02X", 2}, {"RLA $%02X", 2},
    {"PLP", 1}, {"AND #$%02X", 2}, {"ROL A", 1}, {"ANC #$%02X", 2}, {"BIT $%04X", 3}, {"AND $%04X", 3}, {"ROL $%04X", 3}, {"RLA $%04X", 3},
    {"BMI $%04X", 2}, {"AND ($%02X),Y", 2}, {"KIL", 1}, {"RLA ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"AND $%02X,X", 2}, {"ROL $%02X,X", 2}, {"RLA $%02X,X", 2},
    {"SEC", 1}, {"AND $%04X,Y", 3}, {"NOP", 1}, {"RLA $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"AND $%04X,X", 3}, {"ROL $%04X,X", 3}, {"RLA $%04X,X", 3},
    {"RTI", 1}, {"EOR ($%02X,X)", 2}, {"KIL", 1}, {"SRE ($%02X,X)", 2}, {"NOP $%02X", 2}, {"EOR $%02X", 2}, {"LSR $%02X", 2}, {"SRE $%02X", 2},
    {"PHA", 1}, {"EOR #$%02X", 2}, {"LSR A", 1}, {"ALR #$%02X", 2}, {"JMP $%04X", 3}, {"EOR $%04X", 3}, {"LSR $%04X", 3}, {"SRE $%04X", 3},
    {"BVC $%04X", 2}, {"EOR ($%02X),Y", 2}, {"KIL", 1}, {"SRE ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"EOR $%02X,X", 2}, {"LSR $%02X,X", 2}, {"SRE $%02X,X", 2},
    {"CLI", 1}, {"EOR $%04X,Y", 3}, {"NOP", 1}, {"SRE $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"EOR $%04X,X", 3}, {"LSR $%04X,X", 3}, {"SRE $%04X,X", 3},
    {"RTS", 1}, {"ADC ($%02X,X)", 2}, {"KIL", 1}, {"RRA ($%02X,X)", 2}, {"NOP $%02X", 2}, {"ADC $%02X", 2}, {"ROR $%02X", 2}, {"RRA $%02X", 2},
    {"PLA", 1}, {"ADC #$%02X", 2}, {"ROR A", 1}, {"ARR #$%02X", 2}, {"JMP ($%04X)", 3}, {"ADC $%04X", 3}, {"ROR $%04X", 3}, {"RRA $%04X", 3},
    {"BVS $%04X", 2}, {"ADC ($%02X),Y", 2}, {"KIL", 1}, {"RRA ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"ADC $%02X,X", 2}, {"ROR $%02X,X", 2}, {"RRA $%02X,X", 2},
    {"SEI", 1}, {"ADC $%04X,Y", 3}, {"NOP", 1}, {"RRA $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"ADC $%04X,X", 3}, {"ROR $%04X,X", 3}, {"RRA $%04X,X", 3},
    {"NOP #$%02X", 2}, {"STA ($%02X,X)", 2}, {"NOP #$%02X", 2}, {"SAX ($%02X,X)", 2}, {"STY $%02X", 2}, {"STA $%02X", 2}, {"STX $%02X", 2}, {"SAX $%02X", 2},
    {"DEY", 1}, {"NOP #$%02X", 2}, {"TXA", 1}, {"XAA #$%02X", 2}, {"STY $%04X", 3}, {"STA $%04X", 3}, {"STX $%04X", 3}, {"SAX $%04X", 3},
    {"BCC $%04X", 2}, {"STA ($%02X),Y", 2}, {"KIL", 1}, {"AHX ($%02X),Y", 2}, {"STY $%02X,X", 2}, {"STA $%02X,X", 2}, {"STX $%02X,Y", 2}, {"SAX $%02X,Y", 2},
    {"TYA", 1}, {"STA $%04X,Y", 3}, {"TXS", 1}, {"TAS $%04X,Y", 3}, {"SHY $%04X,X", 3}, {"STA $%04X,X", 3}, {"SHX $%04X,Y", 3}, {"AHX $%04X,Y", 3},
    {"LDY #$%02X", 2}, {"LDA ($%02X,X)", 2}, {"LDX #$%02X", 2}, {"LAX ($%02X,X)", 2}, {"LDY $%02X", 2}, {"LDA $%02X", 2}, {"LDX $%02X", 2}, {"LAX $%02X", 2},
    {"TAY", 1}, {"LDA #$%02X", 2}, {"TAX", 1}, {"LAX #$%02X", 2}, {"LDY $%04X", 3}, {"LDA $%04X", 3}, {"LDX $%04X", 3}, {"LAX $%04X", 3},
    {"BCS $%04X", 2}, {"LDA ($%02X),Y", 2}, {"KIL", 1}, {"LAX ($%02X),Y", 2}, {"LDY $%02X,X", 2}, {"LDA $%02X,X", 2}, {"LDX $%02X,Y", 2}, {"LAX $%02X,Y", 2},
    {"CLV", 1}, {"LDA $%04X,Y", 3}, {"TSX", 1}, {"LAS $%04X,Y", 3}, {"LDY $%04X,X", 3}, {"LDA $%04X,X", 3}, {"LDX $%04X,Y", 3}, {"LAX $%04X,Y", 3},
    {"CPY #$%02X", 2}, {"CMP ($%02X,X)", 2}, {"NOP #$%02X", 2}, {"DCP ($%02X,X)", 2}, {"CPY $%02X", 2}, {"CMP $%02X", 2}, {"DEC $%02X", 2}, {"DCP $%02X", 2},
    {"INY", 1}, {"CMP #$%02X", 2}, {"DEX", 1}, {"AXS #$%02X", 2}, {"CPY $%04X", 3}, {"CMP $%04X", 3}, {"DEC $%04X", 3}, {"DCP $%04X", 3},
    {"BNE $%04X", 2}, {"CMP ($%02X),Y", 2}, {"KIL", 1}, {"DCP ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"CMP $%02X,X", 2}, {"DEC $%02X,X", 2}, {"DCP $%02X,X", 2},
    {"CLD", 1}, {"CMP $%04X,Y", 3}, {"NOP", 1}, {"DCP $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"CMP $%04X,X", 3}, {"DEC $%04X,X", 3}, {"DCP $%04X,X", 3},
    {"CPX #$%02X", 2}, {"SBC ($%02X,X)", 2}, {"NOP #$%02X", 2}, {"ISC ($%02X,X)", 2}, {"CPX $%02X", 2}, {"SBC $%02X", 2}, {"INC $%02X", 2}, {"ISC $%02X", 2},
    {"INX", 1}, {"SBC #$%02X", 2}, {"NOP", 1}, {"SBC #$%02X", 2}, {"CPX $%04X", 3}, {"SBC $%04X", 3}, {"INC $%04X", 3}, {"ISC $%04X", 3},
    {"BEQ $%04X", 2}, {"SBC ($%02X),Y", 2}, {"KIL", 1}, {"ISC ($%02X),Y", 2}, {"NOP $%02X,X", 2}, {"SBC $%02X,X", 2}, {"INC $%02X,X", 2}, {"ISC $%02X,X", 2},
    {"SED", 1}, {"SBC $%04X,Y", 3}, {"NOP", 1}, {"ISC $%04X,Y", 3}, {"NOP $%04X,X", 3}, {"SBC $%04X,X", 3}, {"INC $%04X,X", 3}, {"ISC $%04X,X", 3},
};


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_rom.nes>\n", argv[0]);
        return 1;
    }

    FILE *rom_file = fopen(argv[1], "rb");
    if (rom_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    fseek(rom_file, 0, SEEK_END);
    int rom_size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);

    uint8_t *program = (uint8_t *)malloc(rom_size);
    if (program == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a ROM.\n");
        fclose(rom_file);
        return 1;
    }
    fread(program, sizeof(uint8_t), rom_size, rom_file);
    fclose(rom_file);

    FILE *output = fopen("output.asm", "w");
    if (output == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo .asm\n");
        free(program);
        return 1;
    }

    free(program);
    fclose(output);

    printf("Arquivo output.asm gerado com sucesso!\n");
    return 0;
}