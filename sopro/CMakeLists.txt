OPTIX_add_sample_executable(sopro 
    src/sopro.cpp
    src/entrypoint.cu
    src/pinholeCamera.cu
    src/light.cu
    src/material.cu
    src/program1.cpp
    src/program2.cpp
    src/miss.cu
    include/program1.h
    include/program2.h
    include/sopro.h
    include/shadow.h
    include/material.h
    include/light.h
    
)
