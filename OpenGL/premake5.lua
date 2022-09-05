project "OpenGL"
    kind "StaticLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}/lib"
   architecture "x86"
   ignoredefaultlibraries { "MSVCRT" }
   cppdialect "c++17"

    files {"src/impl/**.cpp", "src/impl/**.c", "src/intf/**.h", "src/intf/**.hpp", "../inipp/**.h"}
    includedirs {"../libs/include", "src/intf", "../inipp"}
    links {"opengl32"}

    filter "configurations:Debug"
      defines { "DEBUG" }
      architecture "x86"
      symbols "On"
   
   filter "configurations:Release"
      defines { "NDEBUG" }
      architecture "x86"
      optimize "On"