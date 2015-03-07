-- create Makefile with "./premake4 --platform=rpi gmake" or "./premake4 gmake"
function newplatform(plf)
    local name = plf.name
    local description = plf.description
 
    -- Register new platform
    premake.platforms[name] = {
        cfgsuffix = "_"..name,
        iscrosscompiler = true
    }
 
    -- Allow use of new platform in --platfroms
    table.insert(premake.option.list["platform"].allowed, { name, description })
    table.insert(premake.fields.platforms.allowed, name)
 
    -- Add compiler support
    -- gcc
    premake.gcc.platforms[name] = plf.gcc
    --other compilers (?)
end

newplatform {
    name = "rpi",
    description = "Raspberry Pi",
    gcc = {
        cc = "arm-linux-gnueabihf-gcc",
        cxx = "arm-linux-gnueabihf-g++",
        ar = "arm-linux-gnueabihf-ar",
        cppflags = "-MMD"
    }
}

if _ACTION == 'clean' then
    os.rmdir('./build')
    os.rmdir('./bin')
end

solution "Sensor"
   configurations { "Debug", "Release" }
   platforms { "rpi", "native" }
   location "build"
   
   -- set working directory for visual studio projects
   if os.get() == "windows" then
     debugdir "."
   end

   -- prevent "warning LNK4098: defaultlib 'MSVCRTD' conflicts with use of other libs; use /NODEFAULTLIB:library"
   configuration { "vs*" }
      buildoptions { "/MDd" }
   
   project "SensorApp"
      kind "ConsoleApp"
      language "C++"
      
      files { "components/sensor/src/**.h", "components/sensor/src/**.cc"}
      includedirs { "lib", "src" , "lib/asio" }
      
      -- defines for asio
      defines { "ASIO_STANDALONE" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
         targetdir "bin/debug"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings" }
         targetdir "bin/release" 
         
      configuration "vs*"
         defines { "_WIN32_WINNT=0x0601" }
         if os.get() == "windows" then
            vpaths { ["*"] = "components/sensor/src" }
         end
         
         buildoptions
         {
            --'GetVersionExA': was declared deprecated
            "/wd4996"
         }
   
      -- compiler flags
      configuration { "gmake" }
        buildoptions { "-std=c++0x" }

      configuration { "gmake" , "rpi"}
         buildoptions { "-mcpu=arm1176jzf-s -mthumb -mtune=arm1176jzf-s -mfpu=vfp -marm -march=armv6k -mfloat-abi=hard" }
      
      -- Link wiringPi
      configuration { "not rpi" } 
         links { "wiringPi-x86" }

      configuration { "rpi" }
         libdirs { "lib/wiringPi/lib-rpi" }
         links { "pthread", "wiringPi" }
   
   -- wiringRpi for x86
   project "wiringPi-x86"
      kind "StaticLib"
      language "C"
      targetdir "build/libs"
      
      includedirs { "lib" }
      files { "lib/wiringPi/**.h", "lib/wiringPi/src-x86/**.c"}
      if os.get() == "windows" then
         vpaths { ["*"] = "lib/wiringPi" }
      end

