#include "Kart.h"

Kart::Kart(const std::string& resourcesFolder, Shader& kartShader) : kartMesh("kart.obj")
{
	InitKart(resourcesFolder, kartShader);

	kartShader.Use();
	kartShader.SetVec3("lightColor", glm::vec3(0.7f, 0.7f, 0.7f));

    MovementSpeed = 0.50f;
    TurningSpeed = 1.0f;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateFront();
}

void Kart::Render(Camera* camera, Shader& kartShader)
{
	kartShader.Use();
	camera->UpdateCameraVectors();
	camera->Use(kartShader);
	glBindTexture(GL_TEXTURE_2D, kartTexture);
	kartMesh.Render(kartShader);
}

void Kart::ProcessKeyboard(Direction direction, float deltaTime)
{
    if (direction == K_LEFT)
    {
        Yaw = 0.0f;
        kartMesh.SetPosition(kartMesh.GetPosition() - Right * MovementSpeed * deltaTime);
        kartMesh.SetRotation(glm::vec3(0.0f, 275.0f, 0.0f));
    }
    if (direction == K_RIGHT)
    {
        Yaw = -120.0f;
        kartMesh.SetPosition(kartMesh.GetPosition() + Right * MovementSpeed * deltaTime);
        kartMesh.SetRotation(glm::vec3(0.0f, -275.0f, 0.0f));
    }
    if (direction == K_BACKWARD)
    {
        Yaw = -60.0f;
        kartMesh.SetPosition(kartMesh.GetPosition() + Front * MovementSpeed * deltaTime);
        kartMesh.SetRotation(glm::vec3(0.0f, 179.0f, 0.0f));
    }
    if (direction == K_FORWARD)
    {
        Yaw = 60.0f;
        kartMesh.SetPosition(kartMesh.GetPosition() - Front * MovementSpeed * deltaTime);
        kartMesh.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void Kart::InitKart(const std::string& resourcesFolder, Shader& kartShader)
{
	kartShader.Set("Texture.shader");

	kartTexture = CreateTexture(resourcesFolder + "\\kart.jpg");
	kartShader.SetInt("kart", 2);

	kartMesh.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	kartMesh.SetPosition(glm::vec3(-10.0f, 8.0f, -45.0f));
	kartMesh.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	kartMesh.InitVAO();
}

void Kart::updateFront()
{
    glm::vec3 front;
    front.x = -sin(glm::radians(Yaw / 2));
    front.y = 0.0f;
    front.z = -cos(glm::radians(Yaw / 2));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
}
