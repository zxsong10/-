include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <memory>
#include <limits.h>
using namespace std;  //ע��쳲������Ѿ�����С����
 
template <typename T>
struct FibonacciHeapNode   //쳲������ѽڵ�
{
	T data;
	bool mark = false;  //�������
	unsigned int degree = 0;   //�ڵ�Ķ�
	FibonacciHeapNode* parent = nullptr;
	FibonacciHeapNode* first_child = nullptr;
	FibonacciHeapNode* right_sibling = nullptr;
	FibonacciHeapNode* left_sibling = nullptr;
	FibonacciHeapNode(const T& d) :data(d) {}
};
 
template <typename T>
int Searchd(FibonacciHeapNode<T>* ptr, int d)
{
	if (d == 2)
		return 0;
	else
	{
		if (d == 1)
		{
			if (ptr->right_sibling == nullptr)
				return 0;
			else
				return 2;
		}
		else
		{
			if (ptr->first_child != nullptr)
				return 1;
			else
			{
				if (ptr->right_sibling != nullptr)
					return 2;
				else
					return 0;
			}
		}
	}
}
 
template <typename T>
class FibonacciHeap
{
public:
	T getAndRemoveMinkey();  //���ز��Ƴ���Сֵ
	bool removeFirstNodeWithSpecificValue(const T& key);   //�Ƴ�쳲��������е�һ�����и���ֵ�Ľڵ�
	void insert(const T& key);
	bool changeNodeValue(const T& original_vaule, const T &goal_value);  //��쳲��������е�һ��ԭʼֵ��ΪĿ��ֵ
	T getMinValue()  //��ȡ��Сֵ
	{
		if (head_ptr_for_root_list == nullptr)
			return min_value_for_type;
		else
			return min->data;
	}
	void merge(FibonacciHeap& be_merged);  //�ϲ�����쳲�������
	~FibonacciHeap();
	FibonacciHeap(const T& min_value) :min_value_for_type(min_value) {}
	void printHeap();   //�Թ������ʽ��ӡ쳲�������
	bool isEmpty() { return num_of_node_in_heap == 0; }
private:
	FibonacciHeapNode<T>* removeMinNode();
	FibonacciHeapNode<T>* unionSubHeap(FibonacciHeapNode<T>* left, FibonacciHeapNode<T>* right);   //��쳲��������������ӶѺϲ�
	void insertInRootList(FibonacciHeapNode<T>* &pre, FibonacciHeapNode<T>* be_inserted);   //�������в����½ڵ�
	void changeKey(FibonacciHeapNode<T>* root, FibonacciHeapNode<T>* node, const T& key);
	void removeNode(FibonacciHeapNode<T>* root, FibonacciHeapNode<T>* node);
	bool adjustToRemainOrder(FibonacciHeapNode<T>* parent, FibonacciHeapNode<T>* node, bool increase_or_decrease);  //�Ӷ��е����ֵ�����ĳ�ڵ�ؼ�����ֵ���ֵ������ά�����ֵ������ڵ�Ĵ�С˳��,����true��ʾ���ֵ������ڵ㸸�ڵ�degree��С��false�෴
	pair<FibonacciHeapNode<T>*, FibonacciHeapNode<T>*> searchFirstAppearKey(const T& key);  //����쳲��������е�һ�����и����ؼ���Ľڵ�
	bool checkAndMaintainSibListOrderliness(FibonacciHeapNode<T>*& cur, FibonacciHeapNode<T>* node, bool increase_or_decrease);  //�������ֵ�����С�����ά����������ֵ����ϸ��ڵ㸸�ڵ�����ޱ仯�ͼ�������ж��Ƿ���Ҫ��������,true�����������,false��ʾ��Ҫ
	void destorySubHeap(FibonacciHeapNode<T>* root);  //�����Ӷ�
 
	FibonacciHeapNode<T>* min = nullptr;  //ָ����Сֵָ��
	FibonacciHeapNode<T>* head_ptr_for_root_list = nullptr;  //ָ��������׽ڵ�ָ��
	unsigned long long num_of_node_in_heap = 0;  //쳲��������нڵ���
	unsigned long long size_of_root_list = 0;  //�������С
	T min_value_for_type;   //쳲��������б������Ϳ��ܾ��е���Сֵ,����Сֵ����Ϊ�ڵ�ؼ���
};
 
template <typename T>
void FibonacciHeap<T>::destorySubHeap(FibonacciHeapNode<T>* root)
{
	FibonacciHeapNode<T>* cur = root->first_child;
	while (cur != nullptr)
	{
		departRightHeap(cur);
		FibonacciHeapNode<T>* next = cur->right_sibling;
		if (next == cur)
		{
			next = nullptr;
		}
 
		if (cur->first_child == nullptr)
		{
			delete cur;
		}
		else
		{
			destorySubHeap(cur);
		}
		cur = next;
	}
	delete root;
}
 
