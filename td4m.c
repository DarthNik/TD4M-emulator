#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

//Вывод значений на каждом ходу
void new_print(int A, int B, int c, int z, int input, int output, int pc, char* command){
    printf("IN: %s OUT: %s A: %s B: %s c: %d z: %d PC: %s Команда: %s\n", Bin(input, 4), Bin(output, 4), Bin(A, 4), Bin(B, 4), c, z, Bin(pc, 8), command);
}

//сложение двух чисел
int addition(int A, int Im){
    int res = A + Im;
    if (res > 15){
        res -= 16;
        c = 1;
    }
    
    if (res == 0){
        z = 1;
    }
            
    else{
	c = 0;
	z = 0;
    }
    return res;
}

void prog(){
    char command[9];
    memset(command, 0, sizeof(command));
    memcpy(command, rom[pc], 8);
    command[9] = '\0';
    int Im = 0;
    char name[12];
    memset(name, 0, sizeof(name));
    if (strncmp(command, "0000", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name,"ADD A,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        A = addition(A, Im);
        pc++;
    }
    
    else if (strncmp(command, "0001", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "MOV A,B");
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
            name[strlen(name)] = '\0';
            new_print(A, B, c, z, input, output, pc, name);
            A = addition(B, Im);
            pc++;
        }
    }
    
    else if (strncmp(command, "0010", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "IN A");
            printf("Введите значение для регистра A:\nВвод: ");
            scanf("%d", &input);
            input = convert(input);
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
            name[strlen(name)] = '\0';
            new_print(A, B, c, z, input, output, pc, name);
            A = addition(input, Im);
            pc++;
        }
    }
    
    else if (strncmp(command, "0011", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "MOV A,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        A = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "0100", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "MOV B,A");
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
            name[strlen(name)] = '\0';
            new_print(A, B, c, z, input, output, pc, name);
            B = addition(A, Im);
            pc++;
        }
    }
    
    else if (strncmp(command, "0101", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "ADD B,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        B = addition(B, Im);
        pc++;
    }
    
    else if (strncmp(command, "0110", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "IN B");
            printf("Введите значение для регистра B:\nВвод: ");
            scanf("%d", &input);
            input = convert(input);
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
            name[strlen(name)] = '\0';
            new_print(A, B, c, z, input, output, pc, name);
            B = addition(input, Im);
            pc++;
        }
    }
    
    else if (strncmp(command, "0111", 4) == 0){
        char* endptr;
        Im = strtol(command + 4, &endptr, 2) & 0xF;
        strcpy(name, "MOV B,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        B = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "1000", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "ADD A,B");
            A = addition(A, B); 
            pc++;
        }
        
        else if (strncmp(command+4, "0001", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "NEG A");
            A = 16 - A;
            if (A > 15){
                A = 0;
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
            new_print(A, B, c, z, input, output, pc, "NOT A");
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
            new_print(A, B, c, z, input, output, pc, "OR A,B");
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
            new_print(A, B, c, z, input, output, pc, "AND A,B");
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
            new_print(A, B, c, z, input, output, pc, "XOR A,B");
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
            new_print(A, B, c, z, input, output, pc, "SUB A,B");
            A -= B; 
            if (A < 0){
                A += 16;
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
            new_print(A, B, c, z, input, output, pc, "OUT A");
            output = A;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "LD A");
            char XY[9];
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            XY[9] = '\0';
            char* endptr;
            A = strtol(ram[strtol(XY, &endptr, 2) & 0xF], &endptr, 2) & 0xF;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1001", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "ST A");
            char XY[9];
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            XY[9] = '\0';
            char* endptr;
            Im = strtol(XY, &endptr, 2) & 0xFF;
            strcpy(ram[Im], Bin(A, 4));
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1010", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "LD B");
            char XY[9];
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            XY[9] = '\0';
            char* endptr;
            B = strtol(ram[strtol(XY, &endptr, 2) & 0xFF], &endptr, 2) & 0xF;
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1011", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "ST B");
            char XY[9];
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            XY[9] = '\0';
            char* endptr;
            Im = strtol(XY, &endptr, 2) & 0xFF;
            strcpy(ram[Im], Bin(B, 4));
            c = 0;
            z = 0;
            pc++;
        }
        
        else if (strncmp(command+4, "1100", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "MOV X,A");
            x = A;
            pc++;
            c = 0;
            z = 0;
        }
        
        else if (strncmp(command+4, "1101", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "MOV Y,A");
            y = A;
            pc++;
            c = 0;
            z = 0;
        }
        
        else if (strncmp(command+4, "1110", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "INC XY");
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
            new_print(A, B, c, z, input, output, pc, "JMP XY");
            char XY[9];
            strcat(XY, Bin(x,4));
            strcat(XY, Bin(y,4));
            XY[9] = '\0';
            char* endptr;
            Im = strtol(XY, &endptr, 2) & 0xFF;
            pc = Im;
        }
    }
    
    else if (strncmp(command, "1001", 4) == 0){
        if (strncmp(command+4, "0000", 4) == 0){
            new_print(A, B, c, z, input, output, pc, "OUT B");
            output = B;
            c = 0;
            z = 0;
            pc++;
        }
        
        else{
            char* endptr;
            strcpy(name, "OUT B+");
            strcat(name, command+4);
            name[strlen(name)] = '\0';
            new_print(A, B, c, z, input, output, pc, name);
            Im = strtol(command+4, &endptr, 2) & 0xF;
            output = addition(B, Im);
            pc++;
        }
    }
    
    else if (strncmp(command, "1010", 4) == 0){
        char* endptr;
        strcpy(name, "JZ ");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        if (z == 1){
            int pcl = strtol(command+4, NULL, 2) & 0xF;
            pc = (pc & 0xF0) | pcl;
        }
        
        else
            pc++;
    }
    
    else if (strncmp(command, "1011", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "OUT ");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        output = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "1100", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "MOV Y,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        y = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "1101", 4) == 0){
        char* endptr;
        Im = strtol(command+4, &endptr, 2) & 0xF;
        strcpy(name, "MOV X,");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        x = Im;
        c = 0;
        z = 0;
        pc++;
    }
    
    else if (strncmp(command, "1110", 4) == 0){
        strcpy(name, "JNC ");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        if (c == 0){
            int pcl = strtol(command+4, NULL, 2) & 0x0F;
            pc = (pc & 0xF0) | pcl;
        }
        
        else
            pc++;
    }
    
     else if (strncmp(command, "1111", 4) == 0){
        char* endptr;
        strcpy(name, "JMP ");
        strcat(name, command+4);
        name[strlen(name)] = '\0';
        new_print(A, B, c, z, input, output, pc, name);
        int pcl = strtol(command+4, NULL, 2) & 0xF;
        pc = (pc & 0xF0) | pcl;
    }
    
    else{
        new_print(A, B, c, z, input, output, pc, "NOP");
        pc++;
    }
}

