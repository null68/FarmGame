#include "Renderer.h"
#include "../Shader/ShaderStorage.h"

#include <glad/glad.h>

namespace Engine {
	CameraComponent* Renderer::s_ActiveCamera = nullptr;
	std::vector<std::unique_ptr<Batch>> Renderer::s_Batches;

	void Renderer::Init() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

		s_ActiveCamera = nullptr;
	}

	void Renderer::Shutdown() {
		s_Batches.clear();
	}

	void Renderer::BeginScene(CameraComponent& camera) {
		s_ActiveCamera = &camera;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (auto& batch : s_Batches) {
			batch->Begin();
			batch->GetShader()->Bind();
			batch->GetShader()->SetUniformMat4f("u_View", s_ActiveCamera->GetViewMatrix());
			batch->GetShader()->SetUniformMat4f("u_Projection", s_ActiveCamera->GetProjectionMatrix());
		}
	}

	void Renderer::EndScene() {
		for (auto& batch : s_Batches) {
			batch->End();
			batch->Flush();
		}
		s_ActiveCamera = nullptr;
	}

	void Renderer::Submit(const Mesh& mesh, TransformComponent& transform, MaterialComponent& material) {
		auto* shader = material.shader.get();

		Batch* batch = nullptr;
		for (auto& b : s_Batches) {
			if (b->GetShader() == shader && b->GetMesh() == &mesh && b->GetMaterial() == &material) {
				batch = b.get();
				break;
			}
		}

		if (!batch) {
			batch = new Batch(shader);
			s_Batches.emplace_back(batch);

			batch->Begin();

			batch->GetShader()->Bind();
			batch->GetShader()->SetUniformMat4f("u_View", s_ActiveCamera->GetViewMatrix());
			batch->GetShader()->SetUniformMat4f("u_Projection", s_ActiveCamera->GetProjectionMatrix());

			batch->SetMesh(&mesh);
			batch->SetMaterial(&material);
		}
		batch->Submit(mesh, transform, material);
	}

}