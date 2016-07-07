#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <picoscad/math/mat4f.h>

static const char* vertex_shader_text =
                "uniform mat4 m;\n"
                "uniform mat4 v;\n"
                "uniform mat4 proj;\n"
                "attribute vec4 pos;\n"
                "void main() {\n"
                "    mat4 mv = v * m;\n"
                "    gl_Position = proj * mv * pos;\n"
                "}\n";
static const char* fragment_shader_text =
                "uniform vec4 color;\n"
                "void main() {\n"
                "    gl_FragColor = color;\n"
                "}\n";

int main(int argc, char **argv) {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow *window = glfwCreateWindow(640, 480, "picoSCAD", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();
    glfwSwapInterval(1);
    glClearColor(0.95f, 0.95f, 0.90f, 1.0f);
    glLineWidth(2.0f);

    Ps4f verticies[] = {
            ps_4f(-0.6f, -0.4f, 0.0f, 1.0f),
            ps_4f(0.6f, -0.4f, 0.0f, 1.0f),
            ps_4f(-0.4f, 0.3f, 0.0f, 1.0f),
            ps_4f(0.0f, 0.6f, 0.0f, 1.0f),
    };

    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint m_location, v_location, proj_location, pos_location, color_location;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    m_location = glGetUniformLocation(program, "m");
    v_location = glGetUniformLocation(program, "v");
    proj_location = glGetUniformLocation(program, "proj");
    color_location = glGetUniformLocation(program, "color");
    pos_location = glGetAttribLocation(program, "pos");

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glEnableVertexAttribArray((GLuint)pos_location);
    glVertexAttribPointer((GLuint)pos_location, 4, GL_FLOAT, GL_FALSE, sizeof(Ps4f), NULL);

    Ps4f color = ps_4f(0.0f, 0.0f, 0.0f, 1.0f);
    Ps4f cam_pos = ps_4f_zero();
    Ps4f cam_angles = ps_4f_zero();
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspect = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        PsMat4f m, proj;
        ps_mat4f_identity(&m);
        ps_mat4f_ortho(&proj, -aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f);

        PsMat4f rotx, roty, rotz;
        ps_mat4f_rot_x(&rotx, ps_4f_x(cam_angles));
        ps_mat4f_rot_y(&roty, ps_4f_y(cam_angles) - PS_MATH_TAU);
        ps_mat4f_rot_z(&rotz, ps_4f_z(cam_angles));
        PsMat4f trans;
        ps_mat4f_translation(&trans, -ps_4f_x(cam_pos), -ps_4f_y(cam_pos), -ps_4f_z(cam_pos));

        PsMat4f view;
        ps_mat4f_mul(&roty, &rotx, &view);
        ps_mat4f_mul(&view, &rotz, &view);
        ps_mat4f_mul(&trans, &view, &view);

        glUseProgram(program);
        glUniformMatrix4fv(m_location, 1, GL_FALSE, (const GLfloat *)&m);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, (const GLfloat *)&view);
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, (const GLfloat *)&proj);
        glUniform4fv(color_location, 1, (const GLfloat *)&color);
        glDrawArrays(GL_LINE_LOOP, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}