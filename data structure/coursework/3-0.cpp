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

/*左旋*/
rbtnode* rb_rotate_left(rbtnode* node, rbtnode* root)
{
    rbtnode* rchild = node->rchild;    //指定指针指向 right<--node->right

    if ((node->rchild = rchild->lchild))
    {
        rchild->lchild->parent = node;  //好比上面的注释图，node成为b的父母
    }
    rchild->lchild = node;   //node成为rchild的左孩子

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
    node->parent = rchild;  //right成为node的父母

    return root;
}


/*右旋*/
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


/*查找结点*/
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

//返回上述rb_search查找结果
rbtnode* rb_search(elemtype data, rbtnode* root)
{
    return rb_search(data, root, NULL);
}


/*插入结点*/
rbtnode* rb_insert(elemtype key, elemtype data, rbtnode* root)
{
    rbtnode* parent = NULL, * node;

    parent = NULL;
    if ((node = rb_search(key, root, &parent)))  //调用rb_search找到插入结点的地方
    {
        return root;
    }

    node = (rbtnode*)malloc(sizeof(rbtnode)); //分配结点
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

    return rb_insert_rebalance(node, root);   //插入结点后，调用rb_insert_rebalance修复红黑树的性质
}


//红黑树的3种插入情况
//接下来，咱们重点分析针对红黑树插入的3种情况，而进行的修复工作。
//--------------------------------------------------------------
//红黑树修复插入的3种情况
//用z表示当前结点，p[z]表示父母、p[p[z]]表示祖父、y表示叔叔。
//--------------------------------------------------------------
rbtnode* rb_insert_rebalance(rbtnode* node, rbtnode* root)
{
    rbtnode* parent, * gparent, * uncle, * tmp;  //父母p[z]、祖父p[p[z]]、叔叔y、临时结点*tmp

    while ((parent = node->parent) && parent->color == red)
    {     //parent 为node的父母，且当父母的颜色为红时
        gparent = parent->parent;   //gparent为祖父

        if (parent == gparent->lchild)  //当祖父的左孩子即为父母时。
                                 //其实上述几行语句，无非就是理顺孩子、父母、祖父的关系。:D。
        {
            uncle = gparent->rchild;  //定义叔叔的概念，叔叔y就是父母的右孩子。

            if (uncle && uncle->color == red) //情况1：z的叔叔y是红色的
            {
                uncle->color = black;   //将叔叔结点y着为黑色
                parent->color = black;  //z的父母p[z]也着为黑色。解决z，p[z]都是红色的问题。
                gparent->color = red;
                node = gparent;     //将祖父当做新增结点z，指针z上移俩层，且着为红色。
            //上述情况1中，只考虑了z作为父母的右孩子的情况。
            }
            else                     //情况2：z的叔叔y是黑色的，
            {
                if (parent->rchild == node)  //且z为右孩子
                {
                    root = rb_rotate_left(parent, root); //左旋[结点z，与父母结点]
                    tmp = parent;
                    parent = node;
                    node = tmp;     //parent与node 互换角色
                }
                //情况3：z的叔叔y是黑色的，此时z成为了左孩子。
                       //注意，1：情况3是由上述情况2变化而来的。
                       //......2：z的叔叔总是黑色的，否则就是情况1了。
                parent->color = black;   //z的父母p[z]着为黑色
                gparent->color = red;    //原祖父结点着为红色
                root = rb_rotate_right(gparent, root); //右旋[结点z，与祖父结点]
            }
        }

        else
        {
            // if (parent == gparent->right) 当祖父的右孩子即为父母时。（解释请看本文评论下第23楼，同时，感谢SupremeHover指正！）
            uncle = gparent->lchild;  //祖父的左孩子作为叔叔结点。[原理还是与上部分一样的]
            if (uncle && uncle->color == red)  //情况1：z的叔叔y是红色的
            {
                uncle->color = black;
                parent->color = black;
                gparent->color = red;
                node = gparent;           //同上。
            }
            else                               //情况2：z的叔叔y是黑色的，
            {
                if (parent->lchild == node)  //且z为左孩子
                {
                    root = rb_rotate_right(parent, root);  //以结点parent、root右旋
                    tmp = parent;
                    parent = node;
                    node = tmp;       //parent与node 互换角色
                }
                //经过情况2的变化，成为了情况3.
                parent->color = black;
                gparent->color = red;
                root = rb_rotate_left(gparent, root);   //以结点gparent和root左旋
            }
        }
    }

    root->color = black; //根结点，不论怎样，都得置为黑色。
    return root;      //返回根结点。
}


