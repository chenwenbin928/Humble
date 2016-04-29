
#ifndef H_LUABINARY_H_
#define H_LUABINARY_H_

#include "Macros.h"

H_BNAMSP

//�����ƽ���
class CBinary
{
public:
    CBinary(void);
    ~CBinary(void);

    //����Ҫ����������
    void setReadBuffer(const char *pszBuf, const size_t iLens);
    unsigned int getRBufLens(void)
    {
        return (unsigned int)m_iParseBufLens;
    };

    //����д
    void reSetWrite(void);

    //��  ����ָ���ֽ�
    void skipRead(const unsigned int iLens);
    //д  ����ָ���ֽ������ֽ���0���
    void skipWrite(const unsigned int iLens);

    //��ȡ��δ�������ֽ���
    size_t getSurpLens(void);

    //char
    void setSint8(char cVal);
    char getSint8(void);
    void setUint8(unsigned char ucVal);
    unsigned char getUint8(void);

    //bool
    void setBool(const bool bVal);
    bool getBool(void);

    //short
    void setSint16(short sVal);
    short getSint16(void);
    void setUint16(unsigned short usVal);
    unsigned short getUint16(void);

    //int
    void setSint32(int iVal);
    int getSint32(void);
    void setUint32(unsigned int uiVal);
    unsigned int getUint32(void);

    //int64_t
    void setSint64(int64_t iVal);
    int64_t getSint64(void);
    void setUint64(uint64_t uiVal);
    uint64_t getUint64(void);

    //double
    void setDouble(const double dVal);
    double getDouble(void);

    //float
    void setFloat(const float fVal);
    float getFloat(void);

    //string ��֤��/0����
    void setString(const char *pszVal);
    std::string getString(void);

    //byte
    void setByte(const char *pszVal, const unsigned int iLens);
    std::string getByte(const unsigned int iLens);

    std::string getWritedBuf(void)
    {
        return m_strWritBuffer;
    };

private:
    void setVal(const void *pszBuf, const size_t iLens);
    template<typename T>
    T readNumber(void)
    {
        T tVal = H_INIT_NUMBER;
        if ((m_iCurParseLens + sizeof(T)) > m_iParseBufLens)
        {
            return tVal;
        }

        tVal = *((T*)(m_pParseBuffer + m_iCurParseLens));
        m_iCurParseLens += sizeof(T);

        return tVal;
    };

private:
    char *m_pParseBuffer;//Ҫ������buffer
    size_t m_iParseBufLens;//Ҫ������buffer����
    size_t m_iCurParseLens;//�Ѿ������ĳ���
    std::string m_strWritBuffer;//дbuffer
};

H_ENAMSP

#endif//H_LUABINARY_H_