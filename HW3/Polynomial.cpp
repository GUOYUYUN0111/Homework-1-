#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

class Polynomial {
private:
    struct Node {
        float coef;  
        int exp;    
        Node* link;  
        Node(float c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
    };
    
    Node* header;  

public:
    
    Polynomial() {
        header = new Node();
        header->link = header;  
    }
    
    Polynomial(const Polynomial& a) {
        header = new Node();
        header->link = header;
        
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp);
            current = current->link;
        }
    }
    
    ~Polynomial() {
        Node* current = header->link;
        while (current != header) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        delete header;
    }
    
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            Node* current = header->link;
            while (current != header) {
                Node* temp = current;
                current = current->link;
                delete temp;
            }
            header->link = header;
            
            current = a.header->link;
            while (current != a.header) {
                addTerm(current->coef, current->exp);
                current = current->link;
            }
        }
        return *this;
    }
   
    void addTerm(float coef, int exp) {
        if (coef == 0) return;  
        
        Node* prev = header;
        Node* current = header->link;
        
        while (current != header && current->exp > exp) {
            prev = current;
            current = current->link;
        }
        
        if (current != header && current->exp == exp) {
            current->coef += coef;
            if (current->coef == 0) { 
                prev->link = current->link;
                delete current;
            }
        } else {

            Node* newNode = new Node(coef, exp, current);
            prev->link = newNode;
        }
    }
    
    friend istream& operator>>(istream& is, Polynomial& x) {
        cout << "Enter number of terms: ";
        int numTerms;
        is >> numTerms;
        
        cout << "Enter terms (coefficient exponent pairs):\n";
        for (int i = 0; i < numTerms; i++) {
            float coef;
            int exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }
    
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.header->link;
        bool first = true;
        
        if (current == x.header) {
            os << "0";
            return os;
        }
        
        while (current != x.header) {
            if (!first && current->coef > 0) {
                os << " + ";
            } else if (current->coef < 0) {
                os << (first ? "-" : " - ");
            }
            
            float absCoef = (current->coef < 0) ? -current->coef : current->coef;
            
            if (current->exp == 0) {
                os << absCoef;
            } else if (current->exp == 1) {
                if (absCoef == 1 && !first) {
                    os << "x";
                } else if (absCoef == 1 && first) {
                    os << "x";
                } else {
                    os << absCoef << "x";
                }
            } else {
                if (absCoef == 1 && !first) {
                    os << "x^" << current->exp;
                } else if (absCoef == 1 && first) {
                    os << "x^" << current->exp;
                } else {
                    os << absCoef << "x^" << current->exp;
                }
            }
            
            first = false;
            current = current->link;
        }
        return os;
    }
    
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        
        Node* current = header->link;
        while (current != header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        current = b.header->link;
        while (current != b.header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        return result;
    }
    
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        
        Node* current = header->link;
        while (current != header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        current = b.header->link;
        while (current != b.header) {
            result.addTerm(-current->coef, current->exp);
            current = current->link;
        }
        
        return result;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        
        Node* current1 = header->link;
        while (current1 != header) {
            Node* current2 = b.header->link;
            while (current2 != b.header) {
                float newCoef = current1->coef * current2->coef;
                int newExp = current1->exp + current2->exp;
                result.addTerm(newCoef, newExp);
                current2 = current2->link;
            }
            current1 = current1->link;
        }
        
        return result;
    }

    float Evaluate(float x) const {
        float result = 0;
        Node* current = header->link;
        
        while (current != header) {
            float termValue = current->coef * pow(x, current->exp);
            result += termValue;
            current = current->link;
        }
        
        return result;
    }
    
    bool isEmpty() const {
        return header->link == header;
    }
    
    void clear() {
        Node* current = header->link;
        while (current != header) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        header->link = header;
    }
};

int main() {
    Polynomial p1, p2;
    
    cout << "Enter polynomial P1:\n";
    cin >> p1;
    cout << "P1 = " << p1 << "\n";
    
    cout << "Enter polynomial P2:\n";
    cin >> p2;
    cout << "P2 = " << p2 << "\n";
    
    cout << "P1 + P2 = " << p1 + p2 << "\n";
    cout << "P1 - P2 = " << p1 - p2 << "\n";
    cout << "P1 * P2 = " << p1 * p2 << "\n";
      
    return 0;
}