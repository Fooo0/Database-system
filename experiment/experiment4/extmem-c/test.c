/*
 * test.c
 * Zhaonian Zou
 * Harbin Institute of Technology
 * Jun 22, 2011
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "extmem.h"

#define BASER 31415926
#define BASES 41415926
#define BASEONE 21415926
#define BASETWO 11415926
#define BASETHREEO 51415926
#define BASETHREET 61415926
#define BASEFOUR 71415926

int InitData(int amount, int min, int max, unsigned int addr);    // 准备数据
int Func1(Buffer *buf, int *count_out, int *count_tuple);     // 功能1
int Func2(Buffer *buf, int *count_out, int *count_tuple);     // 功能2
int Func3_1(Buffer *buf, int *count_out, int *count_tuple);     // 功能3.1
int Func3_2(Buffer *buf, int *count_out, int *count_tuple);     // 功能3.2
int Func4(Buffer *buf, int *count_out, int *count_tuple);     // 功能4
void Bubble_twoway(int *buffer);    // 双向冒泡排序

int main(int argc, char **argv)
{
    Buffer buf;
    unsigned char *blk = NULL;
    int count_tuple = 0, count_out = 0;    // 分别记录元组数 和  记录输出次数
    int i, j, *blk_int = NULL;
    /*准备数据*/
