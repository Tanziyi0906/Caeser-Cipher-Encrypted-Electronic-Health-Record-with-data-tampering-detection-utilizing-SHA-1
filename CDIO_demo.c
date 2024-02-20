#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "CDIO_demo.h"

bool verification(char *userName)
{
    int username_length = strlen(userName);
    if (username_length<6||username_length>12)
    {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_symbol =false;

    for (int i=0; i<username_length; i++)
    {
        if (isupper(userName[i]))
        {
            has_upper = true;
        }
         if (islower(userName[i]))
        {
            has_lower = true;
        }
         if (isdigit(userName[i]))
        {
            has_digit = true;
        }
         if (ispunct(userName[i]))
        {
            has_symbol = true;
        }
    }

    if(!has_upper)
    {
        return false;
    }
     if(!has_lower)
    {
        return false;
    }
     if(!has_digit)
    {
        return false;
    }
     if(!has_symbol)
    {
        return false;
    }

    return true;
}

void sha_1_1()
{
  int length,number_of_block,str_length;
  unsigned int i = 0,j = 0,l = 0,e = 0,n = 0, t=0, k=0,f=0;
  float x=0;
  char c;
  int H[5]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0};
  unsigned int temp = 0;

  FILE *file;
  file = fopen("patient_info.csv", "r");//Choose the file that want to access
  if (file == NULL)//detect the file is empty or not
  {
      printf("The file is empty");
  }

  fseek(file, 0, SEEK_END);// move the file pointer to the end of the file
  length = ftell(file);//calculate the length of sting in file
  fseek(file, 0, SEEK_SET);// move file pointer back to start of file so we can read each character

  char *string = malloc(sizeof(char) * (length+1));

  while ( (c = fgetc(file)) != EOF)//pass the every character in the file to the string array
  {
    string[i] = c;
    i++;
  }

  string[i] = '\0';//terminate the string storing

  unsigned char long_msg[length+1];

  for (i=0;i<length;i++)//pass the pointer array to the unsigned character array
  {
      long_msg[i]=string[i];
  }

  long_msg[length]=128;

  if (length<=55)
  {
      number_of_block = 1;
  }
  else if (length>55 && length<120)
  {
      number_of_block = 2;
  }
  else
  {
      x = ((length - 55)/64);//calculate the number of block needed
      number_of_block = x+2;
  }

  unsigned char blocks[number_of_block][64];

  for (i=0;i<number_of_block;i++)//Split the long string into n number of blocks
  {
      for(j=0;j<64;j++)
      {
          blocks[i][j]=long_msg[l];
          if(l>length)//padding 0
          {
              blocks[i][j]=0;
          }
          l++;
      }
  }

  str_length = 8*length;//sting length in bits

  if (length < 0x1F)//if length of string is 1 bytes in hexadecimal
  {
      blocks[number_of_block-1][63]=str_length;
  }
  else if (length >= 0x1F && length < 0x1FFF)
  {
      blocks[number_of_block-1][62]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<8)>>8);//last block
  }
  else if (length >= 0x1FFF && length < 0x1FFFFF)
  {
      blocks[number_of_block-1][61]=(str_length>>16);//third last block
      blocks[number_of_block-1][62]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<16)>>16);//last block
  }
  else
  {
      blocks[number_of_block-1][60]=(str_length>>24);//fourth last block
      blocks[number_of_block-1][62]=(str_length>>16);//third last block
      blocks[number_of_block-1][61]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<24)>>24);//last block
  }

  unsigned int w[number_of_block][16][4];
  unsigned int W[number_of_block][80];
  unsigned int A[number_of_block],B[number_of_block],C[number_of_block],D[number_of_block],E[number_of_block];

  for (e=0;e<number_of_block;e++)
  {
      /*The problem is here*/
      n=0;
      for (i=0;i<16;i++)//split the padding message into w0 to w15 ,exp. w0 = (w[0][1]),....,(w[0][3])
        {
            for(j=0;j<4;j++)
            {
                w[e][i][j] = blocks[e][n];
                n++;
            }
        }

      for (i=0;i<16;i++)//combine the hex --> 16 block of hexadecimal(W0 to W15)
        {
            W[e][i] = ((w[e][i][0])<<24 | (w[e][i][1])<<16 | (w[e][i][2])<<8 | (w[e][i][3]));
        }

      for (i=16;i<80;i++)
        {
            W[e][i] = 0;
        }

    /*Compute message digest*/
    if (e==0)
    {
        A[e] = 0x67452301;
        B[e] = 0xEFCDAB89;
        C[e] = 0x98BADCFE;
        D[e] = 0x10325476;
        E[e] = 0xC3D2E1F0;
    }
    else
    {
        A[e] = H[0];
        B[e] = H[1];
        C[e] = H[2];
        D[e] = H[3];
        E[e] = H[4];
    }

      for (t=0;t<=79;t++)
    {
        //for t = 16 -> 79
        if (t>=16 && t<=79)//prepare W16 to W79
        {
            W[e][t]= ( (W[e][t-3]) ^ (W[e][t-8]) ^ (W[e][t-14]) ^ (W[e][t-16]) );
            W[e][t]= ( ((W[e][t])<<1) | ((W[e][t]) >> (32-1)));//perform circular left shift
        }

        if (t>=0 && t<=19)
        {
            f = (B[e]&C[e]) | ((~B[e])&D[e]);
            k = 0x5A827999;
        }
        else if (t>=20 && t<=39)
        {
            f = (B[e]^C[e]^D[e]);
            k = 0x6ED9EBA1;
        }
        else if (t>=40 && t<=59)
        {
            f = (B[e]&C[e]) | (B[e]&D[e]) | (C[e]&D[e]);
            k = 0x8F1BBCDC;
        }
        else if(t>=60 && t<=79)
        {
            f = (B[e]^C[e]^D[e]);
            k = 0xCA62C1D6;
        }

        temp = ((A[e]<<5) | (A[e] >> (32-5))) + f + E[e] + W[e][t] + k;

        E[e] = D[e];
        D[e] = C[e];
        C[e] = ( (B[e]<<30) | (B[e]>> (32-30)));
        B[e] = A[e];
        A[e] = temp;
    }
    H[0] = ( H[0] + A[e]);
    H[1] = ( H[1] + B[e]);
    H[2] = ( H[2] + C[e]);
    H[3] = ( H[3] + D[e]);
    H[4] = ( H[4] + E[e]);

  }

 // printf("Message digest:");

  FILE *fa;
  fa=fopen("detect_tampering.txt", "w");
  for (i=0;i<5;i++)
    {
       fprintf(fa,"%X ",H[i]);
    }

}

