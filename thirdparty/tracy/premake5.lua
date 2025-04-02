project "tracy"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"TracyClient.cpp",
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Profile"
		defines {"TRACY_ENABLE"}
		runtime "Release"
		optimize "on"
		symbols "on"
