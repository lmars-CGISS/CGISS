#pragma once

namespace geostar {
struct geo_object;
};

typedef const char* string_t;

//\brief reader����Ļص����� 
//\param user �û�����Ĳ���
//\param i Ҫ��ȡ�ĵ�i������
//\return ���صĽ��
//\details ����ص����������԰����û�ʵ��geo_reader�ӿ�,�ο�geo_factory::new_reader
//\details ����i��1��ʼ�����i=0��ʾҪ�ͷ�geo_reader�����û�����Ӧ���ͷ�user�е���Դ
typedef geostar::geo_object* (*reader_callback)(void* user,unsigned int i);

//writer����Ļص�����
typedef void (*writer_callback)(void* user,geostar::geo_object* );

typedef geostar::geo_object* (*open_callback)(string_t format,string_t filename);

namespace geostar {

//�����Ķ���ӿ�
struct geo_object
{
    virtual ~geo_object(){};
    virtual string_t type_info()const=0;         //�õ�����������
    virtual void* type_cast(string_t)=0;         //����ת��

    virtual int addref()=0;                         //������ü���
    virtual int release()=0;                        //�������ü���
    
    virtual int i4_get(int i)=0;                    //�õ�����
    virtual bool i4_set(int i,int v)=0;             //��������
};

//\brief geo_reader�Ķ�ȡ�ӿ�
struct geo_reader : geo_object
{
    virtual geo_object* read()=0;
};

//geo_reader�Ķ�ȡ�ӿ�
struct geo_writer : geo_object
{
    //\brief xxxx
    //\details  
    //\param in xxxxx

    virtual void write(geo_object* in)=0;
};

//��д�ӿ�
struct geo_reader2 : geo_reader,geo_writer
{	
	//�õ�������
	virtual unsigned int count()=0;

	//�õ��±�
	virtual unsigned int get_pos()=0;

	//�����±�
	virtual void set_pos(unsigned int i)=0;

	//����һ������
	virtual geo_reader2* duplicate()=0; 
};

//���ݱ任�Ľӿ�
struct geo_trans : geo_object
{
    virtual geo_object* trans(geo_object*)=0;
	virtual bool setpara(string_t name,void* para)=0;
};

//���ݱȽϽӿ�
struct geo_compare : geo_object
{
	//a<b����-1��a=b����0��a>b����1
    virtual int compare(geo_object* a,geo_object* b)=0;
};

//һά����Ľӿ� ����һ�����"��"��"����ȫ"�Ľӿ�
//���ӿڲ��޶�ÿ����Ԫ�ص����ͱ���һ�£�Ҳ����˵vector�е�0��������int������1��������string_t����2��������geo_object*
//ÿ��Ԫ�صľ��������ɽӿڵ�ʵ���ߺ͵������Լ�Լ������Լ�����������׵��³������
//���ӿ�Լ���ľ�������ֻ��ָ�����ͺ�ֵ�������֣�ָ������Ŀǰֻ����string_t,wstring_t,geo_object*���֣�ֵ���͵����ߺ�ʵ���߱���Լ������ֵ��sizeof
//geo_vectorһ��ͻ�����ص���Լ��get�������صĶ����ⲿ����Ӧ�����٣�Ҳ����˵����֪get���ص���geo_object*������£��ⲿ����ֻ��ǿ��ת����ʹ������������release
struct geo_vector : geo_object
{
	//������Ԫ�صĸ���
	virtual int count()=0;
	
	//��ȡ��i��Ԫ��
	//ptrΪ�������ݵ��ⲿָ�룬�����i��Ԫ������ֵ���ͣ���ô����ptr������и���ֵ����sizeof�Ŀռ�
	//�����i��Ԫ����ָ�����ͣ���ôptr���Ժ��ԣ����ӷ���ֵ�еõ�Ԫ��ָ�룬�ⲿ������ת��Ϊstring_t��wstring_t��geo_object*
	//�������ֵ��geo_object*�����ڲ���geo_object*����ʽ�������Լ���ⲿ����û�б�Ҫrelease������ֵ
	virtual const void* get(int i,void* ptr)=0;
	
