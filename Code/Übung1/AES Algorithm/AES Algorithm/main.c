//
//  main.c
//  AES Algorithm
//
//  Created by Finn on 15/11/6.
//  Copyright (c) 2015年 Zhiwei. All rights reserved.
//

#include <stdio.h>
/******************************************************************************************************************/
#define uchar unsigned char                                      //marco define
#define uint  unsigned int
/**********************************************************************************/

uchar SBox[16][16] =                    //SBox Table
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
uchar MCM[4][4] =                       //MixColumns factortable
{
    0x02,0x03,0x01,0x01,
    0x01,0x02,0x03,0x01,
    0x01,0x01,0x02,0x03,
    0x03,0x01,0x01,0x02
};
uchar RCon[10] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
/**********************************************************************************/

uchar AddRoundkey(uchar State[4][4], uchar Key[4][4]);
uchar SubBytes(uchar State[4][4]);
uchar ShiftRows(uchar State[4][4]);
uchar MixColumns(uchar State[4][4]);
uchar AES(uchar State[4][4], uchar Key[4][4]);
/******************************************************************************************************************/
uchar KeyExpansion(uchar Key[4][4], uchar RoundNum);
uint ByteToWord(uchar Key[4][4],uchar k);
uchar WordToByte(uint Word, uchar Key[4][4],uchar k);
uint GiFunction(uint Word, uchar Round);
/**********************************************************************************/

uchar State[4][4] = {   0x11,0x12,0x14,0x18,
                        0x21,0x22,0x24,0x28,
                        0x41,0x42,0x44,0x48,
                        0x81,0x82,0x84,0x88
                    };
uchar Key[4][4] =   {
                        0x81,0x82,0x84,0x88,
                        0x41,0x42,0x44,0x48,
                        0x21,0x22,0x24,0x28,
                        0x11,0x12,0x14,0x18
};

/**********************************************************************************/

int main(int argc, const char * argv[]) {

    //   WordToByte(j, Key, 0);
    AES(State, Key);
//    KeyExpansion(Key,1);
    uchar x,y;
    for (x=0; x<4; x++) {
        for (y=0; y<4; y++) {
            printf("%x ",State[x][y]);
        }
        printf("\n");
    }

    
}

/******************************************************************************************************************/

uchar AddRoundkey(uchar State[4][4], uchar Key[4][4])                                     //First step AddRoundKey
{
    unsigned char i,j;
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            State[j][i] ^= Key[j][i];
        }
    }
    return 0;
}


/******************************************************************************************************************/

uchar SubBytes(uchar State[4][4])                                     //Second step SubBytes
{
    uchar i,j;
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            State[i][j]=SBox[State[i][j]/16][ State[i][j]%16];
        }
    }
    return 0;
}


/******************************************************************************************************************/
uchar ShiftRows(uchar State[4][4])                                                        //Third step ShiftRows
{
    uchar i,j,k;
    for (i=1; i<4; i++) {
        for (j=1; j<i+1; j++) {
            uchar temp = State[i][3];
            for (k=3; k>0; k--)
                State[i][k]=State[i][k-1];
            State[i][0]=temp;
        }
    }
    return 0;
}

/******************************************************************************************************************/

uchar MixColumns(uchar State[4][4])                                                       //Forth step MixCloumns
{
    uchar i,j,k;
    uchar Temp[4][4];
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            switch (MCM[i][0]) {
                case 0x01:
                    Temp[i][j] = State[0][j];
                    break;
                case 0x02:
                    Temp[i][j] = State[0][j] << 1;
                    if (State[0][j] & 0x80)
                        Temp[i][j] ^= 0x1b;
                    break;
                case 0x03:
                    Temp[i][j] = State[0][j]<<1;
                    if (State[0][j] & 0x80)
                        Temp[i][j] ^= 0x1b;
                    Temp[i][j] ^= State[0][j];
                    break;
                default:
                    break;
            }
            for (k=1; k<4; k++) {
                uchar AddFactor;
                switch (MCM[i][k]) {
                    case 0x01:
                        AddFactor = State[k][j];
                        break;
                    case 0x02:
                        AddFactor = State[k][j] << 1;
                        if (State[k][j] & 0x80)
                            AddFactor ^= 0x1b;
                        break;
                    case 0x03:
                        AddFactor = State[k][j] << 1;
                        if (State[k][j] & 0x80)
                            AddFactor ^= 0x1b;
                        AddFactor ^= State[k][j];
                        break;
                    default:
                        break;
                }
                Temp[i][j] ^= AddFactor;
            }
        }
    }
    for (i=0; i<4; i++)
        for (j=0; j<4; j++)
            State[i][j] = Temp[i][j];
    return 0;
}
uchar AES(uchar State[4][4], uchar Key[4][4])
{
    uchar i;
    AddRoundkey(State, Key);
    for (i=1; i<10; i++) {
        SubBytes(State);
        ShiftRows(State);
        MixColumns(State);
        KeyExpansion(Key, i);
        AddRoundkey(State, Key);
        
    }
    SubBytes(State);
    ShiftRows(State);
    KeyExpansion(Key, 10);
    AddRoundkey(State, Key);
    return 0;
}

/******************************************************************************************************************/
uchar KeyExpansion(uchar Key[4][4], uchar RoundNum)                                                   //KeyExpansion
{
    if (RoundNum>10)
        printf("RoundNum error");
    uint W0 = ByteToWord(Key, 0),W1 = ByteToWord(Key, 1),W2 = ByteToWord(Key, 2),W3 = ByteToWord(Key, 3);
    W0 ^= GiFunction(W3, RoundNum);
    W1 ^= W0;
    W2 ^= W1;
    W3 ^= W2;
    WordToByte(W0, Key, 0);
    WordToByte(W1, Key, 1);
    WordToByte(W2, Key, 2);
    WordToByte(W3, Key, 3);
    return 0;
}
uint ByteToWord(uchar Key[4][4],uchar k)                                                            //transfer the Bytes into Word
{
    return (Key[0][k]+Key[1][k]*0x100+Key[2][k]*0x10000+Key[3][k]*0x1000000);
}
uchar WordToByte(uint Word, uchar Key[4][4],uchar k)                                                //transfer the word into Bytes
{
    uchar   i;
    uint WWord = Word;
    for (i=0; i<4; i++) {
        Key[3-i][k] = WWord / 0x1000000;
        WWord <<= 8;
    }
    return 0;
}

uint GiFunction(uint Word, uchar RoundNum)                                                          //GiFunction
{
    uint WWord = Word;
    uchar B2 = WWord / 0X1000000, B3 = WWord % 0x100;
    WWord <<=8;uchar B1 = WWord / 0x1000000;
    WWord <<=8;uchar B0 = WWord / 0x1000000;
    B3 = SBox[B3 / 0x10][ B3 % 0X10];
    B2 = SBox[B2 / 0x10][ B2 % 0X10];
    B1 = SBox[B1 / 0x10][ B1 % 0X10];
    B0 = SBox[B0 / 0x10][ B0 % 0X10];
    B0 ^= RCon[RoundNum-1];
    WWord = B3 * 0X1000000 + B2 * 0x10000 + B1 * 0x100 + B0;
    return WWord;
}

