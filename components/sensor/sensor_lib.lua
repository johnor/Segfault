project "SensorLib"
   configuration {}
   
   kind "StaticLib"
   language "C++"
   
   files { "src/**.h", "src/**.cc"}
   includedirs { "src" }
   
   if os.get() == "windows" then
      vpaths { ["*"] = "components/sensor/src" }
   end

   -- Link wiringPi
   configuration { "not rpi" } 
      links { "wiringPi-x86" }

   configuration { "rpi" }
      links { "pthread", "wiringPi" }
