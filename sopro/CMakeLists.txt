OPTIX_add_sample_executable(sopro 
    src/sopro.cpp
    src/entrypoint.cu
    src/pinholeCamera.cu
    src/light.cu
    src/material.cu
    src/shadow.cu

    include/shadow.h
)
