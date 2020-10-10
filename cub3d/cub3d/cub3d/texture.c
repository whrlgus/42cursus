#include "texture.h"

int** initTexture() {
	int **texture = (int**)malloc(8*sizeof(int*));
	for(int i=0;i<8;++i)texture[i] = (int*)malloc(texWidth * texHeight*sizeof(int));
	
	for(int x = 0; x < texWidth; x++)for(int y = 0; y < texHeight; y++)
	{
		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		//int xcolor = x * 256 / texWidth;
		int ycolor = y * 256 / texHeight;
		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}
	
	return texture;
}