template <typename T>
FibonacciHeap<T>::~FibonacciHeap()
{
	if (head_ptr_for_root_list == nullptr)
	{
		return;
	}
 
	while (head_ptr_for_root_list != nullptr)
	{
		FibonacciHeapNode<T>* cur = nullptr;
		cur = head_ptr_for_root_list->right_sibling;
		cur->left_sibling = head_ptr_for_root_list->left_sibling;
		cur->left_sibling->right_sibling = cur;
 
		if (cur == head_ptr_for_root_list)
		{
			cur = nullptr;
		}
 
		head_ptr_for_root_list->right_sibling = nullptr;
		destorySubHeap(head_ptr_for_root_list);
		head_ptr_for_root_list = cur;
	}
}
 
template<typename T>
bool FibonacciHeap<T>::changeNodeValue(const T& original_vaule, const T& goal_value)
{
	if (original_vaule == goal_value)
	{
		return false;
	}
 
	pair<FibonacciHeapNode<T>*, FibonacciHeapNode<T>*> temp = searchFirstAppearKey(original_vaule);
	if (temp.first == nullptr)
	{
		return false;
	}
	changeKey(temp.first, temp.second, goal_value);
	return true;
}
 
template <typename T>
T FibonacciHeap<T>::getAndRemoveMinkey()
{
	shared_ptr<FibonacciHeapNode<T>> t(removeMinNode());
	if (t == nullptr)
	{
		return min_value_for_type;
	}
	else
	{
		return t->data;
	}
}
 
template <typename T>
void FibonacciHeap<T>::merge(FibonacciHeap<T>& be_merged)
{
	if (head_ptr_for_root_list == nullptr)
	{
		min = be_merged.min;
		head_ptr_for_root_list = be_merged.head_ptr_for_root_list;
		num_of_node_in_heap = be_merged.num_of_node_in_heap;
		size_of_root_list = be_merged.size_of_root_list;
		be_merged.min = nullptr;
		be_merged.head_ptr_for_root_list = nullptr;
		be_merged.num_of_node_in_heap = 0;
		be_merged.size_of_root_list = 0;
	}
	else if (be_merged.head_ptr_for_root_list != nullptr)
	{
		FibonacciHeapNode<T>* pre = head_ptr_for_root_list->left_sibling;
		pre->right_sibling = be_merged.head_ptr_for_root_list;
		FibonacciHeapNode<T>* last = be_merged.head_ptr_for_root_list->left_sibling;
		be_merged.head_ptr_for_root_list->left_sibling = pre;
		last->right_sibling = head_ptr_for_root_list;
		head_ptr_for_root_list->left_sibling = last;
		if (min->data > be_merged.min->data)
		{
			min = be_merged.min;
		}
		num_of_node_in_heap += be_merged.num_of_node_in_heap;
		size_of_root_list += be_merged.size_of_root_list;
 
		be_merged.min = nullptr;
		be_merged.head_ptr_for_root_list = nullptr;
		be_merged.num_of_node_in_heap = 0;
		be_merged.size_of_root_list = 0;
	}
}
 
template <typename T>
void FibonacciHeap<T>::insert(const T& key)
{
	FibonacciHeapNode<T>* pre = nullptr;
	if (head_ptr_for_root_list != nullptr)
	{
		pre = head_ptr_for_root_list->left_sibling;
	}
 
	FibonacciHeapNode<T>* be_inserted = new FibonacciHeapNode<T>(key);
	if (head_ptr_for_root_list == nullptr || min->data > be_inserted->data)
	{
		min = be_inserted;
	}
 
	insertInRootList(pre, be_inserted);
	++num_of_node_in_heap;
	++size_of_root_list;
}
 
