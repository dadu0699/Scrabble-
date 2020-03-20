#ifndef SCRABBLE___SPARSEMATRIX_H
#define SCRABBLE___SPARSEMATRIX_H

#include <iostream>
#include "SparseMatrixNode.h"

using namespace std;

template<class T>
class SparseMatrix {
private:
    SparseMatrixNode<T> *root;

    SparseMatrixNode<T> *searchColumn(int x);

    SparseMatrixNode<T> *searchRow(int y);

    SparseMatrixNode<T> *insertIntoColumn(SparseMatrixNode<T> *node, SparseMatrixNode<T> *headerRow);

    SparseMatrixNode<T> *insertIntoRow(SparseMatrixNode<T> *node, SparseMatrixNode<T> *headerRow);

    SparseMatrixNode<T> *createColumn(int x);

    SparseMatrixNode<T> *createRow(int y);

public:
    SparseMatrix();

    ~SparseMatrix();

    void addNode(int x, int y, T object);

    void printHeadersR();

    void printHeadersC();

    void printRows();

    void printColumns();
};


template<class T>
SparseMatrix<T>::SparseMatrix() {
    root = new SparseMatrixNode<T>(-1, -1, 0);
}

template<class T>
SparseMatrix<T>::~SparseMatrix() {
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::searchColumn(int x) {
    SparseMatrixNode<T> *temp = root;

    while (temp != nullptr) {
        if (temp->getX() == x) {
            return temp;
        }
        temp = temp->getNextNode();
    }

    return nullptr;
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::searchRow(int y) {
    SparseMatrixNode<T> *temp = root;

    while (temp != nullptr) {
        if (temp->getY() == y) {
            return temp;
        }
        temp = temp->getDownNode();
    }

    return nullptr;
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::insertIntoColumn(SparseMatrixNode<T> *node, SparseMatrixNode<T> *headerRow) {
    SparseMatrixNode<T> *temp = headerRow;
    bool flag = false;

    while (true) {
        if (temp->getX() == node->getX()) {
            temp->setY(node->getY());
            temp->setObject(node->getObject());
            return temp;
        } else if (temp->getX() > node->getX()) {
            flag = true;
            break;
        }

        if (temp->getNextNode() != nullptr) {
            temp = temp->getNextNode();
        } else {
            // flag = false;
            break;
        }
    }

    if (flag) {
        node->setNextNode(temp);
        temp->getPreviousNode()->setNextNode(node);
        node->setPreviousNode(temp->getPreviousNode());
        temp->setPreviousNode(node);
    } else {
        temp->setNextNode(node);
        node->setPreviousNode(temp);
    }

    return node;
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::insertIntoRow(SparseMatrixNode<T> *node, SparseMatrixNode<T> *headerColumn) {
    SparseMatrixNode<T> *temp = headerColumn;
    bool flag = false; // true; // Verify

    while (true) {
        if (temp->getY() == node->getY()) {
            temp->setX(node->getX());
            temp->setObject(node->getObject());
            return temp;
        } else if (temp->getY() > node->getY()) {
            flag = true;
            break;
        }

        if (temp->getDownNode() != nullptr) {
            temp = temp->getDownNode();
        } else {
            // flag = false;
            break;
        }
    }

    if (flag) {
        node->setDownNode(temp);
        temp->getUpNode()->setDownNode(node);
        node->setUpNode(temp->getUpNode());
        temp->setUpNode(node);
    } else {
        temp->setDownNode(node);
        node->setUpNode(temp);
    }

    return node;
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::createColumn(int x) {
    SparseMatrixNode<T> *headerColumn = root;
    SparseMatrixNode<T> *column = insertIntoColumn(new SparseMatrixNode<T>(x, -1, 0), headerColumn);
    return column;
}

template<class T>
SparseMatrixNode<T> *SparseMatrix<T>::createRow(int y) {
    SparseMatrixNode<T> *headerRow = root;
    SparseMatrixNode<T> *row = insertIntoRow(new SparseMatrixNode<T>(-1, y, 0), headerRow);
    return row;
}

template<class T>
void SparseMatrix<T>::addNode(int x, int y, T object) {
    SparseMatrixNode<T> *node = new SparseMatrixNode<T>(x, y, object);
    SparseMatrixNode<T> *columnNode = searchColumn(x);
    SparseMatrixNode<T> *rowNode = searchRow(y);

    if (columnNode == nullptr && rowNode == nullptr) {
        columnNode = createColumn(x);
        rowNode = createRow(y);
        node = insertIntoColumn(node, rowNode);
        node = insertIntoRow(node, columnNode);
        return;
    } else if (columnNode == nullptr && rowNode != nullptr) {
        columnNode = createColumn(x);
        node = insertIntoColumn(node, rowNode);
        node = insertIntoRow(node, columnNode);
        return;
    } else if (columnNode != nullptr && rowNode == nullptr) {
        rowNode = createRow(y);
        node = insertIntoColumn(node, rowNode);
        node = insertIntoRow(node, columnNode);
        return;
    } else if (columnNode != nullptr && rowNode != nullptr) {
        node = insertIntoColumn(node, rowNode);
        node = insertIntoRow(node, columnNode);
        return;
    }
}

template<class T>
void SparseMatrix<T>::printHeadersR() {
    SparseMatrixNode<T> *auxiliaryNode = root;
    while (auxiliaryNode != nullptr) {
        cout << "^" << endl << auxiliaryNode->getX() << "," << auxiliaryNode->getY() << endl;
        auxiliaryNode = auxiliaryNode->getDownNode();
    }
}

template<class T>
void SparseMatrix<T>::printHeadersC() {
    SparseMatrixNode<T> *auxiliaryNode = root;
    while (auxiliaryNode != nullptr) {
        cout << auxiliaryNode->getX() << "," << auxiliaryNode->getY() << " -> ";
        auxiliaryNode = auxiliaryNode->getNextNode();
    }
    cout << endl;
}

template<class T>
void SparseMatrix<T>::printRows() {
    SparseMatrixNode<T> *auxiliaryRow = root->getDownNode();
    SparseMatrixNode<T> *auxiliaryNode = auxiliaryRow;

    while (auxiliaryRow != nullptr) {
        while (auxiliaryNode != nullptr) {
            cout << auxiliaryNode->getObject() << " -> ";
            auxiliaryNode = auxiliaryNode->getNextNode();
        }

        auxiliaryRow = auxiliaryRow->getDownNode();
        auxiliaryNode = auxiliaryRow;
        cout << endl;
    }
    cout << endl;
}

template<class T>
void SparseMatrix<T>::printColumns() {
    SparseMatrixNode<T> *auxiliaryColumn = root->getNextNode();
    SparseMatrixNode<T> *auxiliaryNode = auxiliaryColumn;

    while (auxiliaryColumn != nullptr) {
        while (auxiliaryNode != nullptr) {
            cout << "^" << endl << auxiliaryNode->getObject() << endl;
            auxiliaryNode = auxiliaryNode->getDownNode();
        }

        auxiliaryColumn = auxiliaryColumn->getNextNode();
        auxiliaryNode = auxiliaryColumn;
        cout << endl;
    }
    cout << endl;
}

#endif //SCRABBLE___SPARSEMATRIX_H
