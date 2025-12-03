#define _CRT_SECURE_NOT_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

int password(char pass0[6], char pass1[6]);
void compared(int ret);
void plain(char message0[321], int message1[2560], int blocks[40][64]);
void IP(int blocks[40][64], const int input[40][64], int output[40][64], const int ip[64]);
void divide(int output[40][64], int L[40][32], int R[40][32]);
void ebox(int R[40][32], int EBOX[40][48], const int Etable[48]);
void makekey64(unsigned char key[8], int key64[64]);


int main()
{
   char pass0[6];
   char pass1[6];
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
   printf("HELLO! I am Mari, and I am the developer of this program :)\nThis program does its best to encrypt your messages.\n");
   printf("We will now enter the world of cryptography!");
   printf("\n\n=========================================================================================");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
   printf("\n\n >> Please enter a 5-character password : ");

   int ret = password(pass0, pass1);
   compared(ret);

   char message0[321] = { 0, };
   int message1[2560] = { 0, };
   int blocks[40][64] = { { 0, }{ 0, } };
   plain(message0, message1, blocks);

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
   const int input[40][64] = { {0,},{0,} };
   int output[40][64] = { {0,},{0,} };
   IP(blocks, input, output, ip);

   int L[40][32] = { {0, },{0, } };
   int R[40][32] = { {0, },{0, } };
   divide(output, L, R);

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
   int EBOX[40][48] = { {0, },{0, } };
   ebox(R, EBOX, Etable);

   unsigned char key[8] =
   {
     0x13, 0x34, 0x57, 0x79,
     0x9B, 0xBC, 0xDF, 0xF1
   };
   int key64[64] = { 0, };
   makekey64(key, key64);

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

void plain(char message0[321], int message1[2560], int blocks[40][64])
{
   printf("\n >> Now, Enter your message in 320 characters!");
   printf("\n    If you have completed the input, please press the [ Enter key ].");
   printf("\n : ");

   int len = 0;
   int pad = 0;
   int block = 8;

   fgets(message0, 321, stdin);

   len = strlen(message0);
   message0[strcspn(message0, "\n")] = '\0';
   len = strlen(message0);

   if (len <= 320)
   {
      if (len % block == 0)
      {
         pad = block;
      }
      else
      {
         pad = block - (len % block);
      }
   }

   else
   {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
      printf("\n >> The character limit of 320 has been exceeded...bye...\n");
   }

   for (int i = 0; i < pad; i++)
   {
      message0[len + i] = (char)pad;
   }
   message0[len + pad] = '\0';
   int totalLen = len + pad;
   int idx = 0;

   for (int j = 0; j < totalLen; j++)
   {
      unsigned char c = message0[j];
      for (int i = 7; i >= 0; i--)
      {
         message1[idx++] = (c >> i) & 1;
      }
   }
   for (int h = 0; h < 40; h++)
   {
      for (int k = 0; k < 64; k++)
      {
         blocks[h][k] = message1[h * 64 + k];
      }
   }
}

void IP(int blocks[40][64], const int input[40][64], int output[40][64], const int ip[64]) // const = 절대 원형 바뀌면 안 되는 애들.
{
    for (int i = 0; i < 39; i++) // blocks에 있던 값 그대로 input이랑 output에 갖다 복사해야 됨
    {
        for (int j = 0; j < 63; j++)
        {
            blocks[i][j] = input[i][j];
            blocks[i][j] = output[i][j];
        }
    }

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
}

void makekey64(unsigned char key[8], int key64[64])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            key64[i * 8 + j] = (key[i] >> (7 - j)) & 1;
        }
    }
}

