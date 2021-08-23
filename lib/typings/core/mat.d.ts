export class Mat {
	constructor();

	release(): void;
	asBuffer(): Buffer;
	asJpg(): Buffer;
	asPng(): Buffer;
	width(): number;
	height(): number;
}
