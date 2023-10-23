#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

/*
* Cria uma nova imagem com as dimensões especificadas e o tipo dado.
*
* @param rows O número de linhas da imagem.
* @param cols O número de colunas da imagem.
* @param type O tipo da imagem (por exemplo, "P2" para tons de cinza ou "P3" para RGB).
* @return Um ponteiro para a imagem criada.
*/
Image* create(int rows, int cols, char type[]) {
    Image* image = (Image*)malloc(sizeof(Image));
    if (image == NULL) {
        fprintf(stderr, "Erro ao alocar memoria.\n");
        exit(1);
    }

    image->rows = rows;
    image->cols = cols;
    strncpy(image->type, type, 3);

    // Aloca memória para os valores dos pixels
    image->pixels = (unsigned char**)malloc(rows * sizeof(unsigned char*));
    for (int i = 0; i < rows; i++) {
        image->pixels[i] = (unsigned char*)malloc(cols * sizeof(unsigned char));
    }

    return image;
}

/*
* Carrega uma imagem a partir de um arquivo PPM.
*
* @param filename O nome do arquivo ou caminho a ser carregado.
* @return Um ponteiro para a imagem carregada ou NULL em caso de erro.
*/
Image* load_from_ppm(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para leitura: %s\n", filename);
        return NULL;
    }

    Image* image = (Image*)malloc(sizeof(Image));
    if (image == NULL) {
        fprintf(stderr, "Erro ao alocar memoria.\n");
        fclose(file);
        exit(1);
    }

    char header[3];
    int max_value;

    // Leitura do cabeçalho PPM
    if (fscanf(file, "%2s\n", header) != 1 || header[0] != 'P') {
        fprintf(stderr, "Cabecalho PPM invalido.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    if (header[1] == '2') {
        strcpy(image->type, "P2");
    } else if (header[1] == '3') {
        strcpy(image->type, "P3");
    } else {
        fprintf(stderr, "Tipo PPM invalido.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    if (fscanf(file, "%d %d\n%d\n", &image->cols, &image->rows, &max_value) != 3) {
        fprintf(stderr, "Formato PPM invalido.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    // Aloca memória para os valores dos pixels
    image->pixels = (unsigned char**)malloc(image->rows * sizeof(unsigned char*));
    for (int i = 0; i < image->rows; i++) {
        image->pixels[i] = (unsigned char*)malloc(image->cols * 3 * sizeof(unsigned char)); // 3 bytes for RGB
    }

    if (strcmp(image->type, "P3") == 0) {
        // Leitura de dados da imagem RGB (Tipo "P3")
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols; j++) {
                int r, g, b;
                if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                    fprintf(stderr, "Dados de cores invalidos.\n");
                    fclose(file);
                    free_image(image);
                    return NULL;
                }
                // Guarda os valores RGB na matriz de pixels
                image->pixels[i][j * 3] = (unsigned char)r;
                image->pixels[i][j * 3 + 1] = (unsigned char)g;
                image->pixels[i][j * 3 + 2] = (unsigned char)b;
            }
        }
    } else if (strcmp(image->type, "P2") == 0) {
        // Leitura de dados da imagem em Tons de cinza (Tipo "P2")
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols; j++) {
                if (fscanf(file, "%hhu", (unsigned char*)&image->pixels[i][j]) != 1) {
                    fprintf(stderr, "Dados de tons de cinza invalidos.\n");
                    fclose(file);
                    free_image(image);
                    return NULL;
                }
            }
        }
    }

    fclose(file);
    return image;
}

