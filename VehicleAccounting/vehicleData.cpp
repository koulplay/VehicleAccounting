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

void VehicleData::generateId()
{
	pugi::xpath_node xpathNode = doc.select_node("VehiclesData");
	pugi::xml_node selectedNode = xpathNode.node();

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


void VehicleData::setId(uint32_t id)
{
	this->id_ = id;
}
void VehicleData::setType(string type)
{
	this->type_ = type;
}
void VehicleData::setBrand(string brand)
{
	this->brand_ = brand;
}
void VehicleData::setModel(string model)
{
	this->model_ = model;
}
void VehicleData::setYear(uint32_t year)
{
	this->year_ = year;
}
void VehicleData::setWeight(double weight)
{
	this->weight_ = weight;
}

void VehicleData::getVehicleDataById(uint32_t id, string fileName)
{
	if (doc.load_file(fileName.c_str()))
	{
		string type;
		string brand;
		string model;
		uint32_t year;
		double weight;

		pugi::xml_node nodeToDisplay = nodeFinder(id);

		type = nodeToDisplay.child("Type").text().as_string();
		brand = nodeToDisplay.child("Brand").text().as_string();
		model = nodeToDisplay.child("Model").text().as_string();
		year = nodeToDisplay.child("Year").text().as_int();
		weight = nodeToDisplay.child("Weight").text().as_double();

		std::cout << "Тип транспортного средства: " << type << endl << "Бренд транспортного средства: " << brand << endl << "Модель транспортного средства: " << model << endl
			<< "Год транспортного средства: " << year << endl << "Вес транспортного средства: " << weight << endl;
	}
	else
		cout << "Файл не найден" << endl;
}

void VehicleData::save(string fileName)
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
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(type_.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Brand");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(brand_.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Model");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(model_.c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Year");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(to_string(year_).c_str());

	childrenNodesVehicleData = nodeVehicleData.append_child("Weight");
	childrenNodesVehicleData.append_child(pugi::node_pcdata).set_value(to_string(weight_).c_str());

	doc.save_file(fileName.c_str(), PUGIXML_TEXT("  "));

	cout << "Данные успешно добавлены в файл " << fileName << endl;
}

void VehicleData::update(string fileName)
{
	if (doc.load_file(fileName.c_str()))
	{
		pugi::xml_node nodeToUpdate = nodeFinder(id_);

		nodeToUpdate.child("Type").first_child().set_value(type_.c_str());
		nodeToUpdate.child("Brand").first_child().set_value(brand_.c_str());
		nodeToUpdate.child("Model").first_child().set_value(model_.c_str());
		nodeToUpdate.child("Year").first_child().set_value(to_string(year_).c_str());
		nodeToUpdate.child("Weight").first_child().set_value(to_string(weight_).c_str());

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

void test()
{

}
//Заполняет массив данными по скруктуре из файла
vector<VehicleData> loadVehicleData(vector<VehicleData> vehicles)
{
	VehicleData vehicleData;
	pugi::xpath_node xpathNode = doc.select_node("VehiclesData");
	pugi::xml_node selectedNode = xpathNode.node();
	pugi::xml_node node = selectedNode.first_child();
	for (pugi::xml_node node = selectedNode.first_child(); node; node = node.next_sibling())
	{
		vehicleData.setId(node.child("Id").text().as_int());
		vehicleData.setType(node.child("Type").text().as_string());
		vehicleData.setBrand(node.child("Brand").text().as_string());
		vehicleData.setModel(node.child("Model").text().as_string());
		vehicleData.setYear(node.child("Year").text().as_int());
		vehicleData.setWeight(node.child("Weight").text().as_double());

		vehicles.push_back(vehicleData);

	}
	return vehicles;
}

void VehicleData::loadByField(uint32_t sortType, string fileName)
{
	if (doc.load_file(fileName.c_str()))
	{
		vector<VehicleData> vehicles;
		vehicles = loadVehicleData(vehicles);

		switch (sortType)
		{
		case ID:
			cout << "Сортировка по ID:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getId() < b.getId();
				});
			break;
		case TYPE:
			cout << "Сортировка по типу:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getType() < b.getType();
				});
			break;
		case BRAND:
			cout << "Сортировка по бренду:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getBrand() < b.getBrand();
				});
			break;
		case MODEL:
			cout << "Сортировка по модели:" << endl << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getModel() < b.getModel();
				});
			break;
		case YEAR:
			cout << "Сортировка по году:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getYear() < b.getYear();
				});
			break;
		case WEIGHT:
			cout << "Сортировка по весу:" << endl;
			sort(vehicles.begin(), vehicles.end(), [](VehicleData &a, VehicleData &b)
				{
					return a.getWeight() < b.getWeight();
				});
			break;
		default:
			cout << "Поле отсутствует";
			break;
		}

		for (uint32_t i = 0; i < vehicles.size(); i++)
		{
			cout << "ID: " << vehicles[i].getId() << " Тип: " << vehicles[i].getType() << " Бренд: " << vehicles[i].getBrand() << " Модель: " << vehicles[i].getModel() << " Год: " << vehicles[i].getYear() << " Вес: " << vehicles[i].getWeight() << endl;
		}
	}
	else
		cout << "Файл не найден" << endl;
}


void VehicleData::searchByField(uint32_t sortType, string fileName, string searchWord)
{
	if (doc.load_file(fileName.c_str()))
	{

		vector<VehicleData> vehicles;
		vehicles = loadVehicleData(vehicles);
		vector<VehicleData>::iterator data;
		switch (sortType)
		{
		case ID:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return to_string(a.getId()) == searchWord;
				});
			break;
		case TYPE:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return a.getType() == searchWord;
				});
			break;
		case BRAND:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return a.getBrand() == searchWord;
				});
			break;
		case MODEL:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return a.getModel() == searchWord;
				});
			break;
		case YEAR:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return to_string(a.getYear()) == searchWord;
				});
			break;
		case WEIGHT:
			data = find_if(vehicles.begin(), vehicles.end(), [&searchWord](VehicleData &a)
				{
					return to_string(a.getWeight()) == searchWord;
				});
			break;
		default:
			cout << "Поле отсутствует";
			break;
		}

		cout << "ID: " << data._Ptr->getId() << " Тип: " << data._Ptr->getType() << " Бренд: " << data._Ptr->getBrand() << " Модель: " << data._Ptr->getModel() << " Год: " << data._Ptr->getYear() << " Вес: " << data._Ptr->getWeight() << endl;

	}
	else
		cout << "Файл не найден" << endl;
}

