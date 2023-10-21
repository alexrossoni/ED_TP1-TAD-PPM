#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int rows;
    int cols;
    char type[3]; // Tipos de imagem PPM ("P2" para tons de cinza e "P3" para RGB)
    unsigned char **pixels; // Matriz para os valores dos pixels
} Image;

Image* create(int rows, int cols, char type[]); // Cria uma nova imagem
Image* load_from_ppm(const char* filename); // Carrega uma imagem de um arquivo .ppm
void write_to_ppm(Image* image, const char* filename); // Escreve uma imagem para um arquivo .ppm
void rgb_to_gray(Image* image_rgb, Image* image_gray); // Converte uma imagem RGB (Tipo "P3") para Tons de cinza (Tipo "P2")

void free_image(Image* image); // Libera a memória alocada de uma imagem
Image* load_image(); // Carrega uma imagem a partir de um caminho de entrada
Image* create_grayscale_image(Image* image_rgb); // Cria uma imagem em tons de cinza
void save_image(Image* image); // Salva uma imagem em um arquivo PPM

#endif
