import {Mat} from "./core/mat.d";

export function imencode(ext: string, mat: Mat): Buffer;
export function imdecode(buf: Buffer): Mat;
export function imread(path: string): Mat;
export function imwrite(path: string, mat: Mat): void;
