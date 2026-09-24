#include "AnimationClip.h"
#include <algorithm>

namespace Engine {
	void AnimationClip::AddKeyframe(const std::string& nodeName, AnimationChannel channel, float time, const glm::vec3& value) {
		NodeAnimation& node = m_Nodes[nodeName];
		std::vector<AnimationKeyframe>* keys = nullptr;

		switch (channel) {
			case AnimationChannel::Position:

				keys = &node.PositionKeys;

				break;
			case AnimationChannel::Rotation:

				keys = &node.RotationKeys; 

				break;
			case AnimationChannel::Scale:

				keys = &node.ScaleKeys;    

				break;
		}
				
		keys->push_back({ time, value });	
		std::sort(keys->begin(), keys->end(), [](const AnimationKeyframe& a, const AnimationKeyframe& b) {
			return a.Time < b.Time;
			});
	}
			
	bool AnimationClip::HasNode(const std::string& nodeName) const {
		return m_Nodes.find(nodeName) != m_Nodes.end();
	}
		
	glm::vec3 AnimationClip::Sample(const std::vector<AnimationKeyframe>& keys, float time, const glm::vec3& defaultValue) {
		if (keys.empty())
			return defaultValue;
				
		if (time <= keys.front().Time)
			return keys.front().Value;
		if (time >= keys.back().Time)
			return keys.back().Value;
			

		for (size_t i = 0; i + 1 < keys.size(); i++) {
			const AnimationKeyframe& thisFrame = keys[i];
			const AnimationKeyframe& nextFrame = keys[i + 1];

			if (time >= thisFrame.Time && time <= nextFrame.Time) {
				float span = nextFrame.Time - thisFrame.Time;
				float t = span > 0.0f ? (time - thisFrame.Time) / span : 0.0f;

				return glm::mix(thisFrame.Value, nextFrame.Value, t);
			}
		}

		return keys.back().Value;
	}
	  
	glm::vec3 AnimationClip::SamplePosition(const std::string& nodeName, float time, const glm::vec3& defaultValue) const {
		auto it = m_Nodes.find(nodeName);
		if (it == m_Nodes.end()) return defaultValue;
		return Sample(it->second.PositionKeys, time, defaultValue);
	}
		
	glm::vec3 AnimationClip::SampleRotation(const std::string& nodeName, float time, const glm::vec3& defaultValue) const {
		auto it = m_Nodes.find(nodeName);

		if (it == m_Nodes.end()) return defaultValue;	

		return Sample(it->second.RotationKeys, time, defaultValue);
	}

	glm::vec3 AnimationClip::SampleScale(const std::string& nodeName, float time, const glm::vec3& defaultValue) const {
		auto it = m_Nodes.find(nodeName);  

		if (it == m_Nodes.end()) return defaultValue;	
			
		return Sample(it->second.ScaleKeys, time, defaultValue);	
	}
}	
