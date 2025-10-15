//
// Created by nazarii on 10/14/25.
//

#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Application::Application(AppConfig cfg) : config_(cfg) {}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Application::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    this->window_ = glfwCreateWindow(config_.width, config_.height, config_.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent((GLFWwindow*)this->window_);
}

void Application::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
}

void Application::initImgui() {

    if (!window_) throw std::runtime_error("GLFW window is null");
    // Make sure the GL context is current before this call
    // glfwMakeContextCurrent(window_);  // (if not already current)

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window_), true))
        throw std::runtime_error("ImGui_ImplGlfw_InitForOpenGL failed");

    if (!ImGui_ImplOpenGL3_Init("#version 450"))
        throw std::runtime_error("ImGui_ImplGlfw_InitForOpenGL failed");

}


void Application::renderUi() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");

    ImGui::Button("Restart");

    ImGui::End();




    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::EndFrame();
}

void Application::init() {
    initWindow();
    initGlad();
    initImgui();
}


void Application::run() {
    while (this->running_) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

        this->renderUi();

        glfwSwapBuffers(static_cast<GLFWwindow*>(window_));
    }
}
