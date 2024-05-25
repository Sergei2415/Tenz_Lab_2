#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int global_quantity_list = -1000;
vector<int> path_tree;
vector<int> result_path_tree;
vector<int> result_path_tree_max;
vector<int> result_path_tree_min;
int result_heigh_max = 0;
int result_heigh_min = 100;
//vector<int> result_path_tree_leaves;
struct Node {
    int value;
    std::vector<Node*> children;
};

// Создать тестовый файл
void create_test_file() {
    ofstream file("data2.txt");
    if (file.is_open()) { //открываем файл
        for (int i = 0; i < 2097151; i++) {
            file << "1" << endl;
        }

        file << endl;
        file.close(); // Закрываем файл
    }
    else {
        cout << "Unable to create file\n";
    }

    return;
}

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->value = value;
    return newNode;
}

// Добавить элемент
void addChild(Node* parent, Node* child) {
    parent->children.push_back(child);
}

// Импортировать дерево
void importNTree(const std::string& filename, Node*& root) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);

    int value;
    iss >> value;
    root = createNode(value);

    std::queue<Node*> levelNodes;
    levelNodes.push(root);

    while (!levelNodes.empty()) {
        Node* current = levelNodes.front();
        levelNodes.pop();

        std::getline(file, line);
        std::istringstream childIss(line);

        int childValue;
        while (childIss >> childValue) {
            Node* child = createNode(childValue);
            addChild(current, child);
            levelNodes.push(child);
        }
    }

    file.close();
}

// Вывести дерево
void printNTree(Node* root, int level = 0) {
    if (root == nullptr) {
        return;
    }

    std::cout << std::string(level * 4, ' ') << root->value << std::endl;

    for (Node* child : root->children) {
        printNTree(child, level + 1);
    }
}


