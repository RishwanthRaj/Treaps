 #include<iostream>
#include<stdlib.h>
using namespace std;
struct node
{
    int data,prior;
    node *left,*right,*par;
};

class treap
{
    private:
            node* root;
            int count;
    public:
            int values[20],priors[20];
            treap()
            {
                count=0;
                root=NULL;
            }
            treap(int key)
            {
                node *n=new node;
                n->data=key;
                n->prior=rand()%150;
                n->left=NULL;
                n->right=NULL;
                n->par=NULL;
                root=n;
                values[0]=key;
                priors[0]=n->prior;
                count=1;
            }
            treap(int key,int pr)
            {
                node *n=new node;
                n->data=key;
                n->prior=pr;
                n->left=NULL;
                n->right=NULL;
                n->par=NULL;
                root=n;
                values[0]=key;
                priors[0]=n->prior;
                count=1;
            }
            treap(const treap& t)
            {
                this->root=t.root;
            }
            treap operator=(const treap& t)
            {
                this->root=t.root;
                return t;
            }
            node* create(int key,node *parent)
            {
                node *n=new node;
                n->data=key;
                n->prior=rand()%150;
                n->left=NULL;
                n->right=NULL;
                n->par=parent;
                return n;
            }
            node* createelt(int key,int pr,node *parent)
            {
                node *n=new node;
                n->data=key;
                n->prior=pr;
                n->left=NULL;
                n->right=NULL;
                n->par=parent;
                return n;
            }
            void insert(int key)
            {
                node *ptr,*parent;
                ptr=root;
                while(ptr!=NULL)
                {
                    if(key>(ptr->data))
                    {
                        parent=ptr;
                        ptr=ptr->right;

                    }
                    else
                    {
                        parent=ptr;
                        ptr=ptr->left;

                    }
                }
                node *n=create(key,parent);
                addelt(n);
                if(key>(parent->data))
                {
                    parent->right=n;
                }
                else
                {
                    parent->left=n;
                }

                while((((n->par)->prior)<n->prior))
                {

                        if((n->data)>((n->par)->data))
                        {
                            n=leftrotate(n->par);

                        }
                        else if((n->data)<((n->par)->data))
                        {
                            n=rightrotate(n->par);

                        }
                    if(n->par==NULL)
                    {
                        break;
                    }
                }
                if((n->par)==NULL)
                {
                    root=n;
                }
            }
            void insertelt(int key,int pr)
            {
                int flag=0;
                if(root==NULL)
                {
                    root=createelt(key,pr,NULL);
                    flag=1;
                    addelt(root);
                }
                if(flag==0)
                {
                node *ptr,*parent;
                ptr=root;
                while(ptr!=NULL)
                {
                    if(key>(ptr->data))
                    {
                        parent=ptr;
                        ptr=ptr->right;

                    }
                    else
                    {
                        parent=ptr;
                        ptr=ptr->left;

                    }
                }
                node *n=createelt(key,pr,parent);
                addelt(n);
                if(key>(parent->data))
                {
                    parent->right=n;
                }
                else
                {
                    parent->left=n;
                }

                while((((n->par)->prior)<n->prior))
                {

                        if((n->data)>((n->par)->data))
                        {
                            n=leftrotate(n->par);

                        }
                        else if((n->data)<((n->par)->data))
                        {
                            n=rightrotate(n->par);

                        }
                    if(n->par==NULL)
                    {
                        break;
                    }
                }
                if((n->par)==NULL)
                {
                    root=n;
                }
                }
            }
            node* rightrotate(node *n)
            {
                node *x,*y;
                x=n->left;
                y=x->right;
                x->right=n;
                n->left=y;
                if(((n->par)!=NULL)&&(((n->par)->data)>(x->data)))
                {
                    (n->par)->left=x;
                }
                else if(((n->par)!=NULL)&&(((n->par)->data)<(x->data)))
                {
                    (n->par)->right=x;
                }
                x->par=n->par;
                n->par=x;
                if(y!=NULL)
                {
                    y->par=n;
                }

                return x;
            }
            node* leftrotate(node *n)
            {
                node *x,*y;
                x=n->right;
                y=x->left;
                x->left=n;
                n->right=y;
                if(((n->par)!=NULL)&&(((n->par)->data)>(x->data)))
                {
                    (n->par)->left=x;
                }
                else if(((n->par)!=NULL)&&(((n->par)->data)<(x->data)))
                {
                    (n->par)->right=x;
                }
                x->par=n->par;
                n->par=x;
                if(y!=NULL)
                {
                    y->par=n;
                }
                return x;
            }
            node* maxprior(node* n1,node* n2)
            {
                n1->prior>n2->prior?n1:n2;
            }
            int getcount()
            {
                return count;
            }
            node* merge(node* &t,node* l,node* r)
            {
                if (!l || !r)
                    t = l ? l : r;
                else if (l->prior > r->prior)
                    merge (l->right, l->right, r),  t = l;
                else
                    merge (r->left, l, r->left),  t = r;
                return t;
            }
            void delete_node(int key,node* n)
            {
                while(key!=n->data)
                {
                    if(key>(n->data))
                    {
                        n=n->right;
                    }
                    else if(key<(n->data))
                    {
                        n=n->left;
                    }
                }
                deleteelt(n);
                int flag=0;
                if(n==root)
                {
                    flag=1;
                }
                if((n->left)!=NULL&&n->right!=NULL)
                {
                    node* temp=n->par;
                    if(flag==0)
                    {
                        if(key>(n->par->data))
                        {
                            n->par->right=merge(n,n->left,n->right);
                            n->par=temp;
                        }
                        else if(key<(n->par->data))
                        {
                            n->par->left=merge(n,n->left,n->right);
                            n->par=temp;
                        }
                    }
                    else
                    {
                        root=merge(n,n->left,n->right);
                        root->par=NULL;
                    }
                }
                else if((n->left)!=NULL&&(n->right)==NULL)
                {
                    if(flag==0)
                    {
                        if(n->data>(n->par)->data)
                        {
                            n->par->right=n->left;
                        }
                        else
                            n->par->left=n->left;
                        delete n;
                    }
                    else
                    {
                        root=n->left;
                        root->par=NULL;
                    }
                }
                else if((n->left)==NULL&&(n->right)!=NULL)
                {
                    if(flag==0)
                    {
                        if(n->data>(n->par)->data)
                        {
                            n->par->right=n->right;
                        }
                        else
                            n->par->left=n->right;
                        delete n;
                    }
                    else
                    {
                        root=n->right;
                        root->par=NULL;
                    }
                }
                else
                {
                    if(flag==0)
                    {
                        if(n->data>(n->par)->data)
                        {
                            n->par->right=NULL;
                            n->par=NULL;
                        }
                        else if(n->data<(n->par)->data)
                        {
                            n->par->left=NULL;
                            n->par=NULL;
                        }
                        delete n;
                    }
                    else
                    {
                        root=NULL;
                        root->par=NULL;
                    }
                }
            }
            void inorder(node* n)
            {
                if (n == NULL)
                    return;
                inorder(n->left);
                cout << n->data << "("<<n->prior<<")"<<endl;
                inorder(n->right);
            }
            void preorder(node* n)
            {
                if (n == NULL)
                    return;
                cout << n->data << "("<<n->prior<<")"<<endl;
                preorder(n->left);
                preorder(n->right);
            }
            void addelt(node* n)
            {
                if (n == NULL)
                    return;
                values[count]=n->data;priors[count]=n->prior;
                count++;
            }
            void deleteelt(node* n)
            {
                int j;
                if (n == NULL)
                    return;
                for(int i=0;i<count+1;i++)
                {
                    if(values[i]==n->data)
                    {
                        j=i;
                    }
                }
                for(int k=j;k<count;k++)
                {
                   values[k]=values[k+1];
                   priors[k]=priors[k+1];
                }
                count--;
            }
            node* getRoot()
            {
                return root;
            }
            void printLevelOrder(node* root1)
            {
                int h = height(root1);
                int i;
                for (i=1; i<=h; i++)
                printGivenLevel(root1, i);
            }

