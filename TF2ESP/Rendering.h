#pragma once

#include <vector>
#include "RenderingInputData.h"
#include <Windows.h>
#include <sstream>
#include <iostream> 
#include <math.h>  
//not sure if needed#include "HackProcess.h"
#include <algorithm> 

#pragma warning(disable:4996)

class Rendering
{
public:
	Rendering();
	~Rendering();
	void render(std::vector<RenderingInputData> renderingInputData);
	void DrawESP(float x, float y, float distance);
	void DrawString(int x, int y, COLORREF color, const char* text);
	void DrawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Pen);
	void DrawBorderBox(int x, int y, int w, int h, int thickness);
	void DrawFilledRect(int x, int y, int w, int h);
	void SetupDrawing(HDC hDesktop, HWND handle);
	

private:
	RECT m_Rect;

	//Set of initial variables you'll need
	//Our desktop handle
	HDC HDC_Desktop;
	//Brush to paint ESP etc
	HBRUSH EnemyBrush;
	HFONT Font; //font we use to write text with


	HWND TargetWnd;
	HWND Handle;
	DWORD DwProcId;

	COLORREF SnapLineCOLOR;
	COLORREF TextCOLOR;
};

