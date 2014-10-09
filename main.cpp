#include <stdio.h>

struct TREE
{
    int data;
    TREE *left;
    TREE *right;
    int mark;
} *first_x=NULL, *last_x=NULL;

void Create(TREE *&root, int n, int *A);
void Find(TREE *root, int x);
void Out(TREE *root);
void find_next(TREE *root, TREE *&first, TREE *&second);
void Mark(TREE *root,int mark);

int main()
{
    FILE *f=fopen("input.txt","rt");
    int n;
    fscanf(f,"%d",&n);
    int i, *A=new int [n];
    for (i=0;i<n;i++)
        fscanf(f,"%d",A+i);
    fclose(f);
    TREE *root=NULL;
    Create(root,n,A);
    int x;
    printf("\nEnter x: ");
    scanf("%d",&x);
    Find(root,x);
    if (first_x)
        Mark(first_x,1);
    if (last_x)
        Mark(last_x,2);
    Out(root);
    return 0;
}

void Create(TREE *&root, int n, int *A)
{
    static int i=n-1;
    if (n>0){
        root=new TREE;
        root->data=A[i--];
        root->left=NULL;
        root->right=NULL;
        int temp=n/2;
        Create(root->left,temp,A);
        Create(root->right,n-temp-1,A);
    }
}

void Find(TREE *root, int x)
{
    root->mark=0;
    if (root->data==x){
        if (first_x==NULL)
            first_x=root;
        last_x=root;
    }
    TREE *first, *second;
    find_next(root, first, second);
    if (first)
        Find(first,x);
    if (second)
        Find(second,x);
}

void Mark(TREE *root,int mark)
{
    if (root)
    {
        root->mark+=mark;
        Mark(root->left,mark);
        Mark(root->right,mark);
    }
}

void Out(TREE *root)
{
    printf("%d\t%d\n",root->data,root->mark);
    TREE *first, *second;
    find_next(root, first, second);
    if (first)
        Out(first);
    if (second)
        Out(second);
}

void find_next(TREE *root, TREE *&first, TREE *&second)
{
    bool fl=false,fr=false;
    int left, right;
    if (root->left!=NULL){
        left=root->left->data;
        fl=true;
    }
    if (root->right!=NULL){
        right=root->right->data;
        fr=true;
    }
    if (fl){
        if (fr){
            if (left<=right){
                first=root->left;
                second=root->right;
            }
            else{
                first=root->right;
                second=root->left;
            }
        }
        else{
            first=root->left;
            second=NULL;
        }
    }
    else{
        if(fr){
            first=root->right;
            second=NULL;
        }
        else{
            first=NULL;
            second=NULL;
        }
    }
}
