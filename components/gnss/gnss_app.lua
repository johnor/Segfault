project "GnssApp"
   configuration {}

   kind "ConsoleApp"
   language "C++"

   files { "*.h", "*.cc"}
   includedirs { "src" }

   links { "Common" }

   if os.get() == "windows" then
      vpaths { ["*"] = "components/gnss/" }
   end

   -- Link wiringPi
   configuration { "not rpi" }
      links { "pthread", "rt", "m" }

   configuration { "rpi" }
      links { "pthread", "rt", "m" }
      
   
