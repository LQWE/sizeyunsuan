#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// class Of Arighm
class szys
{
public:
    // ���캯��
    szys();
    // ���캯��
    ~szys();
    // ���ɺ���numOfNode���������ֵ�������ʽ���
    void CreateEx(int numOfNode);
    // �����ɵı��ʽ�������������������������
    int Count();
    // ��������ɵı��ʽ
    void Display();
     
private:
    // �Ƚ�����������ȼ�
    bool OperIsHigher();
    // �õ��������Ȩֵ
    int GetPriOfOper(const char oper);
 
private:
    int iResult;
        // ���ʽ�Ľ��
    char oper;
        // ���ʽ�������
    szys *lhs;
        // ���ʽ����ڵ�
    szys *rhs;
        // ���ʽ���ҽڵ�
    bool isRoot;
        // �ñ��ʽ�Ƿ�Ϊ���յı��ʽ
    szys *Parent;
        // ���ʽ�ĸ��ڵ�
    bool isLeft;
        // �Ƿ�Ϊ��ڵ�(Ϊ������Ǽ�������)
};
szys::szys()
: iResult(0)
, oper('\0')
, lhs(NULL)
, rhs(NULL)
, Parent(NULL)
, isLeft(false)
{
     
}
 
szys::~szys()
{
    if(lhs != NULL)
    {
        delete lhs;
    }
 
    if (rhs != NULL)
    {
        delete rhs;
    }
}
 
void szys::CreateEx(int numOfNode)
{
    if (1 == numOfNode)
    {
        return ;
    }
    else
    {
        int mode = rand() % 4;
        if (0 == mode)
        {
            oper = '+';
        }
        else if (1 == mode)
        {
            oper = '-';
        }
        else if (2 == mode)
        {
            oper = '*';
        }
        else
        {
            oper = '/';
        }
 
        lhs = new szys();
        rhs = new szys();
        lhs->Parent = this;
        lhs->isLeft = true;
        rhs->Parent = this;
        rhs->isLeft = false;
 
        int numOfNodeLeft = numOfNode - rand() % numOfNode;
        if (numOfNodeLeft == numOfNode)
        {
            numOfNodeLeft = 1;
        }
 
        lhs->CreateEx(numOfNodeLeft);
        rhs->CreateEx(numOfNode - numOfNodeLeft);
    }
}
 
 
int szys::Count()
{
    if (lhs != NULL && rhs != NULL)
    {
        int lResult = 0;
        int rResult = 0;
 
        lResult = lhs->Count();
        rResult = rhs->Count();
 
        while (lResult >= 5000 || lResult <= 0)
        {
            lResult = lhs->Count();
        }
 
        while (rResult >= 5000 || rResult <= 0)
        {
            rResult = rhs->Count();
        }
 
        if ('+' == oper)
        {
            iResult = lResult + rResult;
        }
 
        else if ('-' == oper)
        {
            iResult = lResult - rResult;
            if (iResult < 0)
            {
                szys *temp = lhs;
                lhs = rhs;
                lhs->isLeft = true;
                rhs = temp;
                rhs->isLeft = false;
                iResult = rResult - lResult;
            }
        }
 
        else if ('*' == oper)
        {
            int getNum = 0;
            iResult = lResult * rResult;
            while(iResult >= 3000)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
 
                if (getNum > 3000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        iResult = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        iResult = lResult - rResult;
                        if (iResult < 0)
                        {
                            szys *temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            iResult = rResult - lResult;
                        }
                    }
 
                    return iResult;
                }
 
                iResult = lResult * rResult;
            }
        }
 
        else if ('/' == oper)
        {
            int getNum = 0;
            while (0 == lResult || 0 == rResult || lResult % rResult != 0)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
                if(getNum > 2000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        iResult = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        iResult = lResult - rResult;
                        if (iResult < 0)
                        {
                            szys *temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            iResult = rResult - lResult;
                        }
                    }
 
                    return iResult;
                }
            }
 
            iResult = lResult / rResult;
        }
    }
    else
    {
        iResult = rand() % 5000;
        while (iResult == 0)
        {
            iResult = rand() % 5000;
        }
    }
 
    return iResult;
}
 
void szys::Display()
{
    if(lhs != NULL && rhs != NULL)
    {
        if (!OperIsHigher())
        {
            cout << '(';
        }
        lhs->Display();
        cout << " " << oper << " ";
        rhs->Display();
        if (!OperIsHigher())
        {
            cout << ')';
        }
    }
    else
    {
        cout << iResult;
    }
}
 
bool szys::OperIsHigher()
{
    if (NULL == Parent)
    {
        return true;
    }
    if (isLeft)
    {
        return GetPriOfOper(this->oper) >= GetPriOfOper(Parent->oper);
    }
    else
    {
        return GetPriOfOper(this->oper) > GetPriOfOper(Parent->oper);
    }
}
 
int szys::GetPriOfOper(const char oper)
{
    if ('\0' == oper)
    {
        return 3;
    }
    else if ('/' == oper || '*' == oper)
    {
        return 2;
    }
    else if ('+' == oper || '-' == oper)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    szys *pRoot = NULL;
 
    int numOfArighm = 0;
 
    int numOfNumber = 0;
 
    cout << "please input the number of arithmetic expressions:" << endl;
 
    cin >> numOfArighm;
 
    int iResult = 0;
    srand((int)time(0));
 
    for (int i = 0; i < numOfArighm; i++)
    {
        pRoot = new szys();
        numOfNumber = rand() % 7 + 2;
        pRoot->CreateEx(numOfNumber);
        iResult = pRoot->Count();
        while (iResult >= 5000 || iResult <= 0)
        {
            iResult = pRoot->Count();
        }
        pRoot->Display();
        cout << " = " << iResult;
        cout << endl;
        delete pRoot;
    }
    return 0;
}