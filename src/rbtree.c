#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
 
  // TODO: initialize struct if needed

  //  nil 노드 동적 할당 및 초기화
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  
  //  nil 노드의 색을 black(1)로 설정
  p->nil->color = 1;

  //  초기 root를 nil로 설정(빈 트리 상태)
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  // 트리의 메모리를 해체
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  // 새로운 key를 트리에 삽입

  // key는 값이 아니라 node이므로 node 생성
  // ? calloc으로 생성하는 이유
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;

  // 새로운 노드의 기초값 설정
  z->left = t->nil;
  z->right = t->nil;
  z->color = 0;

  node_t *x = t->root;
  node_t *y = t->nil;
  while(x!=t->nil){
    y = x;
    x = x->left;
  }
  z->parent = y;
  
  if(y==t->nil){
    t->root = z;
  }
  
  else if(z->key<y->key){
    t->root = z;
  }
  else{
    y->right = z;
  }

  z->left=t->nil;
  z->right = t->nil;
  z->color = 0;
  rbtree_insert_fixup(t, z);
  // 삽입으로 인해 틀어진 property 3 고치기

  return t->root;
}

// ! 임의로 함수 만들었음
// 왼쪽으로 회전하는 함수
node_t*rbtree_left_rotate(rbtree*t, node_t* x){
  node_t *y = x->right;

  // y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 회전
  x->right = y->left;

  // y의 왼쪽 서브 트리가 비어 있지 않다면 x는 서브 트리의 부모
  if(y->left!=t->nil){
    y->left->parent = x;
  }
  // x의 부모가 y가 됨
  y->parent = x->parent;
  // x가 루트인 경우
  if(x->parent==t->nil){
    t->root = y;
  }

  // 그렇지 않고 x가 왼쪽 자식인 경우 y는 왼쪽 자식이 됨
  else if(x==x->parent->left){
    x->parent->left = y;
  }
  // x가 오른쪽 자식인 경우 y는 오른쪽 자식이 됨
  else{
    x->parent->right = y;
  }
  // x를 y의 왼쪽 자식이 되게 함
  y->left = x;
  x->parent = y;
}

// ! 임의로 함수 만들었음
// 오른쪽으로 회전하는 함수
node_t*rbtree_right_rotate(rbtree*t, node_t* x){
  node_t *y = x->left;

  x->left = y->right;

  if(x->left!=t->nil){
    x->left->parent = x;
  }

  y->parent = x->parent;

  if(x->parent==t->nil){
    t->root = y;
  } else if(x==x->parent->left){
    x->parent->left = y;
  } else{
    x->parent->right = y;
  }

  y->right = x;
  x->parent = y;
}

// ! 임의로 함수 만들었음
// 삽입한 후 정렬하는 함수
node_t *rbtree_insert_fixup(rbtree *t, node_t *x)
{

  if(x->parent==x->parent->parent->right){
    node_t *y = x->parent->parent->left;
    // 만약 aunt의 색이 RED -> Colorflip
    if (y->color==0){
      x->parent->color = 1;
      y->color = 1;
      x->parent->parent->color = 0;
      x = x->parent->parent;
    } else { // 만약 aunt의 색이 BLACK -> Rotation
      if(x==x->parent->left) {
        x = x->parent;
        rbtree_left_rotate(t, x);
      }
        x->parent->color = 1;
        x->parent->parent->color = 0;
        rbtree_right_rotate(t, x->parent->parent);
    }
  } else {
      node_t *y = x->parent->parent->right;
      if(y->color==0){
        x->parent->color = 1;
        y->color = 1;
        x->parent->parent->color = 0;
        x = x->parent->parent;
      } else {
        if(x==x->parent->left){
          x = x->parent;
          rbtree_right_rotate(t, x);
        }
        x->parent->color = 1;
        x->parent->parent->color = 0;
        rbtree_left_rotate(t, x->parent->parent);
      }
   }
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  // 주어진 키를 검색
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  // 주어진 노드를 삭제하는 함수
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  // 트리의 요소들을 배열로 변환하는 함수
  return 0;
}
