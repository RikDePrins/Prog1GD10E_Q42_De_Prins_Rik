#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Q42 - De Prins, Rik - 1GD10E" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
float g_MaxRadius{};
float g_Radius{ 0 };
float g_Speed{ 2 };
float g_R{}, g_G{}, g_B{};

Point2f g_Center{};

enum class State 
{
	growing,
	shrinking,
	waiting
};

State g_State{ State::waiting };
// Declare your own functions here
void DrawCircle();
void PrintLetters();
void PrintState();
void PrintBorderCollisionMessage();
void PrintSpeed();
void PrintMaxRadius();
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
