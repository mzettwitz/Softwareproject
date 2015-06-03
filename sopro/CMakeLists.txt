OPTIX_add_sample_executable(sopro 
    
	src/sopro.cpp
	src/program1.cpp
	src/program2.cpp
	src/program3.cpp
	src/simpleScene.cpp
	src/baseMaterial.cpp
	src/plainColorMaterial.cpp
	src/display.cpp	

	src/pinholeCamera.cu
	src/miss.cu
	src/entrypoint.cu
	src/plainColorMaterial.cu
	
	src/geometry/baseGeometry.cpp
	src/geometry/basePlane.cpp
	src/geometry/areaPlane.cpp
	src/geometry/infinitePlane.cpp
	src/geometry/mesh.cpp
	src/geometry/sphere.cpp

	src/geometry/infinitePlane.cu
	src/geometry/areaPlane.cu
	src/geometry/sphere.cu

	include/sopro.h
	include/program1.h
	include/program2.h
	include/program3.h
	include/simpleScene.h
	include/structs.h
	include/baseMaterial.h
	include/light.h
	include/plainColorMaterial.h
	include/display.h	

	include/geometry/baseGeometry.h
	include/geometry/basePlane.h
	include/geometry/areaPlane.h
	include/geometry/infinitePlane.h
	include/geometry/mesh.h
	include/geometry/sphere.h 
)