/*
* Escreve os dados de uma imagem em um arquivo PPM.
*
* @param image A imagem a ser salva.
* @param filename O nome do arquivo ou caminho onde os dados da imagem serão escritos.
*/
void write_to_ppm(Image* image, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita: %s\n", filename);
        return;
    }

    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->cols, image->rows);
    fprintf(file, "255\n");

    if (strcmp(image->type, "P3") == 0) {
        // Escrita de dados da imagem RGB (Tipo "P3")
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols; j++) {
                fprintf(file, "%u %u %u ", (unsigned int)image->pixels[i][j * 3], (unsigned int)image->pixels[i][j * 3 + 1], (unsigned int)image->pixels[i][j * 3 + 2]);
            }
            fprintf(file, "\n");
        }
    } else if (strcmp(image->type, "P2") == 0) {
        // Escrita de dados da imagem em Tons de cinza (Tipo "P2")
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols; j++) {
                fprintf(file, "%hhu ", (unsigned int)image->pixels[i][j]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

/*
* Converte uma imagem colorida RGB (Tipo "P3") em uma imagem em Tons de cinza (Tipo "P2").
*
* @param image_rgb A imagem RGB de entrada.
* @param image_gray A imagem em tons de cinza de saída.
*/
void rgb_to_gray(Image* image_rgb, Image* image_gray) {
    if (image_rgb == NULL || image_gray == NULL) {
        fprintf(stderr, "Imagens de entrada invalidas.\n");
        return;
    }

    if (strcmp(image_rgb->type, "P3") != 0 || strcmp(image_gray->type, "P2") != 0) {
        fprintf(stderr, "Tipos de imagens invalidas para conversao.\n");
        return;
    }

    if (image_rgb->rows != image_gray->rows || image_rgb->cols != image_gray->cols) {
        fprintf(stderr, "As dimensoes das imagens sao diferentes.\n");
        return;
    }

    for (int i = 0; i < image_rgb->rows; i++) {
        for (int j = 0; j < image_rgb->cols; j++) {
            int r, g, b;
            r = image_rgb->pixels[i][j * 3];      // Canal Vermelho
            g = image_rgb->pixels[i][j * 3 + 1];  // Canal Verde
            b = image_rgb->pixels[i][j * 3 + 2];  // Canal Azul
            unsigned char gray_value = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            image_gray->pixels[i][j] = gray_value;
        }
    }
}

/*
* Libera a memória alocada para uma imagem.
*
* @param image A imagem a ser liberada.
*/
void free_image(Image* image) {
    if (image != NULL) {
        for (int i = 0; i < image->rows; i++) {
            free(image->pixels[i]);
        }
        free(image->pixels);
        free(image);
    }
}

/*
* Carrega uma imagem a partir de um caminho de entrada especificado pelo usuário.
*
* @return Um ponteiro para a imagem carregada ou NULL em caso de erro.
*/
Image* load_image() {
    char filename[256];
    printf("Digite o caminho do arquivo PPM para carregar: ");
    scanf("%255s", filename);

    Image* image = load_from_ppm(filename);

    if (image == NULL) {
        printf("Falha ao carregar a imagem.\n");
    } else {
        printf("Imagem carregada com sucesso.\n");
    }

    return image;
}

/*
* Cria uma imagem em tons de cinza a partir de uma imagem RGB.
*
* @param image_rgb A imagem RGB de entrada.
* @return Um ponteiro para a nova imagem em tons de cinza.
*/
Image* create_grayscale_image(Image* image_rgb) {
    if (image_rgb == NULL) {
        printf("Nenhuma imagem para converter para tons de cinza.\n");
        return NULL;
    }

    if (strcmp(image_rgb->type, "P2") == 0) {
        printf("Imagem inserida ja esta em tons de cinza.\n");
        return NULL;
    }

    Image* image_gray = create(image_rgb->rows, image_rgb->cols, "P2");

    if (image_gray == NULL) {
        printf("Falha ao criar a imagem em tons de cinza.\n");
        return NULL;
    }

    rgb_to_gray(image_rgb, image_gray);

    printf("Imagem convertida para tons de cinza.\n");

    return image_gray;
}

/*
* Salva uma imagem em um arquivo PPM no caminho especificado pelo usuário.
*
* @param image A imagem a ser salva.
*/
void save_image(Image* image) {
    if (image == NULL) {
        printf("Nenhuma imagem para salvar.\n");
        return;
    }

    char filename[256];
    printf("Digite o caminho do arquivo PPM para salvar: ");
    scanf("%255s", filename);

    write_to_ppm(image, filename);

    printf("Imagem salva com sucesso.\n");
}
