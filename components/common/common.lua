project "Common"
   configuration {}

   kind "StaticLib"
   language "C++"
   
   files { "src/**.h", "src/**.cc"}
   includedirs { "src" }
   
   if os.get() == "windows" then
      vpaths { ["*"] = "components/common/src" }
   end
