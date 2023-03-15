#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<time.h>
#define maxsize 100
#define elemtype int

enum tcolor { red, black };

typedef struct node
{
    elemtype data;
    struct node* lchild;
    struct node* rchild;
    struct node* parent;
    tcolor color;
}rbtnode;

/*����*/
rbtnode* rb_rotate_left(rbtnode* node, rbtnode* root)
{
    rbtnode* rchild = node->rchild;    //ָ��ָ��ָ�� right<--node->right

    if ((node->rchild = rchild->lchild))
    {
        rchild->lchild->parent = node;  //�ñ������ע��ͼ��node��Ϊb�ĸ�ĸ
    }
    rchild->lchild = node;   //node��Ϊrchild������

    if ((rchild->parent = node->parent))
    {
        if (node == node->parent->rchild)
        {
            node->parent->rchild = rchild;
        }
        else
        {
            node->parent->lchild = rchild;
        }
    }
    else
    {
        root = rchild;
    }
    node->parent = rchild;  //right��Ϊnode�ĸ�ĸ

    return root;
}


/*����*/
rbtnode* rb_rotate_right(rbtnode* node, rbtnode* root)
{
    rbtnode* lchild = node->lchild;

    if ((node->lchild = lchild->rchild))
    {
        lchild->rchild->parent = node;
    }
    lchild->rchild = node;

    if ((lchild->parent = node->parent))
    {
        if (node == node->parent->rchild)
        {
            node->parent->rchild = lchild;
        }
        else
        {
            node->parent->lchild = lchild;
        }
    }
    else
    {
        root = lchild;
    }
    node->parent = lchild;

    return root;
}


/*���ҽ��*/
rbtnode* rb_search(elemtype data, rbtnode* root, rbtnode** save)
{
    rbtnode* node = root, * parent = NULL;
    int ret;

    while (node)
    {
        parent = node;
        ret = node->data - data;
        if (0 < ret)
        {
            node = node->lchild;
        }
        else if (0 > ret)
        {
            node = node->rchild;
        }
        else
        {
            return node;
        }
    }

    if (save)
    {
        *save = parent;
    }

    return NULL;
}

//��������rb_search���ҽ��
rbtnode* rb_search(elemtype data, rbtnode* root)
{
    return rb_search(data, root, NULL);
}


/*������*/
rbtnode* rb_insert(elemtype key, elemtype data, rbtnode* root)
{
    rbtnode* parent = NULL, * node;

    parent = NULL;
    if ((node = rb_search(key, root, &parent)))  //����rb_search�ҵ�������ĵط�
    {
        return root;
    }

    node = (rbtnode*)malloc(sizeof(rbtnode)); //������
    node->data = data;
    node->parent = parent;
    node->lchild = node->rchild = NULL;
    node->color = red;

    if (parent)
    {
        if (parent->data > key)
        {
            parent->lchild = node;
        }
        else
        {
            parent->rchild = node;
        }
    }
    else
    {
        root = node;
    }

    return rb_insert_rebalance(node, root);   //������󣬵���rb_insert_rebalance�޸������������
}


