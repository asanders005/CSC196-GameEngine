#include "Pickup.h"
#include "Engine.h"
#include "Player.h"

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			AUDIO.PlaySound("Pickup");
			dynamic_cast<Player*>(actor)->AddHP(10);
			m_destroyed = true;
		}
	}
}