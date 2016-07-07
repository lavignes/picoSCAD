set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror \
    -Wno-unused-result -Wno-unused-parameter -Wno-unused-function \
    -Wno-missing-field-initializers -Wno-missing-braces -mavx")
set(CMAKE_C_STANDARD 11)

set(HEADERS
        )

set(SOURCES
        src/picoscad.c
        )

add_executable(picoscad ${HEADERS} ${SOURCES})

find_package(glfw3 REQUIRED)
# Grab OpenGL since the glfw 3.1 package script doesn't automatically link it
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(picoscad libpicoscad ${OPENGL_LIBRARY} glfw GLEW)
