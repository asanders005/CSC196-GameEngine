#include "Renderer.h"
#include "Vector2.h"

#include <SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);
	
	Vector2 v1{ 400, 300 };
	Vector2 v2{ 500, 400 };

	std::vector<Vector2> points;
	for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}

	//main
	while (true)
	{
		// input
		// update
		// draw
		
		// UPDATE
		Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.02f;
		}


		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		// draw shape 
		renderer.SetColor(255, 255, 255, 0); 
		renderer.DrawLine(400, 150, 500, 450);
		renderer.DrawLine(500, 450, 250, 250);
		renderer.DrawLine(250, 250, 550, 250);
		renderer.DrawLine(550, 250, 300, 450);
		renderer.DrawLine(300, 450, 400, 150);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i], points[i + 1]);
		}

		// random lines
		for (int i = 0; i < rand() % 300; i++)
		{
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600);
		}

		// random dots
		for (int i = 0; i < rand() % 5000; i++)
		{
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawPoint(rand() % 800, rand() % 600);
		}

		// show screen
		renderer.EndFrame();
	}

	return 0;
}