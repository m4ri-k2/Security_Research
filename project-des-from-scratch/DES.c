#define _CRT_SECURE_NOT_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

//---

int password(char pass0[6], char pass1[6]);
void compared(int ret);
void plain(char message0[301], int message1[2560], int blocks[40][64]);
void IP(const int input[40][64], int output[40][64], const int ip[64]);
void divide(int output[40][64], int L[40][32], int R[40][32]);
void ebox(int R[40][32], int EBOX[40][48], const int Etable[48]);
void makekey64(unsigned char key[8], int key64[64]);
void PC1(const int pc1[56], int pc1table[56], const int key64[64]);
void devideCD(int C[28], int D[28], int pc1table[56]);
void left_rotate_1(int A[28]);
void shift(int C[28], int D[28], int round);
void CD1(int C[28], int D[28], int CD[56]);
void PC2(const int pc2[48], int out48[48], int CD[56]);
const int shift_table[16] = { 0, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
void F(const int R[32], const int roundkey[48], int out32[32], const int Etable[48], const int Ptable[32], const int SBOX[8][4][16]);
static void xor48(const int a[48], const int b[48], int out[48]); 
static void pbox32(const int in32[32], int out32[32], const int Ptable[32]);
static void sbox_6_to_4(const int six[6], const int S[4][16], int out4[4]);
static void sboxes_48_to_32(const int in48[48], int out32[32], const int SBOX[8][4][16]);
static void xor32(const int AA[32], const int BB[32], int outout[32]);
void one_round(const int L[32], const int R[32], const int roundKey[48], int newL[32], int newR[32], const int Etable[48], const int Ptable[32], const int SBOX[8][4][16]);
//---

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("HELLO! I am m4ri, and I am the developer of this program :)");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    printf("\nThis program does its best to encrypt your messages.\n");
    printf("We will now enter the world of cryptography!");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("\n\n=========================================================================================");
    printf("\n\n >> Please enter a 5-character password : ");

    char pass0[6];
    char pass1[6];
    int ret = password(pass0, pass1);
    char message0[301];
    int message1[2560];
    int blocks[40][64];
    const int ip[64] =
    {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };
    const int input[40][64];
    int output[40][64];
    int L[40][32];
    int R[40][32];
    const int Etable[48] =
    {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };
    int EBOX[40][48];
    unsigned char key[8] =
    {
        0x13, 0x34, 0x57, 0x79,
        0x9B, 0xBC, 0xDF, 0xF1
    };
    int key64[64];
    int pc1table[56];
    const int pc1[56] =
    {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };
    int round = 0;
    int roundkey[16][48];
    int C[28];
    int D[28];
    int CD[56];
    int out48[48];
    const int pc2[48] =
    {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };
    int out32[32];
    const int Ptable[32];
    const int SBOX[8][4][16];
    const int a[48];
    const int b[48];
    int out[48];
    const int in32[32];
    int out32[32];
    const int six[6];
    const int S[4][16]; 
    int out4[4];
    const int in48[48];
    const int AA[32];
    const int BB[32];
    int outout[32];
    int newL[32];
    int newR[32];


    compared(ret);
    plain(message0, message1, blocks);
    IP(input, output, ip);
    divide(output, L, R);
    ebox(R, EBOX, Etable);
    makekey64(key, key64);
    PC1(pc1, pc1table, key64);
    devideCD(C, D, pc1table);
    
    for (int round = 0; round < 16; round++) 
    {
        shift(C, D, round);
        CD1(C, D, CD);
        PC2(pc2, roundkey[round], CD);
    }

    left_rotate_1(A);
    shift(C, D, round);
    CD1(C, D, CD);
    PC2(pc2, out48, CD);
    F(R, roundkey, out32, Etable, Ptable, SBOX);
    xor48(a, b, out);
    pbox32(in32, out32, Ptable);
    sbox_6_to_4(six, S, out4);
    sboxes_48_to_32(in48, out32, SBOX);
    xor32(AA, BB, outout);
    one_round(L, R, roundkey, newL, newR, Etable, Ptable, SBOX);

}


// --------------------------- 여기서부터 함수 구역 --------------------------- //


int password(char pass0[6], char pass1[6])
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        pass0[i] = _getch();
        printf("*");
    }
    pass0[5] = '\0';
    printf("\n >> try again!: ");

    for (i = 0; i < 5; i++)
    {
        pass1[i] = _getch();
        printf("*");
    }
    pass1[5] = '\0';
    printf("\n");
    return strcmp(pass0, pass1);
}