template <typename T>
void FibonacciHeap<T>::printHeap()
{
	if (head_ptr_for_root_list == nullptr)
	{
		cout<<"NULL";
		cout << endl;
		return;
	}
 
	size_t num = 0;
	for (FibonacciHeapNode<T>* run = head_ptr_for_root_list; ; run = run->right_sibling)
	{
		cout << "��" << ++num << "���ӶѵĹ������ʽ:";
		stack<FibonacciHeapNode<T>*> work_stack;
		FibonacciHeapNode<T>* ptr = run;
		FibonacciHeapNode<T>* root_right_bro = run->right_sibling;
		run->right_sibling = nullptr;
		int d = 0;
		while (true)    //�����Ů���ֵ�����������Ӧ�������ʽ
		{
			if (Searchd(ptr, d) == 0)
			{
				if (d == 0)
					cout <<"(" << ptr->data;
 
				cout << ")";
				break;
			}
			else
			{
				FibonacciHeapNode<T>* interval = nullptr;
				if (d == 0)
				{
					if (ptr->first_child != nullptr)
					{
						cout << ptr->data << "(";
						work_stack.push(ptr);
						interval = ptr->first_child;
					}
					else
					{
						if (ptr->right_sibling == work_stack.top()->first_child)
						{
							cout << ptr->data;
							ptr = work_stack.top();
							d = 1;
							work_stack.pop();
							continue;
						}
						else
						{
							cout << ptr->data;
							cout << ",";
							interval = ptr->right_sibling;
						}
					}
				}
				else
				{
					if (ptr->right_sibling == work_stack.top()->first_child)
					{
						cout << ")";
						ptr = work_stack.top();
						d = 1;
						work_stack.pop();
						continue;
					}
					else
					{
						cout << "),";
						interval = ptr->right_sibling;
					}
				}
				d = 0;
				ptr = interval;
			}
		}
		run->right_sibling = root_right_bro;
		cout << endl;
		cout << endl;
		if (run->right_sibling == head_ptr_for_root_list)
		{
			return;
		}
	}
}
 
template <typename T>
pair<FibonacciHeapNode<T>*, FibonacciHeapNode<T>*> FibonacciHeap<T>::searchFirstAppearKey(const T& key)
{
	if (head_ptr_for_root_list == nullptr)
	{
		return { nullptr, nullptr };
	}
 
	for (FibonacciHeapNode<T>* run = head_ptr_for_root_list; ; run = run->right_sibling)
	{
		int d = 0;
		stack<FibonacciHeapNode<T>*> work_stack;
		FibonacciHeapNode<T>* ptr = run;
		FibonacciHeapNode<T>* root_right_bro = run->right_sibling;
		run->right_sibling = nullptr;
		while (true)    
		{
			if (Searchd(ptr, d) == 0)
			{
				break;
			}
			else
			{
				FibonacciHeapNode<T>* interval = nullptr;
				if (d == 0)
				{
					if (key < ptr->data)
					{
						if (work_stack.empty() == true)
						{
							break;
						}
						ptr = work_stack.top();
						d = 1;
						work_stack.pop();
						continue;
					}
					else if (key == ptr->data)
					{
						break;
					}
 
					if (ptr->first_child != nullptr)
					{
						work_stack.push(ptr);
						interval = ptr->first_child;
					}
					else
					{
						if (ptr->right_sibling == work_stack.top()->first_child)
						{
							ptr = work_stack.top();
							d = 1;
							work_stack.pop();
							continue;
						}
						else
						{
							interval = ptr->right_sibling;
						}
					}
				}
				else
				{
					if (ptr->right_sibling == work_stack.top()->first_child)
					{
						ptr = work_stack.top();
						d = 1;
						work_stack.pop();
						continue;
					}
					else
					{
						interval = ptr->right_sibling;
					}
				}
				d = 0;
				ptr = interval;
			}
		}
		run->right_sibling = root_right_bro;
		if (ptr->data == key)
		{
			return { run, ptr };
		}
 
		if (run->right_sibling == head_ptr_for_root_list)
		{
			return {nullptr, nullptr};
		}
	}
}
 
template <typename T>
bool FibonacciHeap<T>::removeFirstNodeWithSpecificValue(const T& key)
{
	pair<FibonacciHeapNode<T>*, FibonacciHeapNode<T>*> temp = searchFirstAppearKey(key);
	if (temp.first == nullptr)
	{
		return false;
	}
 
	removeNode(temp.first, temp.second);
	return true;
}
 
template <typename T>
void departRightHeap(FibonacciHeapNode<T>* right_sub_heap)   //��right_sub_heap�����ֵ����з���
{
	FibonacciHeapNode<T>* p = right_sub_heap->parent;
	if (p != nullptr)
	{
		right_sub_heap->left_sibling->right_sibling = right_sub_heap->right_sibling;
		right_sub_heap->right_sibling->left_sibling = right_sub_heap->left_sibling;
		if (p->first_child == right_sub_heap)
		{
			if (right_sub_heap->right_sibling == right_sub_heap)
			{
				p->first_child = nullptr;
			}
			else
			{
				p->first_child = right_sub_heap->right_sibling;
			}
		}
	}
}
 
template <typename T>
void insertNodeInRightSibLink(FibonacciHeapNode<T>* post, FibonacciHeapNode<T>* be_inserted_root)
{
	FibonacciHeapNode<T>* t = post->left_sibling;
	post->left_sibling = be_inserted_root;
	be_inserted_root->left_sibling = t;
	be_inserted_root->right_sibling = post;
	t->right_sibling = be_inserted_root;
}
 