	//�޸ĵ�i��Ԫ��
	//ptrΪ�������ݵ��ⲿָ�룬�����ߺ�ʵ���߱������ʵ�ʵ�������һ�µ�Լ��
	//�����i��Ԫ������ֵ���ͣ���ô����ptr������и���ֵ����sizeof�Ŀռ�
	//�����i��Ԫ����ָ�����ͣ���ôptr��������֮ƥ���string_t,wstring_t��geo_object*
	virtual bool set(int i,const void* ptr)=0;

	//���һ����Ԫ��
	//ptrΪ�������ݵ��ⲿָ�룬�����ߺ�ʵ���߱������ʵ�ʵ�������һ�µ�Լ��
	//�������add����������ֵ���ͣ���ôptr������и���ֵ����sizeof�Ŀռ�
	//�������add��������ָ�����ͣ���ôptr��������֮ƥ���string_t,wstring_t��geo_object*
	//�������ֵ��geo_object*�����ڲ���geo_object*����ʽ�������Լ���ⲿ����û�б�Ҫrelease������ֵ
	virtual const void* add(const void* ptr)=0;

	//ɾ��[i,i+n)Ԫ��
	virtual bool remove(int i,int n)=0;

	//�õ�����this��һ��geo_reader
	virtual geo_reader* reader()=0;

	//�õ���this������ݵ�writer
	virtual geo_writer* writer()=0;
};

//��ʾGDI����ӿ�
//�����Լ��graphics������Ҫ֧�ֶ��̲߳���
struct geo_graphics : geo_object
{
	//����GDI״̬
	virtual geo_object* gsave()=0;

	//�ָ�GDI״̬
	virtual void grestor(geo_object* gs)=0;

	//����gid����
	virtual geo_object* new_gdi(string_t paras)=0;

	//����gdi���󣬷����ϵ�gdi����
	virtual void set_gdi(geo_object* gdi)=0;

	//��һ��path
	//mode&1��ʾҪ����mode&2��ʾҪ���
	//p��һ����-1Ϊ��β�Ĵ�����������xy�Ľṹ xy��Žڵ�����
	//����p={5,10,-1}��ʾxy������ �����ߣ���һ������5���ڵ㣬�ڶ�������10���ڵ�
	virtual void draw_path(int mode,const int* p,const double* xy)=0;
	
	//�ھ���[x,y,x+w,y+h]����ʾ����
	virtual void draw_text(geo_object* font,double x,double y,double w,double h,wchar_t* text)=0;
};

//���ŷ�Ϊԭ�ӷ��ź���Ϸ������֣��ͻ����������ֱ��ʹ��ԭ�ӷ��ţ����Ǹ�ͨ��geo_draw��new_symbol��������
//��Ϸ�������ʾ�����ڷ��ŵ�draw�������з���ֵ������Ϸ��϶��Դ˷���ֵ��ԶΪ0��
//�������ֵ�Ľӿ���Ϊԭ�ӷ������Ԥ����

//symbol������ʾ geometry ����
struct geo_symbol : geo_object
{
	//senv�Ǹ�������ʾ��������ǰֻԼ������[s,x,y,w,h]5��ֵ�����������,
	//[x,y,w,h)Ϊ��ʾ���ڵľ���,sΪһ�����ص��߼���λ,Ҳ����˵�������path��x,y����s���õ��任ǰpath�Ĵ�С
	virtual void perpare(geo_graphics* dc,const double* senv)=0;

	//ִ�и÷��ŵĶ���
	virtual geo_object* run(geo_graphics* dc,geo_object* para)=0;

	//��path��ʾ��dc��
	void draw(geo_graphics* dc,geo_object* path){ run(dc,path); }
};

//����ӿ���������ԭ�ӷ���
struct geo_sym_fac : geo_object
{
	//������
	virtual string_t name()=0;

