#include <png.h>
#include <err.h>
#include "utils.h"
SDL_Surface* load_image(const char* path)
{
    SDL_Surface* tmp = IMG_Load(path);
    if(tmp == NULL)
        errx(EXIT_FAILURE, "load_image(IMG_Load): %s", SDL_GetError());

    SDL_Surface* result = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888,
            0);
    if(result == NULL)
        errx(EXIT_FAILURE, "load_image(ConvertSurfaceFormat): %s",
                SDL_GetError());

    SDL_FreeSurface(tmp);
    return result;
}

void save_image(SDL_Surface* surface, const char* path){
    if(SDL_SaveBMP(surface, path))
        errx(EXIT_FAILURE, "save_image(SaveBMP): %s", SDL_GetError());
}

void bmp_to_png(char* input,char* output) 
{
    // Input BMP file
    FILE *bmp_file = fopen(input, "rb");
    if (!bmp_file) {
        errx(1,"Failed to open input.bmp");
    }
      unsigned char header[54];
    fread(header, 1, 54, bmp_file);

    // Extract image information from the header
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bits_per_pixel = *(unsigned short*)&header[28];

    // Read the BMP data
    int row_size = (bits_per_pixel * width + 31) / 32 * 4;
    unsigned char* bmp_data = (unsigned char*)malloc(row_size * height);
    fseek(bmp_file, *(int*)&header[10], SEEK_SET);
    fread(bmp_data, 1, row_size * height, bmp_file);
    fclose(bmp_file);

    // Create the PNG image
    FILE* png_file = fopen(output, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, png_file);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    // Convert the BMP data to PNG data
    unsigned char* png_data = (unsigned char*)malloc(width * 3);
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            png_data[x * 3 + 0] = bmp_data[y * row_size + x * 3 + 2];
            png_data[x * 3 + 1] = bmp_data[y * row_size + x * 3 + 1];
            png_data[x * 3 + 2] = bmp_data[y * row_size + x * 3 + 0];
        }
        png_write_row(png_ptr, png_data);
    }

    // Clean up
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(png_file);
    free(bmp_data);
    free(png_data); 

}
