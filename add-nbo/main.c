// main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t my_ntol(uint32_t a) {
        uint32_t a1 = (a & 0x000000ff) << 24;
        uint32_t a2 = (a & 0x0000ff00) << 8;
        uint32_t a3 = (a & 0x00ff0000) >> 8;
        uint32_t a4 = (a & 0xff000000) >> 24;
        a = a1 | a2 | a3 | a4;

        return a;
}


uint32_t readFile(char* filename)
{
	FILE* file = fopen(filename, "rb");

	uint32_t value = 0;
	uint32_t nvalue = 0;

	fread(&value, sizeof(uint32_t), 1, file);
	fclose(file);

	nvalue = my_ntol(value);
	return nvalue;
}


unsigned int hextodec(uint32_t value) {
	unsigned int decvalue = 0;
	unsigned int base = 1;

	while (value > 0) {
		unsigned int digit = value & 0xF;
		decvalue += digit * base;
		base *= 16;
		value >>= 4;
	}

	return decvalue;
}


uint32_t sum(uint32_t a, uint32_t b)
{
	uint32_t result = 0;
	uint16_t a1 = (a & 0xff00) >> 8;
	uint16_t a2 = (a & 0x00ff) << 8 ;
	uint16_t a3 = (a1 | a2);
	uint16_t b1 = (b & 0xff00) >> 8;
	uint16_t b2 = (b & 0x00ff) << 8 ;
	uint16_t b3 = (b1 | b2);

	return a3 | b3;


}


uint16_t my_ntohs(uint16_t a) {
        uint16_t a1 = (a & 0xff00) >> 8;        //3400 -> 0034
        printf("a1 = 0x%x\n", a1);
        uint16_t a2 = (a & 0x00ff) << 8 ;       //0012 -> 1200
        printf("a2 = 0x%x\n", a2);
        uint16_t a3 = (a1 | a2);                //0034 | 1200
        printf("a3 = 0x%x\n", a3);
        return a3;
}


int main(int argc, char* argv[])
{
	if (argc < 3) {
		printf("사용법: %s [파일1] [파일2]\n", argv[0]);
		return 1;
    	}

	uint32_t hex1, hex2, hex3;
	unsigned int dec1, dec2, dec3;

	char* filename1 = argv[1];
	char* filename2 = argv[2];

	hex1 = readFile(filename1);
	hex2 = readFile(filename2);
	dec1 = hextodec(hex1);
	dec2 = hextodec(hex2);

	printf("%d(0x%X) + %d(0x%X) = %d(0x%X)\n", dec1, hex1, dec2, hex2, dec1+dec2, hex1+hex2);

	return 0;
}
