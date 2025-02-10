#include <renderer.hpp>


bool Renderer::initialize(int height, const char* title, InputHandler& inputHandler)
{
    int width = calculateWindowWidth(height);
    if (!initializeOpenGL(width, height, title))
    {
        return false;
    }
    if (!initializeImgui())
    {
        return false;
    }
    return true;
};

bool Renderer::initializeOpenGL(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        UserIO::outputError(1, "GLFW init error");
        shutdown();
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _monitor = glfwGetPrimaryMonitor();
    _mode = glfwGetVideoMode(_monitor);
    
    _window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!_window)
    {
        UserIO::outputError(1, "Window creation failed");
        shutdown();
        return false;
    }

    glfwSetErrorCallback(UserIO::outputError);
    glfwSetKeyCallback(_window, InputHandler::getInstance().keyCallback);

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    return true;
}

bool Renderer::initializeImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
    return true;
}

void Renderer::render()
{
    double time = glfwGetTime();
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (_game)
    {
        char* board = _game->getPlainBoard();
    }
    
    ImGui::Render();
    
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);

    glfwPollEvents();
}

void Renderer::shutdown()
{
    if (_window)
    {
        glfwDestroyWindow(_window);
        _window = nullptr;
    }
    glfwTerminate();
}

bool Renderer::windowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Renderer::toggleDemoWindow()
{
    _showDemoWindow = !_showDemoWindow;
}

void Renderer::showDemoWindow()
{
    ImGui::ShowDemoWindow(&_showDemoWindow);
}