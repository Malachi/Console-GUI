gui: video.o audio.o
	gcc src/main.c -o build/gui `pkg-config --cflags --libs sdl` \
	-L./lib/ -lvideo -lSDL_image -laudio -lwidgets -lSDL_ttf
	
video.o: main_screen.o second_screen.o media_center_screen.o widgets.o
	gcc -c src/video.c -o build/video.o `pkg-config --cflags sdl`
	ar cr lib/libvideo.a build/video.o build/main_screen.o \
	build/second_screen.o build/media_center_screen.o
	
audio.o:
	gcc -c src/audio.c -o build/audio.o `pkg-config --cflags sdl`
	ar cr lib/libaudio.a build/audio.o	

widgets.o: button.o
	ar cr lib/libwidgets.a build/button.o

main_screen.o:
	gcc -I./src -I./src/widgets -c src/screen_handlers/main_screen.c -o build/main_screen.o \
	`pkg-config --cflags sdl`
	
second_screen.o:
	gcc -c src/screen_handlers/second_screen.c -o build/second_screen.o \
	`pkg-config --cflags sdl`

media_center_screen.o:
	gcc -I ./src -c src/screen_handlers/media_center_screen.c -o build/media_center_screen.o \
	`pkg-config --cflags sdl`
	
button.o:
	gcc -c src/widgets/button.c -o build/button.o `pkg-config --cflags \
	sdl`

clean:
	rm -f build/*
