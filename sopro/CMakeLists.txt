OPTIX_add_sample_executable(sopro 
	#####Source Directories    	
	#Scene
	src/sopro.cpp
	src/program1.cpp
	src/program2.cpp
	src/program3.cpp
	src/sceneHandle.cpp
	src/scene.cpp
	src/sceneobject.cpp
	src/display.cpp	
	
	#GUI/AntTweakBar
        src/ATB/antTBar.cpp
        src/ATB/antTBar_material.cpp
        src/ATB/antTBar_geometry.cpp
        src/ATB/antTBar_light.cpp

	#Materials
	src/material/baseMaterial.cpp
	src/material/lambertMaterial.cpp
	src/material/phongMaterial.cpp
	src/material/glassMaterial.cpp
	src/material/disneyMaterial.cpp
	src/material/blinnPhongMaterial.cpp
	src/material/wardMaterial.cpp
	src/material/cookTorranceMaterial.cpp
	src/material/ashikhminShirleyMaterial.cpp

	#Material Cuda/Raytracing
	src/pinholeCamera.cu
	src/miss.cu
	src/entrypoint.cu
	src/material/brdf/lambertMaterial.cu
	src/material/brdf/phongMaterial.cu
	src/material/brdf/glassMaterial.cu
	src/material/brdf/disneyMaterial.cu
	src/material/brdf/blinnPhongMaterial.cu
	src/material/brdf/wardMaterial.cu
	src/material/brdf/ashikhminShirleyMaterial.cu
	src/material/brdf/cookTorranceMaterial.cu

	#Geometry
	src/geometry/baseGeometry.cpp
	src/geometry/basePlane.cpp
	src/geometry/areaPlane.cpp
	src/geometry/infinitePlane.cpp
	src/geometry/mesh.cpp
	src/geometry/meshLoader.cpp
	src/geometry/sphere.cpp

	#Geometry Cuda/Raytracing
	src/geometry/infinitePlane.cu
	src/geometry/areaPlane.cu
	src/geometry/sphere.cu
	src/geometry/mesh.cu

	#####Include Directories
	#Scene
	include/sopro.h
	include/program1.h
	include/program2.h
	include/program3.h
	include/sceneobject.h
	include/sceneHandle.h
	include/scene.h
	include/display.h

	#Data
	include/structs.h

	#GUI/AntTweakBar
        include/ATB/antTBar.h
        include/ATB/antTBar_material.h
        include/ATB/antTBar_geometry.h
        include/ATB/antTBar_light.h

	#Material
	include/material/baseMaterial.h
	include/material/lambertMaterial.h
	include/material/phongMaterial.h
	include/material/glassMaterial.h
	include/material/disneyMaterial.h
	include/material/blinnPhongMaterial.h
	include/material/wardMaterial.h
	include/material/cookTorranceMaterial.h
	include/material/ashikhminShirleyMaterial.h

	#Geometry
	include/geometry/baseGeometry.h
	include/geometry/basePlane.h
	include/geometry/areaPlane.h
	include/geometry/infinitePlane.h
	include/geometry/mesh.h
	include/geometry/sphere.h
	include/geometry/meshLoader.h 
)