            void printGivenLevel(node* root1,int level)
            {
                if(root1==NULL)
                    return;
                if (level==1)
                    cout<<root1->data<<"("<<root1->prior<<")"<<"\t";
                else if(level>1)
                {
                    printGivenLevel(root1->left, level-1);
                    printGivenLevel(root1->right, level-1);
                }
            }

            int height(node* node)
            {
                if (node==NULL)
                    return 0;
                else
                {
                    int lheight = height(node->left);
                    int rheight = height(node->right);
                    if (lheight > rheight)
                        return(lheight+1);
                    else return(rheight+1);
                }
            }


            treap* uniontreap(treap *tr1)
            {
                int flag=0;
                treap* tr3;
                tr3=this;
                for(int c=0;c<tr1->getcount();c++)
                {
                    for(int m=0;m<tr3->getcount();m++)
                    {
                        if(tr1->values[c]==tr3->values[m])
                        {
                            flag=1;
                        }
                    }
                    if(flag==0)
                    {
                        tr3->insertelt(tr1->values[c],tr1->priors[c]);
                    }
                    flag=0;
                }
                return tr3;
            }


            treap* intersectiontreap(treap *tr1)
            {
                int flag=0;
                treap* tr3=new treap;
                for(int c=0;c<tr1->getcount();c++)
                {
                    for(int m=0;m<this->getcount();m++)
                    {
                        if(tr1->values[c]==this->values[m])
                        {
                            flag=1;
                        }
                        if(flag==1)
                        {
                            tr3->insertelt(this->priors[m]>tr1->priors[c]?this->values[m]:tr1->values[c],this->priors[m]>tr1->priors[c]?this->priors[m]:tr1->priors[c]);
                            flag=0;
                        }
                    }
                }
                return tr3;
            }

