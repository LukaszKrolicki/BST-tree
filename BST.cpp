#include<iostream>
using namespace std;

class Node{
    private:
        int value;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int v, Node* l, Node* r, Node* p);
        int getValue();
        Node* getLeft();
        Node* getRight();
        Node* getParent();
        void setValue(int v);
        void setLeft(Node* l);
        void setRight(Node* r);
        void setParent(Node* p);
};

Node::Node(int v, Node* l, Node* r, Node* p){
    value=v;
    this->left= l;
    this->right = r;
    this->parent=p;
}

int Node::getValue()
{
    return value;
}

Node* Node::getLeft(){
    return left;
}

Node* Node::getRight(){
    return right;
}

Node* Node::getParent(){
    return parent;
}

void Node::setValue(int v){
    this->value=v;
}

void Node::setLeft(Node* l){
    this->left=l;
}

void Node::setRight(Node* r){
    this->right=r;
}

void Node::setParent(Node* p){
    this->parent=p;
}

class BSTree{
    private:
        Node* root;
    public:
        BSTree();                        //tworzy puste drzewo
        Node* getRoot();            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
        bool empty(Node* p);        //zwraca prawdê gdy (pod)drzewo o korzeniu p jest puste
        void inorder(Node* p);      //wyœwietla w porz¹dku inorder
        void preorder(Node* p);      //wyœwietla w porz¹dku preorder
        void postorder(Node* p);      //wyœwietla w porz¹dku postorder
    //BST
        void insert(int x);            //wstawia wêze³ z wartoœci¹ x
        Node* search(int x);         //zwraca wskaŸnik do wêz³a z wartoœci¹ x (lub NULL jeœli nie istnieje)
        Node* minimum(Node* p);            //zwraca wskaŸnik do wêz³a z minimaln¹ wartoœci¹ w (pod)drzewie p
        Node* maximum(Node* p);            //zwraca wskaŸnik do wêz³a z maksymaln¹ wartoœci¹ w (pod)drzewie p
        Node* successor(Node* p);    //zwraca wskaŸnik do nastênika p
        Node* predecessor(Node* p);    //zwraca wskaŸnik do poprzednika p
        void del(Node* p);            //usuwa wêze³ wskazywany przez p
};

BSTree::BSTree(){
    root=NULL;
}

Node* BSTree::getRoot(){
    return root;
}

bool BSTree::empty(Node* p){ //?
    if(p==NULL){
        return true;
    }
    else{
        return false;
    }
}

void BSTree::inorder(Node* p){
    if(!empty(p)){
        inorder(p->getLeft());
        cout<<p->getValue()<<" ";
        inorder(p->getRight());
    }
}

void BSTree::preorder(Node* p){
    if(!empty(p)){
        cout<<p->getValue()<<" ";
        preorder(p->getLeft());
        preorder(p->getRight());
    }
}

void BSTree::postorder(Node* p){
    if(!empty(p)){
        postorder(p->getLeft());
        postorder(p->getRight());
        cout<<p->getValue()<<" ";
    }
}

void BSTree::insert(int x){
    if(empty(getRoot())){
        Node* e = new Node(x,NULL,NULL,NULL); //l,r,p
        root=e;
    }
    else{
        bool stop = false;
        Node* e= new Node(x, NULL, NULL, NULL);
        Node* p=root;

        while(!stop){
            if(p->getValue()>x){
                if(!empty(p->getLeft())){
                    p=p->getLeft();
                }
                else{
                    p->setLeft(e);
                    e->setParent(p);
                    stop=true;
                }
            }

            if(p->getValue()<x){
                if(!empty(p->getRight())){
                    p=p->getRight();
                }
                else{
                    p->setRight(e);
                    e->setParent(p);
                    stop=true;
                }
            }

        }
    }
}

Node* BSTree::search(int x){
    Node* n=root;

    while(!empty(n) && n->getValue()!=x){
        if(n->getValue()>x){
            n=n->getLeft();
        }
        else {
            n=n->getRight();
        }
    }

    return n;
}

