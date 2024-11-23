FROM ubuntu:latest

RUN apt-get update

RUN apt-get install -y \
    libgtk-4-dev \
    gcc \
    libxlsxwriter-dev \
    cmake \
    build-essential \
    x11-aps \
    xauth


WORKDIR /pim

COPY src/ ./src/
COPY CMakeLists.txt .

WORKDIR /pim/build

RUN cmake .. && make

ENTRYPOINT ["./PIM"]