// Выполнить задание
void printNTreeTask(Node* root, int level = 0, int quanity_list = 0, int heigh_tree = 0) {

    if (path_tree.size() > (level)) {

        int local_buf = path_tree.size();
        for (int j = 0; j < (local_buf - (level)); j++) {
            path_tree.pop_back();
           //heigh_tree -= 1;
            
        }

        if (heigh_tree < 0) {
            heigh_tree = 0;
        }


    }
    if (quanity_list == 0) {
        heigh_tree = 0;//выключить если будут одиночные элементы уже в полследовательности высот, а не изначальные, которые идут от корня и пока не имели листов
    }
    path_tree.push_back(root->value);

    if (root == nullptr) {
        return;
    }
    int local_index = 0;
    for (Node* child : root->children) {
        if (child->children.size() == 0) {
            local_index += 1;
        }
    }
    cout << endl << "Было посчитано количество детей - " << local_index << endl;
    quanity_list += local_index;
    heigh_tree += 1;

    if (quanity_list == global_quantity_list) {
        cout << endl << "Кол-во листьев РАВНО глобальному значению" << endl;
        cout << endl << "Текущий элемент - " << root->value << endl;
        cout << endl << "Текущее количество литьев - " << quanity_list << endl;
        cout << endl << "Текущая высота - " << heigh_tree << endl;
        cout << endl;
        //
        result_path_tree.clear();
        for (int i : path_tree) {
            result_path_tree.push_back(i);
        }
        for (int i : result_path_tree) {
            cout << i << " ";
        }
        if (local_index == global_quantity_list) {
            cout << endl << "Высота равна 2 в данном случае" << endl;
            if (result_heigh_max < 2) {

                result_heigh_max = 2;
                result_path_tree_max.clear();
                result_path_tree_max = result_path_tree;
            }
             if (result_heigh_min > 2) {
                result_heigh_min = 2;
                result_path_tree_min.clear();
                result_path_tree_min = result_path_tree;
            }
           
        }
        else {
            if (result_heigh_max < (heigh_tree + 1)) {

                result_heigh_max = heigh_tree + 1;
                result_path_tree_max.clear();
                result_path_tree_max = result_path_tree;
            }
             if (result_heigh_min > (heigh_tree + 1)) {
                result_heigh_min = heigh_tree + 1;
                result_path_tree_min.clear();
                result_path_tree_min = result_path_tree;
            }
           
        }
        //
        //
        // 
        //
        /*
        if (local_index == global_quantity_list) {
            quanity_list = 0;
        }
        else {
            quanity_list = local_index;
        }

        heigh_tree = 0;*/

        if (local_index >= global_quantity_list) {
            quanity_list = 0;
            heigh_tree = 0;
        }
        else {
            quanity_list = local_index;
            heigh_tree = 1;
        }
        //

    }
    else if (quanity_list > global_quantity_list) {
        cout << endl << "Кол-во листьев БОЛЬШЕ глобальному значению" << endl;
        cout << endl << "Текущий элемент - " << root->value << endl;
        cout << endl << "Текущее количество литьев - " << quanity_list << endl;
        cout << endl << "Текущая высота - " << heigh_tree << endl;
        cout << endl;
        quanity_list = local_index;

        if (quanity_list == global_quantity_list) {
            cout << endl << "В данном случае ответ это один этот элемент равен 2" << endl;
            result_path_tree.clear();
            for (int i : path_tree) {
                result_path_tree.push_back(i);
            }
            for (int i : result_path_tree) {
                cout << i << " ";
            }
            //cout << endl << "Высота равна 2 в данном случае" << endl;
        }
        ///

        if (local_index == global_quantity_list) {
            cout << endl << "Высота равна 2 в данном случае" << endl;
            if (result_heigh_max < 2) {
                result_heigh_max = 2;
                result_path_tree_max.clear();
                result_path_tree_max = result_path_tree;
            }
             if (result_heigh_min > 2) {
                result_heigh_min = 2;
                result_path_tree_min.clear();
                result_path_tree_min = result_path_tree;
            }
            
        }



        ///
        /*
        quanity_list = 0;
        heigh_tree = 1;//было 0
        */
        if (local_index >= global_quantity_list) {
            quanity_list = 0;
            heigh_tree = 0;
        }
        else {
            quanity_list = local_index;
            heigh_tree = 1;
        }
    }
    else {
        cout << endl << "Кол-во листьев МЕНЬШЕ глобальному значению" << endl;
        cout << endl << "Текущий элемент - " << root->value << endl;
        cout << endl << "Текущее количество литьев - " << quanity_list << endl;
        cout << endl << "Текущая высота - " << heigh_tree << endl;
        cout << endl;
    }
    for (Node* child : root->children) {
        printNTreeTask(child, level + 1, quanity_list, heigh_tree);
    }
}

// Вывести ответ
void conclusion_result() {
    cout << "Результирующий путь min - ";
    for (int i : result_path_tree_min) {
        cout << i << " ";
    }
    //cout << "Значение высоты min - " << result_heigh_min;
    cout << endl;
    cout << "Результирующий путь max - ";
    for (int i : result_path_tree_max) {
        cout << i << " ";
    }
    //cout << "Значение высоты max - " << result_heigh_max;
    cout << endl << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* root = nullptr;
    //string path_file = "n_tree.txt";

    //printNTree(root);
    //printNTreeTest(root);
    //printNTreeTask(root);
    //cout << path_tree.size();


    int choice;
    while (true) {
        cout << "\nДоступные опции:\n";
        cout << "1. Создание тестового файла\n";
        cout << "2. Импорт данных из файла\n";
        cout << "3. Найти в дереве самое высокое (низкое) поддерево, имеющее заданное число листьев.\n";
        cout << "4. Вывести дерево\n";
        cout << "5. Выход\n";
        cout << "Введите число(номер опции): ";
        cin >> choice;

        switch (choice) {
        case 1:
            create_test_file();
            break;
        case 2:
            importNTree("n_tree10.txt", root);
            global_quantity_list = 3;
            break;
        case 3:
            printNTreeTask(root);
            conclusion_result();
            break;
        case 4:
            printNTree(root);
            break;
        case 5:
            cout << "Выход...\n";
            return 0;
        default:
            cout << "Некорректный ввод опции! Повторите попытку.\n";
            break;
        }
    }
    return 0;
}
