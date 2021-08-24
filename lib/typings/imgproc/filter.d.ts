import {Mat} from "../core/mat.d";

type MorphProps = {
	shape: number;
	width: number;
	height: number;
};

export function dilate(mat: Mat, props: MorphProps): Mat;
export function erode(mat: Mat, props: MorphProps): Mat;
