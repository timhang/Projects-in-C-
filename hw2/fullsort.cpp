#include <iostream>
using namespace std;

struct Node {
    /*Node(int v, Node* n) 
    { value = v; next = n; }
    Node(){value = -1;next = NULL;}*/
    int value;
    Node *next;
};

Node* fullsort(Node* in);

/*Node* remove(Node* in, Node* outlier){
    if(in==outlier){
        Node*temp = in;
        in = in->next;
        delete temp;
        return in;
    }
    if(in->next == outlier){
        Node* temp = outlier;
        in->next = outlier->next;
        delete temp;
        return in;
    }
    remove(in->next,outlier);

    return in;
}*/


Node* fullsort(Node* in){
    if(in==NULL || in->next ==NULL) return in;
    Node*p = fullsort (in->next);
    if(p!=NULL){
        if(in->value>p->value){
            int temp = in->value;
            in->value = p->value;
            p->value = temp;
            fullsort(in->next);
        }

    }
    return in;
}


/*Node* destr(Node*in){
    if(in==NULL)return NULL;
    Node*n=destr(in->next);
    if(n)
        delete n;
    return in;
}
int main(){
    Node * in = new Node(20, new Node(1, new Node(2,new Node(3,new Node(4,new Node(
        5, new Node(6, NULL)))))));
    Node* head = fullsort(in);

    if(head!=NULL){
    Node* temp= head;
    while(temp->next){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<temp->value;

    Node*n = destr(head);
    delete n;};
    //cout<<funcA(in)->value<<endl<<(funcA(in)->next)->value<<endl;
    //cout<<((funcA(in)->next)->next)->value<<endl;
    return 0;
}*/