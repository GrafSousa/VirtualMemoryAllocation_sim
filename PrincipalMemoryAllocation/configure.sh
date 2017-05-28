#! /bin/bash
rm ArqGrav.txt
gcc ComponenteDeMemoria.c ComponenteDeMemoria.h main.c ComponenteDeRequisicao.c ComponenteDeDesalocacao.c AlocacaoFF.c ComponenteDeEstatistica.c -o teste
clear
./teste
