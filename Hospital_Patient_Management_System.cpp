#include <iostream>
#include <fstream>
using namespace std;

class Node
{
public:
    int patientID;
    string name;
    int age;

    Node* left;
    Node* right;

    Node(int id, string n, int a)
    {
        patientID = id;
        name = n;
        age = a;

        left = NULL;
        right = NULL;
    }
};

class BST
{
public:
    Node* root;

    BST()
    {
        root = NULL;
    }

    Node* insert(Node* root, int id, string name, int age)
    {
        if (root == NULL)
        {
            return new Node(id, name, age);
        }

        if (id < root->patientID)
        {
            root->left = insert(root->left, id, name, age);
        }
        else if (id > root->patientID)
        {
            root->right = insert(root->right, id, name, age);
        }

        return root;
    }

    void inorder(Node* root)
    {
        if (root == NULL)
        {
            return;
        }

        inorder(root->left);

        cout << "ID: " << root->patientID
             << " Name: " << root->name
             << " Age: " << root->age << endl;

        inorder(root->right);
    }
    void preorder(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    cout << "ID: " << root->patientID
         << " Name: " << root->name
         << " Age: " << root->age << endl;

    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);

    cout << "ID: " << root->patientID
         << " Name: " << root->name
         << " Age: " << root->age << endl;
}
Node* search(Node* root, int id)
{
    if (root == NULL || root->patientID == id)
    {
        return root;
    }

    if (id < root->patientID)
    {
        return search(root->left, id);
    }

    return search(root->right, id);
}
Node* findMin(Node* root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

Node* deletePatient(Node* root, int id)
{
    if (root == NULL)
    {
        return root;
    }

    if (id < root->patientID)
    {
        root->left = deletePatient(root->left, id);
    }
    else if (id > root->patientID)
    {
        root->right = deletePatient(root->right, id);
    }
    else
    {
        if (root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);

        root->patientID = temp->patientID;
        root->name = temp->name;
        root->age = temp->age;

        root->right = deletePatient(root->right, temp->patientID);
    }

    return root;
}
void saveToFile(Node* root, ofstream& file)
{
    if (root == NULL)
    {
        return;
    }

    file << root->patientID << " "
         << root->name << " "
         << root->age << endl;

    saveToFile(root->left, file);
    saveToFile(root->right, file);
}
void loadFromFile()
{
    ifstream file("patients.txt");

    int id, age;
    string name;

    while (file >> id >> name >> age)
    {
        root = insert(root, id, name, age);
    }

    file.close();
}
};

int main()
{
    BST tree;
    tree.loadFromFile();
    int choice;

    do
    {
        cout << "\n===== Hospital Patient Management System =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Delete Patient\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, age;
            string name;

            cout << "Enter Patient ID: ";
            cin >> id;

            cout << "Enter Patient Name: ";
            cin >> name;

            cout << "Enter Age: ";
            cin >> age;

            tree.root = tree.insert(tree.root, id, name, age);

            cout << "\nPatient Added Successfully!\n";
        }

        else if (choice == 2)
        {
            int searchID;

            cout << "Enter Patient ID to Search: ";
            cin >> searchID;

            Node* result = tree.search(tree.root, searchID);

            if (result != NULL)
            {
                cout << "\nPatient Found!\n";
                cout << "ID: " << result->patientID << endl;
                cout << "Name: " << result->name << endl;
                cout << "Age: " << result->age << endl;
            }
            else
            {
                cout << "\nPatient Not Found!\n";
            }
        }

        else if (choice == 3)
        {
            cout << "\nInorder Traversal:\n";
            tree.inorder(tree.root);
        }

        else if (choice == 4)
        {
            cout << "\nPreorder Traversal:\n";
            tree.preorder(tree.root);
        }

        else if (choice == 5)
        {
            cout << "\nPostorder Traversal:\n";
            tree.postorder(tree.root);
        }
        else if (choice == 6)
        {
    int deleteID;

    cout << "Enter Patient ID to Delete: ";
    cin >> deleteID;

    tree.root = tree.deletePatient(tree.root, deleteID);

    cout << "\nPatient Deleted Successfully!\n";
        }

    } while (choice != 7);
     
      cout << "\nData Saved To File!\n";
	  ofstream file("patients.txt");
      tree.saveToFile(tree.root, file);
      file.close();
    cout << "\nProgram Closed.\n";

    return 0;
}
