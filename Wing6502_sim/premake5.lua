project "Wing6502_sim"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x86"
   ignoredefaultlibraries { "MSVCRT" }
   libdirs {"../libs/GLFW/x86", "../libs/OpenAL/Win32"}
   cppdialect "c++17"

   links {"OpenGL", "Engine", "opengl32", "glfw3", "Imgui", "OpenAL32"}
   
   files { "src/include/**.h", "src/impl/**.cpp"}
   includedirs {"../Engine/src/intf", "../libs/include", "../Imgui/src/intf", "../OpenGL/src/intf",
        "src/include"
   }
   
   defines {"IMGUI_DISPLAY"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      architecture "x86"
      symbols "On"
   
   filter "configurations:Release"
      defines { "NDEBUG" }
      architecture "x86"
      optimize "On"