#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int A = 0;
int B = 0;
int c = 0;
int z = 0;
int output = 0;
int input = 0;
int pc = 0;
int x = 0;
int y = 0;
char rom[256][9];
char ram[256][5];

//функция перевода из двоичной системы в десятичную
int convert(int a){
    int dec = 0;
    int base = 1;
    while (a > 0){
	int n = a % 10;
	a /= 10;
	dec += n * base;
	base *= 2;
    }
    return dec;
}

//функция перевода из десятичной в двоичную
char* Bin(int a, int byte){
    char* binary = malloc(byte);
    memset(binary, 0, byte);
    int mas;
    char m[2];
    while (a > 0){
        mas = a % 2; 
        a /= 2;
        sprintf(m, "%d", mas);
        strcat(binary, m);
        byte--;
    }
    
    //дополнение нулями до заданной битности
    if (byte > 0){
        char res[byte];
        memset(res, '0', byte);
        res[byte] = '\0';
        strcat(binary, res);
    }
    
    int length = strlen(binary);
    int temp = 0;
    int i, j;
    //разворот строки
    for (i = 0, j = length - 1; i < j; i++, j--){
        temp = binary[i];
        binary[i] = binary[j];
        binary[j] = temp;
    }
    
    return binary;
}

void compilation(FILE* fd){
    char buf[15];
    char res[9];
    char Im[5];
    int index = 0;
    while (fgets(buf, sizeof(buf), fd) != NULL){
        buf[strcspn(buf, "\r\n")] = 0;
        if ((strncmp(buf, "ADD A,", 6)) == 0){
            if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "0000");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
                
            else if (strlen(buf) == 7){
                strcpy(rom[index++],"10000000");
                rom[index][8] = '\0';
            }
                
            else if (strlen(buf) == 12){
                strcpy(Im, buf+8);
                strcpy(res, "0001");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
            
        else if (strncmp(buf, "MOV A,", 6) == 0){
            if (strlen(buf) == 7){
                strcpy(rom[index++],"00010000");
            rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "0011");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
            
        else if ((strncmp(buf, "IN A", 4)) == 0){
            if (strlen(buf) == 4){
                strcpy(rom[index++],"00100000");
                rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 9){
                strncpy(Im, buf+5, 4);
                strcpy(res, "0010");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }   
        
        else if (strncmp(buf, "MOV B,", 6) == 0){
            if (strlen(buf) == 7){
                strcpy(rom[index++],"01000000");
            rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "0111");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        if ((strncmp(buf, "ADD B,", 6)) == 0){
            if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "0101");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
                
            else if (strlen(buf) == 12){
                strcpy(Im, buf+8);
                strcpy(res, "0100");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if ((strncmp(buf, "IN B", 4)) == 0){
            if (strlen(buf) == 4){
                strcpy(rom[index++],"01100000");
                rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 9){
                strncpy(Im, buf+5, 4);
                strcpy(res, "0110");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if (strcmp(buf, "NEG A") == 0){
            strcpy(rom[index++],"10000001");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "NOT A") == 0){
            strcpy(rom[index++],"10000010");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "OR A,B") == 0){
            strcpy(rom[index++],"10000011");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "AND A,B") == 0){
            strcpy(rom[index++],"10000100");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "XOR A,B") == 0){
            strcpy(rom[index++],"10000101");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "SUB A,B") == 0){
            strcpy(rom[index++],"10000110");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "output A") == 0){
            strcpy(rom[index++],"10000111");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "LD A") == 0){
            strcpy(rom[index++],"10001000");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "ST A") == 0){
            strcpy(rom[index++],"10001001");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "LD B") == 0){
            strcpy(rom[index++],"10001010");
            rom[index][8] = '\0';
        }
        
        else if (strcmp(buf, "ST B") == 0){
            strcpy(rom[index++],"10001011");
            rom[index][8] = '\0';
        }
        
        else if (strncmp(buf, "MOV X,", 6) == 0){
            if (strlen(buf) == 7){
                strcpy(rom[index++],"10001100");
            rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "1100");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if (strncmp(buf, "MOV Y,", 6) == 0){
            if (strlen(buf) == 7){
                strcpy(rom[index++],"10001101");
            rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "1101");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if (strcmp(buf, "INC XY") == 0){
            strcpy(rom[index++],"10001110");
        }
        
        else if (strncmp(buf, "JMP", 3) == 0){
            if (strlen(buf) == 6){
                strcpy(rom[index++],"10001111");
                rom[index][8] = '\0';
            }
            
            else if (strlen(buf) == 8){
                strcpy(Im, buf+4);
                strcpy(res, "1111");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if (strncmp(buf, "output B", 5) == 0){
            if (strlen(buf) == 5){
                strcpy(rom[index++],"10010000");
                rom[index][8] = '\0';
            }
            
             else if (strlen(buf) == 10){
                strcpy(Im, buf+6);
                strcpy(res, "1001");
                strcat(res, Im);
                strcpy(rom[index++], res);
                rom[index][8] = '\0';
            }
        }
        
        else if (strncmp(buf, "JZ", 2) == 0){
            strncpy(Im, buf+3, 4);
            strcpy(res, "1010");
            strcat(res, Im);
            strcpy(rom[index++], res);
            rom[index][8] = '\0';
            
        }
        
        else if (strncmp(buf, "JNC", 3) == 0){
            strncpy(Im, buf+4, 4);
            strcpy(res, "1110");
            strcat(res, Im);
            strcpy(rom[index++], res);
            rom[index][8] = '\0';
        }  
        
        else if (strncmp(buf, "output", 3) == 0){
            if (strlen(buf) == 8){
                strncpy(Im, buf+4, 4);
              strcpy(res, "1011");
              strcat(res, Im);
              strcpy(rom[index++], res);
              rom[index][8] = '\0';
            }
        }
    }
}

//Вывод значений на каждом ходу
void new_print(int A, int B, int c, int input, int output, int pc, char* command){
    printf("A: %s\tB: %s\tc: %d\tPC: %s\tКоманда: %s\tINPUT: %s\tOUT: %s\n", Bin(A, 4), Bin(B, 4), c, Bin(pc, 4), command, Bin(input, 4), Bin(output, 4));
}

void prog(){
    char command[100];
    memset(command, 0, sizeof(command));
    memcpy(command, rom[pc], 8);
    command[strlen(command)] = '\0';
    int Im = 0;
    char name[12];
    memset(name, 0, sizeof(name));
    if (strncmp(command, "0000", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name,"ADD A,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        A += Im;
        if (A > 15){
            A -= 16 ;
            c = 1;
            z = 0;
        }
        
        else if (A == 0){
            z = 1;
            c = 0;
        }
        
        else{
            c = 0;
            z = 0;
        }
        
        pc++;
    }
    
    else if (strncmp(command, "0001", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "MOV A,B");
            A = B;
            pc++;
            c = 0;
            z = 0;
        }
        
        else{
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(name, "ADD A,B,");
            strcat(name, command+4);
            new_print(A, B, c, input, output, pc, name);
            B+= Im;
            A = B;
            if (A > 15){
                A -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (A == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
    }
    
    else if (strncmp(command, "0010", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "IN A");
            A = input;
            pc++;
            c = 0;
            z = 0;
        }
        
        else{
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(name, "IN A+");
            strcat(name, command+4);
            new_print(A, B, c, input, output, pc, name);
            input += Im;
            A = input;
            if (A > 15){
                A -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (A == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
    }
    
    else if (strncmp(command, "0011", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "MOV A,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        A = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "0100", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "MOV B,A");
            B = A;
            pc++;
            c = 0;
            z = 0;
        }
        
         else{
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(name, "ADD B,A,");
            strcat(name, command+4);
            new_print(A, B, c, input, output, pc, name);
            A+= Im;
            B = A;
            if (B > 15){
                B -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (B == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
    }
    
    else if (strncmp(command, "0101", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "ADD B,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        B += Im; 
        if (B > 15){
            B -= 16 ;
            c = 1;
            z = 0;
        }
        
        else if (B == 0){
            z = 1;
            c = 0;
        }
        
        else{
            c = 0;
            z = 0;
        }
        
        pc++;
    }
    
    else if (strncmp(command, "0110", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "IN B");
            B = input;
            pc++;
            c = 0;
            z = 0;
        }
        
        else{
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(name, "IN B+");
            strcat(name, command+4);
            new_print(A, B, c, input, output, pc, name);
            input += Im;
            B = input;
            if (B > 15){
                B -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (B == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
    }
    
    else if (strncmp(command, "0111", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "MOV B,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        B = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "1000", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "ADD A,B");
            A += B; 
            if (A > 15){
                A -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (A == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
        
        else if (strncmp(command+4, "0001", 4) == 0){
            new_print(A, B, c, input, output, pc, "NEG A");
            A -= 16 ;
            if (A > 15){
                A -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (A == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
        
        else if (strncmp(command+4, "0010", 4) == 0){
            new_print(A, B, c, input, output, pc, "NOT A");
            A = 15 - A;
            if (A == 0){
                z = 1;
            }
            
            else{
                z = 0;
            }
            
            c = 0;
            pc++;
         }
         
        else if (strncmp(command+4, "0011", 4) == 0){
            new_print(A, B, c, input, output, pc, "OR A,B");
            A = A | B;
            c = 0;
            if (A == 0){
                z = 1;
            }
            
            else{
                z = 0;
            }
            
            pc++;
        }
        
        else if (strncmp(command+4, "0100", 4) == 0){
            new_print(A, B, c, input, output, pc, "AND A,B");
            A = A & B;
            c = 0;
            if (A == 0){
                z = 1;
            }
            
            else{
                z = 0;
            }
            
            pc++;
        }
        
        else if (strncmp(command+4, "0101", 4) == 0){
            new_print(A, B, c, input, output, pc, "XOR A,B");
            A = A ^ B;
            c = 0;
            if (A == 0){
                z = 1;
            }
            
            else{
                z = 0;
            }
            
            pc++;
        }
        
        if (strncmp(command+4, "0110", 4) == 0){
            new_print(A, B, c, input, output, pc, "SUB A,B");
            A -= B; 
            if (A < 0){
                A -= 16 ;
                c = 1;
                z = 0;
            }
            
            else if (A == 0){
                z = 1;
                c = 0;
            }
            
            else{
                c = 0;
                z = 0;
            }
            
            pc++;
        }
        
        else if (strncmp(command+4, "0111", 4) == 0){
            new_print(A, B, c, input, output, pc, "OUT A");
            output = A;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1000", 4) == 0){
            new_print(A, B, c, input, output, pc, "LD A");
            char *XY;
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            A = strtol(ram[Im], &endptr, 2) & 0xF;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1001", 4) == 0){
            new_print(A, B, c, input, output, pc, "ST A");
            char *XY;
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(ram[Im], Bin(A, 4));
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1010", 4) == 0){
            new_print(A, B, c, input, output, pc, "LD B");
            char *XY;
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            B = strtol(ram[Im], &endptr, 2) & 0xF;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1011", 4) == 0){
            new_print(A, B, c, input, output, pc, "ST B");
            char *XY;
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            strcpy(ram[Im], Bin(B, 4));
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1100", 4) == 0){
            new_print(A, B, c, input, output, pc, "MOV X,A");
            x = A;
            pc++;
            c = 0;
            z = 0;
        }
        
        else if (strncmp(command+4, "1101", 4) == 0){
            new_print(A, B, c, input, output, pc, "MOV Y,A");
            y = A;
            pc++;
            c = 0;
            z = 0;
        }
        
        else if (strncmp(command+4, "1110", 4) == 0){
            new_print(A, B, c, input, output, pc, "INC XY");
            char *XY;
            y++;
            if (y > 15){
                y -= 16;
                x++;
                if (x > 15){
                    x -= 16;
                }
            }
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1111", 4) == 0){
            new_print(A, B, c, input, output, pc, "JMP XY");
            char *XY;
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            char* endptr;
            Im = strtol(command + 4, &endptr, 2) & 0xF;
            c = 0;
            z = 0;
            pc = Im;
        }
    }
    
    else if (strncmp(command, "1001", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, input, output, pc, "OUT B");
            output = B;
            c = 0;
            z = 0;
            pc++;
        }
        
        else{
            char* endptr;
            strcpy(name, "OUT B+");
            strcat(name, command+4);
            new_print(A, B, c, input, output, pc, name);
            output = B;
            c = 0;
            z = 0;
            pc++;
        }
    }
    
    else if (strncmp(command, "1010", 4) == 0){
        char* endptr;
        strcpy(name, "JZ ");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        if (z == 1){
            char PCL[9];
            strncpy(PCL, Bin(pc, 8), 4);
            strcat(PCL, command+4);
            Im = strtol(PCL, &endptr, 2) & 0xF;
            pc = Im;
        }
        
        else
            pc++;
    }
    
    else if (strncmp(command, "1011", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "OUT ");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        output = Im;
    }
    
    else if (strncmp(command, "1100", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "MOV Y,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        y = Im;
    }
    
    else if (strncmp(command, "1101", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "MOV X,");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        x = Im;
    }
    
    else if (strncmp(command, "1110", 4) == 0){
        strcpy(name, "JNC ");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        if (c == 0){
            char pcl[8];
            memcpy(pcl, Bin(pc, 8), 4); 
            strcat(pcl, command+4);
            pcl[8] = '\0';
            char* endptr;
            Im = strtol(pcl, &endptr, 2) & 0xF;
            pc = Im;
        }
        
        else
            pc++;
    }
    
     else if (strncmp(command, "1111", 4) == 0){
        char* endptr;
        strcpy(name, "JMP ");
        strcat(name, command+4);
        new_print(A, B, c, input, output, pc, name);
        char PCL[9];
        strncpy(PCL, Bin(pc, 8), 4);
        strcat(PCL, command+4);
        Im = strtol(PCL, &endptr, 2) & 0xF;
        pc = Im;
    }
}

int main(int argc, char* argv[]){
    char code_file[256], ram_file[256], rom_file[256];
    int mode = 0;
    if (strcmp(argv[1], "-a") == 0)
        mode = 1;
    
    else if (strcmp(argv[1], "-m") == 0)
        mode = 0;
        
    else{
        printf("Неверно указан режим выполнения");
        exit(1);
    }
    
    strcpy(code_file, argv[2]);
    strcpy(ram_file, argv[3]);
    if (argc == 5){
        strcpy(ram_file, argv[4]);
    }

    else if (argc < 4 || argc > 5){
        printf("Указано неверное количество аргументов");
        exit(1);
    }
    
    FILE* fd = fopen(code_file, "r");
    int j = 0;
    compilation(fd);
    fclose(fd);
    while(1){
        if (pc > 255)
            pc = 0;
        
        sleep(1/10);
        prog();
    }
    return 0;
}
