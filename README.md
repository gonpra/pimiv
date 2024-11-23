# PIM IV

Projeto integrado multidisciplinar IV 

## Requisitos

- CMAKE 3.25
- GNU MAKE 4.3
- GCC 12.2
- GTK 4
- Libxlsxwriter

## Docker

É possível iniciar o projeto através de um container docker

É necessário permitir o container para acessar o display externo com
```bash
$ xhost +local:docker
```
Após isso, no diretório raiz, faça o build do projeto
```bash
$ docker build . -t pimiv
```

Rode o projeto com
```bash
$ docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix pimiv
```

## Compilar

Após a instalação dos requisitos, é necessario executar os seguintes passos para a compilação do projeto.

No diretório raiz do projeto:

```bash
$ mkdir build/
```

```bash
$ cd build/
```

```bash
$ cmake ..
```

```bash
$ make
```

## Executar
Nessa etapa verá o binário compilado, apenas execute com:

```bash
$ ./PIM
```