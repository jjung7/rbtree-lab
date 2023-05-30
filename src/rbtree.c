#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void traverse_and_delete_node(rbtree *t, node_t *node);
void rbtree_insert_fixup(rbtree *t, node_t *node);
void left_rotate(rbtree *t, node_t *node);
void right_rotate(rbtree *t, node_t *node);
void transplant(rbtree *t, node_t *u, node_t *v);
void erase_fixup(rbtree *t, node_t *node);
node_t *find_succ(rbtree *t, node_t *p);

/* 1️⃣ RB tree 구조체 생성 */
// 새 트리를 생성하는 함수
rbtree *new_rbtree(void)
{
  // tree 구조체 동적 할당
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));

  // nil 노드 생성 및 초기화
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK; // nil 노드는 항상 BLACK

  // tree의 nil과 root를 nil 노드로 설정 (tree가 빈 경우 root는 nil노드여야 한다.)
  t->nil = t->root = nil;

  return t;
}

/* 2️⃣ RB tree 구조체가 차지했던 메모리 반환 */
// 트리를 순회하면서 각 노드의 메모리를 반환하는 함수
void delete_rbtree(rbtree *t)
{
  node_t *node = t->root;
  if (node != t->nil)
    traverse_and_delete_node(t, node);

  // nil 노드와 rbtree 구조체의 메모리를 반환
  free(t->nil);
  free(t);
}

// 각 노드와 그 자식 노드들의 메모리를 반환하는 함수
void traverse_and_delete_node(rbtree *t, node_t *node)
{
  if (node->left != t->nil)
    traverse_and_delete_node(t, node->left);
  if (node->right != t->nil)
    traverse_and_delete_node(t, node->right);
  // 현재 노드의 메모리를 반환
  free(node);
}

void left_rotate(rbtree *t, node_t *node)
{
  node_t *y = node->right;
  node->right = y->left;

  if (y->left != t->nil)
  {
    y->left->parent = node;
  }

  y->parent = node->parent;
  if (node == t->root)
  {
    t->root = y;
  }
  else if (node == node->parent->left)
  {
    node->parent->left = y;
  }
  else
  {
    node->parent->right = y;
  }

  y->left = node;
  node->parent = y;
}

void right_rotate(rbtree *t, node_t *node)
{
  node_t *y = node->left;
  node->left = y->right;

  if (y->right != t->nil)
  {
    y->right->parent = node;
  }

  y->parent = node->parent;
  if (node == t->root)
  {
    t->root = y;
  }
  else if (node == node->parent->left)
  {
    node->parent->left = y;
  }
  else
  {
    node->parent->right = y;
  }

  y->right = node;
  node->parent = y;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;
  new_node->left = t->nil;
  new_node->right = t->nil;

  node_t *cur = t->root;
  node_t *prev = t->nil;
  while (cur != t->nil)
  {
    prev = cur;
    if (key < cur->key)
    {
      cur = cur->left;
    }
    else
    {
      cur = cur->right;
    }
  }

  new_node->parent = prev;
  if (prev == t->nil)
  {
    // The tree was empty, so set the root to the new node
    t->root = new_node;
  }
  else if (key < prev->key)
  {
    prev->left = new_node;
  }
  else
  {
    prev->right = new_node;
  }

  rbtree_insert_fixup(t, new_node);
  return new_node;
}

