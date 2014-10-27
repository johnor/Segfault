solution "Sensor"
   configurations { "Debug", "Release" }
   location "build"

   project "Sensor"
      kind "ConsoleApp"
      language "C++"
      
      files { "**.h", "**.cc"}

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         targetdir "bin/debug"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
         targetdir "bin/release" 

      configuration { "linux", "gmake" }
         buildoptions { "-std=c++0x" }

