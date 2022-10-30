workspace "graphics-engine"
    location "build"
    architecture "x64"
    configurations {"Release", "Debug"} 

project "graphics-engine"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files {"include/**.h", "include/**.hpp", "src/**.cpp"}    

    includedirs {"libraries/*", "include"}
    libdirs "libraries/lib"
    links {"SDL2", "SDL2main"}

    filter "configurations:Release"
        defines "Release"
        optimize "Speed"
        
    filter "configurations:Debug"
        defines "DEBUG" 
        symbols "On" 