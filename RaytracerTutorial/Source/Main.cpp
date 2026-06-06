#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Dielectric.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Sphere.hpp"

glm::vec3 rayColor(const Ray& ray, const Hittable& world);

GLFWwindow* createWindow();
void renderLoop();

int main()
{
	HittableList world;

	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(glm::vec3{ 0.8f, 0.8f, 0.0f });
	std::shared_ptr<Material> cent = std::make_shared<Lambertian>(glm::vec3{ 0.1f, 0.2f, 0.5f });
	std::shared_ptr<Material> left = std::make_shared<Dielectric>(1.5f);
	std::shared_ptr<Material> leftIns = std::make_shared<Dielectric>(1.0f / 1.5f);
	std::shared_ptr<Material> right = std::make_shared<Metal>(glm::vec3{ 0.8f, 0.6f, 0.2f }, 1.0f);

	std::shared_ptr<Sphere> sphere0 = std::make_shared<Sphere>(glm::vec3{ 0.0f, 0.0f, -1.2f }, 0.5f, cent);
	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3{ 0.0f, -100.0f, -1.0f }, 99.5f, ground);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3{ -1.0f, 0.0f, -1.0f }, 0.5f, left);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(glm::vec3{ -1.0f, 0.0f, -1.0f }, 0.4f, leftIns);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3{ 1.0f, 0.0f, -1.0f }, 0.5f, right);

	world.add(sphere0);
	world.add(sphere1);
	world.add(sphere2);
	world.add(sphere3);
	world.add(sphere4);

	Camera cam;

	cam.imageWidth = 2560;
	cam.imageHeight = 1440;

	cam.render(world);
	
	return 0;
}

GLFWwindow* createWindow() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return window;
}

void renderLoop() {
	GLFWwindow* windPtr = createWindow();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windPtr))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(windPtr);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

glm::vec3 rayColor(const Ray& ray, const Hittable& world)
{
	HitRecord hitRec;
	bool hit = world.hit(ray, Interval{ 0.0f, std::numeric_limits<float>::infinity() }, hitRec);
	if (hit)
	{
		glm::vec3 norm = hitRec.norm;
		norm *= 0.5f;
		norm += 0.5f;
		return norm;
	}

	glm::vec3 unitDir = glm::normalize(ray.getDir());
	float a = 0.5f * (unitDir.y + 1.0f);

	return (1.0f - a) * glm::vec3(0.0f, 0.0f, 0.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}