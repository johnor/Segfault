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
   
   -- prevent "warning LNK4098: defaultlib 'MSVCRTD' conflicts with use of other libs; use /NODEFAULTLIB:library"
   configuration { "Debug", "vs*" }
      buildoptions { "/MDd" }
   
   project "SensorApp"
      kind "ConsoleApp"
      language "C++"
      
      files { "src/**.h", "src/**.cc"}
      includedirs { "lib", "src" }
      vpaths { ["*"] = "src" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
         targetdir "bin/debug"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings" }
         targetdir "bin/release" 
   
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
         links { "wiringPi" }
   
   -- wiringRpi for x86
   project "wiringPi-x86"
      kind "StaticLib"
      language "C"
      targetdir "build/libs"
      
      includedirs { "lib" }
      files { "lib/wiringPi/**.h", "lib/wiringPi/src-x86/**.c"}
      vpaths { ["*"] = "lib/wiringPi" }

