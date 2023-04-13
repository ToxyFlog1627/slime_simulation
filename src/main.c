#define PI 3.14159265359
#define TWO_PI 6.28318530718

#define likely(x)  __builtin_expect((x), 1)
#define unlikely(x)  __builtin_expect((x), 0)
#define abs(a) (a < 0 ? -a : a)
#define red(c) (c & 0x000000ff)
#define green(c) ((c & 0x0000ff00) >> 8)
#define blue(c) ((c & 0x00ff0000) >> 16)
#define color(r, g, b) (0xff000000 | (b << 16) | (g << 8) | r)
#define interpolate(si, ei, sv, ev, xv) ((xv - sv) * (ei - si) / (ev - sv) + si)
#define isInBounds(x, y) x > 0 && x < width && y > 0 && y < height
#define forEachSlime() for (Slime *slime = slimes;slime < memoryEnd;slime++)

extern float sin(float degree);
extern float cos(float degree);
extern float random(void);
extern int round(float value);
extern float sqrt(float value);
extern float arccos(float value);

typedef unsigned int uint;
typedef struct Slime { float x, y, dir; } Slime;

static uint *pixels;
static Slime *slimes, *memoryEnd;
static int width, height;

static const uint bg = 0xff101010, fg = 0xffffffff;
static const int SLIMES = 15000, FADE_RATE = 1, SENSING_DISTANCE = 20, SENSING_SIZE = 1;
static const float SENSING_DEGREE = PI / 3, TURN_DEGREE = PI / 30;

int getSlimesSize() { return SLIMES * sizeof(Slime); }

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

void init(uint* memoryStart, int _width, int _height) {
    width = _width; height = _height;

    pixels = memoryStart;
    slimes = (Slime*) (pixels + width * height);
    memoryEnd = slimes + SLIMES;

    int cx = width / 2, cy = height / 2, spawningRadius = min(cx, cy) / 2;
    forEachSlime() {
        float r = spawningRadius * sqrt(random());
        float theta = random() * 2 * PI;
        *slime = (Slime) {cx + r * cos(theta), cy - r * sin(theta), random() * TWO_PI};
    }
    for (int i = 0;i < width * height;i++) pixels[i] = bg;
}

float sense(Slime *slime, float dir) {
    float sensingDir = slime->dir + dir;
	int sensorCentreX = slime->x + SENSING_DISTANCE * cos(sensingDir);
	int sensorCentreY = slime->y - SENSING_DISTANCE * sin(sensingDir);

	float sum = 0;
	for (int offsetX = -SENSING_SIZE; offsetX <= SENSING_SIZE; offsetX ++) {
		for (int offsetY = -SENSING_SIZE; offsetY <= SENSING_SIZE; offsetY ++) {
			int sampleX = min(width - 1, max(0, sensorCentreX + offsetX));
			int sampleY = min(height - 1, max(0, sensorCentreY + offsetY));
			sum += red(pixels[sampleY * width + sampleX]);
		}
	}

	return sum;
}

void update() {
    for (int i = 0;i < width * height;i++) pixels[i] = color(max(red(bg), red(pixels[i]) - FADE_RATE), max(green(bg), green(pixels[i]) - FADE_RATE), max(blue(bg), blue(pixels[i]) - FADE_RATE));
    
    forEachSlime() {
        pixels[round(slime->y) * width + round(slime->x)] = fg;

        float nx = slime->x + cos(slime->dir);
        float ny = slime->y - sin(slime->dir);

        if (unlikely(nx < 0 || nx > width || ny < 0 || ny > height)) {
            nx = min(width - 1, max(0, nx));
            ny = min(height - 1, max(0, ny));
            slime->dir = random() * TWO_PI;
            continue;
        }

        uint l = sense(slime, SENSING_DEGREE), m = sense(slime, 0), r = sense(slime, -SENSING_DEGREE);
        if (l > m && l > r) slime->dir += SENSING_DEGREE;
        else if (r > m && r > l) slime->dir -= SENSING_DEGREE;

        slime->dir += random() * TURN_DEGREE - TURN_DEGREE / 2;
        slime->x = nx;
        slime->y = ny;
    }
}