	//�������Ŷ���
	virtual geo_symbol* create(string_t* paras,string_t* dc,string_t* path)=0;
};

//draw��װ����ʾ�õķ���
struct geo_draw : geo_object
{
	//���þ�������ֵΪvalue�������ϵľ���ֵ
	//precisionֵȱʡΪ1���������������ݵ�ѹ����
	virtual double precision(double value)=0;

	//ע��һ��ԭ�ӷ��ŵ��೧����
	virtual void regist_sym_fac(geo_sym_fac* fac)=0;

	//����һ��symbol����,typeΪ���������,scripΪ��symbol����ϸ��Ϣ
	virtual geo_symbol* new_symbol(string_t type,string_t scrip)=0;

	//���ô��ڴ�С(env)�� �߼����굽��Ļ����� �任��������(x,y)Ϊһ���߼�����
	//��ô������Ļ����Ϊ tx[0]*x+tx[1]*y+tx[2],ty[0]*x+ty[1]*y+ty[2]
	//env={x,y,w,h}Ϊ���ڵľ���
	virtual void prepare(const double* env,const double* tx,const double* ty)=0;
	
	//��ʾһ��path,���������R�ж�ȡ���ݣ�ʹ�ò�����ѹ���������ֶν�path�任��symbol�ɻ��Ķ���ͨ��sym����ȥ
	//R�з��صĿ�����path����Ҳ������factory��new_sys_path���صĶ���
	//ǰһ���������ʹ��sym��������,��һ���������ʹ�ö����Դ���symbol��������
	virtual void draw_path(geo_reader* R,geo_graphics* dc,geo_symbol* sym,geo_trans* tpath,geo_trans* tsym)=0;

	virtual void draw_path_2(geo_vector* A,int path_cid,int env_cid,geo_graphics* dc,geo_symbol* sym,geo_trans* tsym)=0;

	//����һ��ע�Ƕ��� pathΪע�ǵļ��ζ��� txtΪע�ǵ��ı�
	//font��װ��ע�ǵ�������ɫ����Ϣ modeָ��ע�ǵ��Ű淽ʽ
	//w,hΪ����Ĵ�С,��modeָ��Ϊ�ɲ�ֵ�ʱ��w�ǵ����ֵĿ�ȣ������������ı��Ŀ��
	virtual geo_object* new_text(geo_object* font,geo_object* path,const wchar_t* txt,int mode,int w,int h)=0;

	//��ʾһ��ע��,R�з��صĶ��������new_txt���������Ķ���
	virtual void draw_text(geo_reader* R,geo_graphics* dc)=0;

	//��ʾע��
	virtual void draw_text_2(geo_vector* A,int path_cid,int env_cid,geo_graphics* dc,geo_trans* ttxt)=0;
};

//һ����Ԫ����Ԫ����
struct geo_cell
{
	string_t	name;		//������
	string_t	discribe;	//���ӵ�������Ϣ
	string_t	type;		//���ݵ����� Ŀǰֻ����byte,string,wstring,object
	int			size_of;	//ռ�õ��ֽ��� ���type����string,wstring,object��ֵΪ0�����type����byte��ֵ�������0
};

// GeomathSE�ڲ�ʵ�ֵĶ�ά����(��)�Ľӿ�
struct geo_table : geo_object
{	
	//����һ���� [p,p+n)Ϊ�е�Ԫ��Ϣ
	virtual bool create(int n,geo_cell* p)=0;

	//��this���浽�ļ� filenameΪ�ļ���
	virtual bool save(string_t filename)=0;

	//���ļ���װ������� filenameΪ�ļ���
	virtual bool load(string_t filename)=0;

	//��ĸ������ԣ����ص�geo_vect_1��һ��string_t���͵� һά����
	geo_vector* props();

	//����Ϣ ���ص�geo_vect_1��һ��cell���͵� һά����
	virtual geo_vector* columns()=0;

