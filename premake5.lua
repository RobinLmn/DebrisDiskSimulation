workspace "debris_disk_simulation"
	architecture "x64"
	
	configurations
	{
		"debug",
		"release",
		"profile",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "thirdparty/GLFW"
include "thirdparty/glad"
include "thirdparty/tracy"
include "thirdparty/ImGui"

project "debris_disk_simulation"
	location ""
	language "c++"
	cppdialect "c++latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"source/**.h",
		"source/**.cpp",
		"source/**.hpp",
	}

	includedirs
	{
		"source",
		"thirdparty/GLFW/include",
		"thirdparty/glad/include",
		"thirdparty/spdlog/include",
		"thirdparty/glm",
		"thirdparty/imgui",
		"thirdparty/stb_image",
		"thirdparty/tracy",
	}

	links
	{
		"GLFW",
		"glad",
		"Tracy",
		"ImGui"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	ignoredefaultlibraries 
	{ 
		"libcmt.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		kind "WindowedApp"

		defines
		{
			"PLATFORM_WINDOWS",
		}

		removefiles
		{
			"source/platforms/macos/**.cpp",
			"source/platforms/linux/**.cpp",
		}

	filter "system:macosx"
		kind "ConsoleApp"
		
		defines
		{
			"PLATFORM_MACOS",
		}

		removefiles
		{
			"source/platforms/windows/**.cpp",
			"source/platforms/linux/**.cpp",
		}

	filter "system:linux"
		kind "ConsoleApp"

		defines
		{
			"PLATFORM_LINUX",
		}

		removefiles
		{
			"source/platforms/windows/**.cpp",
			"source/platforms/macos/**.cpp",
		}

	filter "configurations:debug"
		defines {"DEBUG"}
		runtime "debug"
		symbols "on"
	
	filter "configurations:release"
		defines {"RELEASE"}
		runtime "release"
		optimize "on"

	filter "configurations:profile"
		defines {"RELEASE", "PROFILE", "TRACY_ENABLE"}
		runtime "release"
		optimize "on"
		symbols "on"
