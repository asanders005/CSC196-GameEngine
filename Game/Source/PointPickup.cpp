#include "PointPickup.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "Player.h"

void PointPickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			AUDIO.PlaySound("Pickup");
			m_scene->GetGame()->AddPoints(500);
			m_destroyed = true;
		}
	}
}