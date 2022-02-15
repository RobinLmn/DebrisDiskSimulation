workspace "DebrisDisk"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Profile",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "DebrisDisk/ThirdParty/GLFW/include"
IncludeDir["glad"] = "DebrisDisk/ThirdParty/glad/include"
IncludeDir["spdlog"] = "DebrisDisk/ThirdParty/spdlog/include"
IncludeDir["glm"] = "TradescantiaEngine/ThirdParty/glm"
IncludeDir["tracy"] = "TradescantiaEngine/ThirdParty/tracy"
IncludeDir["stb_image"] = "TradescantiaEngine/ThirdParty/stb_image"

include "DebrisDisk/ThirdParty/GLFW"
include "DebrisDisk/ThirdParty/glad"
include "DebrisDisk/ThirdParty/tracy"

project "DebrisDisk"
	location "DebrisDisk"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"DebrisDisk/Source",
		"DebrisDisk/ThirdParty",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.tracy}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"glad",
		"Tracy"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines {"DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {"RELEASE"}
		runtime "Release"
		optimize "on"

	filter "configurations:Profile"
		defines {"RELEASE", "PROFILE", "TRACY_ENABLE"}
		runtime "Release"
		optimize "on"
		symbols "on"
