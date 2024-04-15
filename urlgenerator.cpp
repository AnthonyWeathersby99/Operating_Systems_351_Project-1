#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_SIZE 200

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <latitude> <longitude>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    float latitude = atof(argv[1]);
    float longitude = atof(argv[2]);

    char finalURLBuff[MAX_BUF_SIZE];
    snprintf(finalURLBuff, MAX_BUF_SIZE, "https://api.open-meteo.com/v1/forecast?latitude=%f&longitude=%f&current_weather=True", latitude, longitude);

    printf("The final URL is: %s\n", finalURLBuff);

    return 0;
}
