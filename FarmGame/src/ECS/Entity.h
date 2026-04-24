#pragma once

#include "Components/ScriptComponent.h"

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <tuple>

// usage example: entity.AddComponent<TransformComponent>(params...); entity.GetComponent<TransformComponent>(); entity.HasComponent<TransformComponent>(); entity.getComponents<TransformComponent, MeshComponent>();
namespace Engine {
	class Component;
	class Entity {
	public:
		Entity() = default;
		~Entity() = default;
		// T je Component type, Args parametri kontruktora - ako postoje
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

			if (HasComponent<T>()) {
				throw std::runtime_error("Entity already has component of this type");
			}

			std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
			component->entity = this;
			T& componentRef = *component;

			if constexpr (std::is_base_of<ScriptComponent, T>::value) {
				componentRef.OnCreate();
			}
			
			m_Components[std::type_index(typeid(T))] = std::move(component);
			return componentRef;
		}

		template<typename T>
		T* GetComponent() {
			auto componentIt = m_Components.find(std::type_index(typeid(T)));
			if (componentIt != m_Components.end()) {
				return static_cast<T*>(componentIt->second.get());
			}
			return nullptr;
		}

		template <typename... T>
		std::tuple<T*...> GetComponents() {
			return std::make_tuple(GetComponent<T>()...);
		}

		template<typename T>
		bool HasComponent() const {
			return m_Components.find(std::type_index(typeid(T))) != m_Components.end();
		}

		template<typename T>
		void RemoveComponent() {
			auto component = std::type_index(typeid(T));
			m_Components.erase(component);
		}
	private:
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
	};
}