#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


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