template <typename T>
FibonacciHeapNode<T>* FibonacciHeap<T>::unionSubHeap(FibonacciHeapNode<T>* left, FibonacciHeapNode<T>* right)
{
	struct StackNode
	{
		FibonacciHeapNode<T>* parent;
		FibonacciHeapNode<T>* insert_point;
		StackNode(FibonacciHeapNode<T>* p, FibonacciHeapNode<T>* i) :parent(p), insert_point(i) {}
	};
	stack<StackNode> work_stack;
	FibonacciHeapNode<T>* left_sub_heap = left;
	FibonacciHeapNode<T>* right_sub_heap = right;
	FibonacciHeapNode<T>* cur = nullptr;
	while (true)    //�ϲ��Ӷѣ��Ը��ڵ�ؼ���ֵ�ϴ��Ӷѣ��ڽ�С�ӶѸ��ڵ����ֵ���Ѱ�Ҳ���λ��,�ҵ�λ�������ϴ��ӶѸ��ڵ㣬����˵�����ֵ����з�����ϴ��ӶѸ��ڵ�ؼ����ظ��Ľڵ㣬��ʱ�ݹ�ϲ��ýڵ�����ӶѺͽϴ��Ӷ�
	{
		if (left_sub_heap->data <= right_sub_heap->data)
		{
			FibonacciHeapNode<T>* run = left_sub_heap->first_child;
			if (run != nullptr)
			{
				do
				{
					if (run->data < right_sub_heap->data)
					{
						run = run->right_sibling;
					}
					else
					{
						break;
					}
				} while (run != left_sub_heap->first_child);
			}
 
			if (run != left_sub_heap->first_child || run != nullptr && right_sub_heap->data <= run->data)
			{
				if (run->data != right_sub_heap->data)
				{
					departRightHeap(right_sub_heap);
 
					insertNodeInRightSibLink(run, right_sub_heap);
					if (run == left_sub_heap->first_child)
					{
						left_sub_heap->first_child = right_sub_heap;
					}
				}
				else
				{
					if (run == left_sub_heap->first_child)
					{
						work_stack.push(StackNode(left_sub_heap, left_sub_heap));
					}
					else
					{
						work_stack.push(StackNode(left_sub_heap, run->left_sibling));
					}
					left_sub_heap = run;
					continue;
				}
			}
			else
			{
				departRightHeap(right_sub_heap);
 
				if (run == nullptr)
				{
					left_sub_heap->first_child = right_sub_heap;
					right_sub_heap->left_sibling = right_sub_heap;
					right_sub_heap->right_sibling = right_sub_heap;
				}
				else
				{
					insertNodeInRightSibLink(run, right_sub_heap);
				}
			}
			right_sub_heap->parent = left_sub_heap;
			right_sub_heap->mark = false;
			++left_sub_heap->degree;
			left_sub_heap->mark = false;
			cur = left_sub_heap;
			break;
		}
		else
		{
			FibonacciHeapNode<T>* run = right_sub_heap->first_child;
			if (run != nullptr)
			{
				do
				{
					if (run->data < left_sub_heap->data)
					{
						run = run->right_sibling;
					}
					else
					{
						break;
					}
				} while (run != right_sub_heap->first_child);
			}
 
			if (run != right_sub_heap->first_child || run != nullptr && left_sub_heap->data <= run->data)
			{
				if (run->data != left_sub_heap->data)
				{
					departRightHeap(left_sub_heap);
 
					insertNodeInRightSibLink(run, left_sub_heap);
					if (run == right_sub_heap->first_child)
					{
						right_sub_heap->first_child = left_sub_heap;
					}
				}
				else
				{
					if (run == right_sub_heap->first_child)
					{
						work_stack.push(StackNode(right_sub_heap, right_sub_heap));
					}
					else
					{
						work_stack.push(StackNode(right_sub_heap, run->left_sibling));
					}
					FibonacciHeapNode<T>* t = left_sub_heap;
					left_sub_heap = run;
					right_sub_heap = t;
					continue;
				}
			}
			else
			{
				departRightHeap(left_sub_heap);
 
				if (run == nullptr)
				{
					right_sub_heap->first_child = left_sub_heap;
					left_sub_heap->left_sibling = left_sub_heap;
					left_sub_heap->right_sibling = left_sub_heap;
				}
				else
				{
					insertNodeInRightSibLink(run, left_sub_heap);
				}
			}
			left_sub_heap->parent = right_sub_heap;
			left_sub_heap->mark = false;
			++right_sub_heap->degree;
			right_sub_heap->mark = false;
			cur = right_sub_heap;
			break;
		}
	}
 
	while (work_stack.empty() == false)   //�Ե������������Ӻϲ���������ڵ�
	{
		if (cur->parent != work_stack.top().parent)
		{
			FibonacciHeapNode<T>* run = work_stack.top().insert_point;
 
			departRightHeap(cur);
			if (run != work_stack.top().parent)
			{
				run->right_sibling->left_sibling = cur;
				cur->right_sibling = run->right_sibling;
				run->right_sibling = cur;
				cur->left_sibling = run;
 
			}
			else
			{
				if (run->first_child == nullptr)
				{
					run->first_child = cur;
					cur->left_sibling = cur;
					cur->right_sibling = cur;
				}
				else
				{
					insertNodeInRightSibLink(run->first_child, cur);
					run->first_child = cur;
				}
			}
			cur->parent = work_stack.top().parent;
			cur->mark = false;
		}
		cur = work_stack.top().parent;
		work_stack.pop();
	}
	return cur;
}
template <typename T>
void FibonacciHeap<T>::insertInRootList(FibonacciHeapNode<T>* &pre, FibonacciHeapNode<T>* be_inserted)
{
	if (pre == nullptr)
	{
		pre = head_ptr_for_root_list = be_inserted;
		be_inserted->right_sibling = be_inserted;
		be_inserted->left_sibling = be_inserted;
	}
	else
	{
		be_inserted->right_sibling = pre->right_sibling;
		pre->right_sibling = be_inserted;
		be_inserted->right_sibling->left_sibling = be_inserted;
		be_inserted->left_sibling = pre;
	}
	be_inserted->mark = false;
}
 
