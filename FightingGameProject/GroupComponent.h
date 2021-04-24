#pragma once

namespace RB
{
	class GameObj;
	class Camera;

	class GroupComponent
	{
	public:
		virtual void UpdateComponent() {};
		virtual void RenderComponent() {};
		virtual void RenderComponent(GameObj* obj, Camera& cam) {};
	};
}