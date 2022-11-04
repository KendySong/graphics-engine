workspace "graphics-engine"
    location "build"
    architecture "x64"
    configurations {"Release", "Debug"} 

project "graphics-engine"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files {"src/**.h", "src/**.hpp", "src/**.cpp", "libraries/include/ImGui/*.cpp"}    

    includedirs {"libraries/*"}
    libdirs "libraries/lib"
    links {"SDL2", "SDL2main"}

    filter "configurations:Release"
        defines "Release"
        optimize "Speed"
        
    filter "configurations:Debug"
        defines "DEBUG" 
        symbols "On" 