void compared(int ret)
{
    if (ret == 0)
    {
        printf("");
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("\n=========================================================================================");
        printf("\n...Who are you?");
        exit(0);
    }
}

void plain(char message0[301], int message1[2560], int blocks[40][64])
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    printf("\n >> Now, Enter your message in 300 characters!");
    printf("\n    If you have completed the input, please press the [ Enter key ].");
    printf("\n : ");

    int len = 0; // 입력글자 수
    int pad = 0; // 1블록=1패드
    int block = 8; // 1블록 크기 지정

    fgets(message0, 301, stdin); // message0에 300자 받기

    len = strlen(message0); // message0에 받은 문자열 길이 재기
    message0[strcspn(message0, "\n")] = '\0'; // 엔터키 누르기 전까지의 길이를 재는 거임
    // len = strlen(message0); 얘 왜 두 번 넣었지 나중에 오류 안 나면 빼기 

    if (len <= 300) // 320자보다 입력글자 수가 같거나 작은 경우
    {
        if (len % block == 0) // 문자열을 1블록(= 8글자, bit로 환산하면 64bit) 단위로 나눴을 때 나누어떨어진다면(= 예시: 40자, 160자 등등)
        {
            pad = block; // 1패드 = 1블록
        }
        else // 나누어떨어지지 않는다면(= 예시: 43자, 293자 등등)
        {
            pad = block - (len % block); // 1패드 = 1블록-(문자열을 1블록 단위로 나눈 값의 나머지)
        }
    }

    else // 320자를 넘기는 경우
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("\n >> The character limit of 300 has been exceeded...bye...\n"); // 300자 초과하면 뜨는 메시지. 여기까지가 글자 받는 부분 끝.
    }

    // --------------------------- 여기서부터 암호화 알고리즘 시작 --------------------------- //

    for (int i = 0; i < pad; i++) // 패드(8칸짜리 블럭)에 글자 채울 때
    {
        message0[len + i] = (char)pad; // 입력버퍼에서 남은 자리에 패딩 채워서 1블록(1pad) 완성시키는 거
    }
    message0[len + pad] = '\0'; // 엔터키 칠 때까지 받기
    int totalLen = len + pad; // 입력글자 수 + 패드 수 = 전체 입력글자
    int idx = 0;

    for (int j = 0; j < totalLen; j++) // 블록(암호화 단위)나누는 코드. 
    {
        unsigned char c = message0[j]; // 전체 입력받은 문자열을 unsigned형으로 바꿔서 1글자당 8비트(2진수. 00100010 같은)로 만들어서 계산 본격적으로 들어감

        for (int i = 7; i >= 0; i--)
        {
            message1[idx++] = (c >> i) & 1; // 위에서 2진수로 만들어 놓은 문자열을 하나씩 2560칸 안에 집어넣기. 그리고 비트 번호의 홀수/짝수 판별용으로 & 1 쳐서 LSB(오른쪽 맨 마지막 비트) 만 남김. 비트 하나=LSB 하나
        }
    }
    for (int h = 0; h < 40; h++) // message1(2560칸. 아까 비트번호 홀/짝 판별해놓은 LSB 값들 개수 = 2560개)를 나누어봅시다
    {
        for (int k = 0; k < 64; k++) // h: 블록 번호 (0~39), k: 블록 내의 비트 인덱스 (0~63). 그러면 IP 전치해야 되는 패드 개수는 40개라는 소리가 됨. 당연히 패드 하나 안에 있는 비트 개수는 64개.
        {
            blocks[h][k] = message1[h * 64 + k]; // message1(2560자)에서의 문자 위치 찾으려면 이렇게 
        }
    }
}

void IP(const int input[40][64], int output[40][64], const int ip[64]) // const = 절대 원형 바뀌면 안 되는 애들.
{
    for (int i = 0; i < 40; i++) // IP 전치해야 하는 패드 40개 다 전치시킬 때까지 반복. 
    {
        for (int j = 0; j < 64; j++) // 그 패드에 있는 1번부터 64번까지 64개 다 바꿔서 옮길 때까지 반복
        {
        output[i][j] = input[i][ip[j] - 1]; // ip전치 식
        }
    }
}

void divide(int output[40][64], int L[40][32], int R[40][32]) // 32비트씩 반으로 쪼개기
{
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 32; j++) // 왼쪽 반
        {
            L[i][j] = output[i][j];
        }

        for (int k = 32; k < 64; k++) // 오른쪽 반
        {
            R[i][k - 32] = output[i][k];
        }
    }
}