	//����Ϣ ���ص�geo_vect_1��һ��object���͵�һά���� 
	//��ÿ��row������geo_vect_1*���͵�object��ÿ��row�ľ���ṹ���Ը���columns��֪
	virtual geo_vector* rows()=0;

	//����row���±�����ɾ��row
	virtual int del_rows(int n,const int* row_ids)=0;
};

struct geo_factory : geo_object
{
    //�õ�p������ά�� 2��ƽ�� 3������
    virtual int dim_c(geo_object* p)=0;
  
    //�õ�p�ļ���ά�� 0��ʾ�� 1��ʾ�� 2��ʾ��
    virtual int dim_g(geo_object* p)=0;

    //�õ�p���Ӷ������ ���p�Ǽ򵥶��󷵻�0
    virtual int sub_n(geo_object* p)=0;

    //�õ���i���Ӷ���
    virtual geo_object* sub_at(geo_object* p,int i)=0;
    
    //�õ������
    virtual int point_n(geo_object* p)=0;
    
    //�õ���i������ڲ���Ϣ vt=0����x����,vt=1����y����,vt=2����z����vt=4��������������
    virtual const void* point_at(geo_object* p,int i,int vt)=0;
    
    //��������
    //gdimָ������ά�� pnumָ������� cdimָ������ά�� xyzָ������
    //flagָ���Ƿ�(&1)���ô����xyz���꣬�Լ������ߵ��Ƿ�(&2)�ڲ�
    //vt_pָ������������=0��ʾ����
    virtual geo_object* create_single(int gdim,int pnum,int cdim,const double* xyz,
        int flag,const void* vt_p)=0;

    //����������
    //gdimָ������ά��������geometry�����ǲ����޸ĵ� �ⲿ�������ʹ��һ��multi��������е�geometry��װ�õ���ͬ����ά�����¶���
    //snumָ��sub�ĸ��� subsΪ�Ӷ�����׵�ַ flagԤ��
    virtual geo_object* create_multi(int gdim,int snum,geo_object** subs,int flag)=0;

    //����������Oracle����Ľ��ʹ����괮 ����һ��path����
    //      flag��������path�����Ƿ�(&1)����c_p����
    virtual geo_object* ora_create(int i_n,const int *i_p,int c_n,int cdim,const double *c_p,int flag)=0;

    //�������õ�Oracle����Ľ��ʹ����괮 ora����������ora_create_info���صĽ��
    virtual bool ora_get_info(geo_object* obj,int* i_n,int** i_p,int* c_n,int* cdim,double **c_p)=0;

    //�������ڻص�������geo_reader
    virtual geo_reader* new_reader(void* user,reader_callback func)=0;

    //�������geo_reader�����geo_reader
    virtual geo_reader* new_reader_n(int n,geostar::geo_reader** ppr)=0;

	//����һ�����˵�geo_reader
    virtual geo_reader* new_reader_trans(geo_reader* R,int n,geo_trans** tt)=0;
    
    //�������ڻص�������geo_writer
    virtual geo_writer* new_writer(void* user,writer_callback func)=0;

    //���ݸ�ʽ���ļ�����һ��geo_reader
    virtual geo_reader* open_reader(string_t format,string_t filename)=0;

    //���ݸ�ʽ���ļ�������һ��geo_writer
    virtual geo_writer* open_writer(string_t format,string_t filename)=0;
	
	//�����������ϲ�������һ��geo_trans
	//scrip="cut" ���ص����ü���trans ��Ҫ��������Ϊ���"knife"����,trans����������knife�ڲ��Ĳ��н��
	//scrip="clip" ���ؾ��βü���trans ��trans ��Ҫ����"x0","y0","dx","dy","tx","ty" ��������
	//		clip trans���ص�pathһ����multi���ͣ�multi�е�ÿ����pathһ���г���Ϊ2��i4����
	//scrip="simplify_toint" ����������ļ�trans ��trans ��Ҫ���� pricesion ����
	//scrip="simplify_dauglas", ����dauglas��ļ�trans ��trans��Ҫ���� tol ����
	//scrip="parallel" ����ƽ���ߵ�trans ��trans��Ҫ���� radius ����, ����������narc����(ȱʡֵΪ6)
	//scrip="buffer" ���ػ�������trans ��trans��Ҫ���� radius ����, ����������narc����(ȱʡֵΪ6)
    virtual geo_trans* create_trans(string_t scrip)=0;
	