void sha_1_2()
{
  int length,number_of_block,str_length;
  unsigned int i = 0,j = 0,l = 0,e = 0,n = 0, t=0, k=0,f=0;
  float x=0;
  char c;
  int origin[5];
  int H[5]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0};
  unsigned int temp = 0;

  FILE *file;
  file = fopen("patient_info.csv", "r");//Choose the file that want to access
  if (file == NULL)//detect the file is empty or not
  {
      printf("The file is empty");
  }

  fseek(file, 0, SEEK_END);// move the file pointer to the end of the file
  length = ftell(file);//calculate the length of sting in file
  fseek(file, 0, SEEK_SET);// move file pointer back to start of file so we can read each character

  char *string = malloc(sizeof(char) * (length+1));

  while ( (c = fgetc(file)) != EOF)//pass the every character in the file to the string array
  {
    string[i] = c;
    i++;
  }

  string[i] = '\0';//terminate the string storing

  unsigned char long_msg[length+1];

  for (i=0;i<length;i++)//pass the pointer array to the unsigned character array
  {
      long_msg[i]=string[i];
  }

  long_msg[length]=128;

  if (length<=55)
  {
      number_of_block = 1;
  }
  else if (length>55 && length<120)
  {
      number_of_block = 2;
  }
  else
  {
      x = ((length - 55)/64);//calculate the number of block needed
      number_of_block = x+2;
  }

  unsigned char blocks[number_of_block][64];

  for (i=0;i<number_of_block;i++)//Split the long string into n number of blocks
  {
      for(j=0;j<64;j++)
      {
          blocks[i][j]=long_msg[l];
          if(l>length)//padding 0
          {
              blocks[i][j]=0;
          }
          l++;
      }
  }

  str_length = 8*length;//sting length in bits

  if (length < 0x1F)//if length of string is 1 bytes in hexadecimal
  {
      blocks[number_of_block-1][63]=str_length;
  }
  else if (length >= 0x1F && length < 0x1FFF)
  {
      blocks[number_of_block-1][62]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<8)>>8);//last block
  }
  else if (length >= 0x1FFF && length < 0x1FFFFF)
  {
      blocks[number_of_block-1][61]=(str_length>>16);//third last block
      blocks[number_of_block-1][62]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<16)>>16);//last block
  }
  else
  {
      blocks[number_of_block-1][60]=(str_length>>24);//fourth last block
      blocks[number_of_block-1][62]=(str_length>>16);//third last block
      blocks[number_of_block-1][61]=(str_length>>8);//second last block
      blocks[number_of_block-1][63]=((str_length<<24)>>24);//last block
  }

  unsigned int w[number_of_block][16][4];
  unsigned int W[number_of_block][80];
  unsigned int A[number_of_block],B[number_of_block],C[number_of_block],D[number_of_block],E[number_of_block];

  for (e=0;e<number_of_block;e++)
  {
      /*The problem is here*/
      n=0;
      for (i=0;i<16;i++)//split the padding message into w0 to w15 ,exp. w0 = (w[0][1]),....,(w[0][3])
        {
            for(j=0;j<4;j++)
            {
                w[e][i][j] = blocks[e][n];
                n++;
            }
        }

      for (i=0;i<16;i++)//combine the hex --> 16 block of hexadecimal(W0 to W15)
        {
            W[e][i] = ((w[e][i][0])<<24 | (w[e][i][1])<<16 | (w[e][i][2])<<8 | (w[e][i][3]));
        }

      for (i=16;i<80;i++)
        {
            W[e][i] = 0;
        }

    /*Compute message digest*/
    if (e==0)
    {
        A[e] = 0x67452301;
        B[e] = 0xEFCDAB89;
        C[e] = 0x98BADCFE;
        D[e] = 0x10325476;
        E[e] = 0xC3D2E1F0;
    }
    else
    {
        A[e] = H[0];
        B[e] = H[1];
        C[e] = H[2];
        D[e] = H[3];
        E[e] = H[4];
    }

      for (t=0;t<=79;t++)
    {
        //for t = 16 -> 79
        if (t>=16 && t<=79)//prepare W16 to W79
        {
            W[e][t]= ( (W[e][t-3]) ^ (W[e][t-8]) ^ (W[e][t-14]) ^ (W[e][t-16]) );
            W[e][t]= ( ((W[e][t])<<1) | ((W[e][t]) >> (32-1)));//perform circular left shift
        }

        if (t>=0 && t<=19)
        {
            f = (B[e]&C[e]) | ((~B[e])&D[e]);
            k = 0x5A827999;
        }
        else if (t>=20 && t<=39)
        {
            f = (B[e]^C[e]^D[e]);
            k = 0x6ED9EBA1;
        }
        else if (t>=40 && t<=59)
        {
            f = (B[e]&C[e]) | (B[e]&D[e]) | (C[e]&D[e]);
            k = 0x8F1BBCDC;
        }
        else if(t>=60 && t<=79)
        {
            f = (B[e]^C[e]^D[e]);
            k = 0xCA62C1D6;
        }

        temp = ((A[e]<<5) | (A[e] >> (32-5))) + f + E[e] + W[e][t] + k;

        E[e] = D[e];
        D[e] = C[e];
        C[e] = ( (B[e]<<30) | (B[e]>> (32-30)));
        B[e] = A[e];
        A[e] = temp;
    }
    H[0] = ( H[0] + A[e]);
    H[1] = ( H[1] + B[e]);
    H[2] = ( H[2] + C[e]);
    H[3] = ( H[3] + D[e]);
    H[4] = ( H[4] + E[e]);

  }

 // printf("Message digest:");
 FILE *fa;
 fa= fopen("detect_tampering.txt", "r");
 fscanf(fa,"%X %X %X %X %X",&origin[0],&origin[1],&origin[2],&origin[3],&origin[4]);

  if(strcmp(H,origin)==0)
  {
      printf("Data is not tampered!\n");
  }
  else
  {
      printf("Data is tampered!\n");
  }

}

