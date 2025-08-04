#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// BMP file headers (simplified)
typedef struct {
    uint16_t type;      // "BM"
    uint32_t size;      // File size
    uint32_t reserved;  // Reserved bytes
    uint32_t offset;    // Where pixel data starts
} __attribute__((packed)) BMPHeader;

typedef struct {
    uint32_t size;          // Header size
    int32_t width;          // Image width
    int32_t height;         // Image height  
    uint16_t planes;        // Color planes
    uint16_t bits;          // Bits per pixel
    uint32_t compression;   // Compression type
    uint32_t imagesize;     // Image size
    int32_t xresolution;    // X resolution
    int32_t yresolution;    // Y resolution
    uint32_t ncolours;      // Number of colors
    uint32_t importantcolours; // Important colors
} __attribute__((packed)) BMPInfoHeader;

// Simple pixel structure  
typedef struct {
    uint8_t blue;   // BMP stores as BGR, not RGB!
    uint8_t green;
    uint8_t red;
} Pixel;

// Our image structure
typedef struct {
    BMPHeader header;
    BMPInfoHeader info;
    int width;
    int height;
    Pixel* pixels;      // Pointer to pixel array
    int padding;        // Padding bytes per row
} Image;

// Function to read BMP file
Image* load_bmp(char* filename) {
    printf("Loading %s...\n", filename);
    
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Can't open file!\n");
        return NULL;
    }
    
    // Allocate memory for image structure
    Image* img = malloc(sizeof(Image));
    if (!img) {
        printf("Error: Can't allocate memory!\n");
        fclose(file);
        return NULL;
    }
    
    // Read BMP headers
    fread(&img->header, sizeof(BMPHeader), 1, file);
    fread(&img->info, sizeof(BMPInfoHeader), 1, file);
    
    // Check if it's a valid BMP
    if (img->header.type != 0x4D42) {  // "BM" in hex
        printf("Error: Not a BMP file!\n");
        free(img);
        fclose(file);
        return NULL;
    }
    
    // Only handle 24-bit BMPs (no compression)
    if (img->info.bits != 24 || img->info.compression != 0) {
        printf("Error: Only 24-bit uncompressed BMPs supported!\n");
        free(img);
        fclose(file);
        return NULL;
    }
    
    // Get image dimensions
    img->width = img->info.width;
    img->height = img->info.height;
    
    // Calculate padding (BMP rows must be multiple of 4 bytes)
    img->padding = (4 - (img->width * 3) % 4) % 4;
    
    printf("Image: %dx%d pixels, %d bytes padding per row\n", 
           img->width, img->height, img->padding);
    
    // Allocate memory for pixels
    int total_pixels = img->width * img->height;
    img->pixels = malloc(total_pixels * sizeof(Pixel));
    if (!img->pixels) {
        printf("Error: Can't allocate pixel memory!\n");
        free(img);
        fclose(file);
        return NULL;
    }
    
    // Go to pixel data location
    fseek(file, img->header.offset, SEEK_SET);
    
    // Read pixels row by row (BMP stores bottom-to-top!)
    for (int row = img->height - 1; row >= 0; row--) {
        // Read one row of pixels
        for (int col = 0; col < img->width; col++) {
            int pos = row * img->width + col;  // Position in 1D array
            fread(&img->pixels[pos], sizeof(Pixel), 1, file);
        }
        // Skip padding bytes
        fseek(file, img->padding, SEEK_CUR);
    }
    
    fclose(file);
    printf("Image loaded successfully!\n");
    return img;
}

// Function to save BMP file
void save_bmp(char* filename, Image* img) {
    printf("Saving %s...\n", filename);
    
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Can't create output file!\n");
        return;
    }
    
    // Write headers
    fwrite(&img->header, sizeof(BMPHeader), 1, file);
    fwrite(&img->info, sizeof(BMPInfoHeader), 1, file);
    
    // Write pixels row by row (bottom-to-top)
    uint8_t padding_bytes[3] = {0, 0, 0};
    
    for (int row = img->height - 1; row >= 0; row--) {
        // Write one row of pixels
        for (int col = 0; col < img->width; col++) {
            int pos = row * img->width + col;
            fwrite(&img->pixels[pos], sizeof(Pixel), 1, file);
        }
        // Write padding bytes
        fwrite(padding_bytes, 1, img->padding, file);
    }
    
    fclose(file);
    printf("Image saved successfully!\n");
}

// Convert to grayscale
void make_grayscale(Image* img) {
    printf("Converting to grayscale...\n");
    
    int total_pixels = img->width * img->height;
    
    // Process each pixel
    for (int i = 0; i < total_pixels; i++) {
        Pixel* p = &img->pixels[i];  // Pointer to current pixel
        
        // Calculate grayscale using luminance formula
        uint8_t gray = (uint8_t)(0.3 * p->red + 0.59 * p->green + 0.11 * p->blue);
        
        // Set all color channels to gray value
        p->red = gray;
        p->green = gray;
        p->blue = gray;
    }
}

// Invert all colors
void invert_colors(Image* img) {
    printf("Inverting colors...\n");
    
    int total_pixels = img->width * img->height;
    
    // Process each pixel
    for (int i = 0; i < total_pixels; i++) {
        Pixel* p = &img->pixels[i];  // Pointer to current pixel
        
        // Invert each color channel
        p->red = 255 - p->red;
        p->green = 255 - p->green;
        p->blue = 255 - p->blue;
    }
}

// Mirror horizontally
void mirror_horizontal(Image* img) {
    printf("Mirroring horizontally...\n");
    
    // Process each row
    for (int row = 0; row < img->height; row++) {
        // Swap pixels from left and right
        for (int col = 0; col < img->width / 2; col++) {
            // Calculate positions in 1D array
            int left_pos = row * img->width + col;
            int right_pos = row * img->width + (img->width - 1 - col);
            
            // Swap pixels using pointers
            Pixel temp = img->pixels[left_pos];
            img->pixels[left_pos] = img->pixels[right_pos];
            img->pixels[right_pos] = temp;
        }
    }
}

// Free allocated memory
void free_image(Image* img) {
    if (img) {
        if (img->pixels) {
            free(img->pixels);  // Free pixel array first
        }
        free(img);  // Then free image structure
    }
    printf("Memory freed.\n");
}

int main(int argc, char* argv[]) {
    printf("Simple BMP Image Processor\n");
    printf("==========================\n");
    
    // Check command line arguments
    if (argc != 4) {
        printf("Usage: %s <input.bmp> <output.bmp> <operation>\n", argv[0]);
        printf("Operations: grayscale, invert, mirror\n");
        printf("Example: %s photo.bmp result.bmp grayscale\n", argv[0]);
        return 1;
    }
    
    char* input_file = argv[1];
    char* output_file = argv[2];
    char* operation = argv[3];
    
    // Load the image
    Image* my_image = load_bmp(input_file);
    if (!my_image) {
        printf("Failed to load image!\n");
        return 1;
    }
    
    // Perform the requested operation
    if (strcmp(operation, "grayscale") == 0) {
        make_grayscale(my_image);
    }
    else if (strcmp(operation, "invert") == 0) {
        invert_colors(my_image);
    }
    else if (strcmp(operation, "mirror") == 0) {
        mirror_horizontal(my_image);
    }
    else {
        printf("Unknown operation: %s\n", operation);
        printf("Use: grayscale, invert, or mirror\n");
        free_image(my_image);
        return 1;
    }
    
    // Save the result
    save_bmp(output_file, my_image);
    
    // Clean up memory
    free_image(my_image);
    
    printf("Processing complete!\n");
    return 0;
}