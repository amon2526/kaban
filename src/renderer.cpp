#include <renderer.hpp>

Renderer::Renderer() : _window(nullptr), _monitor(nullptr), _mode(nullptr)
{
    std::cout << "Renderer created!" << std::endl;
}

Renderer::~Renderer()
{
    std::cout << "Renderer destroyed!" << std::endl;
}

bool Renderer::initialize(int height, const char *title)
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
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 0);

    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    _monitor = glfwGetPrimaryMonitor();
    _mode = glfwGetVideoMode(_monitor);

    _window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!_window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        shutdown();
        return false;
    }

    glfwMakeContextCurrent(_window);

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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);
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