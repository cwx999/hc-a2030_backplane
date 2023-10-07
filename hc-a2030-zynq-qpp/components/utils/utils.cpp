#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

const unsigned char crc16_hi_table[256] = 
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

const unsigned char crc16_lo_table[256] = 
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 
    0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 
    0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 
    0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 
    0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 
    0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 
    0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 
    0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 
    0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 
    0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 
    0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 
    0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 
    0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 
    0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 
    0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 
    0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 
    0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 
    0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

// big endian output
unsigned short crc16_compute(unsigned char *buf, unsigned short bytes)
{
    unsigned char crc16_hi = 0xff;
    unsigned char crc16_lo = 0xff;
    unsigned short index = 0;

    while (bytes--) {
        index = crc16_lo ^ *buf++;
        crc16_lo = crc16_hi ^ crc16_hi_table[index];
        crc16_hi = crc16_lo_table[index];
    }
    return ((crc16_hi << 8) | crc16_lo);
}

// big endian output
unsigned short u8buf_to_u16(unsigned char *src)
{
    return ((src[0] << 8) | (src[1]));
}


void u16_to_u8buf(unsigned char *dest, unsigned short src)
{
    dest[0] = (src >>  8) & 0xff;
    dest[1] = (src) & 0xff;
}

unsigned int u8buf_to_u32(unsigned char *src)
{
    return ((src[0] << 24) | 
            (src[1] << 16) | 
            (src[2] <<  8) | 
            (src[3]));
}

void u32_to_u8buf(unsigned char *dest, unsigned int src)
{
    dest[0] = (src >> 24) & 0xff;
    dest[1] = (src >> 16) & 0xff;
    dest[2] = (src >>  8) & 0xff;
    dest[3] = (src) & 0xff;
}

int is_little_endian(void)
{
    union {
        unsigned char byte[4];
        unsigned int value;
    } num;
    num.value = 0x12345678;
    return ((0x12 == num.byte[0]) ? (0) : (1));
}

int is_big_endian(void)
{
    union {
        unsigned char byte[4];
        unsigned int value;
    } num;
    num.value = 0x12345678;
    return ((0x12 == num.byte[0]) ? (1) : (0));
}

unsigned short mhtons(unsigned short value)
{
    return ((is_little_endian()) ? (endian_swap16(value)) : (value));
}

unsigned short mntohs(unsigned short value)
{
    return ((is_little_endian()) ? (endian_swap16(value)) : (value));
}

unsigned int mhtonl(unsigned int value)
{
    return ((is_little_endian()) ? (endian_swap32(value)) : (value));
}

unsigned int mntohl(unsigned int value)
{
    return ((is_little_endian()) ? (endian_swap32(value)) : (value));
}

unsigned int mstrtoul(const char *str)
{
    unsigned int result = 0;
    if ((NULL == strstr(str, "0x")) && (NULL == strstr(str, "0X"))) {
        result = strtoul(str, NULL, 10);
    }
    if ((NULL != strstr(str, "0x")) || (NULL != strstr(str, "0X"))) {
        result = strtoul(str, NULL, 16);
    }
    return result;
}


unsigned short checksum16(unsigned char *buf, unsigned short size)
{
    unsigned int i = 0;
    unsigned short sum = 0;
    for (i = 0; i < size; i++) {
        sum += buf[i];
    }
    return sum;
}

unsigned int checksum32(unsigned char *buf, unsigned int size)
{
    unsigned int i = 0;
    unsigned int sum = 0;
    for (i = 0; i < size; i++) {
        sum += buf[i];
    }
    return sum;
}



int is_printable(unsigned char c)
{
    if ((0x20 <= c) && (c <= 0x7e)) {
        return 1;
    }
    return 0;
}

void show_hexdump(void *buf, unsigned int offset, int count)
{
    int index = 0;
    int x = 0, y = 0, line = 0;
    char str[18] = {0};
    char *ptr = (char *)buf;

    if (NULL == buf) {
        return ;
    }
    line = count / 16;
    if ((count % 16) > 0) {
        line++;
    }
    printf("  offset:  0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F    \n");
    for (y = 0; y < line; y++) {
        printf("%08x: ", offset + y * 16);
        for (x = 0; x < 16; x++) {
            if (index < count) {
                str[x] = (is_printable(ptr[index])) ? (ptr[index]) : ('.');
                printf("%02x ", ptr[index] & 0xFF);
            }
            else {
                str[x] = ' ';
                printf("   ");
            }
            if (7 == x) {
                printf(" ");
            }
            index++;
        }
        printf("[%s]\n", str);
    }
}