	//���ݸ�ʽ���ļ�����һ��geo_reader2
    virtual geo_reader2* open_reader2(string_t format,string_t filename)=0;

	//ע��һ�����ļ��ĺ���,type=0�Ǵ�reader,�����Ǵ�writer
	virtual void regist_open(open_callback func,int type)=0;

	//����һ��draw����
	virtual geo_draw* new_draw()=0;

	//����һ��geo_table����
	virtual geo_vector* new_obj_vect()=0;

	//����һ��geo_table����
	virtual geo_table* new_table()=0;

	//���single path����Ϣ
	//single������һ��single path
	//cdim�������ά��,gdim�������ά��,pnum�����ĸ���
	//xyz���(x,y,z)��ֵ,vt�������������,(xyz��vt�ⲿ������ɾ���͸���)
	virtual bool out_single(geo_object* single,int* cdim,int* gdim,int* pnum,double** xyz,char** vt)=0;
};

struct geo_algorithm : geo_object
{
    //�ݲ�
    virtual double tolerance(double tol)=0;

    //����������ֵ����
    //mode ����ָ�� ���ȡ�����������
    virtual double prop_value(geo_object* obj,int mode)=0;

    //�������ļ�������
    //mode ����ָ�� clone ���ġ����ġ�Label�� 
    //��Ӿ���(��б)���ڽӾ���(��б)���ڽ����(Բ)��͹�� �ȵ�
    virtual geo_object* prop_geo(geo_object* obj,int mode)=0;

	//�������ļ�������
    //mode ����ָ�� clone ���ġ����ġ�Label�� 
    //��Ӿ���(��б)���ڽӾ���(��б)���ڽ����(Բ)��͹�� �ȵ�
    virtual bool prop_geo_2(geo_object* obj,int mode,double* paras)=0;

	//�޸ļ��ζ���
	//mode����ָ�� ���� ȥ���ظ��� ����ѹ��(dauglas) ��������(force_good_dir) �ȵ�
	virtual int gmodify(geo_object* obj,int mode,void* para)=0;

	//���ص���A�����ұߣ����(x,y)��p�ľ���С���ݲ��0����߷���1���ұ߷���2
	virtual int left_right(geo_object* p,double x,double y)=0;

    //���أ�a,b)�������������
    //���ص�geo_object��һ���߶�
    virtual geo_object* nearest(geo_object* a,geo_object* b)=0;

    //�������������
    //�����p������һ��geometryҲ������һ����������
    //������p��Ѱ����x,y������߶Σ�������ݲ����û�ҵ��򷵻�0
    //���򷵻��߶����ڵĵ���s��t��(x,y)��s���������s�ϵĲ���
    virtual geo_object* xy2t(geo_object* p,const double* xy,double* t)=0;

    //�������껯
    //�����s������һ������,��������s�ϲ���Ϊt�ĵ�����
    virtual bool t2xy(geo_object* s,double t,double* xy)=0;
	
    //��ѯ(a,b)�Ƿ�����mode��ϵ
    //a,b�����Ǽ��ζ���Ҳ��������������
	//mode�μ�spr_is_*** �����ģʽ
    virtual bool spr_query_is(geo_object* a,geo_object* b,int mode)=0;

    //��ѯa,b�Ŀռ��ϵspr
	//����ֵspr������a,b�Ŀռ��ϵ��ֱ��ʹ��spr���Ǻܷ���
	//�û����Ե���spr_is������spr�Ƿ�����ĳģʽ
    virtual int spr_query(geo_object* a,geo_object* b)=0;