int caesarCipherEncrypt()
{

    extern  FILE*fp;
    char ch;
    FILE *fpt;
    fp = fopen("patient_info.csv", "r");
    if(fp == NULL)
        return 0;
    fpt = fopen("temp.csv", "w");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fp);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, fpt);
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(fpt);
    fp = fopen("patient_info.csv", "w");
    if(fp == NULL)
        return 0;
    fpt = fopen("temp.csv", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = fputc(ch, fp);
        ch = fgetc(fpt);
    }
    fclose(fp);
    fclose(fpt);
    printf("\nFile Encrypted Successfully!");

    return 0;
}

int caesarCipherDecrypt()
{
    extern FILE *fp;
    char ch;
    FILE *fpt;
    fp = fopen("patient_info.csv", "w");
    if(fp == NULL)
        return 0;
    fpt = fopen("temp.csv", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch, fp);
        ch = fgetc(fpt);
    }
    fclose(fp);
    fclose(fpt);
    printf("\nFile Decrypted Successfully!\n");
    return 0;
}

int age_cdio(char ic[30])
{
    char YY[8], MM[8], DD[8];
    int i = 0, day = 0, month = 0, year = 0, year_bd = 0;
    time_t rawtime; //Display Date
  	//struct tm * timeinfo;
  	time (&rawtime);
    //timeinfo = localtime ( &rawtime );

    int DaysInMon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t ts;
    struct tm *ct;
//1st until 6th number in IC Number determine the Birth Date
//for loop in c >>> https://www.tutorialspoint.com/cprogramming/c_for_loop.htm
    for (i=0; i<2; i++)
      {
        YY[i] = ic[i];
        MM[i] = ic[i+2];
        DD[i] = ic[i+4];
      }
//int atoi(const char *str) converts the string argument str to an integer (type int). >>> https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm
    year  = atoi(YY);
    month = atoi(MM);
    day   = atoi(DD);

    if ((year>=23)&&(year<=99))
      {
        year_bd = 1900 + year;
      }
    else if ((year>=0)&&(year<=22))
      {
        year_bd = 2000 + year;
      }
//printf padding by zeros >>> https://www.includehelp.com/c-programs/input-an-integer-value-and-print-with-padding-by-zeros.aspx
    //printf("Birth Date (dd/mm/yyyy): %02d/%02d/%0d\n", day, month, year_bd);

    int isLeapYear(int year, int mon)
{
    int flag = 0;
    if (year % 100 == 0)
    {
            if (year % 400 == 0)
            {
                    if (mon == 2)
                    {
                            flag = 1;
                    }
            }
    }
    else if (year % 4 == 0)
    {
            if (mon == 2)
            {
                    flag = 1;
            }
    }
       return (flag);
}
    /*get current date.*/
    ts = time(NULL);
    ct = localtime(&ts);

    day = DaysInMon[month - 1] - day + 1;

    /* leap year checking*/
    if (isLeapYear(year_bd, month))
    {
            day = day + 1;
    }

    /* calculating age in no of days, years and months */
    day = day + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year_bd = (ct->tm_year + 1900) - year_bd - 1;

    /* checking for leap year feb - 29 days */
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1)))
    {
            if (day >= (DaysInMon[ct->tm_mon] + 1))
            {
                    day = day - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    }
    else if (day >= DaysInMon[ct->tm_mon])
    {
            day = day - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }

    if (month >= 12)
    {
            year_bd = year_bd + 1;
            month = month - 12;
    }
    /* print age */
    //printf("Age                    : %d Years %d Months %d Days\n", year_bd, month, day);
    return year_bd;
}
