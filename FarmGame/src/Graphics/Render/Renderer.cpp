#include "Renderer.h"
#include "../Shader/ShaderStorage.h"

#include <glad/glad.h>
#include <algorithm>

namespace Engine {
	CameraComponent* Renderer::s_ActiveCamera = nullptr;
	std::vector<std::unique_ptr<Batch>> Renderer::s_Batches;
	std::unordered_map<Renderer::BatchKey, Batch*, Renderer::BatchKeyHasher> Renderer::s_BatchLookup;
	int Renderer::s_ViewportWidth = 800;
	int Renderer::s_ViewportHeight = 600;


	void Renderer::Init() {
		glEnable(GL_DEPTH_TEST);

		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		try {
			ShaderStorage::GetInstance().Load("BasicShader", "assets/shaders/BasicVertexShader.glsl", "assets/shaders/BasicFragmentShader.glsl");
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error loading basic shader in Renderer::Init: " << e.what() << std::endl;
		}

		s_Batches.clear();
		s_BatchLookup.clear();
		s_ActiveCamera = nullptr;
	}

	void Renderer::Shutdown() {
		s_Batches.clear();
		s_BatchLookup.clear();
	}

	void Renderer::SetViewportSize(int width, int height) {
		s_ViewportWidth = width;
		s_ViewportHeight = height;
	}

	void Renderer::BeginScene(CameraComponent& camera) {
		s_ActiveCamera = &camera;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& batch : s_Batches) {
			batch->Begin();
		}
	}

	void Renderer::EndScene() {
		std::stable_sort(s_Batches.begin(), s_Batches.end(), [](const std::unique_ptr<Batch>& a, const std::unique_ptr<Batch>& b) {
			if (!a->HasContent()) return false;
			if (!b->HasContent()) return true;
			return static_cast<int>(a->GetMaterial()->queue) < static_cast<int>(b->GetMaterial()->queue);
		});

		glm::mat4 view = s_ActiveCamera->GetViewMatrix();
		glm::mat4 projection = s_ActiveCamera->GetProjectionMatrix();

		glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

		glm::mat4 uiView = glm::mat4(1.0f);
		glm::mat4 uiProjection = glm::ortho(
			0.0f, static_cast<float>(s_ViewportWidth),
			static_cast<float>(s_ViewportHeight), 0.0f,
			-1.0f, 1.0f);

		RenderQueue current = RenderQueue::Opaque;
		ApplyRenderState(current);

		for (auto& batch : s_Batches) {
			if (!batch->HasContent())
				continue;

			RenderQueue queue = batch->GetMaterial()->queue;
			if (queue != current) {
				ApplyRenderState(queue);
				current = queue;
			}

			batch->End();
			switch (queue) {
			case RenderQueue::Skybox:
				batch->Flush(skyboxView, projection);
				break;
			case RenderQueue::UI:
				batch->Flush(uiView, uiProjection);
				break;
			default:
				batch->Flush(view, projection);
				break;
			}
		}

		ApplyRenderState(RenderQueue::Opaque); 
		s_ActiveCamera = nullptr;
	}

	void Renderer::Submit(const Mesh& mesh, TransformComponent& transform, MaterialComponent& material) {
		auto* shader = material.shader.get();
		BatchKey key{ shader, &mesh, &material };

		auto it = s_BatchLookup.find(key);
		Batch* batch = nullptr;

		if (it != s_BatchLookup.end()) {
			batch = it->second;
		}
		else {
			auto owned = std::make_unique<Batch>(shader);
			batch = owned.get();
			batch->Begin();
			s_Batches.push_back(std::move(owned));
			s_BatchLookup[key] = batch;
		}

		batch->Submit(mesh, transform, material);
	}

	void Renderer::ApplyRenderState(RenderQueue queue) {
		switch (queue) {
		case RenderQueue::Opaque: 
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);
			glDisable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			break;
		case RenderQueue::Transparent:
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_CULL_FACE);
			break;
		case RenderQueue::Skybox:
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_FALSE);
			glDisable(GL_BLEND);
			glDisable(GL_CULL_FACE);
			break;
		case RenderQueue::UI:
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		}
	}
}