template <typename T>
bool FibonacciHeap<T>::adjustToRemainOrder(FibonacciHeapNode<T>* parent, FibonacciHeapNode<T>* node, bool increase_or_decrease)  //increase_or_decrease��ʾnodeֵ���ӣ������С
{
	if (increase_or_decrease)      //nodeֵ�Ѹı䣬������Ҫ��node�������ֵ����ϲ���ֵ����node�Ľڵ㣬����ҵ���Ҫ�ϲ��ýڵ��node�ڵ������Ӷ�
	{
		if (node->right_sibling == parent->first_child)
		{
			return false;
		}
 
		FibonacciHeapNode<T>* run = node->right_sibling;
		do
		{
			if (run->data < node->data)
			{
				run = run->right_sibling;
			}
			else
			{
				break;
			}
		} while (run != parent->first_child);
 
		if (run != parent->first_child)
		{
			if (node->data == run->data)
			{
				departRightHeap(node);
				FibonacciHeapNode<T>* pre = nullptr;
				if (run == parent->first_child)
				{
					pre = parent;
				}
				else
				{
					pre = run->left_sibling;
				}
 
		     	departRightHeap(run);
				node->parent = nullptr;
				run->parent = nullptr;
				run = unionSubHeap(node, run);
				if (parent->first_child == nullptr)
				{
					parent->first_child = run;
					run->left_sibling = run;
					run->right_sibling = run;
				}
				else
				{
					if (pre == parent)
					{
						pre = parent->first_child;
						run->left_sibling = pre->left_sibling;
						run->right_sibling = pre;
						pre->left_sibling = run;
						run->left_sibling->right_sibling = run;
						parent->first_child = run;
					}
					else
					{
						run->right_sibling = pre->right_sibling;
						pre->right_sibling = run;
						run->right_sibling->left_sibling = run;
						run->left_sibling = pre;
					}
				}
				run->parent = parent;
				run->mark = false;
				--parent->degree;
				return true;
			}
			else
			{
				if (node->right_sibling == run)
				{
					return false;
				}
 
				departRightHeap(node);
				FibonacciHeapNode<T>* t = run->left_sibling;
				run->left_sibling = node;
				node->left_sibling = t;
				node->right_sibling = run;
				t->right_sibling = node;
				return false;
			}
		}
		else
		{
			departRightHeap(node);
			run = run->left_sibling;
			run->right_sibling = node;
			node->left_sibling = run;
			node->right_sibling = parent->first_child;
			parent->first_child->left_sibling = node;
			return false;
		}
	}
	else
	{
	   if (node == parent->first_child)
	   {
		   return false;
	   }
 
	   FibonacciHeapNode<T>* run = node->left_sibling;
	   do
	   {
		   if (run->data > node->data)
		   {
			   run = run->left_sibling;
		   }
		   else
		   {
			   break;
		   }
	   } while (run != parent->first_child->left_sibling);
 
	   if (run != parent->first_child->left_sibling)
	   {
		   if (node->data == run->data)
		   {
			   departRightHeap(node);
			   FibonacciHeapNode<T>* pre = nullptr;
			   if (run == parent->first_child)
			   {
				   pre = parent;
			   }
			   else
			   {
				   pre = run->left_sibling;
			   }
 
			   departRightHeap(run);
			   node->parent = nullptr;
			   run->parent = nullptr;
			   run = unionSubHeap(node, run);
			   if (parent->first_child == nullptr)
			   {
				   parent->first_child = run;
				   run->left_sibling = run;
				   run->right_sibling = run;
			   }
			   else
			   {
				   if (pre == parent)
				   {
					   pre = parent->first_child;
					   run->left_sibling = pre->left_sibling;
					   run->right_sibling = pre;
					   pre->left_sibling = run;
					   run->left_sibling->right_sibling = run;
					   parent->first_child = run;
				   }
				   else
				   {
					   run->right_sibling = pre->right_sibling;
					   pre->right_sibling = run;
					   run->right_sibling->left_sibling = run;
					   run->left_sibling = pre;
				   }
			   }
			   run->parent = parent;
			   run->mark = false;
			   --parent->degree;
			   return true;
		   }
		   else
		   {
			   if (node->left_sibling == run)
			   {
				   return false;
			   }
 
			   departRightHeap(node);
			   node->right_sibling = run->right_sibling;
			   run->right_sibling = node;
			   node->right_sibling->left_sibling = node;
			   node->left_sibling = run;
			   return false;
		   }
	   }
	   else
	   {
		   departRightHeap(node);
		   run = parent->first_child;
		   node->left_sibling = run->left_sibling;
		   node->right_sibling = run;
		   run->left_sibling = node;
		   node->left_sibling->right_sibling = node;
		   parent->first_child = node;
		   return false;
	   }  
	}
}
template <typename T>
bool FibonacciHeap<T>::checkAndMaintainSibListOrderliness(FibonacciHeapNode<T>* &cur, FibonacciHeapNode<T>* node, bool increase_or_decrease) 
{
	if (node->parent != nullptr) 
	{
		if (!adjustToRemainOrder(node->parent, node, increase_or_decrease))
		{
			return true;
		}
		else
		{
			if (node->parent->mark == true)
			{
				cur = node->parent;
				return false;
			}
			else
			{
				node->parent->mark = true;
				return true;
			}
		}
	}
	else
	{
		return true;
	}
}
 
