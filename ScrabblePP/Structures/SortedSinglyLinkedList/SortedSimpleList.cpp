#include "SortedSimpleList.h"

SortedSimpleList::SortedSimpleList()
{
    firstNode = nullptr;
    lastNode = nullptr;
}

SortedSimpleList::~SortedSimpleList()
{
}

bool SortedSimpleList::isEmpty()
{
    return firstNode == nullptr;
}

void SortedSimpleList::addFirstNode(string name, int score)
{
    SortedSimpleNode *node = new SortedSimpleNode(name, score);
    if (isEmpty())
    {
        lastNode = node;
    }
    else
    {
        node->setNextNode(firstNode);
    }
    firstNode = node;
    sortList();
}

void SortedSimpleList::addLastNode(string name, int score)
{
    SortedSimpleNode *node = new SortedSimpleNode(name, score);
    if (isEmpty())
    {
        firstNode = node;
    }
    else
    {
        lastNode->setNextNode(node);
    }
    lastNode = node;
    sortList();
}

void SortedSimpleList::readNodes()
{
    SortedSimpleNode *auxiliaryNode = firstNode;
    while (auxiliaryNode != nullptr)
    {
        cout << auxiliaryNode->getName() << " --> ";
        auxiliaryNode = auxiliaryNode->getNextNode();
    }
    cout << endl;
}

void SortedSimpleList::sortList()
{
    SortedSimpleNode *current = firstNode;
    SortedSimpleNode *index;
    int temp;

    if (!isEmpty())
    {
        while (current != nullptr)
        {
            index = current->getNextNode();
            while (index != nullptr)
            {
                if (current->getScore() > index->getScore())
                {
                    temp = current->getScore();
                    current->setScore(index->getScore());
                    index->setScore(temp);
                }
                index = index->getNextNode();
            }
            current = current->getNextNode();
        }
    }
}