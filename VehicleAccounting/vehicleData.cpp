#include "vehicleData.h"

enum
{
	ID = 1,
	TYPE,
	BRAND,
	MODEL,
	YEAR,
	WEIGHT
};

pugi::xml_document doc;

//VehicleData::VehicleData(string fileName)
//{
//	if (!(doc.load_file(fileName.c_str())))
//		cout << "Файл не найден" << endl;
//}

void VehicleData::generateId()
{
	pugi::xpath_node xpathNode = doc.select_node("VehiclesData");
	pugi::xml_node selectedNode = xpathNode.node();
	pugi::xml_node selectedNode1 = xpathNode.node();

	for (pugi::xml_node nodeId = selectedNode.first_child(); nodeId; nodeId = nodeId.next_sibling())
	{
		if (id_ <= nodeId.child("Id").text().as_int())
			id_ = nodeId.child("Id").text().as_int() + 1;
	}
}

pugi::xml_node VehicleData::nodeFinder(uint32_t id)
{
	pugi::xpath_node xpathNode = doc.select_node("VehiclesData");
	pugi::xml_node selectedNode = xpathNode.node();

	for (pugi::xml_node nodeId = selectedNode.first_child(); nodeId; nodeId = nodeId.next_sibling())
	{
		if (id == nodeId.child("Id").text().as_int())
			return nodeId;
	}
}

uint32_t VehicleData::getId()
{
	return id_;
}
string VehicleData::getType()
{
	return type_;
}
string VehicleData::getBrand()
{
	return brand_;
}
string VehicleData::getModel()
{
	return model_;
}
uint32_t VehicleData::getYear()
{
	return year_;
}
double VehicleData::getWeight()
{
	return weight_;
}

void VehicleData::getVehicleDataById(uint32_t id, string fileName)
{
	if (!(doc.load_file(fileName.c_str())))
	{
		pugi::xml_node nodeToDisplay = nodeFinder(id);

		VehicleData vehicle;

		vehicle.type_ = nodeToDisplay.child("Type").text().as_string();
		vehicle.brand_ = nodeToDisplay.child("Brand").text().as_string();
		vehicle.model_ = nodeToDisplay.child("Model").text().as_string();
		vehicle.year_ = nodeToDisplay.child("Year").text().as_int();
		vehicle.weight_ = nodeToDisplay.child("Weight").text().as_double();

		std::cout << "Тип транспортного средства: " << vehicle.type_ << endl << "Бренд транспортного средства: " << vehicle.brand_ << endl
			<< "Модель транспортного средства: " << vehicle.model_ << endl << "Год транспортного средства: " << vehicle.year_ << endl << "Вес транспортного средства: " << vehicle.weight_ << endl;
	}
	else
		cout << "Файл не найден" << endl;
}

