#include "PCH.h"
#include "DataTable.h"

std::unordered_map<int, CropData> DataTable::s_crops;
std::unordered_map<std::string, ObjectInfo> DataTable::s_objects;

void DataTable::Init()
{
	LoadCrops("Data/crops.csv");
	LoadObjects("Data/object_table.csv");
}

void DataTable::LoadCrops(const std::string& path)
{
	std::ifstream file(path);
	std::string line;

	for (int i = 0; i < 5; i++)
		std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		CropData data;
		std::string token;

		std::getline(ss, token, ','); data.id = static_cast<ECropID>(std::stoi(token));
		std::getline(ss, data.name, ',');
		std::getline(ss, token, ','); data.seedPrice = std::stoi(token);
		std::getline(ss, token, ','); data.sellPrice = std::stoi(token);

		for (int i = 0; i < 4; i++)
		{
			std::getline(file, line);
			std::stringstream ss2(line);

			std::getline(ss2, data.levels[i].model, ',');
			std::getline(ss2, token, ','); data.levels[i].waterRequired = std::stof(token);
			std::getline(ss2, token, ','); data.levels[i].timeRequired = std::stof(token);
		}

		s_crops[(int)data.id] = data;
	}
}

const CropData* DataTable::GetCrop(ECropID  id) { return &s_crops[(int)id]; }

void DataTable::LoadObjects(const std::string& path)
{
	std::ifstream file(path);
	std::string line;

	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string type, modelPath, texturePath;

		std::getline(ss, type, ',');
		std::getline(ss, modelPath, ',');
		std::getline(ss, texturePath, ',');

		ObjectInfo info;
		info.modelPath = modelPath;
		info.texturePath = texturePath;

		s_objects[type] = info;
	}
}

const ObjectInfo* DataTable::GetObjectInfo(const std::string& type)
{
	auto it = s_objects.find(type);
	if (it == s_objects.end())
		return nullptr;

	return &it->second;
}