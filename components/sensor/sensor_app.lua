project "SensorApp"
   configuration {}

   kind "ConsoleApp"
   language "C++"

   files { "*.h", "*.cc"}
   includedirs { "src" }

   links { "SensorLib" , "ServerLib", "Common" }

   if os.get() == "windows" then
      vpaths { ["*"] = "components/sensor/" }
   end

   -- Link wiringPi, remove and replace with real code
   configuration { "not rpi" }
      links { "wiringPi-x86" }

   configuration { "rpi" }
      links { "pthread", "wiringPi" }
