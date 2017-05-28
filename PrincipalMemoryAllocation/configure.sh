#! /bin/bash
gcc ComponenteDeMemoria.c ComponenteDeMemoria.h main.c ComponenteDeRequisicao.c ComponenteDeDesalocacao.c AlocacaoFF.c -o teste
./teste
