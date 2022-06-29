#define DECL_SET_GET_COMPLEX(type, name)\
    private:\
    type m##name;\
    public:\
    type get##name(){ return m##name; }\
    void set##name(const type& val){ m##name=val; }
#define DECL_SET_GET_SIMPLE(type, name)\
    private:\
    type m##name;\
    public:\
    type get##name(){ return m##name; }\
    void set##name(const type& val){ m##name=val; }
