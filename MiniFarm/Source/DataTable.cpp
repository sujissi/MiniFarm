#include "PCH.h"
#include "DataTable.h"

std::unordered_map<int, CropData> DataTable::s_crops;

void DataTable::Init()
{
	LoadCrops("Data/crops.csv");
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
