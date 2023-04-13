const FPS = 120;
const interval = Math.round(1000 / FPS);

const width = window.innerWidth;
const height = window.innerHeight;

const canvas = document.querySelector("#c");
canvas.width = width;
canvas.height = height;
const ctxt = canvas.getContext("2d");

const render = w => {
	const exports = w.instance.exports;
	exports.memory.grow(Math.ceil((width * height * 4 + exports.getSlimesSize()) / 65535));

	const {init, update, memory} = exports;
	const memoryStart = exports.__heap_end.value;

	init(memoryStart, width, height);

	setInterval(() => {
		update();
		ctxt.putImageData(new ImageData(new Uint8ClampedArray(memory.buffer, memoryStart, width * height * 4), width), 0, 0);
	}, interval);
};

const {acos, sqrt, random, cos, sin, round} = Math;
WebAssembly.instantiateStreaming(fetch("main.wasm"), {env: {arccos: acos, sqrt, random, cos, sin, round}}).then(render);