	//����spr�Ƿ�����ĳmode������ģʽ
	//spr��spr_query����spr_query_n2n���ص�ֵ
	//mode��spr_is_***�����ģʽ
	virtual bool spr_is(int spr,int mode)=0;
    
    //��ѯ��������P,Q�Ŀռ��ϵ�����д��R
    virtual void spr_query_n2n(geo_reader* P,geo_reader* Q,geo_writer* R,int mode)=0;

    //�����ռ��������� 
    //�ڴ���split���ѯ1��n�����ʱ Ϊ1������׼���ռ��������������Ч��
    virtual geo_object* spi_create(geo_object* obj,int mode)=0;

    //�������ζ�����������
    //mode����ָ����Ϸ�ʽ ����������ԳƲ�
    virtual geo_object* gcombine(geo_object* a,geo_object* b,int mode)=0;
    
    //�����и�K�����ǵ������ζ������������
    //x�����ǵ������ζ���Ҳ������һ��geo_reader
    virtual void gsplit(geo_object* K,geo_object* x,geo_writer* W)=0;

    //�������ϲ� д��W��ÿ�������ǵ���Ȧ�Ķ���
    //����ֻ���������R�е��ߡ���
    virtual void n_union(geo_reader* R,geo_writer* W)=0;

    //��鵥������ļ�����ȷ��
    //modeָ��������� ������ ���ཻ �߶��ص� ������ȷ �Ƿ���
	//����0��ʾû�д��󣬷��򷵻ش������
    virtual int gcheck_1(geo_object* obj,int mode)=0;

	//������ҵ㡢�ݴ�㡢α�ڵ㡢�ڽ���
	//�����ߣ��ظ���
	//�������ĵ����ͨ��W���
	virtual void gcheck_2(geo_object* R,geo_writer* W,int mode)=0;

    //����R�Ļ�����
    //narcָ��Բ�ɼ����߶����
	//���������R�е����ж������߿����������W�����ж�������
    virtual void line_buffer(geo_object* R,double radius,int narc,geo_writer* W)=0;

    //�������� ���������W�ļ��ζ������߶���
    //�Ҷ������ཻ������֮�䲻�ཻ
    //R�����ǵ������ζ���Ҳ������geo_reader
    virtual void line_clean(geo_object* R,geo_writer* W)=0;

    //����
	//mode&1��ʾR�е�ÿ���߶�Ҫ��������������ʹ��
	//mode&2��ʾR�е����Ѿ���Ȧ��,����Ҫ�ٹ�Ȧ��
	//mode&4��ʾֻ��Ȧ�����棬����Ҫ����
    virtual void build(geo_reader* R,geo_writer* W,int mode)=0;

	//ͼ��ĵ���
	//mode�����2λ��ʾ�������ļ���ά��
	//mode&4��ʾ�������Ҫ��Aͼ��Ĺ�ϵ
	//mode&8��ʾ�������Ҫ��Bͼ��Ĺ�ϵ
	//mode&16��ʾ���������һ��ͼ���п��Դ������ϵ
	//A��B����ͼ���������Ҳ�������棬����һ��ͼ���б���ֻ��һ������
    //min_width��������������Ĳ�����һ������������ڳ��ȳ�֮Ϊƽ����ȣ����ƽ�����С��min_width
    //��ô����潫���ںϵ����������У����������
	virtual void overlay(geo_reader* A,geo_reader* B,geo_writer* W,double min_width,int mode)=0;
	
	//����point_pool���󣬴˶��������������path�ĵ�����
	virtual geo_trans* point_pool(geo_object* R,int mode)=0;

	//����line_pool����(�˺�����ʱû��)
	virtual geo_trans* line_pool(geo_object* R,int mode)=0;

	//�������Զ�path����
	virtual geo_reader* sort_by_prop(geo_reader* A,geo_compare* cmp)=0;

