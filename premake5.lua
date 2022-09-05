workspace "Nutmeg"
   configurations { "Debug", "Release"}

project "Engine"
   kind "StaticLib"
   language "C++"
   targetdir "Engine/bin/%{cfg.buildcfg}"
   cppdialect "c++17"
   
   staticruntime "off"

   files { "Engine/src/intf/**.h", "Engine/src/impl/**.cpp", "Engine/src/impl/**.c"}
   
   includedirs {"Engine/src/intf", "libs/include", "Engine/src/intf/imgui/", "imgui/src/intf", "OpenGL/src/intf"}
   

   links {"OpenGL", "opengl32", "glfw3", "Imgui", "OpenAL32"}

   ignoredefaultlibraries { "MSVCRT" }


   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      architecture "x86"
      libdirs {"./libs/GLFW", "./libs/OpenAL/Win32"}

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      architecture "x86"
      libdirs {"./libs/GLFW/x86", "./libs/OpenAL/Win32"}



project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   targetdir "Sandbox/bin/%{cfg.buildcfg}"
   architecture "x86"
   ignoredefaultlibraries { "MSVCRT" }
   libdirs {"./libs/GLFW/x86", "./libs/OpenAL/Win32"}
   cppdialect "c++17"

   links {"OpenGL", "Engine", "opengl32", "glfw3", "Imgui", "OpenAL32"}
   
   files { "Sandbox/src/intf/**.h", "Sandbox/src/impl/**.cpp"}
   includedirs {"Engine/src/intf", "libs/include", "Imgui/src/intf", "OpenGL/src/intf"}
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      architecture "x86"
      symbols "On"
   
   filter "configurations:Release"
      defines { "NDEBUG" }
      architecture "x86"
      optimize "On"





include("OpenGL")
include("imgui")

include("wing6502_sim")