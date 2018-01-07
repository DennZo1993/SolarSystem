#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Engine.h"
#include "Exception.h"
#include "Shader.h"


int main() {
    try {
        TEngine engine(// Engine options
                       TEngineOptions(),
                       // Window options
                       TWindowOptions().Width(500).Height(500)
                                       .Caption("Solar System"));

        // Init core stuff.
        engine.Init();

        // Load and compile shaders.
        TShaderProgram shader;
        shader.LoadShader(GL_VERTEX_SHADER, "../../shaders/common.vert");
        shader.LoadShader(GL_FRAGMENT_SHADER, "../../shaders/common.frag");
        shader.LoadShader(GL_TESS_CONTROL_SHADER, "../../shaders/common.tc");
        shader.LoadShader(GL_TESS_EVALUATION_SHADER, "../../shaders/common.te");
        shader.Build();

        TCamera camera(500, 500);
        camera.MoveTo(glm::vec3(0.0f, 0.0f, 5.0f));

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        GLfloat vertices[] = {
             0.0f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0); 
        glBindVertexArray(0);

        glm::mat4 modelMatrix(1.0f);

        // Main loop.
        while (engine.Running()) {
            engine.BeginMainLoopIteration();

            shader.Use();
            // Update the uniform color
            GLfloat timeValue = glfwGetTime();
            GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
            GLint vertexColorLocation = glGetUniformLocation(shader.GetProgramID(), "vertexColor");
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

            GLint levelLocation = glGetUniformLocation(shader.GetProgramID(), "level");
            glUniform1f(levelLocation, 1.0);

            auto ModelMatrixLocation = glGetUniformLocation(shader.GetProgramID(), "model");
            glUniformMatrix4fv(ModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            auto ViewMatrixLocation = glGetUniformLocation(shader.GetProgramID(), "view");
            glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

            auto ProjectionMatrixLocation = glGetUniformLocation(shader.GetProgramID(), "projection");
            glUniformMatrix4fv(ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));

            // Draw the triangle
            glBindVertexArray(VAO);
            glDrawArrays(GL_PATCHES, 0, 3);
            glBindVertexArray(0);

            engine.EndMainLoopIteration();
        }
    } catch (const TShaderException& shaderException) {
        std::cout << "Shader exception caught!" << std::endl
                  << shaderException.what() << std::endl;
        return 1;
    } catch (const TEngineException& engineException) {
        std::cout << "Engine exception caught!" << std::endl
                  << engineException.what() << std::endl;

        return 1;
    }

    return 0;
}