//�������3�ֲ������
//�������������ص������Ժ���������3������������е��޸�������
//--------------------------------------------------------------
//������޸������3�����
//��z��ʾ��ǰ��㣬p[z]��ʾ��ĸ��p[p[z]]��ʾ�游��y��ʾ���塣
//--------------------------------------------------------------
rbtnode* rb_insert_rebalance(rbtnode* node, rbtnode* root)
{
    rbtnode* parent, * gparent, * uncle, * tmp;  //��ĸp[z]���游p[p[z]]������y����ʱ���*tmp

    while ((parent = node->parent) && parent->color == red)
    {     //parent Ϊnode�ĸ�ĸ���ҵ���ĸ����ɫΪ��ʱ
        gparent = parent->parent;   //gparentΪ�游

        if (parent == gparent->lchild)  //���游�����Ӽ�Ϊ��ĸʱ��
                                 //��ʵ����������䣬�޷Ǿ�����˳���ӡ���ĸ���游�Ĺ�ϵ��:D��
        {
            uncle = gparent->rchild;  //��������ĸ������y���Ǹ�ĸ���Һ��ӡ�

            if (uncle && uncle->color == red) //���1��z������y�Ǻ�ɫ��
            {
                uncle->color = black;   //��������y��Ϊ��ɫ
                parent->color = black;  //z�ĸ�ĸp[z]Ҳ��Ϊ��ɫ�����z��p[z]���Ǻ�ɫ�����⡣
                gparent->color = red;
                node = gparent;     //���游�����������z��ָ��z�������㣬����Ϊ��ɫ��
            //�������1�У�ֻ������z��Ϊ��ĸ���Һ��ӵ������
            }
            else                     //���2��z������y�Ǻ�ɫ�ģ�
            {
                if (parent->rchild == node)  //��zΪ�Һ���
                {
                    root = rb_rotate_left(parent, root); //����[���z���븸ĸ���]
                    tmp = parent;
                    parent = node;
                    node = tmp;     //parent��node ������ɫ
                }
                //���3��z������y�Ǻ�ɫ�ģ���ʱz��Ϊ�����ӡ�
                       //ע�⣬1�����3�����������2�仯�����ġ�
                       //......2��z���������Ǻ�ɫ�ģ�����������1�ˡ�
                parent->color = black;   //z�ĸ�ĸp[z]��Ϊ��ɫ
                gparent->color = red;    //ԭ�游�����Ϊ��ɫ
                root = rb_rotate_right(gparent, root); //����[���z�����游���]
            }
        }

        else
        {
            // if (parent == gparent->right) ���游���Һ��Ӽ�Ϊ��ĸʱ���������뿴���������µ�23¥��ͬʱ����лSupremeHoverָ������
            uncle = gparent->lchild;  //�游��������Ϊ�����㡣[ԭ�������ϲ���һ����]
            if (uncle && uncle->color == red)  //���1��z������y�Ǻ�ɫ��
            {
                uncle->color = black;
                parent->color = black;
                gparent->color = red;
                node = gparent;           //ͬ�ϡ�
            }
            else                               //���2��z������y�Ǻ�ɫ�ģ�
            {
                if (parent->lchild == node)  //��zΪ����
                {
                    root = rb_rotate_right(parent, root);  //�Խ��parent��root����
                    tmp = parent;
                    parent = node;
                    node = tmp;       //parent��node ������ɫ
                }
                //�������2�ı仯����Ϊ�����3.
                parent->color = black;
                gparent->color = red;
                root = rb_rotate_left(gparent, root);   //�Խ��gparent��root����
            }
        }
    }

    root->color = black; //����㣬����������������Ϊ��ɫ��
    return root;      //���ظ���㡣
}


/*ɾ�����*/
rbtnode* rb_erase(elemtype key, rbtnode* root)
{
    rbtnode* child, * parent, * old, * left, * node;
    tcolor color;

    if (!(node = rb_search(key, root, NULL)))  //����rb_search_auxiliary����Ҫɾ���Ľ��
    {
        printf("key %d is not exist!/n");
        return root;
    }

    old = node;

    if (node->lchild && node->rchild)
    {
        node = node->rchild;
        while ((left = node->lchild) != NULL)
        {
            node = left;
        }
        child = node->rchild;
        parent = node->parent;
        color = node->color;

        if (child)
        {
            child->parent = parent;
        }
        if (parent)
        {
            if (parent->lchild == node)
            {
                parent->lchild = child;
            }
            else
            {
                parent->rchild = child;
            }
        }
        else
        {
            root = child;
        }

        if (node->parent == old)
        {
            parent = node;
        }

        node->parent = old->parent;
        node->color = old->color;
        node->rchild = old->rchild;
        node->lchild = old->lchild;

        if (old->parent)
        {
            if (old->parent->lchild == old)
            {
                old->parent->lchild = node;
            }
            else
            {
                old->parent->rchild = node;
            }
        }
        else
        {
            root = node;
        }

        old->lchild->parent = node;
        if (old->rchild)
        {
            old->rchild->parent = node;
        }
    }
    else
    {
        if (!node->lchild)
        {
            child = node->rchild;
        }
        else if (!node->rchild)
        {
            child = node->lchild;
        }
        parent = node->parent;
        color = node->color;

        if (child)
        {
            child->parent = parent;
        }
        if (parent)
        {
            if (parent->lchild == node)
            {
                parent->lchild = child;
            }
            else
            {
                parent->rchild = child;
            }
        }
        else
        {
            root = child;
        }
    }

    free(old);

    if (color == black)
    {
        root = rb_erase_rebalance(child, parent, root); //����rb_erase_rebalance���ָ����������
    }

    return root;
}


