#include <iostream>
#include "Application.h"
#include "../Graphics/Render/Renderer.h"
#include "../Graphics/Mesh/MeshData.h"
#include "../Graphics/Shader/ShaderStorage.h"

namespace Engine {
	Application::Application() {
		Window = std::make_unique<Engine::Window>(800, 600, "Farm Game");
		Input = std::make_unique<Engine::Input>(Window->GetNativeWindow());
		Renderer::Init();
	}
	void Application::Run() {
        CameraComponent camera;
        camera.SetPosition(glm::vec3(2.0f, 2.0f, 5.0f));
        camera.SetPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

        auto shader = ShaderStorage::GetInstance().Get("BasicShader");
        MaterialComponent material;
		material.shader = shader;

        MeshData cubeData = CreateCube(); 
        Mesh cubeMesh(cubeData);
        TransformComponent cubeTransform;


		while (!Window->ShouldClose()) {
			Window->PollEvents();

			Time::Update();

			if (Input->IsKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "Escape key pressed. Exiting application." << std::endl;
				break;
			}

            Renderer::BeginScene(camera);

			cubeTransform.Rotation.y += 50.0f * Time::DeltaTime();
            Renderer::Submit(cubeMesh, cubeTransform, material);

            Renderer::EndScene();

			Window->SwapBuffers();
		}

        Renderer::Shutdown();
	}

    MeshData Application::CreateCube() {
        MeshData data;
        data.vertices = {
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, 
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, 
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, 
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}}, 
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}}, 
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}, 
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}, 
            {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}},
        };
        data.indices = {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            5, 4, 7, 7, 6, 5,
            4, 0, 3, 3, 7, 4,
            3, 2, 6, 6, 7, 3,
            4, 5, 1, 1, 0, 4
        };

        return data;
    }

}