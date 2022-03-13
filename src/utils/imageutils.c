#include "imageutils.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

Image4 makeImage4(uint32_t width, uint32_t height){
	Pixel4 *img = malloc(width * height * sizeof(Pixel4)/* * sizeof(uint8_t)*/);
	Image4 i = {width, height, img};
	return i;
}
Image4 makeImage4WithData(uint32_t width, uint32_t height, Pixel4 pixels[]){
	size_t dimension = width * height * sizeof(Pixel4)/* * sizeof(uint8_t)*/;
	Pixel4 *img = malloc(dimension);
	memcpy(img, pixels, dimension);
	Image4 i = {width, height, img};
	return i;
}
Image3 makeImage3(uint32_t width, uint32_t height){
	Pixel3 *img = malloc(width * height * sizeof(Pixel3)/* * sizeof(uint8_t)*/);
	Image3 i = {width, height, img};
	return i;
}
Image3 makeImage3WithData(uint32_t width, uint32_t height, Pixel3 pixels[]){
	size_t dimension = width * height * sizeof(Pixel3)/* * sizeof(uint8_t)*/;
	Pixel3 *img = malloc(dimension);
	memcpy(img, pixels, dimension);
	Image3 i = {width, height, img};
	return i;
}

AlphaMap getAlphaMap(Image4 img){
	uint32_t dimension = img.width * img.height;
	AlphaMap map = malloc(dimension * sizeof(uint8_t));
	for(uint32_t i = 0; i < dimension; i++)
		map[i] = img.pixels[i].w;
	return map;
}
Image3 image4to3(Image4 img){
	Image3 ret = makeImage3(img.width, img.height);
	uint32_t dimension = img.width * img.height;
	for(uint32_t i = 0; i < dimension; i++){
		ret.pixels[i].x = img.pixels[i].x;
		ret.pixels[i].y = img.pixels[i].y;
		ret.pixels[i].z = img.pixels[i].z;
	}
	return ret;
}
Image4 image3to4FixedAlpha(Image3 img, double alpha){
	Image4 ret = makeImage4(img.width, img.height);
	uint32_t dimension = img.width * img.height;
	for(uint32_t i = 0; i < dimension; i++){
		ret.pixels[i].x = img.pixels[i].x;
		ret.pixels[i].y = img.pixels[i].y;
		ret.pixels[i].z = img.pixels[i].z;
		ret.pixels[i].w = alpha;
	}
	return ret;
}
Image4 image3to4AlphaMap(Image3 img, AlphaMap alphaMap){
	Image4 ret = makeImage4(img.width, img.height);
	uint32_t dimension = img.width * img.height;
	for(uint32_t i = 0; i < dimension; i++){
		ret.pixels[i].x = img.pixels[i].x;
		ret.pixels[i].y = img.pixels[i].y;
		ret.pixels[i].z = img.pixels[i].z;
		ret.pixels[i].w = alphaMap[i];
	}
	return ret;
}

void destroyImage4(Image4 img){
	free(img.pixels);
	img.pixels = NULL;
}
void destroyImage3(Image3 img){
	free(img.pixels);
	img.pixels = NULL;
}