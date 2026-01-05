#include "Blaze2D/util/Manifest.h"
#include <fstream>
#include <stdexcept>

namespace blaze
{

    static inline std::string trim(std::string s) // Used by parse_manifest_line()
    {
        auto not_space = [](unsigned char c) { return !std::isspace(c); };

        s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
        s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
        return s;
    }

    /**
 * @brief Parse a single manifest line into an AssetDescriptor.
 *
 * Expected format:
 *   type | name | path/to/file | FLAG | KEY = VALUE | BOOLEAN_FLAG = true
 *
 * Rules:
 * - '|' is the field delimiter
 * - First three fields are required: type, name, path
 * - Remaining fields are optional flags
 * - Flags may be:
 *     - Standalone (treated as key=true)
 *     - Key/value pairs separated by '='
 *
 * This function performs no asset-type logic.
 * All values are preserved as strings and interpreted later by loaders.
 *
 * @throws std::runtime_error if the line is malformed
 */
    AssetDescriptor parse_manifest_line(const std::string& line)
    {
        /*
            Split the line into '|' delimited segments.

            This produces a flat list of tokens that will later be interpreted
            by position:
              [0] = type
              [1] = name
              [2] = path
              [3+] = flags
        */
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, '|')) {
            parts.push_back(trim(segment));
        }

        /*
            Validate the minimum structure.

            A manifest line without at least:
              type | name | path
            is considered invalid and cannot be meaningfully interpreted.
        */
        if (parts.size() < 3) {
            throw std::runtime_error(
                "Invalid manifest line: expected at least type, name, and path"
            );
        }

        /*
            Populate the required AssetDescriptor fields.

            At this stage:
            - 'type' represents semantic intent (sprite, audio, etc.)
            - 'name' is a human-readable identifier
            - 'path' is relative to the manifest root
        */
        AssetDescriptor desc;
        desc.type = parts[0];
        desc.name = parts[1];
        desc.path = std::filesystem::path(parts[2]);

        /*
            Parse optional flags.

            Flags are intentionally stored as string key/value pairs.
            Interpretation (booleans, numbers, enums) is deferred to the loader.

            Supported forms:
              FLAG            -> FLAG = "true"
              KEY = VALUE     -> KEY = VALUE
        */
        for (size_t i = 3; i < parts.size(); ++i) {
            const std::string& flag = parts[i];

            auto eq = flag.find('=');
            if (eq == std::string::npos) {
                // Standalone flag: presence implies true
                desc.flags.emplace(trim(flag), "true");
            }
            else {
                std::string key = trim(flag.substr(0, eq));
                std::string value = trim(flag.substr(eq + 1));
                desc.flags.emplace(std::move(key), std::move(value));
            }
        }

        /*
            Return a fully populated, type-erased asset description.

            At this point, the descriptor is purely declarative and
            contains no engine-specific behavior.
        */
        return desc;
    }

    /**
 * @brief Load and parse a manifest file.
 *
 * The constructor:
 * - Verifies the manifest file exists and is readable
 * - Parses the file line-by-line
 * - Converts each valid line into an AssetDescriptor
 * - Builds a name-to-index lookup table
 *
 * Parsing rules:
 * - Empty lines, comment lines, and segment lines (a continuous series of hyphens) are ignored
 * - Each non-empty line must conform to the manifest grammar
 * 
 * @throws std::runtime_error if the file cannot be opened,
 *         if a line is malformed, or if duplicate asset names are found.
 */
    Manifest::Manifest(const std::filesystem::path& manifestPath)
        : root(manifestPath.parent_path())
    {
        /*
            Validate that the manifest path exists.

            This check is performed before attempting to open the file
            to produce a clearer error message.
        */
        if (!std::filesystem::exists(manifestPath)) {
            throw std::runtime_error(
                "Manifest file does not exist: " + manifestPath.string()
            );
        }

        /*
            Open the manifest file for reading.
        */
        std::ifstream file(manifestPath);
        if (!file.is_open()) {
            throw std::runtime_error(
                "Failed to open manifest file: " + manifestPath.string()
            );
        }

        //TODO: Add json support

        std::string line;
        std::size_t lineNumber = 0;

        /*
            Parse the manifest line-by-line.

            Each valid line is transformed into an AssetDescriptor and
            appended to internal storage.
        */
        while (std::getline(file, line)) {
            ++lineNumber;

            // Skip empty or whitespace-only lines
            if (std::all_of(line.begin(), line.end(),
                [](unsigned char c) { return std::isspace(c); })) {
                continue;
            }

            // Skip comment lines (optional but recommended)
            if (line.starts_with('#')) {
                continue;
            }

            // Skip segment lines 
            if (line.starts_with('-')) {
                continue;
            }


            AssetDescriptor desc = parse_manifest_line(line);

            /*
                Enforce uniqueness of asset names.

                Duplicate names would make lookup ambiguous and indicate
                an authoring error in the manifest.
            */
            auto [it, inserted] =
                index.emplace(desc.name, assets.size());

            if (!inserted) {
                throw std::runtime_error(
                    "Duplicate asset name '" + desc.name +
                    "' at line " + std::to_string(lineNumber)
                );
            }

            assets.push_back(std::move(desc));
        }
    }


    const AssetDescriptor& Manifest::get(const std::string& name) const
    {
        auto it = index.find(name);
        if (it == index.end()) {
            throw std::out_of_range("Asset not found in manifest: " + name);
        }

        return assets[it->second];
    }

    std::span<const AssetDescriptor> Manifest::getAll() const
    {
        return assets;
    }

    std::span<const AssetDescriptor> Manifest::getByType(const std::string& type) const
    {
        /*
            NOTE:
            This returns a temporary filtered view.
        */

        static thread_local std::vector<const AssetDescriptor*> scratch;
        scratch.clear();

        for (const auto& asset : assets) {
            if (asset.type == type) {
                scratch.push_back(&asset);
            }
        }

        // Convert pointer list to span-like access
        // Caller should treat this as temporary
        return {
            reinterpret_cast<const AssetDescriptor*>(scratch.data()),
            scratch.size()
        };
    }

} // namespace blaze