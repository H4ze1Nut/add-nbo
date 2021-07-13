#define BUFSIZ 2
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main (int argc, char **argv)
{
    FILE *file1 = fopen(argv[1], "rb");
    FILE *file2 = fopen(argv[2], "rb");;
    int num1, num2;
    uint8_t buf1[BUFSIZ] = {0, };
    uint8_t buf2[BUFSIZ] = {0, };

    // file check
    if (file1 == NULL || file2 == NULL) {
        printf("File open error,,\n");
        return 0;
    }

    // bit to buffer
    int i = 0;
    while ((num1 = fgetc(file1)) != EOF){
        if (num1 != 0) {
            buf1[i] = num1;
            i++;
        }
    }

    int k = 0;
    while ((num2 = fgetc(file2)) != EOF){
        if (num2 != 0) {
            buf2[k] = num2;
            k++;
        }
    }

    // network to host
    uint16_t* p = reinterpret_cast<uint16_t*>(buf1);
    uint16_t n = ntohs(*p);
    uint16_t* q = reinterpret_cast<uint16_t*>(buf2);
    uint16_t m = ntohs(*q);

    // print
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n, n, m, m, n+m, n+m);

    // close file
    fclose(file1);
    fclose(file2);

    return 0;
}
