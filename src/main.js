const interval = 100;
const slimes = 1000;
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
	init(width, height, slimes);

	// setInterval(() => {
	update();
	ctxt.putImageData(new ImageData(new Uint8ClampedArray(memory.buffer, exports.__heap_end.value, width * height * 4), width), 0, 0);
	// }, interval);
};

WebAssembly.instantiateStreaming(fetch("main.wasm"), {env: {debug: console.log}}).then(render);