//�������4��ɾ�����
//----------------------------------------------------------------
//������޸�ɾ����4�����
//Ϊ�˱�ʾ����ע�͵ķ��㣬ҲΪ���������������ҵĂzƪ�������Ӧ��
//x��ʾҪɾ���Ľ�㣬*other��w��ʾ�ֵܽ�㣬
//----------------------------------------------------------------
rbtnode* rb_erase_rebalance(rbtnode* node, rbtnode* parent, rbtnode* root)
{
    rbtnode* other, * o_left, * o_right;   //x���ֵ�*other���ֵ�����*o_left,*o_right

    while ((!node || node->color == black) && node != root)
    {
        if (parent->lchild == node)
        {
            other = parent->rchild;
            if (other->color == red)   //���1��x���ֵ�w�Ǻ�ɫ��
            {
                other->color = black;
                parent->color = red;   //�����У��ı���ɫ��w->�ڡ�p[x]->�졣
                root = rb_rotate_left(parent, root);  //�ٶ�p[x]��һ������
                other = parent->rchild;  //x�����ֵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ�����������Ч����
            }
            if ((!other->lchild || other->lchild->color == black) &&
                (!other->rchild || other->rchild->color == black))
                //���2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��

            {                         //����w��w���������Ӷ��Ǻ�ɫ�ģ�����x��w�ϵ�ȥ��һ��ɫ��
                other->color = red;   //���ǣ��ֵ�w��Ϊ��ɫ��
                node = parent;    //p[x]Ϊ�½��x
                parent = node->parent;  //x<-p[x]
            }
            else                       //���3��x���ֵ�w�Ǻ�ɫ�ģ�
            {                          //�ң�w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                if (!other->rchild || other->rchild->color == black)
                {
                    if ((o_left = other->lchild))   //w��������left[w]����ɫ������
                    {
                        o_left->color = black;    //w�����ӱ�Ϊ�ɺ�->��ɫ
                    }
                    other->color = red;           //w�ɺ�->��
                    root = rb_rotate_right(other, root);  //�ٶ�w�����������Ӷ�������ʻָ���
                    other = parent->rchild;        //�仯��ģ��������Һ��ӣ���Ϊ�µ��ֵܽ��w��
                }
                //���4��x���ֵ�w�Ǻ�ɫ��

                other->color = parent->color;  //���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ��
                parent->color = black;  //�ѵ�ǰ�ڵ㸸�ڵ�Ⱦ�ɺ�ɫ
                if (other->rchild)      //��w���Һ����Ǻ�
                {
                    other->rchild->color = black;  //�ֵܽڵ�w�Һ���Ⱦ�ɺ�ɫ
                }
                root = rb_rotate_left(parent, root);  //������һ������
                node = root;   //����x��Ϊ����
                break;
            }
        }
        //������������������ԭ��һ�¡������ԡ�
        else
        {
            other = parent->lchild;
            if (other->color == red)
            {
                other->color = black;
                parent->color = red;
                root = rb_rotate_right(parent, root);
                other = parent->lchild;
            }
            if ((!other->lchild || other->lchild->color == black) &&
                (!other->rchild || other->rchild->color == black))
            {
                other->color = red;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->lchild || other->lchild->color == black)
                {
                    if ((o_right = other->rchild))
                    {
                        o_right->color = black;
                    }
                    other->color = red;
                    root = rb_rotate_left(other, root);
                    other = parent->lchild;
                }
                other->color = parent->color;
                parent->color = black;
                if (other->lchild)
                {
                    other->lchild->color = black;
                }
                root = rb_rotate_right(parent, root);
                node = root;
                break;
            }
        }
    }

    if (node)
    {
        node->color = black;  //���node[����������Ϊ�˸����]����Ϊ��ɫ��
    }
    return root;  //����root
}


/*������*/
int main(void)
{
    int i, count = 100;
    elemtype key;
    rbtnode* root = NULL, * node = NULL;

    srand(time(NULL));
    for (i = 1; i < count; ++i)
    {
        key = rand() % count;
        if ((root = rb_insert(key, i, root)))
        {
            printf("[i = %d] insert key %d success!/n", i, key);
        }
        else
        {
            printf("[i = %d] insert key %d error!/n", i, key);
            exit(-1);
        }

        if ((node = rb_search(key, root)))
        {
            printf("[i = %d] search key %d success!/n", i, key);
        }
        else
        {
            printf("[i = %d] search key %d error!/n", i, key);
            exit(-1);
        }
        if (!(i % 10))
        {
            if ((root = rb_erase(key, root)))
            {
                printf("[i = %d] erase key %d success/n", i, key);
            }
            else
            {
                printf("[i = %d] erase key %d error/n", i, key);
            }
        }
    }

    return 0;
}