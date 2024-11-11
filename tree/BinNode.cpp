#define BinNodePosi(T) BinNode<T>* //�ڵ�λ�� 
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ����������߶�Ϊ-1���mԼ����ͳһ�� 
typedef enum { RB_RED, RB_BLACK} RBColor; //�ڵ���ɫ 
 
template <typename T> struct BinNode { //�������ڵ�ģ���� 
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ�� 
    T data; //��ֵ 
    BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ��� 
    int height; //�߶ȣ�ͨ�ã� 
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩 
    RBColor color; //��ɫ��������� 
// ���캯�� 
    BinNode() : 
       parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { } 
    BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, 
              int h = 0, int l = 1, RBColor c = RB_RED ) : 
       data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { } 
// �����ӿ� 
    int size(); //ͳ����ǰ�ڵ����������༴����Ϊ���m�����m�_ģ 
    BinNodePosi(T) insertAsLC ( T const& ); //��Ϊ��ǰ�ڵ�m���ӓI���½ڵ� 
    BinNodePosi(T) insertAsRC ( T const& ); //��Ϊ��ǰ�ڵ�m�Һ��ӓI���½ڵ� 
    BinNodePosi(T) succ(); //����ǰ�ڵ�mֱ�Ӻ�� 
    template <typename VST> void travLevel ( VST& ); //�����ִα��� 
    template <typename VST> void travPre ( VST& ); //����������� 
    template <typename VST> void travIn ( VST& ); //����������� 
    template <typename VST> void travPost ( VST& ); //����������� 
// �Ƚ������`������������һ���������в��䣩 
    bool operator< ( BinNode const& bn ) { return data < bn.data; } //Сء 
    bool operator== ( BinNode const& bn ) { return data == bn.data; } //��ء 
}; 

#define IsRoot(x) ( ! ( (x).parent ) ) 
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) ) 
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) ) 
#define HasParent(x) ( ! IsRoot(x) ) 
#define HasLChild(x) ( (x).lc ) 
#define HasRChild(x) ( (x).rc ) 
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������ 
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ���������� 
#define IsLeaf(x) ( ! HasChild(x) ) 
  
/****************************************************************************************** 
  * ��BinNode�����ض���ϵ�m�ڵ㼰ָ�� 
  ******************************************************************************************/ 
#define sibling(p) /*�ֵ�*/ \ 
    ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) 
  
#define uncle(x) /*����*/ \ 
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc ) 
  
#define FromParentTo(x) /*���Ը��װm����*/ \    
    ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e ) 
{ return lc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ�m���ӓI������� 
  
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e ) 
{ return rc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ�m�Һ��ӓI������� 

template <typename T> template <typename VST> //Ԫ�����͡������� 
void BinNode<T>::travIn ( VST& visit ) { //��������������㷨ͳһ��� 
    switch ( rand() % 5 ) { //�˴������ѡ���������ԣ�������ѡ�� 
        case 1: travIn_I1 ( this, visit ); break; //������#1 
        case 2: travIn_I2 ( this, visit ); break; //������#2 
        case 3: travIn_I3 ( this, visit ); break; //������#3 
        case 4: travIn_I4 ( this, visit ); break; //������#4 
        default: travIn_R ( this, visit ); break; //�Ϗ��� 
     } 
 } 