	//��һ������������ִ�пռ��ѯ
	virtual geo_vector* geo_query(geo_vector* A,int path_cid,int env_cid,geo_object* geo,int mode)=0;

    //�����˵ļ�
    //env�����Ϊ����ôָ��һ��[x0,y0,x1,y1]�ľ��Σ������ڴ˾����ڲ��ĵ㶼���ᱻ��
    //[pp,pp+n)��Ҫ�򻯵�path���飬����ֻ������ڲ��ĵ㣬������ı�����Լ�������
    virtual void top_reserve_simplify(int n,geo_object** pp,double tol,double* env)=0;

    //���ݲ������䷵��һ����path
    virtual geo_object* t2path(geo_object* p,double t0,double t1)=0;
	
    //���ֲ��ֺ��� p��һ�����ζ��� env[x,y,x1,y1]�Ǵ��ڵĿ��ӷ�Χ(����Ϊnull) font[w��h]�������С(����Ϊnull)
    //n�����ֵĸ���,xy�������ÿ�����ֵ����½�����
    virtual bool layout(geo_object* p,const double* env,const double* font,int n,double* xy)=0;
	//virtual geo_reader* difference_n2n(geo_reader* A,geo_reader* B,geo_writer* dA,geo_writer* dB,int mode)=0;
};

};

/* Ԥ���Ľӿ����
namespace geostar {

struct geo_keymap : geo_object
{
    virtual int keylen()=0;
    virtual geo_object* get(const void* key)=0;
};

struct galgorithm2_ex : geo_algorithm
{
    //�߹���
    //modeָ�� �߹�Ȧ Ȧ���� �߹���
    virtual geo_object* build_by_point(geo_keymap* db,int n,const void* keys,const double* envs,double x,double y)=0;
}; } */

