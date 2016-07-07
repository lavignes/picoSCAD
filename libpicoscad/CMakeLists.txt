set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror \
    -Wno-unused-result -Wno-unused-parameter -Wno-unused-function \
    -Wno-missing-field-initializers -Wno-missing-braces -mavx")
set(CMAKE_C_STANDARD 11)

set(HEADERS
        include/picoscad/porting.h

        include/picoscad/math/math.h
        include/picoscad/math/4f.h
        include/picoscad/math/4d.h
        include/picoscad/math/mat4f.h
        include/picoscad/math/mat4d.h
        include/picoscad/math/scalar/4f.h
        include/picoscad/math/simd/4f.h
        include/picoscad/math/scalar/4d.h
        include/picoscad/math/simd/4d.h

        include/picoscad/cg/vertex.h
        include/picoscad/cg/mesh.h
        )

set(SOURCES
        src/picoscad.c

        src/cg/mesh.c
        src/cg/vertex.c
        )

add_library(libpicoscad ${HEADERS} ${SOURCES})
set_target_properties(libpicoscad PROPERTIES OUTPUT_NAME picoscad)
target_include_directories(libpicoscad PUBLIC include)
target_link_libraries(libpicoscad m)