void rbtree_insert_fixup(rbtree *t, node_t *node)
{
  node_t *parent = node->parent;
  node_t *grandparent = node->parent->parent;
  node_t *uncle;
  // 노드의 부모가 왼쪽 서브 트리일 경우
  while (parent->color == RBTREE_RED)
  {
    if (parent == grandparent->left)
    {
      uncle = grandparent->right;

      // CASE 1 노드의 삼촌이 빨강인 경우
      if (uncle->color == RBTREE_RED)
      {
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandparent->color = RBTREE_RED;
        node = grandparent;
        parent = node->parent;
        grandparent = parent->parent;
      }
      // CASE 2 삼촌이 흑색이며 노드가 오른쪽 자식인 경우
      else
      {
        if (node == parent->right)
        {
          node = parent;
          left_rotate(t, node);
          parent = node->parent;
        }
        // CASE 3 삼촌이 흑색이며 노드가 왼쪽 자식인 경우
        parent->color = RBTREE_BLACK;
        grandparent->color = RBTREE_RED;
        right_rotate(t, grandparent);
        break;
      }
    }
    // 노드의 부모가 오른쪽 서브 트리일 경우
    else
    {
      uncle = grandparent->left;
      // CASE 1 노드의 삼촌이 빨강인 경우
      if (uncle->color == RBTREE_RED)
      {
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandparent->color = RBTREE_RED;
        node = grandparent;
        parent = node->parent;
        grandparent = parent->parent;
      }
      // CASE 2 삼촌이 흑색이며 노드가 왼쪽 자식인 경우
      else
      {
        if (node == parent->left)
        {
          node = parent;
          right_rotate(t, node);
          parent = node->parent;
        }
        // CASE 3 삼촌이 흑색이며 노드가 오른쪽 자식인 경우
        parent->color = RBTREE_BLACK;
        grandparent->color = RBTREE_RED;
        left_rotate(t, grandparent);
        break;
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

// TODO: implement insert
//   return t->root;
// }

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *cur = t->root;
  while (cur != t->nil)
  {
    if (cur->key == key)
    {
      return cur;
    }
    else if (cur->key < key)
    {
      cur = cur->right;
    }
    else if (cur->key > key)
    {
      cur = cur->left;
    }
  }
  return NULL;
  // TODO: implement find
}

node_t *rbtree_min(const rbtree *t)
{
  node_t *min = t->root;
  if (t->root == t->nil)
  {
    return NULL;
  }
  while (min->left != t->nil)
  {
    min = min->left;
  }
  return min;

  // TODO: implement find
}

node_t *rbtree_max(const rbtree *t)
{
  node_t *max = t->root;
  if (t->root == t->nil)
  {
    return NULL;
  }
  while (max->right != t->nil)
  {
    max = max->right;
  }
  return max;
  // TODO: implement find
}
void transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
    t->root = v;
  else if (u->parent->left == u)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}
int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  if (p == NULL)
    return 0;
  node_t *y = p, *x = NULL;
  color_t y_org_color = y->color;
  if (p->left == t->nil)
  {
    x = p->right;
    transplant(t, p, p->right);
  }
  else if (p->right == t->nil)
  {
    x = p->left;
    transplant(t, p, p->left);
  }
  else
  {
    y = find_succ(t, p->right);
    y_org_color = y->color;
    x = y->right;
    if (y->parent == p)
      x->parent = y;
    else
    {
      transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  free(p);
  if (y_org_color == RBTREE_BLACK)
    erase_fixup(t, x);

  return 0;
}

node_t *find_succ(rbtree *t, node_t *p)
{
  node_t *cur = p;
  while (cur->left != t->nil)
    cur = cur->left;
  return cur;
}

void erase_fixup(rbtree *t, node_t *x)
{
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    node_t *w = x == x->parent->left ? x->parent->right : x->parent->left;
    if (x == x->parent->left)
    {
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->right->color == RBTREE_BLACK)
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = w->parent->color;
        w->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root; // 탈출
      }
    }
    else
    {
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->left->color == RBTREE_BLACK)
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = w->parent->color;
        w->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root; // 탈출
      }
    }
  }
  x->color = RBTREE_BLACK;
}

// TODO: implement erase

void indorder_to_array(const rbtree *t, node_t *root, int *pidx, key_t *arr)
{
  if (root != t->nil)
  {
    indorder_to_array(t, root->left, pidx, arr);
    arr[(*pidx)++] = root->key;
    indorder_to_array(t, root->right, pidx, arr);
  }
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  int idx = 0;
  int *pidx = &idx;
  indorder_to_array(t, t->root, pidx, arr);
  return 0;
  // TODO: implement to_array
}