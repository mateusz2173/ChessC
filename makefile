APPNAME=SzachyC.exe
SRCS=$(wildcard src/*.c) $(wildcard src/*/*.c)

CC=gcc
CFLAGS=-o $(APPNAME) -I include -Wall -Og -std=c11
ALLEGRO=`pkg-config --cflags --libs --static allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`

main:
	$(CC) $(CFLAGS) $(SRCS) $(ALLEGRO)

run:
	./$(APPNAME)
