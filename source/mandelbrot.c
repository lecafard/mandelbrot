// Ram Kaniyur, quadrupleslap, z5122495
// Mark, UNSW
// 16 April, 2016
// A HTTP server for rendering the Mandelbrot fractal.

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment (lib, "Ws2_32.lib")
#else
    #include <netinet/in.h>
    #include <unistd.h>
#endif

#include "mandelbrot.h"
#include "pixelColor.h"

#define MAX_ITERATIONS 256
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512
#define PIXEL_SIZE 3
#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE 40
#define IMAGE_SIZE (IMAGE_HEIGHT * IMAGE_WIDTH * PIXEL_SIZE)
#define FILE_SIZE (BMP_HEADER_SIZE + IMAGE_SIZE)

#define SERVER_PORT 8080
#define REQ_SIZE 1000
#define PATH_SIZE 100

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;

void startServer(int port);
int makeSocket(int port);
int waitForConnection(int sock);
void closeSocket(int sock);

void mandelBitmap(char *image, double x, double y, int zoom);
void bitmapHeader(char *image);

int main(int argc, char *argv[]) {
    startServer(SERVER_PORT);
    return EXIT_SUCCESS;
}

void startServer(int port) {
    // Make sure types have the required size.
    assert(sizeof(bits8)  == 1);
    assert(sizeof(bits16) == 2);
    assert(sizeof(bits32) == 4);

    int parsedValues;

    #ifdef _WIN32
        WSADATA wsaData;
        WSAStartup(0x0202, &wsaData);
    #endif

    int sock = makeSocket(port);

    char req[REQ_SIZE + 1];
    req[REQ_SIZE] = 0;

    while (1) {
        int conn = waitForConnection(sock);

        recv(conn, req, REQ_SIZE, 0);

        // Cut the string off to one line.
        char *endOfLine = strchr(req, '\n');
        if (endOfLine != NULL) {
            *endOfLine = '\0';
        }

        // Find the path.
        char path[PATH_SIZE + 1];
        parsedValues = sscanf(req, "GET %s HTTP/1.1", path);

        if (parsedValues == 1) {
            if (strcmp(path, "/") == 0) {
                // Homepage
                char *msg =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "<!DOCTYPE html>\n"
                    "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>\n";
                send(conn, msg, strlen(msg), 0);
            } else {
                double x, y;
                int zoom;

                parsedValues = sscanf(
                    path, "/tile_x%lf_y%lf_z%d.bmp",
                    &x, &y, &zoom);

                if (parsedValues == 3) {
                    char *msg =
                        "HTTP/1.0 200 OK\r\n"
                        "Content-Type: image/bmp\r\n"
                        "\r\n";
                    send(conn, msg, strlen(msg), 0);

                    char image[FILE_SIZE];
                    mandelBitmap(image, x, y, zoom);
                    send(conn, image, FILE_SIZE, 0);
                } else {
                    // HTTP Error 404.
                }
            }
        } else {
            // HTTP Error 400.
        }

        closeSocket(conn);
    }

    // Closing the socket is unnecessary, because the OS will
    // immediately recover it thanks to SO_REUSEADDR.
}

int makeSocket(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int allowReuse = 1;
    setsockopt(
        sock,
        SOL_SOCKET,
        SO_REUSEADDR,
        &allowReuse,
        sizeof(allowReuse));

    struct sockaddr_in addr;
    memset((char *)&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bind(sock,
        (struct sockaddr *) &addr,
        sizeof(addr));

    return sock;
}

int waitForConnection(int sock) {
    listen(sock, SOMAXCONN);

    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    int conn = accept(
        sock,
        (struct sockaddr *) &clientAddr,
        &clientLen);

    return conn;
}

void closeSocket(int sock) {
    #ifdef _WIN32
        closesocket(sock);
    #else
        close(sock);
    #endif
}

void mandelBitmap(char *image, double x, double y, int zoom) {
    double pixelDistance = pow(2, -zoom);
    double bottom = y - pixelDistance * (IMAGE_HEIGHT / 2);
    double left = x - pixelDistance * (IMAGE_WIDTH / 2);

    bitmapHeader(image);
    int offset = BMP_HEADER_SIZE;

    int row = 0;
    while (row < IMAGE_HEIGHT) {
        int col = 0;
        while (col < IMAGE_WIDTH) {
            int steps = escapeSteps(
                left + pixelDistance * col,
                bottom + pixelDistance * row);

            image[offset] = stepsToBlue(steps);
            image[offset + 1] = stepsToGreen(steps);
            image[offset + 2] = stepsToRed(steps);

            offset += 3;
            col += 1;
        }

        row += 1;
    }
}

void bitmapHeader(char *image) {
    // This function is equivalent to the one in chessboard.c,
    // and unfortunately doesn't work on big-endian architectures,
    // because we haven't learnt about bit-shifting yet.

    // BMP Signature
    image[0] = 0x42;
    image[1] = 0x4D;
    // File Size
    *(bits32*)(image + 2) = FILE_SIZE;
    // Reserved
    *(bits32*)(image + 6) = 0;
    // File Offset to Pixel Array
    *(bits32*)(image + 10) = BMP_HEADER_SIZE;
    // DIB Header Size
    *(bits32*)(image + 14) = DIB_HEADER_SIZE;
    // Image Width
    *(bits32*)(image + 18) = IMAGE_WIDTH;
    // Image Height
    *(bits32*)(image + 22) = IMAGE_HEIGHT;
    // Planes
    *(bits16*)(image + 26) = 1;
    // Bits per Pixel
    *(bits16*)(image + 28) = PIXEL_SIZE * 8;
    // Compression
    *(bits32*)(image + 30) = 0;
    // Image Size
    *(bits32*)(image + 34) = IMAGE_SIZE;
    // X Pixels Per Meter
    *(bits32*)(image + 38) = 0xB13;
    // Y Pixels Per Meter
    *(bits32*)(image + 42) = 0xB13;
    // Color Table Color Count
    *(bits32*)(image + 46) = 0;
    // Important Color Count
    *(bits32*)(image + 50) = 0;
}

int escapeSteps(double inX, double inY) {
    double x = 0.0;
    double y = 0.0;

    int i = 1;
    while (i < MAX_ITERATIONS) {
        double nextX = x*x - y*y + inX;
        double nextY = 2 * x*y + inY;

        x = nextX;
        y = nextY;

        if (x*x + y*y > 4) {
            break;
        }

        i += 1;
    }

    return i;
}

