//De bibliotek som anv�nds
#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

char* substring(char* str, int min, int max);

void substring2(char* str, int min, int max);

bool isDigit(char ch);

SDL_Color createColor(int r, int g, int b, int a);

SDL_Rect createRect(int x, int y, int w, int h);

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2);

double distanceBetweenPoints(SDL_Point p1, SDL_Point p2);

SDL_Point getPolarProjectionPoint(SDL_Point source, double distance, double angle_rad);

double radiansToDegrees(double radians);

double degreesToRadians(double degree);

double angleBetweenPointsRad(SDL_Point p1, SDL_Point p2);

double pointToAngle(double x, double y);