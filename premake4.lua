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

   includedirs { "lib", "lib/asio", ".", "components" }

   -- set working directory for visual studio projects
   if os.get() == "windows" then
     debugdir "."
   end

   -- defines for asio
   defines { "ASIO_STANDALONE" }

   -- debug release config
   configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols", "ExtraWarnings" }
      targetdir "bin/debug"

   configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize", "ExtraWarnings" }
      targetdir "bin/release"

   -- specific compiler flags
   configuration { "vs*" }
      -- remove warning from asio
      defines { "_WIN32_WINNT=0x0601" }

      buildoptions
      {
         -- prevent "warning LNK4098: defaultlib 'MSVCRTD' conflicts with use of other libs; use /NODEFAULTLIB:library"
         "/MDd",
         --'GetVersionExA': was declared deprecated
         "/wd4996"
      }

   -- compiler flags
   configuration { "gmake" }
      buildoptions { "-std=c++0x" }

   configuration { "gmake" , "rpi"}
      buildoptions { "-mcpu=arm1176jzf-s -mthumb -mtune=arm1176jzf-s -mfpu=vfp -marm -march=armv6k -mfloat-abi=hard" }

   configuration { "rpi" }
      libdirs { "lib/wiringPi/lib-rpi" }

    dofile "components/sensor/sensor_app.lua"
    dofile "components/sensor/sensor_lib.lua"

    dofile "components/common/common.lua"

    dofile "components/server/server_lib.lua"

    dofile "lib/wiringPi/wiringPi.lua"

