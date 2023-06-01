/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/**
 * @brief 이진 탐색 트리를 초기화하는 함수입니다.
 * 
 * @param h 트리의 헤드 노드의 이중 포인터입니다.
 * @return int 초기화가 성공하면 1을 반환합니다.
 */
int initializeBST(Node** h) {
	// 트리가 비어있지 않으면 모든 노드를 제거합니다.
	if (*h != NULL)
		freeBST(*h);

	// 헤드 노드를 생성하고 초기화합니다.
	*h = (Node*)malloc(sizeof(Node));  // 헤드 노드 메모리 할당
	(*h)->left = NULL;  // 루트 노드 설정
	(*h)->right = *h;  // 헤드 노드 자신을 가리킴
	(*h)->key = -9999;  // 헤드 노드의 키 설정

	top = -1;  // 스택 초기화
	front = rear = -1;  // 큐 초기화

	return 1;
}


/**
 * @brief 재귀적으로 중위 순회를 수행하는 함수입니다.
 * 
 * @param ptr 순회를 시작할 노드의 포인터입니다.
 */
void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);  // 왼쪽 서브트리를 중위 순회합니다.
		printf(" [%d] ", ptr->key);  // 현재 노드의 값을 출력합니다.
		recursiveInorder(ptr->right);  // 오른쪽 서브트리를 중위 순회합니다.
	}
}


/**
 * @brief 스택을 활용하여 반복적으로 중위 순회를 수행하는 함수입니다.
 * 
 * @param node 순회를 시작할 노드의 포인터입니다.
 */
void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left)
			push(node);  // 왼쪽 자식 노드들을 스택에 삽입합니다.
		node = pop();  // 스택에서 노드를 팝하여 현재 노드로 설정합니다.

		if (!node)
			break;  // 현재 노드가 NULL이면 반복을 종료합니다.

		printf(" [%d] ", node->key);  // 현재 노드의 값을 출력합니다.

		node = node->right;  // 오른쪽 자식 노드로 이동합니다.
	}
}
/**
 * @brief 레벨 순서로 이진 트리를 순회하여 출력하는 함수입니다.
 * 
 * @param ptr 순회를 시작할 노드의 포인터입니다.
 */
void levelOrder(Node* ptr)
{
	if (!ptr)
		return;  // 트리가 비어있는 경우, 함수를 종료합니다.

	enQueue(ptr);  // 루트 노드를 큐에 삽입합니다.

	for (;;) {
		ptr = deQueue();  // 큐에서 노드를 디큐하여 현재 노드로 설정합니다.
		if (ptr) {
			printf(" [%d] ", ptr->key);  // 현재 노드의 값을 출력합니다.

			if (ptr->left)
				enQueue(ptr->left);  // 왼쪽 자식 노드를 큐에 삽입합니다.
			if (ptr->right)
				enQueue(ptr->right);  // 오른쪽 자식 노드를 큐에 삽입합니다.
		}
		else
			break;  // 디큐한 노드가 NULL인 경우 반복을 종료합니다.
	}
}


/**
 * @brief 이진 탐색 트리에 새로운 노드를 삽입하는 함수입니다.
 * 
 * @param head 트리의 헤드 노드를 가리키는 포인터입니다.
 * @param key 삽입할 노드의 값입니다.
 * @return int 삽입 성공 여부를 나타내는 정수 값입니다. 성공 시 1을 반환하고, 실패 시 0을 반환합니다.
 */
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드를 동적으로 할당합니다.
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;  // 트리가 비어있는 경우, 새로운 노드를 트리의 루트로 설정합니다.
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;  // 트리의 루트 노드를 가리키는 포인터입니다.

	Node* parentNode = NULL;  // 삽입할 위치의 부모 노드를 가리키는 포인터입니다.
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key)
			return 1;  // 이미 키 값이 존재하는 경우, 삽입을 중단하고 성공으로 간주합니다.

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;  // 현재 노드를 부모 노드로 설정합니다.

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;  // 현재 노드의 키 값이 입력된 키 값보다 작은 경우, 오른쪽 자식 노드로 이동합니다.
		else
			ptr = ptr->left;  // 현재 노드의 키 값이 입력된 키 값보다 큰 경우, 왼쪽 자식 노드로 이동합니다.
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;  // 부모 노드의 키 값이 입력된 키 값보다 큰 경우, 새로운 노드를 왼쪽 자식으로 연결합니다.
	else
		parentNode->right = newNode;  // 부모 노드의 키 값이 입력된 키 값보다 작은 경우, 새로운 노드를 오른쪽 자식으로 연결합니다.
	
	return 1;  // 삽입이 성공적으로 수행되었음을 나타내는 값 1을 반환합니다.
}


/**
 * @brief 이진 탐색 트리에서 노드를 삭제하는 함수
 * 
 * @param head 이진 탐색 트리의 헤드 노드
 * @param key 삭제할 노드의 키 값
 * @return int 삭제 성공 여부를 나타내는 값 (1: 성공, -1: 실패)
 */