//автоматический режим
void auto_mode(){
    printf("Выберите частоту 1 ГЦ или 10 Гц\nВвод: ");
    int herz = 0;
    scanf("%d", &herz);
    while(1){
	if (pc > 255)
	    pc = 0;
	sleep(1/herz);
	prog();
    }
}

//ручной режим
void manual_mode(){
    char m[1];
    while(1){
	if (pc > 255)
	    pc = 0;
	scanf("%c", m);
	prog();
    }
}

int main(int argc, char* argv[]){
    if (argc < 3 || argc > 4){
        printf("Указано неверное количество аргументов");
        exit(1);
    }
    
    FILE* fd = fopen(argv[2], "rb");
    int c = 0;
    int i = 0;
    while ((c = fgetc(fd)) != EOF){
        strcpy(rom[i++], Bin(c, 8));
    }
    
    fclose(fd);
    
    if (argc == 4){
        fd = fopen(argv[3], "rb");
        c = 0;
        i = 0;
        while ((c = fgetc(fd)) != EOF)
            strcpy(ram[i++], Bin(c, 8));
            
        fclose(fd);
    }
    
    else{
        srand(time(NULL));
        for(int i = 0; i < 256; i++){
            strcpy(ram[i], Bin(rand()%16, 4));
        }
    }

    if (strcmp(argv[1], "-a") == 0)
        auto_mode();
    
    else if (strcmp(argv[1], "-m") == 0)
        manual_mode();
        
    else{
        printf("Неверно указан режим выполнения");
        exit(1);
    }
        
    return 0;
}
