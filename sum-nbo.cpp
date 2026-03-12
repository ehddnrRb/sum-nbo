#include <cstdio>
#include <cstdint>
#include <arpa/inet.h>

void print_num(uint32_t n, int is_last) {
    uint32_t h = ntohl(n);
    printf("%u(0x%x)", h, h);
    if (!is_last) {
	    printf(" + ");
	}
}

int main(int argc, char* argv[]) {

    uint32_t total = 0;

    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }

        uint32_t n;
        size_t r = fread(&n, sizeof(uint32_t), 1, fp);
        fclose(fp);

        if (r != 1) {
            printf("failed to read 4 bytes from %s\n", argv[i]);
            return 1;
        }

        print_num(n, i == argc - 1);
        total += ntohl(n);
    }

    printf(" = %u(0x%x)\n", total, total);
    return 0;
}
