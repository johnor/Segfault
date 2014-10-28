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
        cppflags = "-MMD"
    }
}

solution "Sensor"
   configurations { "Debug", "Release" }
   platforms {"rpi", "native"}
   location "build"
   
   project "Sensor"
      kind "ConsoleApp"
      language "C++"

      files { "src/**.h", "src/**.cc"}

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         targetdir "bin/debug"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
         targetdir "bin/release" 

      configuration { "gmake" }
         buildoptions { "-std=c++0x" }
         
         includedirs { "lib/wiringPi" }
         libdirs { "lib/wiringPi" }
         links { "wiringPi" }
         


