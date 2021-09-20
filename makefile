all:
	g++ src/*.cpp src/*.c -o build/x64/WINx64.exe -O2 -I dependencies/x64/include -L dependencies/x64/lib -lglfw3 -lgdi32 -lopengl32