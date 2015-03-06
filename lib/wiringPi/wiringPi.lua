project "wiringPi-x86"
   kind "StaticLib"
   language "C"
   
   includedirs { "lib" }
   files { "**.h", "src-x86/**.c"}
   if os.get() == "windows" then
      vpaths { ["*"] = "lib/wiringPi" }
   end
