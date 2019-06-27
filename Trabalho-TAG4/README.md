# Trabalho-TAG-4

Estudantes: Lucas Verissimo Botelho,Lucas Mendonça.

Matriculas: 170109071,170149668.

Turma: A

Segue no arquivo Trab4.cpp o segundo trabalho de grafos.

Para compilar apenas use: g++ -std=c++11 -o trab4 trab4.cpp

Para exercutar use: ./trab4 e siga o Menu

Nesse trabalho foi implementado uma versão do algoritmo de Dsatur com randomização da solução de conflitos de saturação,
então ele tenta varias versões de randomização da solução desses conflitos ate a solução do sudoku com o limite sendo 50 
tentativas.

Foram implementadas a criação de um sudoku aleatorio resolvivel e o input do arquivo Sudoku.txt no formato onde os numeros sao
inseridos da ordem esquerda a direita descendo as linhas da matriz com os numeros separados por virgula como essse exemplo:

8,0,0,1,5,0,6,0,0,
0,0,0,3,0,0,0,4,1,
5,0,0,0,0,0,7,0,0,
0,0,0,0,0,9,0,6,2,
0,0,0,0,3,0,0,0,0,
1,4,0,8,0,0,2,0,0,
0,0,8,0,0,0,0,0,9,
2,9,0,0,0,1,0,0,0,
0,0,5,0,9,7,0,0,6

Caso não seja possivel olhar o passo a passo da solução foi criado um arquivo 'log.txt' com o log inteiro da execução do programa;

    

