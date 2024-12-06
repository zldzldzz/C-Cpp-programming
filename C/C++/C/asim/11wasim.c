#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *instruction[] = {"MOV", "ADD", "SUB", "CMP", "JMP", "JZ", "JA", "JB", "JAE", "JBE", "INC", "DEC", "INT"};
const char *reg8[] = {"AL", "AH", "BL", "BH", "CL", "CH", "DL", "DH"};
const char *reg16[] = {"AX", "BX", "CX", "DX", "CS", "DS", "ES", "SS", "IP", "SP", "BP", "SI", "DI"};
const char *pseudo[] = {"SEGMENT", "ASSUME", "DW", "DB", "END"};

// 배열 크기 매크로
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// 특정 문자열이 명령어인지 확인
int is_instruction(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(instruction); i++)
    {
        if (_stricmp(word, instruction[i]) == 0)
            return 1;
    }
    return 0;
}
// 특정 문자열이 reg8인지 확인
int is_reg8(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(reg8); i++)
    {
        if (_stricmp(word, reg8[i]) == 0)
            return 1;
    }
    return 0;
}
// 특정 문자열이 reg16인지 확인
int is_reg16(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(reg16); i++)
    {
        if (_stricmp(word, reg16[i]) == 0)
            return 1;
        else if (strchr(word, '+') != NULL)
            return 1;
    }
    return 0;
}
// 특정 문자열이 의사명령어인지 확인
int is_pseudo(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(pseudo); i++)
    {
        if (_stricmp(word, pseudo[i]) == 0)
            return 1;
    }
    return 0;
}
// 특정 문자열이 숫자인지 확인
int is_number(const char *word)
{
    int i = 0;
    int len = strlen(word);
    if (word[0] == '-')
        i++; // 음수 확인
    if (len > 1 && (word[len - 1] == 'H' || word[len - 1] == 'h'))
    {
        for (int j = i; j < len - 1; j++)
        {
            if (!isxdigit(word[j]))
                return 0;
        }
        return 1;
    }
    for (; word[i] != '\0'; i++)
    {
        if (!isdigit(word[i]))
            return 0;
    }
    return 1;
}
// 특정 문자열이 배열에 있는지 확인
int is_in_array(const char *word, const char *arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (_stricmp(word, arr[i]) == 0)
            return 1;
    }
    return 0;
}
// 명령어 길이 계산
int calculate_length(const char *opcode, const char *op1, const char *op2)
{
    if (_stricmp(op1, "DB") == 0)
    {
        return 1; // DB는 1 바이트
    }
    if (_stricmp(op1, "DW") == 0)
    {
        return 2; // DW는 2 바이트
    }
    // MOV 명령어
    if (_stricmp(opcode, "MOV") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8비트 레지스터 간 MOV
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16비트 레지스터 간 MOV
        }
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 2; // 즉시값과의 MOV
            }
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)))
        {
            if (is_number(op2))
            {
                return 3; // 즉시값과의 MOV
            }
            return 4; // 메모리 주소와의 MOV
        }
        return 3; // 기본 메모리 MOV
    }
    // ADD, SUB 명령어
    if (_stricmp(opcode, "ADD") == 0 || _stricmp(opcode, "SUB") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8비트 레지스터 간 ADD/SUB
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16비트 레지스터 간 ADD/SUB
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) || is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 3; // 즉시값과의 ADD/SUB
            }
            return 4; // 메모리 주소와의 ADD/SUB
        }
        return 3; // 기본 메모리 ADD/SUB
    }
    // CMP 명령어
    if (_stricmp(opcode, "CMP") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8비트 레지스터 간 CMP
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16비트 레지스터 간 CMP
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) || is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 3; // 즉시값과의 CMP
            }
            return 4; // 메모리 주소와의 CMP
        }
        return 3; // 기본 메모리 CMP
    }
    // JMP 및 조건부 점프 명령어
    if (is_in_array(opcode, (const char *[]){"JMP", "JZ", "JA", "JB", "JAE", "JBE"}, 6))
    {
        return 2;
    }
    // INC, DEC 명령어
    if (_stricmp(opcode, "INC") == 0 || _stricmp(opcode, "DEC") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) || is_in_array(op1, reg16, ARRAY_SIZE(reg16)))
        {
            return 1; // 레지스터 대상
        }
        return 2; // 메모리 대상
    }
    // INT 명령어
    if (_stricmp(opcode, "INT") == 0)
        return 2;
    // 기본 길이
    return 2;
}

int main()
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    char line[256] = {0};
    const char *delim = " ,\t";
    // txt파일 읽기 모드로 열기
    inputFile = fopen("symbol.txt", "r");
    if (inputFile == NULL)
    {
        printf("Failed to open input file again.\n");
        exit(1);
    }
    // 출력 파일 열기
    outputFile = fopen("output3.txt", "w+");
    if (outputFile == NULL)
    {
        printf("Failed to open output file.\n");
        exit(1);
    }
    // 파일에서 한 줄씩 읽고 치환하기
    while (fgets(line, sizeof(line), inputFile))
    {
        if (strlen(line) <= 1)
        { // 빈 줄은 그대로 출력
            fprintf(outputFile, "\n");
            continue;
        }
        line[strcspn(line, "\n")] = '\0'; // Enter 제거
        fprintf(outputFile, "%s ", line);
        // 원본 복사 후 단어 단위로 분리
        char line_copy[256];
        strcpy(line_copy, line);
        // 레이블이 있으면 다음 단어로 이동
        char *command = strchr(line_copy, ':');
        if (command != NULL)
        {
            command++;
            // 다음 단어가 공백이면 한번 더 이동
            while (*command == ' ' || *command == '\t')
            {
                command++;
            }
        }
        else
        {
            command = line_copy;
        }
        // 명령어와 오퍼랜드 파싱
        char opcode[16] = "", op1[16] = "", op2[16] = "";
        char *token = strtok(command, delim);
        int count = 0;
        // 검사 및 치환
        fprintf(outputFile, " [");

        while (token != NULL)
        {
            if (is_instruction(token))
            {
                strcpy(opcode, token);
                fprintf(outputFile, "op ");
            }
            else if (is_reg8(token))
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "reg8 ");
            }
            else if (is_reg16(token))
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "reg16 ");
            }
            else if (is_number(token))
            {
                strcpy(op2, token);
                fprintf(outputFile, "num ");
            }
            else if (is_pseudo(token))
            {
                strcpy(op1, token);
                fprintf(outputFile, "pop ");
            }
            else
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "sym ");
            }
            count++;
            token = strtok(NULL, delim);
        }
        // 길이 계산
        int length = calculate_length(opcode, op1, op2);
        // 결과 출력

        fprintf(outputFile, "] %d\n", length);
    }
    printf("Complete\n");
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}