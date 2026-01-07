#pragma once

#include "../Component.h"

namespace Engine {
	class ScriptComponent : public Component {
	public:
		ScriptComponent() = default;
		virtual ~ScriptComponent() = default;
		virtual void OnCreate() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnDestroy() {}
	};
}