/*删除结点*/
rbtnode* rb_erase(elemtype key, rbtnode* root)
{
    rbtnode* child, * parent, * old, * left, * node;
    tcolor color;

    if (!(node = rb_search(key, root, NULL)))  //调用rb_search_auxiliary查找要删除的结点
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
        root = rb_erase_rebalance(child, parent, root); //调用rb_erase_rebalance来恢复红黑树性质
    }

    return root;
}


//红黑树的4种删除情况
//----------------------------------------------------------------
//红黑树修复删除的4种情况
//为了表示下述注释的方便，也为了让下述代码与我的倆篇文章相对应，
//x表示要删除的结点，*other、w表示兄弟结点，
//----------------------------------------------------------------
rbtnode* rb_erase_rebalance(rbtnode* node, rbtnode* parent, rbtnode* root)
{
    rbtnode* other, * o_left, * o_right;   //x的兄弟*other，兄弟左孩子*o_left,*o_right

    while ((!node || node->color == black) && node != root)
    {
        if (parent->lchild == node)
        {
            other = parent->rchild;
            if (other->color == red)   //情况1：x的兄弟w是红色的
            {
                other->color = black;
                parent->color = red;   //上俩行，改变颜色，w->黑、p[x]->红。
                root = rb_rotate_left(parent, root);  //再对p[x]做一次左旋
                other = parent->rchild;  //x的新兄弟new w 是旋转之前w的某个孩子。其实就是左旋后的效果。
            }
            if ((!other->lchild || other->lchild->color == black) &&
                (!other->rchild || other->rchild->color == black))
                //情况2：x的兄弟w是黑色，且w的俩个孩子也都是黑色的

            {                         //由于w和w的俩个孩子都是黑色的，则在x和w上得去掉一黑色，
                other->color = red;   //于是，兄弟w变为红色。
                node = parent;    //p[x]为新结点x
                parent = node->parent;  //x<-p[x]
            }
            else                       //情况3：x的兄弟w是黑色的，
            {                          //且，w的左孩子是红色，右孩子为黑色。
                if (!other->rchild || other->rchild->color == black)
                {
                    if ((o_left = other->lchild))   //w和其左孩子left[w]，颜色交换。
                    {
                        o_left->color = black;    //w的左孩子变为由黑->红色
                    }
                    other->color = red;           //w由黑->红
                    root = rb_rotate_right(other, root);  //再对w进行右旋，从而红黑性质恢复。
                    other = parent->rchild;        //变化后的，父结点的右孩子，作为新的兄弟结点w。
                }
                //情况4：x的兄弟w是黑色的

                other->color = parent->color;  //把兄弟节点染成当前节点父节点的颜色。
                parent->color = black;  //把当前节点父节点染成黑色
                if (other->rchild)      //且w的右孩子是红
                {
                    other->rchild->color = black;  //兄弟节点w右孩子染成黑色
                }
                root = rb_rotate_left(parent, root);  //并再做一次左旋
                node = root;   //并把x置为根。
                break;
            }
        }
        //下述情况与上述情况，原理一致。分析略。
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
        node->color = black;  //最后将node[上述步骤置为了根结点]，改为黑色。
    }
    return root;  //返回root
}


/*主函数*/
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