            treap* difference(treap* tr)
            {
                for(int c=0;c<this->getcount();c++)
                {
                    for(int m=0;m<tr->getcount();m++)
                    {
                        if(this->values[c]==tr->values[m])
                        {
                            delete_node(this->values[c],this->getRoot());
                        }
                    }
                }
                return this;
            }


            void display()
            {
                for(int  c=0;c<count+1;c++)
                {
                    cout<<values[c]<<"("<<priors[c]<<")";
                }
            }
};

int main()
{
/*    treap t(70);
    t.insert(44);
    t.insert(88);
    t.insert(36);
    t.insert(25);
    t.insert(50);
    cout<<"Original treap 1:"<<"\n";
    t.printLevelOrder(t.getRoot());
    cout<<"\n";
    t.delete_node(36,t.getRoot());
    cout<<"Treap 1 after deleting '36':"<<"\n";
    t.printLevelOrder(t.getRoot());
    cout<<"\n";
    t.insert(36);
    treap s(6);
    s.insert(12);
    s.insert(70);
    s.insert(50);
    s.insert(80);
    cout<<"Original treap 2:"<<"\n";
    s.printLevelOrder(s.getRoot());
    cout<<"\n";
    treap *a,*b,*c;
   /* a=t.uniontreap(&s);
    cout<<"Union of treap 1 and treap 2:"<<"\n";
    a->printLevelOrder(a->getRoot());
    cout<<"\n";*/
    /*b=t.intersectiontreap(&s);
    cout<<"Intersection of treap 1 and treap 2:"<<"\n";
    b->printLevelOrder(b->getRoot());
    cout<<"\n";*/
 /*   c=t.difference(&s);
    cout<<"Difference of treap 1 from treap 2:"<<"\n";
    c->inorder(c->getRoot());
    cout<<"\n";*/

//    t.delete_node(88,t.getRoot());
//    t.preorder(t.getRoot());
//    t.printLevelOrder(t.getRoot());

    treap t(70,120);
    t.insertelt(60,50);
    t.insertelt(40,32);
    t.insertelt(12,10);
    treap s(12,120);
    s.insertelt(40,50);
    s.insertelt(60,32);
    s.insertelt(70,10);
    t.printLevelOrder(t.getRoot());
    cout<<"\n";
    s.printLevelOrder(s.getRoot());
    return 0;
}
