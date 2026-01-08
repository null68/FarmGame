#pragma once

#include "Component.h"

#include <memory>
#include <unordered_map>
#include <typeindex>

// usage example: entity.AddComponent<TransformComponent>(params...); entity.GetComponent<TransformComponent>(); entity.HasComponent<TransformComponent>();
namespace Engine {
	class Entity {
	public:
		Entity() = default;
		~Entity() = default;
		// T je Component type, Args parametri kontruktora - ako postoje
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
			component->entity = this;
			T& componentRef = *component;

			if constexpr (std::is_base_of<ScriptComponent, T>::value) {
				componentRef.OnCreate();
			}

			m_Components[std::type_index(typeid(T))] = componentRef;
			return componentRef;
		}

		template<typename T>
		T* GetComponent() {
			auto componentIt = m_Components.find(std::type_index(typeid(T)));
			if (componentIt != m_Components.end()) {
				return static_cast<T*>(componentIt->second);
			}
			return nullptr;
		}

		template<typename T>
		bool HasComponent() const {
			return m_Components.find(std::type_index(typeid(T))) != m_Components.end();
		}
	private:
		std::unordered_map<std::type_index, Component*> m_Components;
	};
}