Node* BSTree::minimum(Node *p){
    if(p==NULL){
        return NULL;
    }
    else{
        Node* n=p;
        while(!empty(n->getLeft())){
            n=n->getLeft();
        }
        return n;
    }
}

Node* BSTree::maximum(Node* p){
    if(p==NULL){
        return NULL;
    }
    else{
        Node* n=p;
        while(!empty(n->getRight())){
            n=n->getRight();
        }
        return n;
    }
}



//to jest potrzebne do delete
Node* BSTree::successor(Node* p){
    //1 przypadek drzewo puste
    if(empty(p)){
        return NULL;
    }

    //2 przypadek istnieje prawe poddrzewo
    else if(!empty(p->getRight())){
        return minimum(p->getRight());
    }

    //3 przypadek nie istnieje prawe poddrzewo
    else if(empty(p->getRight())){
        Node* n=p->getParent();
        Node* e=p;
        while(!empty(n) && e==n->getRight())
        {
            e=n;
            n=n->getParent();
        }
        return n;
    }
}

Node* BSTree::predecessor(Node* p){
    //1 przypadek drzewo puste
    if(p==NULL){
        return NULL;
    }

    //2 przypadek istnieje lewe poddrzewo
    if(!empty(p->getLeft())){
        maximum(p->getLeft());
    }

    //3 przypadek nie istnieje prawe poddrzewo
    if(empty(p->getLeft())){
        Node* n=p->getParent();
        while(!empty(n) && p==n->getLeft())
        {
            p=n;
            n=n->getParent();
        }
        return n;
    }
}

void BSTree::del(Node* p){
    if(empty(p)){
        cout<<"Element nie istnieje"<<endl;
    }

    //jest liœciem
    if(empty(p->getLeft()) && empty(p->getRight())){
        Node* n= p->getParent();
        cout<<"lisc"<<endl;
        if(empty(n)){ //korzen
            root=NULL;
        }
        else{
            if(p==n->getLeft()){
                n->setLeft(NULL);
            }else{
                n->setRight(NULL);
            }
        }
        delete p;
    }

    //nie jest liœciem i ma jednego syna
    else if(empty(p->getLeft()) && !empty(p->getRight()) || !empty(p->getLeft()) && empty(p->getRight())){
        Node* r = NULL;
        cout<<"ojciec"<<endl;
        if(empty(p->getRight())){
            r=p->getLeft();
        }else{
            r=p->getRight();
        }

        Node* parent=p->getParent();

        if(empty(parent)){
            root= r;
        }
        else{
            if(parent->getLeft()==p){
                parent->setLeft(r);
                r->setParent(parent);
            }
            else{
                parent->setRight(r);
                r->setParent(parent);
            }
            delete p;
        }
    }
    else//ma dwoch synow
    {
        cout<<p->getValue()<<endl;
        cout<<"korzen"<<endl;
        Node* succ= successor(p);
        cout<<succ->getValue();
        cout << "1"<< endl;
        p->setValue(succ->getValue());
        cout<<p->getValue()<<endl;
        cout << "2" << endl;
        del(successor(p));
        cout << "3" << endl;
        delete succ;
        cout << "$$$";


    }
}
int main(){
    BSTree* b= new BSTree();

    b->insert(25);
    b->insert(15);
    b->insert(50);
    b->insert(10);
    b->insert(22);
    b->insert(35);
    b->insert(70);
    b->insert(4);
    b->insert(12);
    b->insert(18);
    b->insert(24);
    b->insert(31);
    b->insert(44);
    b->insert(66);
    b->insert(90);

    b->inorder(b->getRoot());

    cout<<endl;
    Node* p = b->search(4);
    Node* p2 = b->search(90);
    Node* p3 = b->search(70);
    Node* p4 = b->search(25);
    cout<<b->successor(p4)->getValue()<<endl;

    b->del(p4);
    cout<<"Nie udalo sie"<<endl;
    b->inorder(b->getRoot());
    cout<<endl;

    Node* a = b->minimum(b->getRoot());
    Node* c = b->maximum(b->getRoot());
    cout<<a->getValue()<<" , "<<c->getValue();
    cout<<endl;
    b->inorder(b->getRoot());

}
