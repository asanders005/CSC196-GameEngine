#include "GameData.h"

namespace GameData
{
	const std::vector<std::vector<Vector2>> playerShipPoints
	{
		{
			{ 11, 0 },
			{ 8, 1 },
			{ -3, 7 },
			{ -4, 6 },
			{ -2, 2 },
			{ -9, 5 },
			{ -9, 4 },
			{ -8, 2 },
			{ -11, 4 },
			{ -11, 3 },
			{ -9, 1 },
			{ -9, -1 },
			{ -11, -3 },
			{ -11, -4 },
			{ -8, -2 },
			{ -9, -4 },
			{ -9, -5 },
			{ -2, -2 },
			{ -4, -6 },
			{ -3, -7 },
			{ 8, -1 },
			{ 11, 0 }
		},
		{
			{ 9, 0 },
			{ 6, 1 },
			{ 6, -1 },
			{ 9, 0 }
		},
		{
			{ -2, 0 },
			{ 3, 0 },
			{ 4, 1 },
			{ -1, 2 },
			{ -2, 1 },
			{ -2, -1 },
			{ -1, -2 },
			{ 4, -1 },
			{ 3, 0 }
		},
		{
			{ -7, 1 },
			{ -4, 0 },
			{ -7, -1 },
			{ -8, -1 },
			{ -7, -2 },
			{ -3, -1 },
			{ -3, 1 },
			{ -7, 2 },
			{ -8, 1 },
			{ -7, 1 },
			{ -8, 0 },
			{ -7, -1 }
		}
	};

	const std::vector<std::vector<Vector2>> playerBulletPoints
	{
		{
			{ 5, 0 },
			{ -5, -4 },
			{ -3, 0 },
			{ -5, 4 },
			{ 5, 0 }
		}
	};

	const std::vector<std::vector<Vector2>> playerShieldPoints
	{
		{
			{ 14, 8 },
			{ 14, -8 },
			{ 8, -14 },
			{ -8, -14 },
			{ -14, -8 },
			{ -14, 8 },
			{ -8, 14 },
			{ 8, 14 },
			{ 14, 8 },
		}
	};

	const std::vector<std::vector<Vector2>> rammerShipPoints
	{
		{
			{ 4, -1 },
			{ 4, 1 },
			{ 2, 1 },
			{ 2, -1 },
			{ -1, -1 },
			{ -1, 1 },
			{ 3, 1 },
			{ 3, -1 },
			{ -2, -1 },
			{ -2, 1 },
			{ -1, 1 },
			{ -1, 0 },
			{ 2, 0 },
			{ 2, -1 },
			{ 4, -1}
		},
		{
			{ 2, -2 },
			{ 2, -3 },
			{ 1, -3 },
			{ 1, -4 },
			{ -2, -4 },
			{ -2, -3 },
			{ -3, -3 },
			{ -3, -2 },
			{ 2, -2 }
		},
		{
			{ 0, -3 },
			{ -1, -3 }
		},
		{
			{ 2, 2 },
			{ 2, 3 },
			{ 1, 3 },
			{ 1, 4 },
			{ -2, 4 },
			{ -2, 3 },
			{ -3, 3 },
			{ -3, 2 },
			{ 2, 2 }
		},
		{
			{ 0, 3 },
			{ -1, 3 }
		}
	};

	const std::vector<std::string> upgradeText
	{
		"Faster Firing",
		"Extra Gun",
		"Faster Bullets",
		"Bigger Bullets",
		"Stronger Bullets",
		"Faster Shield",
		"Stronger Hull",
		"Faster Flying",
		"Faster Turning",
		"Hull Repair",
		"Points",
		"Destroy Enemies"
	};
}