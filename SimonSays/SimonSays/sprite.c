#include "sprite.h"

void sprite_setup(struct Sprite *s, SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey)
{
	if (columns >= MAX_FRAME_COL || rows >= MAX_FRAME_ROW) {
		printf("ERROR: createSprite_____Overflow\n");
	}
	SDL_Surface *s_loadedSurface = IMG_Load(filepath);
	if (s_loadedSurface == NULL) {
		printf("ERROR: Unable to load texture %s. SDL_Image Error: %s\n", filepath, IMG_GetError());
	}
	else {
		SDL_SetColorKey(s_loadedSurface, SDL_TRUE, SDL_MapRGB(s_loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
		s->texture = SDL_CreateTextureFromSurface(renderer, s_loadedSurface);
		if (s->texture == NULL) {
			printf("Error: Unable to load texture. SDL_Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(s_loadedSurface);
	}
	// Setup
	s->col = columns;
	s->row = rows;
	int texture_w;
	int texture_h;
	SDL_QueryTexture(s->texture, NULL, NULL, &texture_w, &texture_h);
	s->frame_w = texture_w / s->col;
	s->frame_h = texture_h / s->row;
	for (int r = 0; r < rows; r++) {		// Default number of frames initiated per row
		s->frames_on_row[r] = columns;
	}


	/*
	struct Sprite {
		SDL_Texture* texture;				// Texture
		SDL_Rect clip[MAX_FRAME_COL];		// Frame clip
		int frames_on_row[MAX_FRAME_ROW];	// Declared frames on row
		int frame_w;						// Frame width
		int frame_h;						// Frame height
		int col;							// Columns on spritesheet
		int row;							// Rows on spritesheet
	};
	#define MAX_FRAME_COL				10
	#define MAX_FRAME_ROW				10
	#define MAX_FRAME_TOT				100
	*/
	printf("Sprite created. Col: %d = %d Row: %d = %d. Frame w/h = %d/%d\n", s->col, columns, s->row, rows, s->frame_w, s->frame_h);

	for (int c = 0; c < MAX_FRAME_COL; c++) {
		for (int r = 0; r < MAX_FRAME_ROW; r++) {
			if (c < columns && r < rows) {
				s->clip[c + r*MAX_FRAME_COL].x = s->frame_w*c;
				s->clip[c + r*MAX_FRAME_COL].y = s->frame_h*r;
				s->clip[c + r*MAX_FRAME_COL].w = s->frame_w;
				s->clip[c + r*MAX_FRAME_COL].h = s->frame_h;
			}
			else {
				s->clip[c + r*MAX_FRAME_COL].x = 0;
				s->clip[c + r*MAX_FRAME_COL].y = 0;
				s->clip[c + r*MAX_FRAME_COL].w = 0;
				s->clip[c + r*MAX_FRAME_COL].h = 0;
			}
		}
	}
	printf("Sprite created. Col: %d = %d Row: %d = %d. Frame w/h = %d/%d\n", s->col, columns, s->row, rows, s->frame_w, s->frame_h);


	if (s->texture == NULL) {
		printf("ERROR: Failed to load sprite texture.\n");
	}
	else {
		printf("Sprite created. Col: %d = %d Row: %d = %d. Frame w/h = %d/%d\n", s->col, columns, s->row, rows, s->frame_w, s->frame_h);
	}
}

SDL_Rect sprite_getClipRect(struct Sprite *s, int col, int row)
{
	SDL_Rect r = { 0, 0, 0, 0 };
	if (row >= s->row || col >= s->col) {
		printf("Error: sprite_getClipRect: IndexOutOfBounds! %d %d\n", col, row);
		return r;
	}
	return s->clip[col + row*MAX_FRAME_COL];
}

void sprite_RenderCopy(struct Sprite *s, SDL_Renderer* renderer, int col, int row, SDL_Rect dsrect)
{
	// Renders to screen
	SDL_Rect srect = sprite_getClipRect(s, col, row);
	SDL_RenderCopy(renderer, s->texture, &srect, &dsrect);
}

SDL_Texture* sprite_getTexture(struct Sprite *s)
{
	return s->texture;
}

//=====================//
// ~~ GAMMALT NEDAN ~~ // 
//=====================//



/*
#include "sprite.h"

struct Sprite_type {
	int frameWidth;
	int frameHeight;
	int col;
	int row;
	int* numOfFrames;
	int textureWidth;
	int textureHeight;			
	SDL_Texture* texture;			// Texture 
	SDL_Rect** clip;				// Frame[][]
};

Sprite *createSprite(SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey)
{
	Sprite *s = malloc(sizeof(Sprite));
	SDL_Surface *s_loadedSurface = IMG_Load(filepath);
	if (s_loadedSurface == NULL) {
		printf("ERROR: Unable to load texture %s. SDL_Image Error: %s\n", filepath, IMG_GetError());
	}
	else {
		SDL_SetColorKey(s_loadedSurface, SDL_TRUE, SDL_MapRGB(s_loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
		s->texture = SDL_CreateTextureFromSurface(renderer, s_loadedSurface);
		if (s->texture == NULL) {
			printf("Error: Unable to load texture. SDL_Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(s_loadedSurface);
	}
	s->col = columns;
	s->row = rows;
	SDL_QueryTexture(s->texture, NULL, NULL, &(s->textureWidth), &(s->textureHeight));
	s->frameWidth = s->textureWidth / columns;
	s->frameHeight = s->textureHeight / rows;
	s->clip = malloc(columns * sizeof(SDL_Rect));
	s->numOfFrames = malloc(rows * sizeof(int));

	for (int r = 0; r < rows; r++) {		// Default number of frames initiated per row
		s->numOfFrames[r] = columns;
	}

	for (int c = 0; c < columns; c++) {
		s->clip[c] = malloc(rows * sizeof(SDL_Rect));
		for (int r = 0; r < rows; r++) {
			s->clip[c][r].x = s->frameWidth*c;
			s->clip[c][r].y = s->frameHeight*r;
			s->clip[c][r].w = s->frameWidth;
			s->clip[c][r].h = s->frameHeight;
		}
	}
	if (s->texture == NULL) {
		printf("ERROR: Failed to load sprite texture. createSprite()\n");
	}
	return s;
}

void destroySprite(Sprite *ptr_sprite)
{
	if (ptr_sprite != NULL) {
		printf("Error: destroySprite - Null pointer reference.\n");
	}
	if (ptr_sprite->texture != NULL) {
		SDL_DestroyTexture(ptr_sprite->texture);
	}
	for (int c = 0; c < ptr_sprite->col; c++) {
		free(ptr_sprite->clip[c]);
	}
	free(ptr_sprite->clip);
	free(ptr_sprite->numOfFrames);
	free(ptr_sprite);
}

void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: IndexOutOfBounds (row): %d.\n", row);
		return;
	}
	if (value >= ptr_sprite->col || value < 0) {
		printf("ERROR: IndexOutOfBounds (value): %d.\n", value);
		return;
	}
	ptr_sprite->numOfFrames[row] = value;
}

int sprite_getRowFrameCount(Sprite *ptr_sprite, int row)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: IndexOutOfBounds (row): %d.\n", row);
		return 0;
	}
	return ptr_sprite->numOfFrames[row];
}

SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: sprite_getClipRect, IndexOutOfBounds (row): %d.\n", row);
	}
	if (col >= ptr_sprite->col || col < 0) {
		printf("ERROR: sprite_getClipRect, IndexOutOfBounds (col): %d.\n", col);
	}
	return ptr_sprite->clip[col][row];
}

void sprite_RenderCopy(SDL_Renderer* renderer, Sprite *ptr_sprite, int col, int row, SDL_Rect dsrect)
{
	// Renders to screen
	SDL_Rect srect = sprite_getClipRect(ptr_sprite, col, row);
	SDL_RenderCopy(renderer, ptr_sprite->texture, &srect, &dsrect);
}


SDL_Texture *sprite_getTexture(Sprite *ptr_sprite)
{
	if (ptr_sprite->texture == NULL) {
		printf("ERROR: sprite_getTexture, No media loaded.\n");
	}
	return ptr_sprite->texture;
}


int sprite_getRows(Sprite  *ptr_sprite)
{
	return ptr_sprite->row;
}

int sprite_getColumns(Sprite  *ptr_sprite)
{
	return ptr_sprite->col;
}

int sprite_getFrameWidth(Sprite *ptr_sprite)
{
	return ptr_sprite->frameWidth;
}

int sprite_getFrameHeight(Sprite *ptr_sprite)
{
	return ptr_sprite->frameHeight;
}

int sprite_getTextureWidth(Sprite *ptr_sprite)
{
	return ptr_sprite->textureWidth;
}

int sprite_getTextureHeight(Sprite *ptr_sprite)
{
	return ptr_sprite->textureHeight;
}

void sprite_print(Sprite *ptr_sprite)
{
	printf("-----------------------------------------\n");
	printf("- Sprite --------------------------------\n");
	printf("-----------------------------------------\n");
	printf("frameWidth\t%d\n", ptr_sprite->frameWidth);
	printf("frameHeight\t%d\n", ptr_sprite->frameHeight);
	printf("columns\t\t%d\n", ptr_sprite->col);
	printf("rows\t\t%d\n", ptr_sprite->col);
	printf("textureWidth:\t%d\n", ptr_sprite->textureWidth);
	printf("textureHeight:\t%d\n", ptr_sprite->textureHeight);
	printf("-----------------------------------------\n");
}

*/