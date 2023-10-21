#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
    Image* current_image = NULL;

    while (1) {
        int choice;
        printf("\nMenu:\n");
        printf("1. Carregar imagem\n");
        printf("2. Converter para niveis de cinza\n");
        printf("3. Gravar imagem\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (current_image != NULL) {
                    free_image(current_image);
                }
                current_image = load_image();
                break;
            case 2:
                if (current_image == NULL) {
                    printf("Nenhuma imagem carregada.\n");
                } else {
                    Image* grayscale_image = create_grayscale_image(current_image);
                    free_image(current_image);
                    current_image = grayscale_image;
                }
                break;
            case 3:
                if (current_image == NULL) {
                    printf("Nenhuma imagem carregada.\n");
                } else {
                    save_image(current_image);
                }
                break;
            case 4:
                if (current_image != NULL) {
                    free_image(current_image);
                }
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    }

    return 0;
}
