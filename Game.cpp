// De Prins, Rik - 1GD10E

#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	
	// Print alphabet according to given amount of letters per line
	PrintLetters();
}

void Draw()
{
	// Clear background
	utils::ClearBackground();

	// Put your own draw statements here

	// Draw random circle in growing and shrinking state
	switch (g_State)
	{
	case State::growing:
	case State::shrinking:
	{
		DrawCircle();
		break;
	}
	}
}

void Update(float elapsedSec)
{
	// process input, do physics 

	const int baseSpeed{ 100 };

	// Handle growing and shrinking of circle
	switch (g_State)
	{
	case State::growing:
	{
		if (g_Center.x - g_Radius <= 0 || g_Center.y - g_Radius <= 0 || 
			g_Center.x + g_Radius >= g_WindowWidth || g_Center.y + g_Radius >= g_WindowHeight)
		{
			PrintBorderCollisionMessage();

			// Make circle red on border collision
			g_R = 1;
			g_G = 0;
			g_B = 0;

			g_State = State::shrinking;
			PrintState();

			break;
		}

		if (g_Radius >= g_MaxRadius)
		{
			g_State = State::shrinking;
			PrintState();
		}
		else
		{
			g_Radius += g_Speed * baseSpeed * elapsedSec;
		}

		break;
	}
	case State::shrinking:
	{
		if (g_Radius > g_Speed * baseSpeed * elapsedSec)
		{
			g_Radius -= g_Speed * baseSpeed * elapsedSec;
		}
		else
		{
			g_Radius = 0;

			g_State = State::waiting;
			PrintState();
		}

		break;
	}
	}

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	// Adjust speed modifier
	const float min{ .2f };
	const float max{ 5 };
	const float step{ .4f };

	switch (key)
	{
	case SDLK_DOWN:
	{
		if (g_Speed > min)
		{
			g_Speed -= step;
		}

		if (g_Speed < min)
		{
			g_Speed = min;
		}

		PrintSpeed();

		break;
	}
	case SDLK_UP:
	{
		if (g_Speed < max)
		{
			g_Speed += step;
		}

		if (g_Speed > max)
		{
			g_Speed = max;
		}

		PrintSpeed();

		break;
	}
	}

	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	// Create random circle after releasing left mouse button
	const int min{ 50 };
	const int max{ 150 };

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		switch (g_State)
		{
		case State::waiting:
			g_State = State::growing;
			PrintState();

			g_R = (rand() % 256) / 255.f;
			g_G = (rand() % 256) / 255.f;
			g_B = (rand() % 256) / 255.f;

			g_Center = Point2f(float(e.x), float(g_WindowHeight - e.y));
			g_MaxRadius = float(rand() % (max - min + 1) + min);
			PrintMaxRadius();

			break;
		}

		break;
	}
	}

	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void DrawCircle()
{
	// Draw random circle
	const Color4f rColor{ g_R, g_G, g_B, 1 };

	utils::SetColor(rColor);
	utils::FillEllipse(g_Center, g_Radius, g_Radius);
}

void PrintLetters()
{
	// Print alphabet according to given amount of letters per line
	const char firstLetter{ 'a' };
	const char lastLetter{ 'z' };

	int lettersPerLine{};
	int count{ 0 };

	std::cout << "How many characters per line ?";
	std::cin >> lettersPerLine;
	std::cout << '\n';

	for (char letter{ firstLetter }; letter <= lastLetter; ++letter) 
	{
		std::cout << letter;

		count = letter - firstLetter + 1;

		if (count % lettersPerLine == 0 || letter == lastLetter)
		{
			std::cout << '\n';
		}
	}

	std::cout << "\n\n";
}

void PrintState()
{
	// Print circle state
	switch (g_State)
	{
	case State::growing:
		std::cout << "Growing state." << '\n';
		break;
	case State::shrinking:
		std::cout << "Shrinking state." << '\n';
		break;
	case State::waiting:
		std::cout << "Waiting state." << "\n\n";
		break;
	}
}

void PrintBorderCollisionMessage()
{
	// Print border collision message
	std::cout << "Ouch!" << "\n";
}

void PrintSpeed()
{
	// Print speed multiplier
	std::cout << "g_Speed = " << g_Speed << '\n';
}

void PrintMaxRadius()
{
	// Print maximum circle radius
	std::cout << "The maximum radius is " << g_MaxRadius << '\n';
}
#pragma endregion ownDefinitions