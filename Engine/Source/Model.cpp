#include "Model.h"

void Model::Draw(Renderer& renderer, const Vector2& position, float angle, float scale)
{
	if (m_points.empty()) return;

	for (int i = 0; i < m_points.size(); i++)
	{
		for (int j = 0; j < m_points[i].size() - 1; j++)
		{
			Vector2 p1 = (m_points[i][j].Rotate(angle) * scale) + position;
			Vector2 p2 = (m_points[i][j + 1].Rotate(angle) * scale) + position;

			renderer.DrawLine(p1, p2);
		}
	}
}

void Model::Draw(Renderer& renderer, const Transform& transform)
{
	if (m_points.empty()) return;

	renderer.SetColor(m_color);
	for (int i = 0; i < m_points.size(); i++)
	{
		for (int j = 0; j < m_points[i].size() - 1; j++)
		{
			Vector2 p1 = (m_points[i][j].Rotate(transform.rotation) * transform.scale) + transform.position;
			Vector2 p2 = (m_points[i][j + 1].Rotate(transform.rotation) * transform.scale) + transform.position;

			renderer.DrawLine(p1, p2);
		}
	}
}
