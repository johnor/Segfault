project "ServerLib"
   configuration {}

   kind "StaticLib"
   language "C++"

   files { "src/**.h", "src/**.cc"}
   includedirs { "src" }

   links { "Common" }

   if os.get() == "windows" then
      vpaths { ["*"] = "components/server/src" }
   end

   configuration { "rpi" }
      links { "pthread" }