void ebox(int R[40][32], int EBOX[40][48], const int Etable[48])
{
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            int src_index = Etable[j] - 1;
            EBOX[i][j] = R[i][src_index];
        }
    }
} // 여기까지가 평문 암호화할 준비. 이 밑으로가 암호화 과정 본격적으로 시작

void makekey64(unsigned char key[8], int key64[64]) // 64비트 암호화 패드 만들기 완료
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            key64[i * 8 + j] = (key[i] >> (7 - j)) & 1;
        }
    }
}

void PC1(const int pc1[56], int pc1table[56], const int key64[64]) // 이제 해당 함수에서는 PC1에 사용할 테이블 만들어야 함
{
    for (int i = 0; i < 56; i++)
    {
        pc1table[i] = key64[pc1[i] - 1];
    }
}

void devideCD(int C[28], int D[28], int pc1table[56])
{
    for (int i = 0; i < 28; i++)
    {
        C[i] = pc1table[i];
    }
    for (int j = 0; j < 28; j++)
    {
        D[j] = pc1table[j + 28];
    }
}

void left_rotate_1(int A[28])
{
    int temp = A[0];
    for (int i = 0; i < 27; i++)
    {
      A[i] = A[i + 1];
    }
    A[27] = temp;
}


void shift(int C[28], int D[28], int round)
{ 
    for (int k = 0; k < shift_table[round]; k++)
    {
        left_rotate_1(C);
        left_rotate_1(D);
    }
}

void CD1(int C[28], int D[28], int CD[56])
{
    for (int i = 0; i < 28; i++)
    {
        CD[i] = C[i];
    }
    for (int j = 0; j < 28; j++)
    {
        CD[j + 28] = D[j];
    }
}

void PC2(const int pc2[48], int out48[48], int CD[56])
{
    for (int i = 0; i < 48; i++)
    {
        out48[i] = CD[pc2[i] - 1];
       
    }
}

static void xor48(const int a[48], const int b[48], int out[48])
{
    for (int i = 0; i < 48; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

static void pbox32(const int in32[32], int out32[32], const int Ptable[32])
{
    for (int i = 0; i < 32; i++)
    {
        out32[i] = in32[Ptable[i] - 1];
    }
}

static void sbox_6_to_4(const int six[6], const int S[4][16], int out4[4])
{
    int row = (six[0] << 1) | six[5];
    int col = (six[1] << 3) | (six[2] << 2) | (six[3] << 1) | six[4];

    int val = S[row][col]; 

    out4[0] = (val >> 3) & 1;
    out4[1] = (val >> 2) & 1;
    out4[2] = (val >> 1) & 1;
    out4[3] = (val >> 0) & 1;
}

static void sboxes_48_to_32(const int in48[48], int out32[32], const int SBOX[8][4][16])
{
    for (int box = 0; box < 8; box++) 
    {
        int six[6];
        for (int j = 0; j < 6; j++)
        { 
            six[j] = in48[box * 6 + j];
        }

        int out4[4];
        sbox_6_to_4(six, SBOX[box], out4);

        for (int k = 0; k < 4; k++)
        {
            out32[box * 4 + k] = out4[k];
        }
    }
}

void F(const int R[32], const int roundkey[48], int out32[32], const int Etable[48], const int Ptable[32], const int SBOX[8][4][16])
{
    int ER[48];     // E(R)
    int X[48];      // ER XOR roundKey
    int S_out[32];  // S-box output (32)
    int P_out[32];  // P-box output (32)

    // 1) ER = E(R)  (1-based table)
    for (int j = 0; j < 48; j++) 
    {
        ER[j] = R[Etable[j] - 1];
    } 
    // 2) X = ER XOR roundKey
    xor48(ER, roundkey, X);
    // 3) S_out = S-boxes(X)
    sboxes_48_to_32(X, S_out, SBOX);
    // 4) P_out = P(S_out)
    pbox32(S_out, P_out, Ptable);
    // 5) out32 = P_out
    for (int i = 0; i < 32; i++) 
    {
        out32[i] = P_out[i];
    }
}

static void xor32(const int AA[32], const int BB[32], int outout[32])
{
   for (int i = 0; i < 32; i++)
   {
       outout[i] = AA[i] ^ BB[i];
   }
            
}

void one_round(const int L[32], const int R[32], const int roundkey[48], int newL[32], int newR[32], const int Etable[48], const int Ptable[32], const int SBOX[8][4][16])
{
    int f_out[32];
    F(R, roundkey, f_out, Etable, Ptable, SBOX);
    for (int i = 0; i < 32; i++) 
    {
        newL[i] = R[i];
    }
    xor32(L, f_out, newR);
}




