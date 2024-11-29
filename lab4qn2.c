#include <stdio.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512

// Function to read a PGM image in text format.
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Read PGM header
    char format[3];
    int max_val;
    fscanf(file, "%s%d%d%d", format, &width, &height, &max_val);

    // Read pixel data
    for (int i = 0; i < width * height; i++) {
        int pixel;
        fscanf(file, "%d", &pixel);
        pixels[i] = (unsigned char) pixel;
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in text format.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Write PGM header
    fprintf(file, "P2\n%d %d\n255\n", width, height);

    // Write pixel data
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d\n", pixels[i]);
    }

    fclose(file);
    return 0;
}

// Function to write a PGM image in binary format.
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Write PGM header
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    // Write pixel data
    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file);
    return 0;
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        coverPixels[i] = (coverPixels[i] & 0xF0) | (secretPixels[i] >> 4);
    }
}

// Function to extract the secret image using 4-LSB steganography algorithm.
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        outputPixels[i] = (coverPixels[i] & 0x0F) << 4;
    }
}

int main() {
    const char *cover_image = "D:\\baboon.pgm";
    const char *secret_image = "D:\\farm.pgm";
    const char *stego_image = "D:\\stego_image_bin.pgm";
    const char *extracted_secret = "D:\\extracted_secret.pgm";
    
    unsigned char *coverPixels, *secretPixels, *outputPixels;
    int coverWidth = WIDTH, coverHeight = HEIGHT, secretWidth = WIDTH, secretHeight = HEIGHT;

    // Allocate memory for cover image pixels
    coverPixels = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char));
    if (coverPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for coverPixels\n");
        return 1;
    }

    // Read the cover image file (text PGM)
    if (readPGMText(cover_image, coverPixels, coverWidth, coverHeight) != 0) {
        fprintf(stderr, "Failed to read cover image\n");
        free(coverPixels);
        return 1;
    }

    // Allocate memory for secret image pixels
    secretPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (secretPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for secretPixels\n");
        free(coverPixels);
        return 1;
    }

    // Read the secret image file (text PGM)
    if (readPGMText(secret_image, secretPixels, secretWidth, secretHeight) != 0) {
        fprintf(stderr, "Failed to read secret image\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Check if the dimensions of both images match
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        fprintf(stderr, "Image dimensions do not match\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Embed the secret image into the cover image
    embedLSB(coverPixels, secretPixels, coverWidth, coverHeight);

    // Save the stego image in binary format
    if (writePGMBinary(stego_image, coverPixels, coverWidth, coverHeight) != 0) {
        fprintf(stderr, "Failed to write stego image\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Allocate memory for output (extracted) image pixels
    outputPixels = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char));
    if (outputPixels == NULL) {
        fprintf(stderr, "Memory allocation failed for outputPixels\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Extract the secret image from the stego image
    extractLSB(coverPixels, outputPixels, coverWidth, coverHeight);

    // Save the extracted secret image in text format
    if (writePGMText(extracted_secret, outputPixels, secretWidth, secretHeight) != 0) {
        fprintf(stderr, "Failed to write extracted secret image\n");
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        return 1;
    }

    // Free allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;
}
