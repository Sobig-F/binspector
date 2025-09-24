#include <stdio.h>
#include <getopt.h>

#define FLAGS "hvf:"

#define PROGRAM_NAME "binspector"

#define HELP_MESSAGE printf("Usage: %s [OPTIONS] <filename>\n\
    A simple binary file inspector.\n\
    \nOptions:\n\
    -h, --help    Show this help message\n\
    -v, --version Show version information\n", PROGRAM_NAME)

int main(int argc, char *argv[]) {

    int parse = 0;

    char *filename = NULL;

    while ((parse = getopt(argc, argv, FLAGS)) != -1) {
        switch (parse)
        {
        case 'h':
            HELP_MESSAGE;
            break;
        case 'f':
            filename = optarg;
            break;
        default:
            break;
        }
    }

    FILE *file = fopen(filename, "rb");

    unsigned char line_hex[16];
    int count = 1;
    unsigned int offset = 0x0;

    while (1) {
        count = fread(line_hex, 1, 16, file);
        if (!count) {
            break;
        }
        printf("offset:0x%08x | ", offset);
        for (int i = 0; i < count; ++i) {
            printf(" %02x", line_hex[i]);
        }
        for (int i = count; i < 16; ++i) {
            printf("   ");
        }
        printf("  |");
        for (int i = 0; i < count; ++i) {
            if (line_hex[i] >= 0x20 && line_hex[i] <= 0x7E) {
                printf("%c", line_hex[i]);
            } else {
                printf(".");
            }
        }
        for (int i = count; i < 16; ++i) {
            printf(" ");
        }
        printf("|\n");
        offset += 0x10;
    }
}