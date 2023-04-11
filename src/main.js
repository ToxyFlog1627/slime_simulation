const interval = 5;
const slimes = 1;
const fadeRate = 1;

const width = window.innerWidth;
const height = window.innerHeight;

const canvas = document.querySelector("#c");
canvas.width = width;
canvas.height = height;
const ctxt = canvas.getContext("2d");

const render = w => {
	const exports = w.instance.exports;
	exports.memory.grow(Math.ceil((width * height * 4 + slimes * exports.getSlimeSize()) / 65535));

	const {init, update, memory} = exports;
	const memoryStart = exports.__heap_end.value;

	init(memoryStart, width, height, slimes, fadeRate, 0xff181818, 0xffffffff);

	setInterval(() => {
		update();
		ctxt.putImageData(new ImageData(new Uint8ClampedArray(memory.buffer, memoryStart, width * height * 4), width), 0, 0);
	}, interval);
};

WebAssembly.instantiateStreaming(fetch("main.wasm"), {env: {random: Math.random, cos: Math.cos, sin: Math.sin, round: Math.round}}).then(render);
