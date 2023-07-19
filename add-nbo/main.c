// main.cpp
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

void printValue(unsigned char* buffer, long int size) {
	size_t idx = 0;

	// 16진수를 10진수로 변환하여 출력
        unsigned int val1_d = 0;
        for (size_t i = idx; i < size; ++i) {
                val1_d = val1_d * 256 + buffer[i];
        }
        printf("%d(0x", val1_d);

	// 앞에 있는 0을 찾기
	while (idx < size && buffer[idx] == 0) {
		idx++;
	}

	// 0을 제외한 나머지 데이터 출력
	for (size_t i = idx; i < size; ++i) {
		printf("%02X", buffer[i]);
	}
	printf(")\n");
}


int main(int argc, char* argv[])
{
	if (argc < 3) {
		printf("사용법: %s [파일1] [파일2]\n", argv[0]);
		return 1;
    	}

	char* filename1 = argv[1];
	char* filename2 = argv[2];

	uint32_t val1 = readFile(filename1);
	uint32_t val2 = readFile(filename2);

	printf("0x%08X, 0x%08X\n", val1, val2);

	return 0;
}
