#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <glm.hpp>
	
namespace Engine {	
	enum class AnimationChannel {
		Position,
		Rotation,
		Scale
	};	
			
	struct AnimationKeyframe {
		float Time = 0.0f;
		glm::vec3 Value{ 0.0f, 0.0f, 0.0f };
	};	
				
	struct NodeAnimation {
		std::vector<AnimationKeyframe> PositionKeys;
		std::vector<AnimationKeyframe> RotationKeys;
		std::vector<AnimationKeyframe> ScaleKeys;
	};	
			
	class AnimationClip {
	public:
		std::string Name;
		float Length = 0.0f;
		bool Loop = false;	
			
		void AddKeyframe(const std::string& nodeName, AnimationChannel channel, float time, const glm::vec3& value);

		bool HasNode(const std::string& nodeName) const;
		glm::vec3 SamplePosition(const std::string& nodeName, float time, const glm::vec3& defaultValue) const;
		glm::vec3 SampleRotation(const std::string& nodeName, float time, const glm::vec3& defaultValue) const;
		glm::vec3 SampleScale(const std::string& nodeName, float time, const glm::vec3& defaultValue) const;
	private:
		static glm::vec3 Sample(const std::vector<AnimationKeyframe>& keys, float time, const glm::vec3& defaultValue);

		std::unordered_map<std::string, NodeAnimation> m_Nodes;
	};
}