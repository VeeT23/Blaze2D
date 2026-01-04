#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <span>

namespace blaze
{

	struct AssetDescriptor {
		std::string name;
		std::string type;
		std::filesystem::path path;
		std::unordered_map<std::string, std::string> flags;
	};



	class Manifest
	{
	public:
		explicit Manifest(const std::filesystem::path& manifestPath);

		const AssetDescriptor& get(const std::string& name) const;
		std::span<const AssetDescriptor> getAll() const;
		std::span<const AssetDescriptor> getByType(const std::string& type) const;

	private:
		std::filesystem::path root;
		std::vector<AssetDescriptor> assets;
		std::unordered_map<std::string, size_t> index;
	};


} // namespace blaze