//���ֳ���
namespace geostar {

const int prop_cancel = -100;	//ȡ��������

//ga_i4��ͷ���������ü���ȫ�ֱ���
const int ga_i4_clockwise = 0;		//����ʱ�����i4_set(ga_i4_clockwise,0)��ʾ��ʱ�����i4_set(ga_i4_clockwise,1)��ʾ˳ʱ�����ȷʡΪ0
const int ga_i4_narc = 1;			//����Բ������ߵ��߶���Ŀi4_set(ga_i4_narc,num),ȱʡnum=24
const int ga_i4_max_pt_in_mem = 2;  //�����ڲ���������������ڴ��еĵ���Ŀi4_set(ga_i4_max_pt_in_mem,num)��ȱʡnum=1024*1024*8 (ÿ����16���ֽ��൱��128M�ڴ�)
									//���ֵһ����������̫С��������������ļ���������Ӱ�����ܣ��ⲿ�������ڴ����һЩ�����С��������úܶ�

const int geometry_i4_gdim = -2;	//Geometry����ͨ�����i4_set(geometry_i4_gdim,gdim)�õ������ü���ά��
const int geometry_i4_prop_len = -1;//Geometry����ͨ�����i4_set(geometry_i4_prop_len,len)�õ����������Գ���

const int prop_value_length = 11;		//����
const int prop_value_width =  21;		//���
const int prop_value_height = 31;		//�߶�
const int prop_value_area =	  12;		//���

const int prop_geo_clone =   0;		    //��¡
const int prop_geo_clone_mem0 = 1;		//ֻ��û����ʵ�ڴ��path��¡

const int prop_geo_label =   10;		//��־��
const int prop_geo_center =  20;		//����	
const int prop_geo_centroid = 30;		//����
const int prop_geo_maxline = 11;		//���
const int prop_geo_env =	 12;		//��Ӿ���
const int prop_geo_hull = 22;			//͹��
const int prop_geo_env_nstd = 32;		//б��Ӿ���
const int prop_geo_env_circle = 42;		//������Բ
const int prop_geo_inner_rect = 52;		//�ڽӾ���
const int prop_geo_inner_square = 62;	//�ڽӾ���
const int prop_geo_inner_circle = 72;	//�ڽӾ���
const int prop_geo_simplify = 13;		//�򻯶���
const int prop_geo_boundary = 23;		//�򻯶���

const int gmodify_remove_repeat = 1;	//ɾ���ظ��ĵ� paraΪ����ƽ��
const int gmodify_dauglas = 2;			//������˹ѹ�� paraΪ����
const int gmodify_reverse = 3;			//����         paraΪnull
const int gmodify_force_good_dir = 4;	//force_good_dir paraΪnull
const int gmodify_force_geo_close = 5;	//force_geo_close paraΪnull

const int gcombine_union = 1;			//����
const int gcombine_intersect = 2;		//����
const int gcombine_diffrence = 3;		//�����
const int gcombine_sym_diffrence = 4;	//����ԳƲ�

const int gcheck_1_e_simple = 0;		//�Ƿ��Ǽ򵥶���
const int gcheck_1_e_close_2 = 1;		//ǿ��ռ��
const int gcheck_1_e_close = 2;			//��ռ��
const int gcheck_1_e_dir = 4;			//�����Ƿ���ȷ
const int gcheck_1_e_cross = 8;			//���ཻ
const int gcheck_1_e_lap = 16;			//���ص�
const int gcheck_1_e_repeat = 32;       //���ص�

const int gc2_pt_repeat = 0x01;			//�ظ���
const int gc2_pt_isolate = 0x02;		//���ҵ�
const int gc2_pt_endp_x = 0x04;			//α�˵�
const int gc2_pt_tol_x = 0x08;			//�ݴ�� ���ݲΧ�ڵ�����ȷ��ͬ
const int gc2_pt_nodal = 0x10;			//�ཻ�Ľڵ� һ�������ǽڵ�
const int gc2_pt_cross = 0x20;			//�ഩ��

const int gc2_l_1 = 0x100;				//������
const int gc2_l_n = 0x200;				//�ص���

const int gc2_a_0 = 0x1000;				//¥�յ���
const int gc2_a_1 = 0x2000;				//ֻ��һ����������
const int gc2_a_n = 0x4000;				//�������������

// spr_is��ģʽ
const int spr_is_disjion = 1;
const int spr_is_intersect = 2;
const int spr_is_cross = 3;
const int spr_is_equal = 4;   //�������(�߶ο��Բ��)
const int spr_is_equal_2 = 5; //��ȷ���(�߶β����Բ��)

const int spr_is_touch = 6; //�����ߵĶ˵㣻������Ľڵ��߽����ϵ㣻�����߽��ཻ�ڶ˵��Ҳ����ഩ���������ڽڵ㴦�ཻ�Ҳ��ഩ�������ڲ����������ڽڵ㴦�ཻ�Ҳ��ص�
const int spr_is_overlap = 7; //��ͬά��֮��Ŵ����ص�

const int spr_is_contain = 8;
const int spr_is_within = 16;
const int spr_is_cross_l = 32;

const int spr_no_touch = 0x10000000;  //���������ζ���ı߽��ཻ��ʱ����Ϊ����û��is��ϵ
const int spr_can_touch = 0x20000000; //���������ζ���ı߽��ཻ��ʱ��Ӱ�����ǵ�is��ϵ

const int pp_ipt_create = 0x01; //point_pool������mode&pp_ipt_createʱ��������߶μ�Ľ���Ҳ��������
const int pp_ipt_trans = 0x02;  //point_pool������mode&pp_ipt_transʱ���ص�geo_trans��transʱ������߶μ��ڲ�ڵ�
const int pp_use_line = 0x04;  //point_pool������mode&pp_use_lineʱ���ص�geo_trans��transʱ���Ե�����߶������ϵ�����

const int draw_txt_nocover = 1; //��ʾ�ı�����ѹ�Ƕ���
const int draw_txt_split = 2;   //��ʾ�ı����Բ�ֳɵ�����

};

