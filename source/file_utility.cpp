#include "file_utility.hpp"

#include "log.hpp"

#include <fstream>
#include <sstream>
#include <string>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <commdlg.h>
#endif

#define MAGIC 0x53494D00
#define VERSION 1

namespace sim
{
    std::vector<orbit> load_orbits_from_file(const char* filename, const float fixed_radiation)
	{
		std::string line;
		std::ifstream file(filename);

		ASSERT(file.is_open(), return {}, "Unable to open orbit file.");

		std::vector<orbit> orbits;

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

			orbit new_orbit;
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

    bool save_particles_to_file(const std::vector<particle>& particles, const std::string& filename)
    {
        std::ofstream file(filename, std::ios::binary);
        ASSERT( file.is_open(),  return false, "Could not open file {0}", filename);

        const uint32_t magic = MAGIC;
        const uint32_t version = VERSION;
        const uint64_t particle_count = particles.size();

        file.write(reinterpret_cast<const char*>(&magic), sizeof(magic));
        file.write(reinterpret_cast<const char*>(&version), sizeof(version));
        file.write(reinterpret_cast<const char*>(&particle_count), sizeof(particle_count));
        file.write(reinterpret_cast<const char*>(particles.data()), particles.size() * sizeof(particle));

        return true;
    }

    std::vector<particle> load_particles_from_file(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return {};

        uint32_t magic, version;
        file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        ASSERT(magic == MAGIC, return {}, "File type not supported");

        file.read(reinterpret_cast<char*>(&version), sizeof(version));
        ASSERT( version == VERSION, return {}, "File version mismatch");

        uint64_t particle_count;
        file.read(reinterpret_cast<char*>(&particle_count), sizeof(particle_count));

        std::vector<particle> particles(particle_count);
        file.read(reinterpret_cast<char*>(particles.data()), particle_count * sizeof(particle));

        return particles;
    }

	std::string open_file_dialog(const char* initial_directory, const char* files_filter)
	{
#ifdef PLATFORM_WINDOWS
		char filename[MAX_PATH];

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
#else
		LOG_ERROR("Platform not supported");
#endif

		return {};
	}

	std::string new_file_dialog(const char* initial_filename, const char* initial_directory, const char* files_filter)
	{
#ifdef PLATFORM_WINDOWS
		char filename[MAX_PATH];
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
#else
		LOG_ERROR("Platform not supported");
#endif

		return {};
	}
}
