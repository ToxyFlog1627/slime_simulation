#define MEMORY 131072;

typedef unsigned int uint;
typedef struct Slime {
    int x, y;
    int dir;
} Slime;

static uint *pixelMemory, *slimeMemory;
static int width, height, slimes;

int getSlimeSize() { return sizeof(Slime); }

inline uint color(int r, int g, int b) { return 0xff000000 | ((b % 256) << 16) | ((g % 256) << 8) | (r % 256); }

void init(int _width, int _height, int _slimes) {
    width = _width; height = _height; slimes = _slimes;
    pixelMemory = (uint*) MEMORY;
    slimeMemory = pixelMemory + width * height * 4;
}

void update() {
    for (int y = 0;y < height;y++) {
        for (int x = 0;x < width;x++) {
            pixelMemory[y * width + x] = color(x / (float) width * 255, y / (float) height * 255, 0);
        }
    }
}