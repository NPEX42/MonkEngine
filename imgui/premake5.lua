project "Imgui"
   kind "StaticLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x86"
   ignoredefaultlibraries { "MSVCRT" }
   libdirs {"../libs/GLFW/x86"}
   cppdialect "c++17"

   links {"opengl32", "glfw3", "OpenGL"}
   
   files { "src/intf/**.h", "src/impl/**.cpp"}
   includedirs {"src/intf", "../libs/include", "../OpenGL/src/intf"}
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      architecture "x86"
      symbols "On"
   
   filter "configurations:Release"
      defines { "NDEBUG" }
      architecture "x86"
      optimize "On"