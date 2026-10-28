
#include <iostream>
#include <string>
#include <limits>
#include <utility>
using namespace std;

// ========================================
// Webpage Node
// ========================================

struct PageNode
{
    int pageID;
    string title;
    string url;
    PageNode* next;
};

// ========================================
// Linked List Class
// ========================================

class LinkedList
{
private:
    PageNode* head;
    int count;

    // Get node at a specific index
    PageNode* GetNodeAt(int index)
    {
        PageNode* current = head;

        for (int i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }

        return current;
    }

    // Swap webpage data between two nodes
    void CopyPageData(PageNode* a, PageNode* b)
    {
        swap(a->pageID, b->pageID);
        swap(a->title, b->title);
        swap(a->url, b->url);
    }

public:

    // Constructor
    LinkedList()
    {
        head = nullptr;
        count = 0;
    }

    // Check whether list is empty
    bool IsEmpty()
    {
        return head == nullptr;
    }

    // Check whether list is not empty
    bool IsNotEmpty()
    {
        return head != nullptr;
    }

    // Insert webpage at head
    void Insert(PageNode* page)
    {
        if (page == nullptr)
            return;

        page->next = head;
        head = page;
        count++;
    }

    // Remove webpage from head
    PageNode* Remove()
    {
        if (IsEmpty())
            return nullptr;

        PageNode* page = head;
        head = head->next;

        page->next = nullptr;
        count--;

        return page;
    }

    // Insert webpage at a specific index
    void InsertAt(PageNode* page, int index)
    {
        if (page == nullptr)
            return;

        if (index < 0 || index > count)
        {
            cout << "Invalid index!\n";
            return;
        }

        if (index == 0)
        {
            Insert(page);
            return;
        }

        PageNode* previous = GetNodeAt(index - 1);

        page->next = previous->next;
        previous->next = page;

        count++;
    }

    // Remove webpage at a specific index
    PageNode* RemoveAt(int index)
    {
        if (index < 0 || index >= count)
            return nullptr;

        if (index == 0)
            return Remove();

        PageNode* previous = GetNodeAt(index - 1);
        PageNode* page = previous->next;

        previous->next = page->next;
        page->next = nullptr;

        count--;

        return page;
    }

    // Swap webpages at two indexes
    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count)
        {
            cout << "Invalid index!\n";
            return;
        }

        if (index1 == index2)
        {
            cout << "Both indexes are the same.\n";
            return;
        }

        PageNode* first = GetNodeAt(index1);
        PageNode* second = GetNodeAt(index2);

        CopyPageData(first, second);

        cout << "Webpages swapped successfully!\n";
    }

    // Sort webpages by page ID
    void Sort()
    {
        for (PageNode* i = head; i != nullptr; i = i->next)
        {
            for (PageNode* j = i->next; j != nullptr; j = j->next)
            {
                if (i->pageID > j->pageID)
                {
                    CopyPageData(i, j);
                }
            }
        }

        cout << "Browser history sorted by ID!\n";
    }

    // Reverse browser history
    void Reverse()
    {
        PageNode* previous = nullptr;
        PageNode* current = head;
        PageNode* next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = previous;

            previous = current;
            current = next;
        }

        head = previous;

        cout << "Browser history reversed!\n";
    }

    // Display all webpages
    void Print()
    {
        if (IsEmpty())
        {
            cout << "\nBrowser history is empty!\n";
            return;
        }

        PageNode* current = head;
        int index = 0;

        cout << "\nIndex\tPage ID\tTitle\t\tURL\n";
        cout << "----------------------------------------------------------\n";

        while (current != nullptr)
        {
            cout << index << "\t"
                 << current->pageID << "\t"
                 << current->title << "\t\t"
                 << current->url << endl;

            current = current->next;
            index++;
        }

        cout << "\nTotal webpages: " << count << endl;
    }

    // Return total number of webpages
    int GetCount()
    {
        return count;
    }

    // Destructor
    ~LinkedList()
    {
        while (!IsEmpty())
        {
            delete Remove();
        }
    }
};

// ========================================
// Create a Webpage Node
// ========================================

PageNode* CreatePage(int id, string title, string url)
{
    PageNode* page = new PageNode;

    page->pageID = id;
    page->title = title;
    page->url = url;
    page->next = nullptr;

    return page;
}

// ========================================
// Main Function
// ========================================

int main()
{
    LinkedList browser;

    int choice, id, index, index1, index2;
    string title, url;
    PageNode* removed;

    // Add initial browser history
    browser.InsertAt(
        CreatePage(103, "YouTube", "youtube.com"), 0);

    browser.InsertAt(
        CreatePage(101, "Google", "google.com"), 1);

    browser.InsertAt(
        CreatePage(105, "GitHub", "github.com"), 2);

    browser.InsertAt(
        CreatePage(102, "Wikipedia", "wikipedia.org"), 3);

    browser.InsertAt(
        CreatePage(104, "StackOverflow", "stackoverflow.com"), 4);

    do
    {
        cout << "\n====================================\n";
        cout << " BROWSER HISTORY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Display Browser History\n";
        cout << "2. Browse New Page (Insert at Head)\n";
        cout << "3. Remove Most Recent Page\n";
        cout << "4. Insert Page at Index\n";
        cout << "5. Remove Page at Index\n";
        cout << "6. Swap Two Pages\n";
        cout << "7. Sort Pages by ID\n";
        cout << "8. Reverse Browser History\n";
        cout << "9. Check History Status\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        switch (choice)
        {
        case 1:
            browser.Print();
            break;

        case 2:
            cout << "Enter Page ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Page Title: ";
            getline(cin, title);

            cout << "Enter Page URL: ";
            getline(cin, url);

            browser.Insert(CreatePage(id, title, url));

            cout << "New page added to browser history!\n";
            break;

        case 3:
            removed = browser.Remove();

            if (removed != nullptr)
            {
                cout << "Removed page: "
                     << removed->title << endl;

                delete removed;
            }
            else
            {
                cout << "Browser history is empty!\n";
            }
            break;

        case 4:
            cout << "Enter Page ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Page Title: ";
            getline(cin, title);

            cout << "Enter Page URL: ";
            getline(cin, url);

            cout << "Enter index (0 to "
                 << browser.GetCount() << "): ";

            if (!(cin >> index))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            if (index < 0 || index > browser.GetCount())
            {
                cout << "Invalid index!\n";
                break;
            }

            browser.InsertAt(
                CreatePage(id, title, url), index);

            cout << "Page inserted successfully!\n";
            break;

        case 5:
            cout << "Enter index to remove: ";

            if (!(cin >> index))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            removed = browser.RemoveAt(index);

            if (removed != nullptr)
            {
                cout << "Removed page: "
                     << removed->title << endl;

                delete removed;
            }
            else
            {
                cout << "Invalid index or empty history!\n";
            }
            break;

        case 6:
            cout << "Enter first index: ";
            cin >> index1;

            cout << "Enter second index: ";
            cin >> index2;

            browser.Swap(index1, index2);
            break;

        case 7:
            browser.Sort();
            break;

        case 8:
            browser.Reverse();
            break;

        case 9:
            if (browser.IsEmpty())
            {
                cout << "Browser history is empty.\n";
            }
            else
            {
                cout << "Browser history is not empty.\n";
                cout << "Total webpages: "
                     << browser.GetCount() << endl;
            }
            break;

        case 10:
            cout << "Exiting Browser History System.\n";
            break;

        default:
            cout << "Invalid choice! Select 1-10.\n";
        }

    } while (choice != 10);

    return 0;
}
