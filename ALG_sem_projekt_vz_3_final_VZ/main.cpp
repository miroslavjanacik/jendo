#include <iostream>
#include <string>

using namespace std;

/**
* @mainpage ALG_semestralny projekt
*
* @brief Úvodná stránka dokumentácie projektu.
*
* Táto dokumentácia poskytuje podrobný popis funkcií a ich očakávaného správania v rámci implementácie binárneho stromu pomocou reťazcov.
*
* @section expectations Očakávania
* - @ref fromString(const string& s, int& i): Očakáva sa, že táto funkcia rekonštruuje binárny strom zo zadaného reťazca "s" a pracuje s indexom "i" pre správne prechádzanie reťazca.
* - @ref string toString(Node root): Funkcia má za úlohu uložiť binárny strom, ktorý je definovaný pomocou ukazovateľa na koreň "root", do reťazca v postorder formáte.
* - @ref print_inline(Node n): Očakáva sa, že táto funkcia vypisuje uzly binárneho stromu v postorder (LRN) formáte v inline štýle.
*
* @section goals Ciele
* - Poskytnúť možnosť rekonštrukcie binárneho stromu zo vstupného reťazca a zároveň umožniť užívateľovi uložiť strom do reťazca pre ďalšie spracovanie.
* - Implementovať efektívne prechádzanie stromu a vypisovanie uzlov v postorder formáte.
* - Zabezpečiť, aby funkcie boli ľahko použiteľné a zrozumiteľné pre ďalší vývoj a údržbu kódu.
*/
/**
 * @brief Štruktúra reprezentujúca uzol binárneho stromu.
 */
struct Node {
    int data; ///< Hodnota uzla
    Node* left; ///< Ukazovateľ na ľavého potomka
    Node* right; ///< Ukazovateľ na pravého potomka

    /**
     * @brief Konštruktor pre inicializáciu uzla stromu.
     * @param data -  Hodnota dátového poľa uzla.
     */
    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

/**
 * @brief Funkcia pre rekonštrukciu stromu zo zadaného reťazca.
 * princip fugovania : Táto funkcia rekonštruuje binárny strom zo vstupného reťazca "s".
 * Prechadza reťazec postorder(Lavy podstrom,Pravy podstrom, kerenový uzol) spôsobom a vytvára uzly stromu na základe zátvoriek a hodnôt uzlov.
 * @param "s" Vstupný reťazec reprezentujúci strom.
 * @param "i" Index pre prácu s reťazcom.
 * @return Vracia ukazovateľ na koreň rekonštruovaného stromu.
 */
Node* fromString(const string& s, int& i) {
    if (s.empty() || i >= s.length()) {
        cerr << "BAD!\n";
        return nullptr;
    }

    while (i < s.length() && !isdigit(s[i])) {
        i++; // Preskočiť neciselné znaky
    }

    int data = 0;
    while (i < s.length() && isdigit(s[i])) {
        data = data * 10 + (s[i] - '0');
        i++;
    }

    if (data == 0) {
        return nullptr;
    }

    Node* root = new Node(data);

    if (i < s.length() && s[i] == '(') {
        i++;
        root->left = fromString(s, i);

        if (i < s.length() && s[i] == ')') {
            i++;
            root->right = fromString(s, i);
        }

        // Preskočiť koncovú zátvorku
        i++;
    }

    return root;
}

/**
 * @brief Funkcia pre uloženie stromu do reťazca.
 *
 * princip fungovania : Ukladá binárny strom do reťazca v postorder(Lavy,Pravy podstrom,korenovy uzol) formáte. Využíva rekurziu na prechod stromom a tvorbu reťazca.
 *
 * @param "root" Koreň stromu.
 * @return Reťazec reprezentujúci uložený strom.
 */
string toString(Node* root) {
    if (root == nullptr) {
        return "";
    }

    string s = to_string(root->data);

    if (root->left != nullptr || root->right != nullptr) {
        s += "(" + toString(root->left) + ")";
    }

    if (root->right != nullptr) {
        s += "(" + toString(root->right) + ")";
    }

    return s;
}

/**
 * @brief Funkcia na výpis uzlov stromu v inline formáte.
 *
 * princip fugovania: Vypisuje uzly stromu vo formate inline (postorder) - najprv ľavý potomok, potom pravý potomok a nakoniec hodnotu uzla.
 *
 * @param "n" Ukazovateľ na aktuálny uzol.
 * @return
 */
void print_inline(Node* n) {
    if (!n) {
        return;
    }
    cout << "(";
    print_inline(n->left);
    cout << n->data;
    print_inline(n->right);
    cout << ")";
}


/**
 * @brief Hlavná funkcia programu.
 *
 * Tu sa odohrávajú všetky potrebné operácie vrátane testovania reťazcov
 * na rekonštrukciu a uloženie binárneho stromu do reťazca.
 *
 * @return Funkcia main() vráti 0 ak sa program správne ukončí.
 */
int main() {
    // Testovacie reťazce a ich odpovedajúce binárne stromy
    string inputStrings[] = { "1", "1(2)(3)", "4(2(3)(1))(6(5))", "10(9(8)(7(6(5))))"," " };

    cout << "Rekonstrukcia a ulozenie binarneho stromu do retazca:" << endl;

    for (const auto& s : inputStrings) {
        int i = 0;
        Node* root = fromString(s, i);
        print_inline(root);
        cout << endl;
        string reconstructedString = toString(root);
        cout << "Vstupny retazec: " << s << " -> Rekonstruovany retazec: " << reconstructedString << endl;
        delete root; // Uvoľnenie pamäte
    }

    return 0;
}
