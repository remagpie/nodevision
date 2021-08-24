import {Mat} from "../core/mat.d";

export const MORPH_RECT: number;
export const MORPH_CROSS: number;
export const MORPH_ELLIPSE: number;

export function dilate(mat: Mat, shape: number, width: number, height: number): Mat;
export function erode(mat: Mat, shape: number, width: number, height: number): Mat;
