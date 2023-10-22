# Trabalho de Estrutura de Dados: Manipulação de Imagens PPM

Este repositório contém um programa em C que implementa um Tipo Abstrato de Dados (TAD) para a leitura e gravação de imagens no formato PPM, além de realizar a conversão de imagens coloridas em imagens em níveis de cinza. O programa é destinado à disciplina de Estrutura de Dados e foi desenvolvido no ambiente Ubuntu 22.04 com GCC v11 (É **fortemente recomendável** a execução do programa em um ambiente de mesma configuração).

---

## ▶️ Executando o Programa

Para executar o programa, siga os passos abaixo:

### Pré-requisitos

1. Certifique-se de que você tenha o GCC v11+ instalado no seu sistema. Você pode verificar se o GCC está instalado executando o seguinte comando no terminal:

```bash
gcc --version
```

  - Se o GCC não estiver instalado, você pode instalá-lo com o seguinte comando:
  ```bash
  sudo apt install gcc
  ```

2. Certifique-se de que o utilitário Make esteja instalado:

```bash
make --version
```

  - Se o Make estiver instalado, você verá informações sobre a versão. Caso contrário, você pode instalá-lo usando o seguinte comando:
  ```bash
  sudo apt-get install make
  ```

### Compilando o Programa

1. Clone este repositório para o seu sistema:
```bash
git clone https://github.com/alexrossoni/ED_TP1-TAD-PPM.git
```

2. Acesse o diretório do projeto:
```bash
cd ED_TP1-TAD-PPM
```

3. Compile o programa usando o Makefile:
```bash
make
```

### Executar o Programa

Após a compilação, você pode executar o programa da seguinte maneira:
```bash
./tad_imagens_ppm
```

---

## 💡 Principais Decisões de Implementação

#### Estrutura de Dados
O projeto utiliza uma estrutura de dados Image, definida em image.h, para representar imagens PPM. Esta estrutura contém os seguintes campos:

  - int rows: O número de linhas da imagem.
  - int cols: O número de colunas da imagem.
  - char type[3]: Uma string de tamanho 3 que armazena o tipo da imagem PPM ("P2" para tons de cinza e "P3" para RGB).
  - unsigned char **pixels: Uma matriz que armazena os valores dos pixels da imagem.

#### Alocação de Memória
Para a alocação de memória, o projeto utiliza funções malloc para criar uma estrutura Image e alocar memória para a matriz de pixels. É importante notar que o código trata possíveis erros de alocação de memória, exibindo mensagens de erro e encerrando o programa em caso de falha na alocação.

#### Gerenciamento de Memória
O projeto inclui uma função free_image para liberar a memória alocada para as imagens. Essa função é chamada para evitar vazamento de memória quando as imagens não são mais necessárias.

#### Leitura e Escrita de Imagens
A leitura e escrita de imagens PPM são implementadas nas funções load_from_ppm e write_to_ppm no arquivo image.c. O projeto suporta tanto imagens RGB (Tipo "P3") quanto imagens em tons de cinza (Tipo "P2"). A leitura de cores RGB é feita de acordo com os valores RGB fornecidos no arquivo PPM, enquanto a leitura de imagens em tons de cinza lê valores de tons de cinza diretamente. É importante notar que as funções load_from_ppm e write_to_ppm são utilizadas por outras funções sendo elas: load_image e save_image respectivamente, onde recebem seus devidos parâmetros para o carregamento e armazenamento de imagens.

#### Conversão para Tons de Cinza
A conversão de imagens coloridas em tons de cinza é implementada na função rgb_to_gray no arquivo image.c, a função rgb_to_gray é utilizada pela função create_grayscale_image onde recebe seus devidos parâmetros. O projeto utiliza uma fórmula para calcular o valor de cinza com base nos valores dos canais de cor vermelho, verde e azul. A fórmula utilizada é: gray = 0.299 * r + 0.587 * g + 0.114 * b.

#### Interface de Usuário
O arquivo main.c implementa um menu de texto simples para interagir com o usuário. O menu oferece as seguintes opções:

1. Carregar imagem
2. Converter para níveis de cinza
3. Gravar imagem
4. Sair

O programa permite que o usuário realize essas ações em imagens PPM carregadas.

---

## 👨🏽‍💻 Autor

Alex Rossoni Junior