int deleteNode(Node* head, int key)
{
    if (head == NULL) {
        printf("\n Nothing to delete!!\n");
        return -1;  // 삭제할 노드가 없으므로 실패를 나타내는 값 -1을 반환합니다.
    }

    if (head->left == NULL) {
        printf("\n Nothing to delete!!\n");
        return -1;  // 삭제할 노드가 없으므로 실패를 나타내는 값 -1을 반환합니다.
    }

    /* head->left가 루트 노드입니다. */
    Node* root = head->left;

    Node* parent = NULL;
    Node* ptr = root;

    // 삭제할 노드를 찾습니다.
    while ((ptr != NULL) && (ptr->key != key)) {
        if (ptr->key != key) {
            parent = ptr;  // 부모 노드를 저장합니다.

            if (ptr->key > key)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
    }

    /* 삭제할 노드가 없는 경우 */
    if (ptr == NULL)
    {
        printf("No node for key [%d]\n ", key);
        return -1;  // 삭제할 노드가 없으므로 실패를 나타내는 값 -1을 반환합니다.
    }

    /* case 1: 삭제하려는 노드가 리프 노드인 경우 */
    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (parent != NULL) {
            /* 부모 노드가 존재하는 경우, 부모의 왼쪽 또는 오른쪽 링크를 조정합니다. */
            if (parent->left == ptr)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else {
            /* 부모 노드가 없는 경우, 삭제하려는 노드가 루트인 경우입니다. */
            head->left = NULL;
        }

        free(ptr);
        return 1;  // 삭제가 성공적으로 수행되었음을 나타내는 값 1을 반환합니다.
    }

    /* case 2: 삭제하려는 노드가 하나의 자식을 가진 경우 */
    if ((ptr->left == NULL) || (ptr->right == NULL))
    {
        Node* child;
        if (ptr->left != NULL)
            child = ptr->left;
        else
            child = ptr->right;

        if (parent != NULL)
        {
            if (parent->left == ptr)
                parent->left = child;
            else
                parent->right = child;
        }
        else {
            /* 부모 노드가 없는 경우, 삭제하려는 노드가 루트이며 하나의 자식을 가진 경우입니다. */
            root = child;  // 해당 자식을 새로운 루트로 설정합니다.
        }

        free(ptr);
        return 1;  // 삭제가 성공적으로 수행되었음을 나타내는 값 1을 반환합니다.
    }

    /* case 3: 삭제하려는 노드가 두 개의 자식을 가진 경우 */
    Node* candidate;
    parent = ptr;

    candidate = ptr->right;

    /* 오른쪽 서브트리에서 가장 작은 값을 가지는 노드를 찾습니다. */
    while (candidate->left != NULL)
    {
        parent = candidate;
        candidate = candidate->left;
    }

    /* 후보 노드는 삭제할 노드의 오른쪽 자식 노드입니다. (후보의 왼쪽 자식은 NULL입니다.) */
    if (parent->right == candidate)
        parent->right = candidate->right;
    else
        parent->left = candidate->right;

    /* 삭제할 노드 대신 후보 노드의 키 값을 대입하고, 후보 노드를 삭제합니다. */
    ptr->key = candidate->key;

    free(candidate);
    return 1;  // 삭제가 성공적으로 수행되었음을 나타내는 값 1을 반환합니다.
}


/**
 * @brief 이진 탐색 트리의 노드들을 재귀적으로 해제하는 함수
 * 
 * @param ptr 해제할 노드의 포인터
 */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);    // 왼쪽 서브트리의 노드들을 해제합니다.
		freeNode(ptr->right);   // 오른쪽 서브트리의 노드들을 해제합니다.
		free(ptr);              // 자신의 노드를 해제합니다.
	}
}


/**
 * @brief 이진 탐색 트리를 해제하는 함수
 * 
 * @param head 이진 탐색 트리의 헤드 노드 포인터
 * @return int 해제 성공 여부를 나타내는 값 (1: 성공, -1: 실패)
 */
int freeBST(Node* head)
{
	if(head->left == head)
	{
		free(head);             // 빈 트리인 경우 헤드 노드만 해제하고 반환합니다.
		return 1;
	}

	Node* p = head->left;       // 트리의 루트 노드를 p에 저장합니다.

	freeNode(p);                // 트리의 모든 노드를 해제합니다.

	free(head);                 // 헤드 노드를 해제합니다.

	return 1;
}

/**
 * @brief 스택에서 요소를 꺼내는 함수
 * 
 * @return Node* 꺼낸 요소의 포인터 (NULL인 경우 스택이 비어있음을 나타냄)
 */
Node* pop()
{
	if (top < 0) return NULL;       // 스택이 비어있는 경우 NULL을 반환합니다.
	return stack[top--];            // 스택에서 요소를 꺼내고 top을 감소시킵니다.
}

/**
 * @brief 스택에 저장된 요소들을 출력하는 함수
 */
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
}

/**
 * @brief 큐에서 요소를 제거하고 반환하는 함수
 * 
 * @return Node* 제거된 요소의 포인터 (큐가 비어있을 경우 NULL 반환)
 */
Node* deQueue()
{
	if (front == rear) {
		// 큐가 비어있는 경우
		// printf("\n....Now Queue is empty!!\n");
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;  // front를 다음 위치로 이동하여 요소 제거
	return queue[front];  // 제거된 요소 반환
}

/**
 * @brief 노드를 큐에 넣는 함수입니다.
 * 
 * @param aNode 큐에 넣을 노드입니다.
 */
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear 값을 증가시키고, 원형 큐에서의 인덱스 조정을 수행합니다.
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // 큐의 rear 인덱스에 노드를 저장합니다.
}




