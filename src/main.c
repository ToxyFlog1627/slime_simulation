#define PI 3.14159265359
#define TWO_PI 6.28318530718

#define likely(x)  __builtin_expect((x), 1)
#define unlikely(x)  __builtin_expect((x), 0)
#define abs(a) (a < 0 ? -a : a)
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define red(c) (c & 0x000000ff)
#define green(c) ((c & 0x0000ff00) >> 8)
#define blue(c) ((c & 0x00ff0000) >> 16)
#define color(r, g, b) (0xff000000 | (b << 16) | (g << 8) | r)
#define interpolate(si, ei, sv, ev, xv) ((xv - sv) * (ei - si) / (ev - sv) + si)
#define blend_colors(c1, c2, k) color(round(interpolate(red(c1), red(c2), 0, 1, k)), round(interpolate(green(c1), green(c2), 0, 1, k)), round(interpolate(blue(c1), blue(c2), 0, 1, k)))

#define forEachSlime() for (Slime *slime = slimes;slime < memoryEnd;slime++)

extern float debug(float degree);
extern float sin(float degree);
extern float cos(float degree);
extern float random(void);
extern int round(float value);

typedef unsigned int uint;
typedef struct Slime { float x, y, dir; } Slime;

static uint bg, fg, *pixels;
static Slime *slimes, *memoryEnd;
static int width, height, slimesNumber, fadeRate;

int getSlimeSize() { return sizeof(Slime); }

void init(uint* memoryStart, int _width, int _height, int _slimesNumber, int _fadeRate, uint _bg, uint _fg) {
    width = _width; height = _height; slimesNumber = _slimesNumber; fadeRate = _fadeRate; bg = _bg; fg = _fg;

    pixels = memoryStart;
    slimes = pixels + width * height;
    memoryEnd = slimes + slimesNumber;

    int cx = width / 2, cy = height / 2;
    forEachSlime() *slime = (Slime) {cx, cy, random() * TWO_PI};
    for (int i = 0;i < width * height;i++) pixels[i] = bg;
}

void update() {
    for (int i = 0;i < width * height;i++) pixels[i] = color(max(red(bg), red(pixels[i]) - fadeRate), max(green(bg), green(pixels[i]) - fadeRate), max(blue(bg), blue(pixels[i]) - fadeRate));
    forEachSlime() {
        pixels[round(slime->y) * width + round(slime->x)] = fg;
        float nx = slime->x + cos(slime->dir);
        float ny = slime->y - sin(slime->dir);
        if (unlikely(nx < 0 || nx > width || ny < 0 || ny > height)) {
            // TODO: bounce off
        }
        slime->x = nx;
        slime->y = ny;
    }
}