
#include "Binary.h"
#include "Funcs.h"

H_BNAMSP

CBinary::CBinary(void) : m_pParseBuffer(NULL),
    m_iParseBufLens(H_INIT_NUMBER), m_iCurParseLens(H_INIT_NUMBER)
{

}

CBinary::~CBinary(void)
{
    m_pParseBuffer = NULL;
}

void CBinary::setReadBuffer(const char *pszBuf, const size_t iLens)
{
    H_ASSERT(pszBuf, "pointer is null.");

    m_pParseBuffer = (char*)pszBuf;
    m_iParseBufLens = iLens;
    m_iCurParseLens = H_INIT_NUMBER;
}

void CBinary::reSetWrite(void)
{
    m_strWritBuffer.clear();
}

void CBinary::skipRead(const unsigned int iLens)
{
    m_iCurParseLens += iLens;
}

void CBinary::skipWrite(const unsigned int iLens)
{
    if (H_INIT_NUMBER == iLens)
    {
        return;
    }

    setVal(NULL, iLens);
}

size_t CBinary::getSurpLens(void)
{
    return m_iParseBufLens - m_iCurParseLens;
}

void CBinary::setVal(const void *pszBuf, const size_t iLens)
{
    m_strWritBuffer.append((const char*)pszBuf, iLens);   
}

void CBinary::setSint8(char cVal)
{
    setVal(&cVal, sizeof(cVal));
}
char CBinary::getSint8(void)
{
    return readNumber<char>();
}
void CBinary::setUint8(unsigned char ucVal)
{
    setVal(&ucVal, sizeof(ucVal));
}
unsigned char CBinary::getUint8(void)
{
    return readNumber<unsigned char>();
}

void CBinary::setBool(const bool bVal)
{
    unsigned char ucVal((bVal ? 1 : 0));

    setVal(&ucVal, sizeof(ucVal));
}
bool CBinary::getBool(void)
{
    return ((H_INIT_NUMBER == readNumber<unsigned char>()) ? false : true);
}

void CBinary::setSint16(short sVal)
{
    sVal = ntohs(sVal);

    setVal(&sVal, sizeof(sVal));
}
short CBinary::getSint16(void)
{
    return ntohs(readNumber<short>());
}
void CBinary::setUint16(unsigned short usVal)
{
    usVal = ntohs(usVal);

    setVal(&usVal, sizeof(usVal));
}
unsigned short CBinary::getUint16(void)
{
    return ntohs(readNumber<unsigned short>());
}

void CBinary::setSint32(int iVal)
{
    iVal = ntohl(iVal);

    setVal(&iVal, sizeof(iVal));
}
int CBinary::getSint32(void)
{
    return ntohl(readNumber<int>());
}
void CBinary::setUint32(unsigned int uiVal)
{
    uiVal = ntohl(uiVal);

    setVal(&uiVal, sizeof(uiVal));
}
unsigned int CBinary::getUint32(void)
{
    return ntohl(readNumber<unsigned int>());
}

void CBinary::setSint64(int64_t iVal)
{
    iVal = ntohl64(iVal);

    setVal(&iVal, sizeof(iVal));
}
int64_t CBinary::getSint64(void)
{
    return ntohl64(readNumber<int64_t>());
}
void CBinary::setUint64(uint64_t uiVal)
{
    uiVal = ntohl64(uiVal);

    setVal(&uiVal, sizeof(uiVal));
}
uint64_t CBinary::getUint64(void)
{
    return ntohl64(readNumber<uint64_t>());
}

void CBinary::setDouble(const double dVal)
{
    setVal(&dVal, sizeof(dVal));
}
double CBinary::getDouble(void)
{
    return readNumber<double>();
}

void CBinary::setFloat(const float fVal)
{
    setVal(&fVal, sizeof(fVal));
}
float CBinary::getFloat(void)
{
    return readNumber<float>();
}

void CBinary::setString(const char *pszVal)
{
    setVal(pszVal, strlen(pszVal));
    skipWrite(1);
}
std::string CBinary::getString(void)
{
    if (m_iCurParseLens >= m_iParseBufLens)
    {
        return std::string("");
    }

    std::string strVal(m_pParseBuffer + m_iCurParseLens);

    m_iCurParseLens += (strVal.size() + 1);

    return strVal;
}

void CBinary::setByte(const char *pszVal, const unsigned int iLens)
{
    setVal(pszVal, iLens);
}

std::string CBinary::getByte(const unsigned int iLens)
{
    if ((m_iCurParseLens + iLens) > m_iParseBufLens)
    {
        return std::string("");
    }

    std::string strVal(m_pParseBuffer + m_iCurParseLens, iLens);

    m_iCurParseLens += iLens;

    return strVal;
}

H_ENAMSP