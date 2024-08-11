#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "graphics/renderer.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/shader.hpp"
#include "logics/game.hpp"
#include "logics/Unit.hpp"

struct AppData
{
    RenderWindow render_window;
    Game game;
};

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    AppData *app_data = static_cast<AppData *>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_RIGHT)
        {
            app_data->render_window.update_offset_right();
        }
        else if (key == GLFW_KEY_LEFT)
        {
            app_data->render_window.update_offset_left();
        }
        else if (key == GLFW_KEY_1)
        { // Purchase patrol boat
            app_data->game.purchase_unit("Patrol Boat");
        }
        else if (key == GLFW_KEY_2)
        { // Purchase destroyer
            app_data->game.purchase_unit("Destroyer");
        }
        else if (key == GLFW_KEY_3)
        { // Purchase submarine
            app_data->game.purchase_unit("Submarine");
        }
        else if (key == GLFW_KEY_4)
        { // Purchase bomber
            app_data->game.purchase_unit("Bomber");
        }
        else if (key == GLFW_KEY_5)
        { // Purchase helicopter
            app_data->game.purchase_unit("Helicopter");
        }
        else if (key == GLFW_KEY_Z)
        { // Upgrade income
            app_data->game.purchase_income_upgrade();
        }
        else if (key == GLFW_KEY_X)
        { // Upgrade base health regeneration
            app_data->game.purchase_health_regen_upgrade();
        }
        else if (key == GLFW_KEY_C)
        { // Upgrade max resources
            app_data->game.purhcase_max_resource_upgrade();
        }
        else if (key == GLFW_KEY_V)
        { // Upgrade max base health
            app_data->game.purchase_max_health_upgrade();
        }
    }
}

void SetupImGui(GLFWwindow *window)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void OnButtonClick(std::string type, Game &game)
{
    // Do something when the button is clicked
    if (type == "Patrol Boat")
    {
        game.purchase_unit("Patrol Boat");
    }

    if (type == "Destroyer")
    {
        game.purchase_unit("Destroyer");
    }

    if (type == "Submarine")
    {
        game.purchase_unit("Submarine");
    }

    if (type == "Helicopter")
    {
        game.purchase_unit("Helicopter");
    }
}

void RenderImGui(Game &game)
{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("GUI");
    ImGui::Text("Resources: %d", static_cast<int>(game.get_game_resources().get_resources()));

    if (ImGui::Button("Patrol Boat"))
    {
        OnButtonClick("Patrol Boat", game);
    }

    if (ImGui::Button("Destroyer"))
    {
        OnButtonClick("Destroyer", game);
    }

    if (ImGui::Button("Submarine"))
    {
        OnButtonClick("Submarine", game);
    }

    if (ImGui::Button("Helicopter"))
    {
        OnButtonClick("Helicopter", game);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(800, 800, "cpp Black Navy War", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    AppData app_data; // Initialize app data which includes info about the game and render window

    glfwSetWindowUserPointer(window, &app_data); // Point the window to app_data so it can be used in key callback

    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE; // Magic line that makes it so the whole program doesn't seg fault
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    SetupImGui(window);

    float base_positions[] = {
        0.0f, -0.5f,
        10.0f, -0.5f,
        0.0f, 0.5f,

        90.0f, -0.5f,
        100.0f, -0.5f,
        100.0f, 0.5f};

    float background_color[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f};

    float sea_line[] = {
        -1.0f, 0.0f,
        1.0f, 0.0f};

    unsigned int indices[] = {0, 1, 2, 3, 4, 5};

    unsigned int background_indices[] = {0, 1, 2, 2, 3, 0};

    unsigned int sea_line_indices[] = {0, 1};

    // Set up arrays and buffers for bases
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vb(base_positions, sizeof(base_positions));

    glEnableVertexAttribArray(0);

    IndexBuffer ib(indices, 6);

    VertexBuffer background_color_vb(background_color, sizeof(background_color));

    IndexBuffer background_color_ib(background_indices, 6);

    VertexBuffer sea_line_vb(sea_line, sizeof(sea_line));

    IndexBuffer sea_line_ib(sea_line_indices, 4);

    const std::string vertexShader = // Initialize Vertex Shaders
        R"(#version 330 core
        layout(location = 0) in vec4 position;
        void main()
        {
           gl_Position = position;
        })";

    const std::string fragmentShader = // Initialize Fragment Shaders
        R"(#version 330 core
        layout(location = 0) out vec4 color;

        uniform vec4 u_Color;

        void main()
        {
           color = u_Color;
        })";

    // Create and compile shaders
    Shader shader(vertexShader, fragmentShader);
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

        shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.55f, 1.0f); // Draw background
        app_data.render_window.draw_object(vao, background_color_vb, background_color_ib);

        float norm_positions[12];
        app_data.render_window.normalize_vb(base_positions, norm_positions, 12);
        VertexBuffer my_vb(norm_positions, sizeof(norm_positions));
        shader.SetUniform4f("u_Color", 0.1f, 0.1f, 0.1f, 1.0f); // Draw bases
        app_data.render_window.draw_object(vao, my_vb, ib);

        shader.SetUniform4f("u_Color", 0.1f, 0.1f, 0.1f, 1.0f); // Draw sea line
        sea_line_ib.Bind();
        sea_line_vb.Bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, nullptr);

        app_data.game.play_turn(); // Simulate one "turn" or fraction of a second of the game
        app_data.game.play_enemy_turn();

        // Render units in the window
        std::vector<Unit> friendly_units = app_data.game.get_friendly_units();
        std::vector<Unit> enemy_units = app_data.game.get_enemy_units();

        // Render friendly units
        for (int i = 0; i < friendly_units.size(); ++i)
        {
            std::vector<float> window_unit_positions = friendly_units.at(i).get_window_position(app_data.render_window);
            float un_norm_window_unit_positions[] = {
                window_unit_positions.at(0), window_unit_positions.at(1),
                window_unit_positions.at(2), window_unit_positions.at(3),
                window_unit_positions.at(4), window_unit_positions.at(5),
                window_unit_positions.at(6), window_unit_positions.at(7)};
            float norm_window_unit_positions[8];
            app_data.render_window.normalize_vb(un_norm_window_unit_positions, norm_window_unit_positions, 8);
            VertexBuffer friendly_unit_vb(norm_window_unit_positions, sizeof(norm_window_unit_positions));
            shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
            app_data.render_window.draw_object(vao, friendly_unit_vb, background_color_ib); // Since unit shapes are same shape as background we can just reuse background ib
        }

        // Render enemy units
        for (int i = 0; i < enemy_units.size(); ++i)
        {
            std::vector<float> window_unit_positions = enemy_units.at(i).get_window_position(app_data.render_window);
            float un_norm_window_unit_positions[] = {
                window_unit_positions.at(0), window_unit_positions.at(1),
                window_unit_positions.at(2), window_unit_positions.at(3),
                window_unit_positions.at(4), window_unit_positions.at(5),
                window_unit_positions.at(6), window_unit_positions.at(7)};
            float norm_window_unit_positions[8];
            app_data.render_window.normalize_vb(un_norm_window_unit_positions, norm_window_unit_positions, 8);
            VertexBuffer friendly_unit_vb(norm_window_unit_positions, sizeof(norm_window_unit_positions));
            shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
            app_data.render_window.draw_object(vao, friendly_unit_vb, background_color_ib); // Since unit shapes are same shape as background we can just reuse background ib
        }

        RenderImGui(app_data.game);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
