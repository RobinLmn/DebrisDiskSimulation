#include "file_utility.hpp"

#include "engine/core/log.hpp"

#include <fstream>
#include <sstream>
#include <string>

#if defined(PLATFORM_WINDOWS)
    #include <windows.h>
    #include <commdlg.h>
#elif defined(PLATFORM_LINUX)
    #include <gtk/gtk.h>
#elif defined(PLATFORM_MACOS)
    #include <Cocoa/Cocoa.h>
#endif

#define MAGIC 0x53494D00
#define VERSION 1

namespace utils
{
	std::vector<app::orbit> load_orbits_from_file(const char* filename, const float fixed_radiation)
	{
		std::string line;
		std::ifstream file(filename);

		ASSERT(file.is_open(), return {}, "Unable to open orbit file.");

		std::vector<app::orbit> orbits;

		while (std::getline(file, line))
		{
			std::vector<float> Params;
			std::string currentParam;

			for (int i = 0; i < line.length(); i++)
			{
				const char c = line[i];

				if (c == ' ')
				{
					Params.push_back(std::stof(currentParam));
					currentParam = "";
				}
				else
				{
					currentParam.append(1, c);
				}
			}

			Params.push_back(std::stof(currentParam));

			app::orbit new_orbit;
			new_orbit.a = Params[0];
			new_orbit.e = Params[1];
			new_orbit.I = Params[2];
			new_orbit.Omega = Params[3];
			new_orbit.omega = Params[4];
			new_orbit.Beta = Params.size() > 5 ? Params[5] : fixed_radiation;

			orbits.push_back(new_orbit);
		}

		file.close();

		return orbits;
	}

	bool save_particles_to_file(const std::vector<app::particle>& particles, const std::string& filename)
	{
		std::ofstream file(filename, std::ios::binary);
		ASSERT(file.is_open(), return false, "Could not open file {0}", filename);

		const uint32_t magic = MAGIC;
		const uint32_t version = VERSION;
		const uint64_t particle_count = particles.size();

		file.write(reinterpret_cast<const char*>(&magic), sizeof(magic));
		file.write(reinterpret_cast<const char*>(&version), sizeof(version));
		file.write(reinterpret_cast<const char*>(&particle_count), sizeof(particle_count));
		file.write(reinterpret_cast<const char*>(particles.data()), particles.size() * sizeof(app::particle));

		return true;
	}

	std::vector<app::particle> load_particles_from_file(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file.is_open()) return {};

		uint32_t magic, version;
		file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
		ASSERT(magic == MAGIC, return {}, "File type not supported");

		file.read(reinterpret_cast<char*>(&version), sizeof(version));
		ASSERT(version == VERSION, return {}, "File version mismatch");

		uint64_t particle_count;
		file.read(reinterpret_cast<char*>(&particle_count), sizeof(particle_count));

		std::vector<app::particle> particles(particle_count);
		file.read(reinterpret_cast<char*>(particles.data()), particle_count * sizeof(app::particle));

		return particles;
	}

	std::string open_file_dialog(const char* initial_directory, const char* files_filter)
	{
#if defined(PLATFORM_WINDOWS)
        char filename[MAX_PATH] = {0};

        OPENFILENAMEA ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = GetActiveWindow();
        ofn.lpstrFilter = files_filter;
        ofn.lpstrFile = filename;
        ofn.nMaxFile = sizeof(filename);
        ofn.lpstrInitialDir = initial_directory;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn))
        {
            return filename;
        }
#elif defined(PLATFORM_LINUX)
        if (!gtk_init_check(nullptr, nullptr))
        {
            LOG_ERROR("Failed to initialize GTK");
            return {};
        }

        GtkWidget* dialog = gtk_file_chooser_dialog_new(
            "Open File",
            nullptr,
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Open", GTK_RESPONSE_ACCEPT,
            nullptr
        );

        if (initial_directory)
        {
            gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_directory);
        }

        if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        {
            char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            std::string result(filename);
            g_free(filename);
            gtk_widget_destroy(dialog);
            return result;
        }

        gtk_widget_destroy(dialog);
#elif defined(PLATFORM_MACOS)
        @autoreleasepool {
            NSOpenPanel* panel = [NSOpenPanel openPanel];
            [panel setCanChooseFiles:YES];
            [panel setCanChooseDirectories:NO];
            [panel setAllowsMultipleSelection:NO];

            if (initial_directory)
            {
                [panel setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:initial_directory]]];
            }

            if ([panel runModal] == NSModalResponseOK)
            {
                NSURL* url = [[panel URLs] firstObject];
                return [[url path] UTF8String];
            }
        }
#else
        LOG_ERROR("Platform not supported");
#endif

        return {};
	}

	std::string new_file_dialog(const char* initial_filename, const char* initial_directory, const char* files_filter)
	{
#if defined(PLATFORM_WINDOWS)
        char filename[MAX_PATH] = {0};
        strcpy_s(filename, initial_filename);

        OPENFILENAMEA ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = GetActiveWindow();
        ofn.lpstrFilter = files_filter;
        ofn.lpstrFile = filename;
        ofn.nMaxFile = sizeof(filename);
        ofn.lpstrInitialDir = initial_directory;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetSaveFileNameA(&ofn))
        {
            return filename;
        }
#elif defined(PLATFORM_LINUX)
        if (!gtk_init_check(nullptr, nullptr))
        {
            LOG_ERROR("Failed to initialize GTK");
            return {};
        }

        GtkWidget* dialog = gtk_file_chooser_dialog_new(
            "Save File",
            nullptr,
            GTK_FILE_CHOOSER_ACTION_SAVE,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Save", GTK_RESPONSE_ACCEPT,
            nullptr
        );

        if (initial_directory)
        {
            gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_directory);
        }

        if (initial_filename)
        {
            gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), initial_filename);
        }

        if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        {
            char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            std::string result(filename);
            g_free(filename);
            gtk_widget_destroy(dialog);
            return result;
        }

        gtk_widget_destroy(dialog);
#elif defined(PLATFORM_MACOS)
        @autoreleasepool {
            NSSavePanel* panel = [NSSavePanel savePanel];
            [panel setCanCreateDirectories:YES];

            if (initial_filename)
            {
                [panel setNameFieldStringValue:[NSString stringWithUTF8String:initial_filename]];
            }

            if (initial_directory)
            {
                [panel setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:initial_directory]]];
            }

            if ([panel runModal] == NSModalResponseOK)
            {
                NSURL* url = [panel URL];
                return [[url path] UTF8String];
            }
        }
#else
        LOG_ERROR("Platform not supported");
#endif

        return {};
	}
}
