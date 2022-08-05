#include <iostream>
#include "vehicleData.h"

using namespace std;

string fileName = "asdasd.xml";

enum
{
	ADD = 1,
	UPDATE,
	REMOVE,
	LOAD,
	SEARCH,
};

void addNewVehicleData();
void updateVehicleData();
void removeVehicleData();
void loadByFieldVehicleData();
void searchByFieldVehicleData();

uint32_t main()
{
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		cout << "Введите название файла (с расширением .xml): ";
		cin >> fileName;

		uint32_t exit = true;
		uint32_t exit1 = true;
		while (exit == 1)
		{
			uint32_t action;
			cout << "Выберите действие:" << endl << endl;
			cout << "1. Ввести в учёт транспортное средство (при отсутствии файла будет создан новый)" << endl
				<< "2. Изменить данные транспортного средства" << endl
				<< "3. Вывести из учёта транспортное средство" << endl
				<< "4. Отбражение транспортных средств с сортировкой по полю" << endl
				<< "5. Поиск транспортного средства по полю" << endl << endl;
			cin >> action;
			switch (action)
			{
			case ADD:
				addNewVehicleData();
				break;
			case UPDATE:
				updateVehicleData();
				break;
			case REMOVE:
				removeVehicleData();
				break;
			case LOAD:
				loadByFieldVehicleData();
				break;
			case SEARCH:
				searchByFieldVehicleData();
				break;
			default:
				cout << "Такого действия не существует" << endl;
				break;
			}

			cout << "Продолжить действие в текущем файле? 1/0" << endl << endl;
			cin >> exit;
		}
	}
}

void addNewVehicleData()
{
	string type;
	string brand;
	string model;
	uint32_t year;
	double weight;

	cout << "Введите тип транспортного средства" << endl;
	cin >> type;
	cout << "Введите бренд транспортного средства" << endl;
	cin >> brand;
	cout << "Введите модель транспортного средства" << endl;
	cin >> model;
	cout << "Введите год выпуска транспортного средства" << endl;
	cin >> year;
	cout << "Введите вес(кг) транспортного средства" << endl;
	cin >> weight;

	VehicleData *vehicle = new VehicleData;
	vehicle->save(fileName, type, brand, model, year, weight);
	delete vehicle;
}

void updateVehicleData()
{
	uint32_t id;
	string type;
	string brand;
	string model;
	uint32_t year;
	double weight;

	

	cout << "Введите идентификатор транспорного средства для изменения данных: ";
	cin >> id;

	cout << endl << "Текущие данные:" << endl << endl;
	VehicleData *vehicle = new VehicleData;
	vehicle->getVehicleDataById(id, fileName);

	cout << endl << "Введите новые данные:" << endl << endl;

	cout << "Тип транспортного средства: ";
	cin >> type;
	cout << endl << "Бренд транспортного средства: ";
	cin >> brand;
	cout << endl << "Модель транспортного средства: ";
	cin >> model;
	cout << endl << "Год выпуска транспортного средства: ";
	cin >> year;
	cout << endl << "Вес(кг) транспортного средства: ";
	cin >> weight;


	vehicle->update(id, fileName, type, brand, model, year, weight);
	delete vehicle;
}

void removeVehicleData()
{
	uint32_t id;
	cout << "Введите идентификатор транспорного средства для удаления: ";
	cin >> id;

	VehicleData *vehicle = new VehicleData;
	vehicle->remove(id, fileName);
	delete vehicle;
}

void loadByFieldVehicleData()
{
	uint32_t sortType;
	cout << "Выберите поле для сортировки данных транспортных средств:" << endl << endl;
	cout << "1. ID" << endl
		<< "2. Тип" << endl
		<< "3. Бренд" << endl
		<< "4. Модель" << endl
		<< "5. Год" << endl
		<< "6. Вес" << endl;
	cin >> sortType;

	VehicleData *vehicle = new VehicleData;
	vehicle->loadByField(sortType, fileName);
	delete vehicle;
}

void searchByFieldVehicleData()
{
	string searchWord;
	uint32_t sortType;

	cout << "Выберите поле для сортировки данных транспортных средств:" << endl << endl;
	cout << "1. ID" << endl
		<< "2. Тип" << endl
		<< "3. Бренд" << endl
		<< "4. Модель" << endl
		<< "5. Год" << endl
		<< "6. Вес" << endl;
	cin >> sortType;

	cout << "Введите слово: ";
	cin >> searchWord;

	VehicleData *vehicle = new VehicleData;
	vehicle->searchByField(sortType, fileName, searchWord);
	delete vehicle;
}
