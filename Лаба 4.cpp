#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;
int j = 1;
template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void displayPair() const {
        cout << first << ": " << second << '\n';
    }

    void savePairToFile(ofstream& outFile) const {
        outFile << first << " " << second << " ";
    }

private:
    T1 first;
    T2 second;
};



class Excursion {
public:
    Excursion(const string& Name, const string& Time, const string& Guide) : Name(Name), Time(Time), Guide(Guide) {}

    ~Excursion() {}

    const string& getName() const 
    {
        return Name;
    }

    const string& getTime() const 
    {
        return Time;
    }

    const string& getGuide() const 
    {
        return Guide;
    }

    void setName(const string& newName) 
    {
        Name = newName;
    }

    void setTime(const string& newTime) 
    {
        Time = newTime;
    }

    void setGuide(const string& newGuide) 
    {
        Guide = newGuide;
    }
    virtual void displayInfo() const 
    {
        std::cout << "Экскурсия" << j << ": " << Name << ", Время " << j << ": " << Time << ", Гид " << j << " : " << Guide << endl;
    }

    void saveToFile(ofstream& outFile) const 
    {
        outFile << Name << j << " " << Time << j << " " << Guide << j << " ";
    }

    static bool compareByName(const Excursion* Ex1, const Excursion* Ex2)
    {
        return Ex1->getName() < Ex2->getName();
    }
    static bool compareByTime(const Excursion * Ex1, const Excursion * Ex2)
    {
        return Ex1->getTime() < Ex2->getTime();
    }
   
protected:
    string Name;
    string Time;
    string Guide;
};
class Tour : public Excursion
{
public:
    const string& getTour() const
    {
        return Place;
    }
    void setTour(const string& newPlace)
    {
        Place = newPlace;
    }
    void displayInfo() const override
    {
        std::cout << "Экскурсия: " << Name << ", Время: " << Time << ", Гид: " << Guide << ", место: " << Place << endl;
    };
protected:
    string Place;
};
vector<Excursion*> Excursions;

void saveExcursionToFile(const vector<Excursion*>& Ex, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    for (const auto* Excursion : Excursions) {
        Excursion->saveToFile(outFile);
    }
    outFile.close();
}
void modifyExcursion(Excursion* Ex)
{
    cout << "Экскурсия найдена. Что вы хотите изменить?" << endl;
    cout << "1. Имя" << endl;
    cout << "2. Время" << endl;
    cout << "3. Гид" << endl;

    int choice;
    cout << "Введите ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string newName;
        cout << "Введите новое название: ";
        cin >> newName;
        Ex->setName(newName);
        break;
    }
    case 2: {
        string newTime;
        cout << "Введите новое время: ";
        cin >> newTime;
        Ex->setTime(newTime);
        break;
    }
    case 3: {
        string newGuide;
        cout << "Введите нового гида: ";
        cin >> newGuide;
        Ex->setGuide(newGuide);
        break;
    }
    default:
        cout << "Неверный выбор." << endl;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;
    string filename;
    do 
    {
        cout << "Меню:" << endl;
        cout << "1. Добавить экскурсию" << endl;
        cout << "2. Изменить информацию экскурсии" << endl;
        cout << "3. Удалить экскурсию" << endl;
        cout << "4. Найти экскурсию" << endl;
        cout << "5. Вывести список экскурсий" << endl;
        cout << "6. Сохранить в файл" << endl;
        cout << "7. Сортировать по времени" << endl;
        cout << "8. Сортировать по названию" << endl;
        cout << "9. Выход" << endl;

        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            string Name, Time, Guide, Place;
            cout << "Введите информацию, о экскурсии:" << endl;
            cout << "Название: ";
            cin >> Name;
            cout << "Время: ";
            cin >> Time;
            cout << "Гид: ";
            cin >> Guide;
            cout << "Место: ";
            cin >> Place;
            Excursions.push_back(new Excursion(Guide, Time, Guide));
            break;
        }
        case 2: 
        {
            string Name, Time;
            cout << "Введите информацию изменения:" << endl;
            cout << "Название: ";
            cin >> Name;
            cout << "Время: ";
            cin >> Time;

            auto it = find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Ex) 
                {
                return Ex->getName() == Name && Ex->getTime() == Time;
                });

            if (it != Excursions.end()) 
            {
                modifyExcursion(*it);
            }
            else 
            {
                cout << "Экскурсия не найдена." << endl;
            }

            break;
        }
        case 3: 
        {
            string Name, Time;
            cout << "Введите данные экскурсии для удаления:" << endl;
            cout << "Название: ";
            cin >> Name;
            cout << "Время: ";
            cin >> Time;

            auto it = find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Ex) 
                {
                return Ex->getName() == Name && Ex->getTime() == Time;
                });

            if (it != Excursions.end()) 
            {
                delete* it;
                Excursions.erase(it);
                cout << "Экскурсия удалена." << endl;
            }
            else 
            {
                cout << "Экскурсия не найдена." << endl;
            }

            break;
        }
        case 4: 
        {
            string Name, Time;
            cout << "Введите данные экскурсии для поиска:" << endl;
            cout << "Название: ";
            cin >> Name;
            cout << "Время: ";
            cin >> Time;

            auto it = std::find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Ex) {
                return Ex->getName() == Name && Ex->getTime() == Time;
                });

            if (it != Excursions.end()) {
                (*it)->displayInfo();
            }
            else {
                cout << "Экскурсия не найден." << endl;
            }
            break;
        }
        case 5: 
        {
            cout << "Список экскурсий:" << endl;
            for (const auto* Excursion : Excursions)
            {
                Excursion->displayInfo();
            }
            break;
        }
        case 6: 
        {
            cout << "Введите имя файла для сохранения данных: ";
            cin >> filename;
            saveExcursionToFile(Excursions, filename);
            break;
        }
        case 7: 
        {
            sort(Excursions.begin(), Excursions.end(), Excursion::compareByTime);
            cout << "Список экскурсий отсортирован по времени." << endl;
            break;
        }
        case 8:
        {
            sort(Excursions.begin(), Excursions.end(), Excursion::compareByName);
            cout << "Список экскурсий отсортирован по названиям." << endl;
            break;
        }
        case 9:
            cout << "Выход." << endl;
            break;
        default:
            cout << "Неверный выбор." << endl;
        }
    } while (choice != 9);

    for (const auto* Excursion : Excursions) 
    {
        delete Excursion;
    }

    return 0;
}