//    if(InitData(16, 1, 40, BASER) == -1)     // R
//    {
//        printf("Failed to prepare S");
//    }
//    if(InitData(32, 20, 60, BASES) == -1)    // S
//    {
//        printf("Failed to prepare S");
//    }
    if (!initBuffer(520, 64, &buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }

    /*数据全部读出*/
    printf("Tuples in R:\n");
    for(i = 0;i < 16; i ++)
    {
        if ((blk = readBlockFromDisk(BASER + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 7; j ++)
        {
            printf("(%d,%d),", blk_int[0], blk_int[1]);
            blk_int += 2;
        }
        freeBlockInBuffer(blk, &buf);    // 清空输入缓冲区
        blk = NULL;
        printf("\n");
    }
    printf("Tuples in S:\n");
    for(i = 0;i < 32; i ++)
    {
        if ((blk = readBlockFromDisk(BASES + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 7; j ++)
        {
            printf("(%d,%d),", blk_int[0], blk_int[1]);
            blk_int += 2;
        }
        freeBlockInBuffer(blk, &buf);    // 清空输入缓冲区
        blk = NULL;
        printf("\n");
    }
    /*功能1*/
    if(Func1(&buf, &count_out, &count_tuple) == -1)
    {
        printf("Func1 failed.\n");
        exit(0);
    }
    /*输出功能1的结果*/
    printf("Func1: %d tuples in all\n", count_tuple);
    printf("Result for func1:\n");
    printf("R.A(S.C)\tR.B(S.D)\n");
    i = 0;    // 输出结果检查
    while(i <= count_out)
    {
        if ((blk = readBlockFromDisk(BASEONE + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        if(count_tuple >= 64)
        {
            for(j = 0; j <= 63; j ++)
            {
                printf("%d\t\t%d\n", blk_int[0], blk_int[1]);
                blk_int += 2;
            }
            count_tuple -= 64;
        }
        else
        {
            for(j = 0; j < count_tuple; j ++)
            {
                printf("%d\t\t%d\n", blk_int[0], blk_int[1]);
                blk_int += 2;
            }
        }
        i += 1;
    }
    /*功能2*/
    count_tuple = 0;
    count_out = 0;
    if(Func2(&buf, &count_out, &count_tuple) == -1)
    {
        printf("Func2 failed.\n");
        exit(0);
    }
    /*输出功能2的结果*/
    printf("Func2: %d tuples in all\n", count_tuple);
    printf("Result for func2:\n");
    printf("R.A\n");
    for(i = 0; i < count_out; i ++)
    {
        if ((blk = readBlockFromDisk(BASETWO + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 16; j ++)
        {
            printf("%d\n", blk_int[j]);
        }
        freeBlockInBuffer(blk, &buf);
        blk = NULL;
    }
    /*功能3.1*/
    count_tuple = 0;
    count_out = 0;
    if(Func3_1(&buf, &count_out, &count_tuple) == -1)
    {
        printf("Func2 failed.\n");
        exit(0);
    }
    /*输出功能3.1的结果*/
    printf("Func3.1: %d tuples in all\n", count_tuple);
    printf("Result for func3.1:\n");
    printf("R.A(S.C)\tR.B\tS.D\n");
    for(i = 0; i < count_out; i ++)
    {
        if ((blk = readBlockFromDisk(BASETHREEO + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 5; j ++)
        {
            printf("%d\t\t%d\t%d\n", blk_int[0], blk_int[1], blk_int[2]);
            blk_int += 3;
        }
        freeBlockInBuffer(blk, &buf);
        blk = NULL;
    }
    /*功能3.2*/
    count_tuple = 0;
    count_out = 0;
    if(Func3_1(&buf, &count_out, &count_tuple) == -1)
    {
        printf("Func2 failed.\n");
        exit(0);
    }
    /*输出功能3.2的结果*/
    printf("Func3.2: %d tuples in all\n", count_tuple);
    printf("Result for func3.2:\n");
    printf("R.A(S.C)\tR.B\tS.D\n");
    for(i = 0; i < count_out; i ++)
    {
        if ((blk = readBlockFromDisk(BASETHREEO + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 5; j ++)
        {
            printf("%d\t\t%d\t%d\n", blk_int[0], blk_int[1], blk_int[2]);
            blk_int += 3;
        }
        freeBlockInBuffer(blk, &buf);
        blk = NULL;
    }
    /*功能4*/
    count_tuple = 0;
    count_out = 0;
    if(Func4(&buf, &count_out, &count_tuple) == -1)
    {
        printf("Func2 failed.\n");
        exit(0);
    }
    /*输出功能4的结果*/
    printf("Func4: %d tuples in all\n", count_tuple);
    printf("Result for func4:\n");
    printf("R.A(S.C)\n");
    for(i = 0; i < count_out; i ++)
    {
        printf("%d\n", i);
        if ((blk = readBlockFromDisk(BASEFOUR + i, &buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 16; j ++)
        {
            printf("%d\n", blk_int[j]);
        }
        freeBlockInBuffer(blk, &buf);
        blk = NULL;
    }
    freeBuffer(&buf);
    return 0;
}

int InitData(int amount, int min, int max, unsigned int addr)    // 准备数据
{
    Buffer buf;
    unsigned char *blk = NULL;
    int i, j, a_c, b_d, *blk_int = NULL;

    if (!initBuffer(520, 64, &buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    srand((unsigned)time(NULL));
    for(i = 0;i < amount; i ++)
    {
        if(!(blk = getNewBlockInBuffer(&buf)))
        {
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 7; j ++)
        {
            a_c = rand()%(max- min + 1) + min;
            b_d = rand()%1000 + 1;
            blk_int[0] = a_c;
            blk_int[1] = b_d;
            printf("(%d,%d),", blk_int[0], blk_int[1]);
            blk_int += 2;
        }
        if(i == amount - 1)    // 结尾块
        {
            blk_int[0] = 0;
        }
        else    // 后继块地址
        {
            blk_int[0] = addr + i + 1;
        }
        blk_int[1] = 0;
        printf("\n");
        if (writeBlockToDisk(blk, addr + i, &buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        blk = NULL;
    }
    freeBuffer(&buf);
    return 0;
}

int Func1(Buffer *buf, int *count_out, int *count_tuple)     // 功能1
{
    unsigned char *blk, *outblk;
    int i, j, k, *blk_int, *outblk_int;
    if(!(outblk = getNewBlockInBuffer(buf)))    // 输出缓冲区
    {
        return -1;
    }
    k = 0;
    outblk_int = (int *)outblk;
    for(i = 0;i < 16; i ++)    // 读R
    {
        if ((blk = readBlockFromDisk(BASER + i, buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 7; j ++)
        {
            if(blk_int[0] == 40)
            {
                (*count_tuple) ++;
                outblk_int[0] = blk_int[0];
                outblk_int[1] = blk_int[1];
                outblk_int += 2;    // 输出缓冲区下一个存储位置
                k ++;    // 辅助记录缓冲区满否
                if(k == 56)    // 输出缓冲区满
                {
                    if (writeBlockToDisk(outblk, BASEONE + (*count_out), buf) != 0)    // 输出并释放缓冲区
                    {
                        perror("Writing Block Failed!\n");
                        return -1;
                    }
                    if(!(outblk = getNewBlockInBuffer(buf)))    // 再次申请缓冲区输出缓冲区
                    {
                        return -1;
                    }
                    k = 0;
                    outblk_int = (int *)outblk;
                    (*count_out) ++;
                }
            }
            blk_int += 2;    // 下一个元组的位置
        }
        freeBlockInBuffer(blk, buf);    // 清空输入缓冲区
    }
    for(i = 0;i < 32; i ++)    // 读S
    {
        if ((blk = readBlockFromDisk(BASES + i, buf)) == NULL)
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_int = (int *)blk;
        for(j = 0; j < 7; j ++)
        {
            if(blk_int[0] == 60)
            {
                (*count_tuple) ++;
                outblk_int[0] = blk_int[0];
                outblk_int[1] = blk_int[1];
                outblk_int += 2;    // 输出缓冲区下一个存储位置
                k ++;    // 辅助记录缓冲区满否
                if(k == 56)    // 输出缓冲区满
                {
                    if (writeBlockToDisk(outblk, BASEONE + (*count_out), buf) != 0)    // 输出并释放缓冲区
                    {
                        perror("Writing Block Failed!\n");
                        return -1;
                    }
                    if(!(outblk = getNewBlockInBuffer(buf)))    // 再次申请缓冲区输出缓冲区
                    {
                        return -1;
                    }
                    k = 0;
                    outblk_int = (int *)outblk;
                    (*count_out) ++;
                }
            }
            blk_int += 2;    // 下一个元组的位置
        }
        freeBlockInBuffer(blk, buf);    // 清空输入缓冲区
    }
    if (writeBlockToDisk(outblk, BASEONE + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
    {
        perror("Writing Block Failed!\n");
        return -1;
    }
    return 0;
}

int Func2(Buffer *buf, int *count_out, int *count_tuple)
{
    unsigned char *blk = NULL, *blk_out = NULL;
    int i, j, k, *blk_int = NULL, *blk_out_int = NULL;
    if ((blk = readBlockFromDisk(BASER, buf)) == NULL)
    {
        perror("Reading Block Failed!\n");
        return -1;
    }
    blk_int = (int *)blk;
    if(!(blk_out = getNewBlockInBuffer(buf)))    // 去重的输出缓冲区
    {
        return -1;
    }
    blk_out_int = (int *)blk_out;
    for(i = 0;i < 16; i ++)
    {
        for(j = 0; j < 7; j ++)
        {
            if((*count_tuple) == 0)
            {
                blk_out_int[(*count_tuple)] = blk_int[0];
                (*count_tuple) ++;
            }
            else
            {
                for(k = 0; k < ((*count_tuple)); k ++)    // 去重
                {
                    if(blk_out_int[k] == blk_int[0])    // 重
                    {
                        break;
                    }
                }
                if(k == (*count_tuple))    // 未重
                {
                    blk_out_int[(*count_tuple)] = blk_int[0];
                    (*count_tuple) ++;
                }
            }
            blk_int += 2;
        }
        freeBlockInBuffer(blk, buf);    // 清空输入缓冲区
//        blk = NULL;
        if(i < 15)
        {
            if ((blk = readBlockFromDisk(BASER + i + 1, buf)) == NULL)    // 下一块
            {
                perror("Reading Block Failed!\n");
                return -1;
            }
            blk_int = (int *)blk;
        }
    }
    if(!(blk = getNewBlockInBuffer(buf)))    // 向磁盘输出的缓冲
    {
        return -1;
    }
    blk_int = (int *)blk;
    i = 0;
    j = 0;
    while(i < (*count_tuple))
    {
        blk_int[j] = blk_out_int[i];    // 移入缓冲
        j ++;
        if(j == 16)    // 满则输出
        {
            if (writeBlockToDisk(blk, BASETWO + (*count_out), buf) != 0)
            {
                perror("Writing Block Failed!\n");
                return -1;
            }
            if(!(blk = getNewBlockInBuffer(buf)))    // 再一次申请缓冲，因为输出时释放了
            {
                return -1;
            }
            blk_int = (int *)blk;
            (*count_out) ++;
            j = 0;
        }
        i ++;
    }
    if(j)    // 缓冲非空
    {
        if (writeBlockToDisk(blk, BASETWO + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        (*count_out) ++;
        j = 0;
    }
    blk = NULL;    // 释放相关资源
    blk_int = NULL;
    freeBlockInBuffer(blk_out, buf);
    blk_out = NULL;
    blk_out_int = NULL;
    return 0;
}

int Func3_1(Buffer *buf, int *count_out, int *count_tuple)
{
    unsigned char *blk_r = NULL, *blk_s = NULL, *blk_out = NULL;
    int i, j, k, l, n = 0, *blk_r_int = NULL, *blk_s_int = NULL, *blk_out_int = NULL;
    for(i = 0;i < 16; i ++)
    {
        if ((blk_r = readBlockFromDisk(BASER + i, buf)) == NULL)    // 下一块R
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_r_int = (int *)blk_r;
        for(j = 0; j < 7; j ++)
        {
            for(k = 0;k < 32; k ++)
            {
                if ((blk_s = readBlockFromDisk(BASES + k, buf)) == NULL)    // 下一块S
                {
                    perror("Reading Block Failed!\n");
                    return -1;
                }
                blk_s_int = (int *)blk_s;
                for(l = 0; l < 7; l ++)
                {
                    if(blk_out == NULL)
                    {
                        if(!(blk_out = getNewBlockInBuffer(buf)))
                        {
                            return -1;
                        }
                        blk_out_int = (int *)blk_out;
                    }
                    if(blk_r_int[0] == blk_s_int[0])
                    {
                        blk_out_int[0] = blk_r_int[0];
                        blk_out_int[1] = blk_r_int[1];
                        blk_out_int[2] = blk_s_int[1];
                        blk_out_int += 3;
                        (*count_tuple) ++;
                        n ++;
                        if(n == 5)
                        {
                            if (writeBlockToDisk(blk_out, BASETHREEO + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
                            {
                                perror("Writing Block Failed!\n");
                                return -1;
                            }
                            (*count_out) ++;
                            n = 0;
                            blk_out = NULL;
                            blk_out_int = NULL;
                        }
                    }
                    blk_s_int += 2;
                }
                freeBlockInBuffer(blk_s, buf);    // 清空S的输入缓冲区
                blk_s = NULL;
            }
            blk_r_int += 2;
        }
        freeBlockInBuffer(blk_r, buf);    // 清空R的输入缓冲区
        blk_r = NULL;
    }
    if(n)
    {
        if (writeBlockToDisk(blk_out, BASETHREEO + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        (*count_out) ++;
        n = 0;
    }
    return 0;
}

int Func3_2(Buffer *buf, int *count_out, int *count_tuple)
{
    unsigned char *blk = NULL, *blk_bu[7] = {NULL}, *blk_buf = NULL, *blk_out = NULL;
    int n[7] = {0}, *blk_int = NULL, *blk_bu_int[7] = {NULL}, *blk_buf_int = NULL, *blk_out_int = NULL;
    int tuples_r[7] = {0}, out_r[7] = {0}, bubase_r[7]={0,20,40,60,80,100,120};
    int tuples_s[7] = {0}, out_s[7] = {0}, bubase_s[7]={140,180,220,260,300,340,380};
    int i, j, k, l, q, m, tu_r, tu_s, limi_r, limi_s;
    /*R入桶*/
    if ((blk = readBlockFromDisk(BASER, buf)) == NULL)
    {
        perror("Reading Block R Failed!\n");
        return -1;
    }
    blk_int = (int *)blk;
    for(i = 0; i < 7; i ++)
    {
        if(!(blk_bu[i] = getNewBlockInBuffer(buf)))
        {
            return -1;
        }
        blk_bu_int[i] = (int *)blk_bu[i];
    }
    for(i = 0;i < 16; i ++)
    {
        for(j = 0; j < 7; j ++)
        {
            k = blk_int[0] % 7;
            blk_bu_int[k][0] = blk_int[0];
            blk_bu_int[k][1] = blk_int[1];
            blk_bu_int[k] += 2;
            tuples_r[k] ++;
            n[k] ++;
            if(n[k] == 8)
            {
                if (writeBlockToDisk(blk_bu[k], bubase_r[k] + out_r[k], buf) != 0)    // 输出未满的缓冲区并释放
                {
                    perror("Writing Block Failed!\n");
                    return -1;
                }
                out_r[k] ++;
                n[k] = 0;
                if(!(blk_bu[k] = getNewBlockInBuffer(buf)))
                {
                    return -1;
                }
                blk_bu_int[k] = (int *)blk_bu[k];
            }
            blk_int += 2;
        }
        freeBlockInBuffer(blk, buf);    // 清空R的输入缓冲区
        blk = NULL;
        if(i < 15)
        {
            if ((blk = readBlockFromDisk(BASER + i + 1, buf)) == NULL)    // 下一块
            {
                perror("Reading Block Failed!\n");
                return -1;
            }
            blk_int = (int *)blk;
        }
    }
    for(i = 0; i < 7; i ++)
    {
        if(n[i])
        {
            if (writeBlockToDisk(blk_bu[i], bubase_r[i] + out_r[i], buf) != 0)    // 输出未满的缓冲区并释放
            {
                perror("Writing Block Failed!\n");
                return -1;
            }
            out_r[i] ++;
            n[i] = 0;
        }
    }
    /*S入桶*/
    if ((blk = readBlockFromDisk(BASES, buf)) == NULL)
    {
        perror("Reading Block R Failed!\n");
        return -1;
    }
    blk_int = (int *)blk;
    for(i = 0; i < 7; i ++)
    {
        if(!(blk_bu[i] = getNewBlockInBuffer(buf)))
        {
            return -1;
        }
        blk_bu_int[i] = (int *)blk_bu[i];
    }
    for(i = 0;i < 32; i ++)
    {
        for(j = 0; j < 7; j ++)
        {
            k = blk_int[0] % 7;
            blk_bu_int[k][0] = blk_int[0];
            blk_bu_int[k][1] = blk_int[1];
            blk_bu_int[k] += 2;
            tuples_s[k] ++;
            n[k] ++;
            if(n[k] == 8)
            {
                if (writeBlockToDisk(blk_bu[k], bubase_s[k] + out_s[k], buf) != 0)    // 输出未满的缓冲区并释放
                {
                    perror("Writing Block Failed!\n");
                    return -1;
                }
                out_s[k] ++;
                n[k] = 0;
                if(!(blk_bu[k] = getNewBlockInBuffer(buf)))
                {
                    return -1;
                }
                blk_bu_int[k] = (int *)blk_bu[k];
            }
            blk_int += 2;
        }
        freeBlockInBuffer(blk, buf);    // 清空R的输入缓冲区
        blk = NULL;
        if(i < 31)
        {
            if ((blk = readBlockFromDisk(BASES + i + 1, buf)) == NULL)    // 下一块
            {
                perror("Reading Block Failed!\n");
                return -1;
            }
            blk_int = (int *)blk;
        }
    }
    for(i = 0; i < 7; i ++)
    {
        if(n[i])
        {
            if (writeBlockToDisk(blk_bu[i], bubase_s[i] + out_s[i], buf) != 0)    // 输出未满的缓冲区并释放
            {
                perror("Writing Block Failed!\n");
                return -1;
            }
            out_s[i] ++;
            n[i] = 0;
        }
    }
//    printf("R in bucket:");
//    for(i = 0; i < 7; i ++)
//    {
//        printf("\n>>>> %d:\n", i);
//        for(j = 0; j < out_r[i]; j ++)
//        {
//            if ((blk_buf = readBlockFromDisk(bubase_r[i] + j, buf)) == NULL)
//            {
//                perror("Reading Block Failed!\n");
//                return -1;
//            }
//            blk_buf_int = (int *)blk_buf;
//            for(k = 0; k < 8; k ++)
//            {
//                printf("(%d,%d),", blk_buf_int[0], blk_buf_int[1]);
//                blk_buf_int += 2;
//            }
//            freeBlockInBuffer(blk_buf, buf);    // 缓冲区
//            blk_buf = NULL;
//        }
//    }
//
//    printf("\nS in bucket:");
//    for(i = 0; i < 7; i ++)
//    {
//        printf("\n>>>> %d:\n", i);
//        for(j = 0; j < out_s[i]; j ++)
//        {
//            if ((blk_buf = readBlockFromDisk(bubase_s[i] + j, buf)) == NULL)
//            {
//                perror("Reading Block Failed!\n");
//                return -1;
//            }
//            blk_buf_int = (int *)blk_buf;
//            for(k = 0; k < 8; k ++)
//            {
//                printf("(%d,%d),", blk_buf_int[0], blk_buf_int[1]);
//                blk_buf_int += 2;
//            }
//            freeBlockInBuffer(blk_buf, buf);    // 缓冲区
//            blk_buf = NULL;
//        }
//    }
    /*一个bucket一个bucket来连接*/
    for(q = 0; q < 7; q ++)
    {
        for(i = 0;i < out_r[q]; i ++)
        {
            if ((blk = readBlockFromDisk(bubase_r[q] + i, buf)) == NULL)
            {
                perror("Reading Block R Failed!\n");
                return -1;
            }
            blk_int = (int *)blk;
            limi_r = tu_r >= 8? 8:tu_r;
            for(j = 0; j < limi_r; j ++)
            {
                printf("%d\n", blk_int[0]);
                tu_s = tuples_s[q];
                for(k = 0;k < out_s[q]; k ++)
                {
//                    printf("round start, k = %d\n", k);
//                    printf("tu_s = %d\n", tu_s);
//                    printf("q = %d, bubase_s[q] = %d, bubase_s[q] + k = %d", q,bubase_s[q],bubase_s[q] + k);
                    if ((blk_buf = readBlockFromDisk(bubase_s[q] + k, buf)) == NULL)
                    {
                        perror("Reading Block R Failed!\n");
                        return -1;
                    }
                    blk_buf_int = (int *)blk_buf;
                    limi_s = tu_s >= 8? 8:tu_s;
//                    printf("limi_s=%d\n", limi_s);
                    for(l = 0; l < limi_s; l ++)
                    {
//                        printf("r: %d,%d  s:%d,%d\n", i,j,k,l);
                        if(blk_out == NULL)
                        {
                            if(!(blk_out = getNewBlockInBuffer(buf)))
                            {
                                return -1;
                            }
                            blk_out_int = (int *)blk_out;
                        }
                        if(blk_int[0] == blk_buf_int[0])
                        {
                            blk_out_int[0] = blk_int[0];
                            blk_out_int[1] = blk_int[1];
                            blk_out_int[2] = blk_buf_int[1];
                            blk_out_int += 3;
                            (*count_tuple) ++;
                            m ++;
                            if(m == 5)
                            {
                                if (writeBlockToDisk(blk_out, BASETHREET + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
                                {
                                    perror("Writing Block Failed!\n");
                                    return -1;
                                }
                                (*count_out) ++;
                                m = 0;
                                blk_out = NULL;
                            }
                        }
                        blk_buf_int += 2;
                        tu_s --;
                    }
                    freeBlockInBuffer(blk_buf, buf);    // 清空S的输入缓冲区
                    blk_buf = NULL;
                    blk_buf_int = NULL;
                }
                blk_int += 2;
                tu_r --;
            }
            freeBlockInBuffer(blk, buf);    // 清空R的输入缓冲区
            blk = NULL;
            blk_int = NULL;
        }
    }
    return 0;
}

int Func4(Buffer *buf, int *count_out, int *count_tuple)
{
    unsigned char *blk_r = NULL, *blk_s = NULL, *blk = NULL, *blk_out = NULL;
    int i, j, h, l, k, n = 0, *blk_r_int = NULL, *blk_s_int = NULL, *blk_int = NULL, *blk_out_int = NULL;
    int base_r_so = 420, base_s_so = 430, out_r = 0, out_s = 0, add = 1, flag = 0;
    /*R.A 按块分组排序*/
    for(i = 0;i < 16; i ++)
    {
        if ((blk_r = readBlockFromDisk(BASER + i, buf)) == NULL)    // 下一块
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_r_int = (int *)blk_r;
        for(j = 0; j < 7; j ++)
        {
            if(blk_out == NULL)
            {
                if(!(blk_out = getNewBlockInBuffer(buf)))
                {
                    return -1;
                }
                blk_out_int = (int *)blk_out;
            }
            blk_out_int[0] = blk_r_int[0];
            blk_out_int += 1;
            blk_r_int += 2;
            n ++;
            if(n == 16)
            {
                Bubble_twoway((int *)blk_out);
                if (writeBlockToDisk(blk_out, base_r_so + out_r, buf) != 0)    // 输出未满的缓冲区并释放
                {
                    perror("Writing Block Failed!\n");
                    return -1;
                }
                out_r ++;
                n = 0;
                blk_out = NULL;
            }
        }
        freeBlockInBuffer(blk_r, buf);    // 清空输入缓冲区
        blk_r = NULL;
    }
    /*S.C 按块分组排序*/
    for(i = 0;i < 32; i ++)
    {
        if ((blk_s = readBlockFromDisk(BASES + i, buf)) == NULL)    // 下一块
        {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_s_int = (int *)blk_s;
        for(j = 0; j < 7; j ++)
        {
            if(blk_out == NULL)
            {
                if(!(blk_out = getNewBlockInBuffer(buf)))
                {
                    return -1;
                }
                blk_out_int = (int *)blk_out;
            }
            blk_out_int[0] = blk_s_int[0];
            blk_out_int += 1;
            blk_s_int += 2;
            n ++;
            if(n == 16)
            {
                Bubble_twoway((int *)blk_out);
                if (writeBlockToDisk(blk_out, base_s_so + out_s, buf) != 0)    // 输出未满的缓冲区并释放
                {
                    perror("Writing Block Failed!\n");
                    return -1;
                }
                out_s ++;
                n = 0;
                blk_out = NULL;
            }
        }
        freeBlockInBuffer(blk_s, buf);    // 清空输入缓冲区
        blk_s = NULL;
    }
    i = 0;
    j = 0;
    n = 0;
    while(i < out_r || j < out_s)
    {
        if(i < out_r)
        {
            if ((blk_r = readBlockFromDisk(base_r_so + i, buf)) == NULL)    // 下一块
            {
                perror("Reading Block Failed!\n");
                return -1;
            }
            blk_r_int = (int *)blk_r;
        }
        if(j < out_s)
        {
            if ((blk_s = readBlockFromDisk(base_s_so + j, buf)) == NULL)    // 下一块
            {
                perror("Reading Block Failed!\n");
                return -1;
            }
            blk_s_int = (int *)blk_s;
        }
        h = 0;
        l = 0;
        if(i >= out_r)
        {
            h = 16;
        }
        if(j >= out_s)
        {
            l = 16;
        }
        while(h < 16 || l < 16)
        {
            if(blk == NULL)
            {
                if(!(blk = getNewBlockInBuffer(buf)))
                {
                    return -1;
                }
                blk_int = (int *)blk;
            }
            flag = 0;
            if(h >= 16)
            {
                flag = 2;
            }
            if(l >= 16)
            {
                flag = 1;
            }
            if((flag == 1) || ((flag == 0) && (blk_r_int[h] <= blk_s_int[l])))
            {
                add = 1;
                if(n)
                {
                    for(k = 0; k < n; k ++)
                    {
                        if(blk_int[k] == blk_r_int[h])
                        {
                            add = 0;
                            break;
                        }
                    }
                }
                if(add)
                {
                    blk_int[n] = blk_r_int[h];
                    n ++;
                }
                h ++;
                while((h < 16) && (blk_r_int[h] == blk_r_int[h - 1]))
                {
                    h ++;
                }
            }
            else if((flag == 2) || ((flag == 0) && (blk_s_int[l] <= blk_r_int[h])))
            {
                add = 1;
                if(n)
                {
                    for(k = 0; k < n; k ++)
                    {
                        if(blk_int[k] == blk_s_int[l])
                        {
                            add = 0;
                            break;
                        }
                    }
                }
                if(add)
                {
                    blk_int[n] = blk_s_int[l];
                    n ++;
                }
                l ++;
                while((l < 16) && (blk_s_int[l] == blk_s_int[l - 1]))
                {
                    l ++;
                }
            }
        }
        if(blk_s)
        {
            freeBlockInBuffer(blk_s, buf);    // 清空输入缓冲区
            blk_s = NULL;
        }
        if(blk_r)
        {
            freeBlockInBuffer(blk_r, buf);    // 清空输入缓冲区
            blk_r = NULL;
        }
        i ++;
        j ++;
    }
//    for(i = 0; i < n; i++)
//    {
//        printf("%d\n", blk_int[i]);
//    }

    j = 0;
    for(i = 0; i < n; i ++)
    {
        if(blk_out == NULL)
        {
            if(!(blk_out = getNewBlockInBuffer(buf)))
            {
                return -1;
            }
            blk_out_int = (int *)blk_out;
        }
        blk_out_int[j] = blk_int[i];
        j ++;
        (*count_tuple) ++;
        if(j == 16)
        {
            if (writeBlockToDisk(blk_out, BASEFOUR + (*count_out), buf) != 0)    // 输出缓冲区并释放
            {
                perror("Writing Block Failed!\n");
                return -1;
            }
            blk_out = NULL;
            (*count_out) ++;
            j = 0;
        }
    }
    if(j)
    {
        if (writeBlockToDisk(blk_out, BASEFOUR + (*count_out), buf) != 0)    // 输出未满的缓冲区并释放
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        blk_out = NULL;
        (*count_out) ++;
        j = 0;
    }
    return 0;
}

void Bubble_twoway(int *buffer)
{
    int low = 0, high = 15, i, tmp;
//    printf("BEFORE SORT:\n");
//    for(i = 0; i < 16; i ++)
//    {
//        printf("%d\n", buffer[i]);
//    }
    while(low < high)
    {
        for(i = low; i < high; i++)
        {
            if(buffer[i] > buffer[i + 1])
            {
                tmp = buffer[i];
                buffer[i] = buffer[i + 1];
                buffer[i + 1] = tmp;
            }
        }
        high --;
        for(i = high; i > low; i--)
        {
            if(buffer[i] < buffer[i - 1])
            {
                tmp = buffer[i];
                buffer[i] = buffer[i - 1];
                buffer[i - 1] = tmp;
            }
        }
        low ++;
    }
//    printf("CHECK AFTER SORT:\n");
//    for(i = 0; i < 16; i ++)
//    {
//        printf("%d\n", buffer[i]);
//    }
}
