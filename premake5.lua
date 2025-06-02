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
	kind "WindowedApp"
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

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PLATFORM_WINDOWS",
		}
		ignoredefaultlibraries 
		{ 
			"libcmt.lib"
		}

	filter "system:linux"
		defines
		{
			"PLATFORM_LINUX",
		}
		links
		{
			"X11",
			"dl",
			"pthread",
			"gtk-3",
			"gdk-3",
			"gobject-2.0",
			"glib-2.0"
		}
		buildoptions
		{
			"`pkg-config --cflags gtk+-3.0`"
		}
		linkoptions
		{
			"`pkg-config --libs gtk+-3.0`"
		}

	filter "system:macosx"
		defines
		{
			"PLATFORM_MACOS",
		}
		links
		{
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework",
			"AppKit.framework"
		}
		buildoptions
		{
			"-fobjc-arc",
			"-x", "objective-c++"
		}
		
		sysincludedirs
		{
			"thirdparty/GLFW/include",
			"thirdparty/glad/include",
			"thirdparty/spdlog/include",
			"thirdparty/glm",
			"thirdparty/imgui",
			"thirdparty/stb_image",
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
