#include "Rendering.h"



Rendering::Rendering()
{
}


Rendering::~Rendering()
{
}

void Rendering::SetupDrawing(HDC hDesktop, HWND handle)
{
	HDC_Desktop = hDesktop;
	Handle = handle;
	EnemyBrush = CreateSolidBrush(RGB(255, 0, 0));
	//Color
	SnapLineCOLOR = RGB(0, 0, 255);
	TextCOLOR = RGB(0, 255, 0);
}


//We receive the 2-D Coordinates the colour and the device we want to use to draw those colours with
//HDC so we know where to draw and brush because we need it to draw
void Rendering::DrawFilledRect(int x, int y, int w, int h)
{
	//We create our rectangle to draw on screen
	RECT rect = { x, y, x + w, y + h };
	//We clear that portion of the screen and display our rectangle
	FillRect(HDC_Desktop, &rect, EnemyBrush);
}


void Rendering::DrawBorderBox(int x, int y, int w, int h, int thickness)
{
	//Top horiz line
	DrawFilledRect(x, y, w, thickness);
	//Left vertical line
	DrawFilledRect(x, y, thickness, h);
	//right vertical line
	DrawFilledRect((x + w), y, thickness, h);
	//bottom horiz line
	DrawFilledRect(x, y + h, w + thickness, thickness);
}

//Here is where we draw our line from point A to Point B
void Rendering::DrawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Pen)
{
	int a, b = 0;
	HPEN hOPen;
	// penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);
	hOPen = (HPEN)SelectObject(HDC_Desktop, hNPen);
	// starting point of line
	MoveToEx(HDC_Desktop, StartX, StartY, NULL);
	// ending point of line
	a = LineTo(HDC_Desktop, EndX, EndY);
	DeleteObject(SelectObject(HDC_Desktop, hOPen));
}

//Draw our text with this function
void Rendering::DrawString(int x, int y, COLORREF color, const char* text)
{
	SetTextAlign(HDC_Desktop, TA_CENTER | TA_NOUPDATECP);

	SetBkColor(HDC_Desktop, RGB(0, 0, 0));
	SetBkMode(HDC_Desktop, TRANSPARENT);

	SetTextColor(HDC_Desktop, color);

	SelectObject(HDC_Desktop, Font);

	TextOutA(HDC_Desktop, x, y, text, strlen(text));

	DeleteObject(Font);
}

//x and y are offsets from center of screen
void Rendering::DrawESP(float x, float y, float distance)
{
	//ESP RECTANGLE
	int playerWidth = 18100 / distance;
	int playerHeight = 36000 / distance;

	long windowWidth = m_Rect.right - m_Rect.left;
	long windowHeight = m_Rect.bottom - m_Rect.top;

	x = x + 0.25; // Idk why this works but it makes the drawing switch to the right place. Don't worry, the calculated angles are definitely correct though.
	y = y + 0.1; // well ok maybe I forgot to switch the y axis at some point but fuck it.

	//long playerLeftLocation = windowWidth / 2 + x - 5;//windowWidth / 2 + x - (playerWidth / 2);
	//long playerRightLocation = windowWidth / 2 + x + 5;//windowWidth / 2 + x + (playerWidth / 2);
	long playerLeftLocation = windowWidth * (x + 1)/2 - 5;
	long playerRightLocation = windowWidth * (x + 1)/2 + 5;
	long playerBottomLocation = windowHeight * (y + 1) / 2 + playerHeight;
	long playerTopLocation = windowHeight * (y + 1) / 2;
	//long playerBottomLocation = windowHeight / 2 + y + playerHeight;
	//long playerTopLocation = windowHeight / 2 + y;


	//std::cout << x << "   " << y << "\n";
	//RECT rect = { x, y, x + w, y + h }; // params from drawborderbox top horiz line
	//fillrect(rect)
	RECT rect = {playerLeftLocation, playerTopLocation, playerRightLocation, playerBottomLocation};
	FillRect(HDC_Desktop, &rect, EnemyBrush);
	//DrawBorderBox(x - (width / 2), y - height, width, height, 1);
	/*
	//Sandwich ++
	DrawLine((m_Rect.right - m_Rect.left) / 2,
		m_Rect.bottom - m_Rect.top, x, y,
		SnapLineCOLOR);


	std::stringstream ss;
	ss << (int)distance;

	char * distanceInfo = new char[ss.str().size() + 1];
	strcpy(distanceInfo, ss.str().c_str());

	DrawString(x, y, TextCOLOR, distanceInfo);

	delete[] distanceInfo;*/
}



void Rendering::render(std::vector<RenderingInputData> renderingInputData) {
	//Find the target window and stuff
	GetWindowRect(FindWindow(NULL, "Team Fortress 2"), &m_Rect); //m_Rect's values are relative to the upper left corner of the screen.
	TargetWnd = FindWindow(0, "Team Fortress 2");
	HDC HDC_Desktop = GetDC(TargetWnd);
	SetupDrawing(HDC_Desktop, TargetWnd); //sets up some non important parameters

	for (int i = 0; i < renderingInputData.size(); i++) {

		std::cout << renderingInputData[i].screenPositions[1] << "   " << renderingInputData[i].screenPositions[0] << "\n";

		float pixelsXY[2]; //the number of pixels that the enemy is off from the center of the window
		pixelsXY[0] = renderingInputData[i].screenPositions[1]; //* (m_Rect.right - m_Rect.left) / 2; // divide by two because you're counting from the center of the screen.
		pixelsXY[1] = renderingInputData[i].screenPositions[0]; //* (m_Rect.bottom - m_Rect.top) / 2;
		DrawESP(pixelsXY[0], pixelsXY[1], renderingInputData[i].distance);
	}
	
}