template <typename T>
void FibonacciHeap<T>::changeKey(FibonacciHeapNode<T> *root, FibonacciHeapNode<T> *node, const T& key)
{
	if (key == node->data)
	{
		return;
	}
 
	FibonacciHeapNode<T>* cur = nullptr;
	FibonacciHeapNode<T>* pre = root;
	if (key > node->data)  //���node��ֵ����,����Ҫ��node����Ů�ڵ��в��������Ľڵ������ӶѼ�����������,Ȼ���ж�node�Ƿ���Ҫ�����ж�
	{
		node->data = key;
		if (node->first_child == nullptr)
		{
			if (checkAndMaintainSibListOrderliness(cur, node, true))
			{
				return;
			}
		}
		else
		{
			FibonacciHeapNode<T>* run = node->first_child;
			unsigned long long num_of_lossing_node = 0;
			bool finish = false;
			while (finish == false)
			{
				if (run->data >= node->data)
				{
					node->first_child = run;
					break;
				}
				run->right_sibling->left_sibling = run->left_sibling;
				run->left_sibling->right_sibling = run->right_sibling;
				--node->degree;
				++num_of_lossing_node;
 
				run->parent = nullptr;
				FibonacciHeapNode<T>* temp = nullptr;
				if (run->right_sibling == run)
				{
					finish = true;
				}
				else
				{
					temp = run->right_sibling;
				}
 
				insertInRootList(pre, run);
				++size_of_root_list;
				if (min->data > run->data)
				{
					min = run;
				}
				run = temp;
				pre = pre->right_sibling;
			}
 
			if (node->degree == 0)
			{
				node->first_child = nullptr;
			}
 
			if (finish == false)
			{
				if (node->mark == false)
				{
					if (num_of_lossing_node == 0 || num_of_lossing_node == 1)
					{
						if (num_of_lossing_node == 1)
						{
							node->mark = true;
						}
 
						if (checkAndMaintainSibListOrderliness(cur, node, true))
						{
							return;
						}
					}
					else
					{
						cur = node;
					}
				}
				else
				{
					if (num_of_lossing_node == 0)
					{
						if (checkAndMaintainSibListOrderliness(cur, node, true))
						{
							return;
						}
					}
					else
					{
						cur = node;
					}
				}
			}
			else
			{
				if (node->mark == false && num_of_lossing_node == 1)
				{
					node->mark = true;
					if (checkAndMaintainSibListOrderliness(cur, node, true))
					{
						return;
					}
				}
				else
				{
					cur = node;
				}
			}
		}
	}
	else
	{
		node->data = key;
		if (node->parent == nullptr)
		{
			if (min->data > node->data)
			{
				min = node;
			}
			return;
		}
 
		if (node->parent->data <= node->data)  //nodeֵ��С����Ӧ�ж�node���丸�ڵ��Ƿ�������С����,�����������node�������ֵ����Ͻڵ�Ĵ�С�����ж�node�ĸ��ڵ��Ƿ���Ҫ�����ж� ����������node�����Ӷ�Ӧ����������������
		{
			if (checkAndMaintainSibListOrderliness(cur, node, false))
			{
				return;
			}
		}
		else
		{
			cur = node;   
		}
	}
 
	while (true)  //�ӵ�ǰ�ڵ�cur��ʼ�����Ͻ��м����жϲ���
	{
		if (cur->parent == nullptr)
		{
			cur->mark = false;
			break;
		}
 
		departRightHeap(cur);
		insertInRootList(pre, cur);
		pre = pre->right_sibling;
		node = cur->parent;
		cur->parent = nullptr;
		if (cur->data < min->data)
		{
			min = cur;
		}
		++size_of_root_list;
 
		--node->degree;
		if (node->mark == false)
		{
			cur->mark = true;
			break;
		}
		cur = node;
	}
}
 template <typename T>
 FibonacciHeapNode<T>* FibonacciHeap<T>::removeMinNode()   //�ò�������ϸ˵���μ��㷨����
 {
	 if (head_ptr_for_root_list == nullptr)
	 {
		 return nullptr;
	 }
 
	 FibonacciHeapNode<T>* pre = min->left_sibling;
	 FibonacciHeapNode<T>* original_min = min;
	 if (pre == min)
	 {
		 pre = nullptr;
		 head_ptr_for_root_list = nullptr;
	 }
	 else
	 {
		 pre->right_sibling = min->right_sibling;
		 min->right_sibling->left_sibling = pre;
	 }
 
	 FibonacciHeapNode<T>* run = min->first_child;
	 if (run == nullptr)
	 {
		 min->left_sibling = min->right_sibling = nullptr;
		 if (head_ptr_for_root_list == min)
		 {
			 head_ptr_for_root_list = pre->right_sibling;
		 }
 
		 if (head_ptr_for_root_list != nullptr)
		 {
			 min = head_ptr_for_root_list;
			 for (FibonacciHeapNode<T>* tra = head_ptr_for_root_list; ; tra = tra->right_sibling)
			 {
				if (min->data > tra->data)
				{
				   min = tra;
				}
 
				if (tra->right_sibling == head_ptr_for_root_list)
				{
					break;
				}
			 }
		 }
		 else
		 {
			 min = nullptr;
			 --num_of_node_in_heap;
			 --size_of_root_list;
			 return original_min;
		 }
	 }
	 else
	 {
		 FibonacciHeapNode<T>* tail_or_head = pre;
		 while (true)
		 {
			 run->right_sibling->left_sibling = run->left_sibling;
			 run->left_sibling->right_sibling = run->right_sibling;
 
			 run->parent = nullptr;
			 if (run->right_sibling == run)
			 {
				 insertInRootList(pre, run);
				 break;
			 }
 
			 FibonacciHeapNode<T>* temp = run->right_sibling;
			 insertInRootList(pre, run);
			 run = temp;
			 pre = pre->right_sibling;
		 }
		 min->first_child = nullptr;
		 min->left_sibling = nullptr;
		 min->right_sibling = nullptr;
 
		 if (head_ptr_for_root_list == nullptr)
		 {
			 head_ptr_for_root_list = pre;
		 }
		 else if (head_ptr_for_root_list == min)
		 {
			 head_ptr_for_root_list = tail_or_head->right_sibling;
		 }
	 }
 
	 vector<FibonacciHeapNode<T>*> be_merged_sub_heap;
	 bool finish = false;
	 while (finish == false)   //�ϲ��������ϸ��ڵ������ȵ��Ӷ�
	 {
		 head_ptr_for_root_list->right_sibling->left_sibling = head_ptr_for_root_list->left_sibling;
		 head_ptr_for_root_list->left_sibling->right_sibling = head_ptr_for_root_list->right_sibling;
		 FibonacciHeapNode<T>* temp = head_ptr_for_root_list;
		 if (temp->right_sibling == temp)
		 {
			 finish = true;
			 head_ptr_for_root_list = nullptr;
		 }
		 else
		 {
			 head_ptr_for_root_list = head_ptr_for_root_list->right_sibling;
		 }
		 temp->left_sibling = temp->right_sibling = nullptr;
 
		 while (true)
		 {
			 if (be_merged_sub_heap.empty() == true || be_merged_sub_heap.size() < temp->degree + 1)
			 {
				 be_merged_sub_heap.resize(temp->degree + 1, nullptr);
				 be_merged_sub_heap[temp->degree] = temp;
				 break;
			 }
 
			 if (be_merged_sub_heap[temp->degree] == nullptr)
			 {
				 be_merged_sub_heap[temp->degree] = temp;
				 break;
			 }
 
			 unsigned int pre_degree = temp->degree;
			 temp = unionSubHeap(be_merged_sub_heap[temp->degree], temp);
			 if (temp->degree == pre_degree)
			 {
				 be_merged_sub_heap[pre_degree] = temp;
				 break;
			 }
 
			 be_merged_sub_heap[pre_degree] = nullptr;
			 if (be_merged_sub_heap.size() < temp->degree + 1)
			 {
				 be_merged_sub_heap.resize(temp->degree + 1, nullptr);
			 }
 
			 if (be_merged_sub_heap[temp->degree] == nullptr)
			 {
				 be_merged_sub_heap[temp->degree] = temp;
				 break;
			 }
		 }
	 }
 
	 min = nullptr;
	 pre = nullptr;
	 size_of_root_list = 0;
	 for (size_t i = 0; i < be_merged_sub_heap.size(); ++i)   //�ϲ���ԭ������
	 {
		 if (be_merged_sub_heap[i] != nullptr)
		 {
			 ++size_of_root_list;
			 insertInRootList(pre, be_merged_sub_heap[i]);
			 pre = pre->right_sibling;
			 if (min == nullptr || min->data > pre->data)
			 {
				 min = pre;
			 }
		 }
	 }
 
	 --num_of_node_in_heap;
	 return original_min;
 }
 
 template <typename T>
 void FibonacciHeap<T>::removeNode(FibonacciHeapNode<T>* root, FibonacciHeapNode<T>* node)
 {
	 changeKey(root, node, min_value_for_type);
	 removeMinNode();
 }
 