void VehicleData::save(string fileName, string type, string brand, string model, uint32_t year, double weight)
{
	pugi::xml_node nodeVehiclesData;
	pugi::xml_node nodeVehicleData;
	pugi::xml_node childrenNodesVehicleData;

	bool existingFile;
	if (!doc.load_file(fileName.c_str()))
	{
		auto declarationNode = doc.append_child(pugi::node_declaration);
		declarationNode.append_attribute("version") = "1.0";
		declarationNode.append_attribute("encoding") = "ISO-8859-1";
		declarationNode.append_attribute("standalone") = "yes";
		nodeVehiclesData = doc.append_child("VehiclesData");
		existingFile = false;
	}
	else
	{
		nodeVehiclesData = doc.child("VehiclesData");
		existingFile = true;
	}

	if (existingFile)
		generateId();

	nodeVehicleData = nodeVehiclesData.append_child("VehicleData");

	childrenNodesVehicleData = nodeVehicleData.append_child("Id");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(to_string(id_).c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Type");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(type.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Brand");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(brand.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Model");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(model.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Year");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(to_string(year).c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Weight");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(to_string(weight).c_str());

	doc.save_file(fileName.c_str(), PUGIXML_TEXT("  "));

	cout << "Данные успешно добавлены в файл " << fileName << endl;
}

void VehicleData::update(uint32_t id, string fileName, string type, string brand, string model, uint32_t year, double weight)
{
	if (doc.load_file(fileName.c_str()))
	{
		pugi::xml_node nodeToUpdate = nodeFinder(id);

		nodeToUpdate.child("Type").first_child().set_value(type.c_str());
		nodeToUpdate.child("Brand").first_child().set_value(brand.c_str());
		nodeToUpdate.child("Model").first_child().set_value(model.c_str());
		nodeToUpdate.child("Year").first_child().set_value(to_string(year).c_str());
		nodeToUpdate.child("Weight").first_child().set_value(to_string(weight).c_str());

		doc.save_file(fileName.c_str(), PUGIXML_TEXT("  "));

		cout << "Данные с ID - " << id_ << " успешно изменены в файле " << fileName << endl;
	}
	else
		cout << "Файл не найден" << endl;
}

void VehicleData::remove(uint32_t id, string fileName)
{
	if (doc.load_file(fileName.c_str()))
	{
		pugi::xml_node nodeToRemove = nodeFinder(id);
		nodeToRemove.parent().remove_child(nodeToRemove);

		doc.save_file(fileName.c_str(), PUGIXML_TEXT("  "));

		cout << "Данные с ID - " << id << " успешно удалены из файла " << fileName << endl;
	}
	else
		cout << "Файл не найден" << endl;
}

vector<VehicleData> VehicleData::loadVehicleData()
{
	vector<VehicleData> vehicles;
	VehicleData vehicleData;
	pugi::xpath_node xpathNode = doc.select_node("VehiclesData");
	pugi::xml_node selectedNode = xpathNode.node();
	for (pugi::xml_node node = selectedNode.first_child(); node; node = node.next_sibling())
	{
		vehicleData.id_ = node.child("Id").text().as_int();
		vehicleData.type_ = node.child("Type").text().as_string();
		vehicleData.brand_ = node.child("Brand").text().as_string();
		vehicleData.model_ = node.child("Model").text().as_string();
		vehicleData.year_ = node.child("Year").text().as_int();
		vehicleData.weight_ = node.child("Weight").text().as_double();

		vehicles.push_back(vehicleData);
	}
	return vehicles;
}

void VehicleData::loadByField(uint32_t sortType, string fileName)
{
	if (doc.load_file(fileName.c_str()))
	{
		vector<VehicleData> vehicles;
		vehicles = loadVehicleData();

		switch (sortType)
		{
		case ID:
			cout << "Сортировка по ID:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getId() < b.getId(); });
			break;
		case TYPE:
			cout << "Сортировка по типу:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getType() < b.getType(); });
			break;
		case BRAND:
			cout << "Сортировка по бренду:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getBrand() < b.getBrand(); });
			break;
		case MODEL:
			cout << "Сортировка по модели:" << endl << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getModel() < b.getModel(); });
			break;
		case YEAR:
			cout << "Сортировка по году:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getYear() < b.getYear(); });
			break;
		case WEIGHT:
			cout << "Сортировка по весу:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b) { return a.getWeight() < b.getWeight(); });
			break;
		default:
			cout << "Поле отсутствует";
			break;
		}
		for (auto &el : vehicles)
			cout << "ID: " << el.id_ << " Тип: " << el.type_ << " Бренд: " << el.brand_ << " Модель: " << el.model_ << " Год: " << el.year_ << " Вес: " << el.weight_ << endl;
	}
	else
		cout << "Файл не найден" << endl;
}


void VehicleData::searchByField(uint32_t sortType, string fileName, string searchWord)
{
	if (doc.load_file(fileName.c_str()))
	{
		vector<VehicleData> allVehicles;
		vector<VehicleData> sortVehicles;
		allVehicles = loadVehicleData();
		switch (sortType)
		{
		case ID:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return to_string(a.getId()) == searchWord; });
			break;
		case TYPE:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return a.getType() == searchWord; });
			break;
		case BRAND:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return a.getBrand() == searchWord; });
			break;
		case MODEL:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return a.getModel() == searchWord; });
			break;
		case YEAR:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return to_string(a.getYear()) == searchWord; });
			break;
		case WEIGHT:
			copy_if(allVehicles.begin(), allVehicles.end(), back_inserter(sortVehicles), [&searchWord](VehicleData &a) { return to_string(a.getWeight()) == searchWord; });
			break;
		default:
			cout << "Поле отсутствует";
			break;
		}
		for (auto &el : sortVehicles)
			cout << "ID: " << el.id_ << " Тип: " << el.type_ << " Бренд: " << el.brand_ << " Модель: " << el.model_ << " Год: " << el.year_ << " Вес: " << el.weight_ << endl;
	}
	else
		cout << "Файл не найден" << endl;
}

