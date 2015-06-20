OPTIX_add_sample_executable(sopro 
	#####Source Directories    	
	#Scene
	src/sopro.cpp
	src/program1.cpp
	src/program2.cpp
	src/program3.cpp
	src/scene.cpp
	src/sceneobject.cpp
	src/display.cpp	
	
	#GUI/AntTweakBar
        src/antTBar.cpp

	#Materials
	src/material/baseMaterial.cpp
	src/material/lambertMaterial.cpp
	src/material/phongMaterial.cpp

	#Material Cuda/Raytracing
	src/pinholeCamera.cu
	src/miss.cu
	src/entrypoint.cu
	src/material/lambertMaterial.cu
	src/material/phongMaterial.cu
	
	#Geometry
	src/geometry/baseGeometry.cpp
	src/geometry/basePlane.cpp
	src/geometry/areaPlane.cpp
	src/geometry/infinitePlane.cpp
	src/geometry/mesh.cpp
	src/geometry/sphere.cpp

	#Geometry Cuda/Raytracing
	src/geometry/infinitePlane.cu
	src/geometry/areaPlane.cu
	src/geometry/sphere.cu

	#####Include Directories
	#Scene
	include/sopro.h
	include/program1.h
	include/program2.h
	include/program3.h
	include/sceneobject.h
	include/scene.h
	include/display.h

	#Data
	include/structs.h

	#GUI/AntTweakBar
	include/antTBar.h

	#Material
	include/material/baseMaterial.h
	include/material/lambertMaterial.h
	include/material/phongMaterial.h

	#Geometry
	include/geometry/baseGeometry.h
	include/geometry/basePlane.h
	include/geometry/areaPlane.h
	include/geometry/infinitePlane.h
	include/geometry/mesh.h
	include/geometry/sphere.h 
)