int main()
{
	FibonacciHeap<int> obj(INT_MIN);
	vector<int> input{3, 9, 1, 23, 67, 14, 7, 35, 15, 78, 99, 12, 16};
	for (const int& i : input)
	{
		cout << "����ؼ���" << i << endl;
		cout << endl;
		obj.insert(i);
		cout << "��ǰ��Сֵ" << obj.getMinValue() << endl;
		cout << "쳲������Ѵ�ӡ���" << endl;
		obj.printHeap();
		cout << endl;
	}
 
	while(true)
	{
		int t = obj.getAndRemoveMinkey();
		cout << "�Ƴ���Сֵ" << endl;
		if (t == INT_MIN)
		{
			cout << "�Ƴ�ʧ��" << endl;
			break;
		}
		else
		{
			cout << "�Ƴ���Сֵ" << t << "�ɹ�" << endl;
			cout << "��ǰ��Сֵ" << obj.getMinValue() << endl;
			obj.printHeap();
		}
	}
 
	vector<int> input2{ 9, 13, 34, 12, 90, 32, 16, 78, 56, 23, 45 };
	for (const int& i : input2)
	{
		cout << "����ؼ���" << i << endl;
		cout << endl;
		obj.insert(i);
	}
 
	/*cout << "ɾ���ؼ���" << 9 << endl;
	cout << endl;
	if (obj.removeFirstNodeWithSpecificValue(9))
	{
		cout << "ɾ���ɹ�" << endl;
		cout << "��ǰ��Сֵ" << obj.getMinValue() << endl;
		cout << "쳲������Ѵ�ӡ���" << endl;
		obj.printHeap();
	}
	else
	{
		cout << "ɾ��ʧ��" << endl;
	}
	for (size_t i = 1; i<input2.size(); ++i)
	{
		while (true)
		{
			if (!obj.changeNodeValue(input2[i], 14))
				break;
			else
			{
				cout << "��ֵ" << input2[i] << "����Ϊ14" << endl;
				obj.printHeap();
			}
		}
	}
	cout << "��ǰ��Сֵ" << obj.getMinValue() << endl;
	*/
 
	for (const int& i : input2)
	{
		cout << "ɾ���ؼ���" << i << endl;
		cout << endl;
		if (obj.removeFirstNodeWithSpecificValue(i))
		{
			cout << "ɾ���ɹ�" << endl;
			cout << "��ǰ��Сֵ" << obj.getMinValue() << endl;
			cout << "쳲������Ѵ�ӡ���" << endl;
			obj.printHeap();
		}
		else
		{
			cout << "ɾ��ʧ��" << endl;
		}
	}
 
	if (obj.isEmpty())
	{
		cout << "��ǰ��Ϊ��" << endl;
	}
 
	return 0;
