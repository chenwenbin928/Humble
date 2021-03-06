
#include "SnowFlake.h"
#include "Funcs.h"

H_BNAMSP

#define Epoch 1358902800000LL
//机器标识位数
#define WorkerIdBits 5
//数据中心标识位数
#define DatacenterIdBits 5
//机器ID最大值
#define MaxWorkerId  (-1 ^ (-1 << WorkerIdBits))
//数据中心ID最大值
#define MaxDatacenterId (-1 ^ (-1 << DatacenterIdBits))
//毫秒内自增位
#define SequenceBits 12
//机器ID偏左移12位
#define WorkerIdShift SequenceBits
//数据中心ID左移17位
#define DatacenterIdShift (SequenceBits + WorkerIdBits)
//时间毫秒左移22位
#define TimestampLeftShift (SequenceBits + WorkerIdBits + DatacenterIdBits)
#define SequenceMask (-1 ^ (-1 << SequenceBits))

CSnowFlake::CSnowFlake(void) : m_uiWorkid(H_INIT_NUMBER), m_lSequence(H_INIT_NUMBER)
{
    m_ulLastTime = getCurMS();
}

CSnowFlake::~CSnowFlake(void)
{

}

void CSnowFlake::setWorkid(const int uiID)
{
    H_ASSERT((uiID <= MaxWorkerId) && (uiID >= 0), "param error.");

    m_uiWorkid = uiID;
}

void CSnowFlake::setCenterid(const int uiID)
{
    H_ASSERT((uiID <= MaxDatacenterId) && (uiID >= 0), "param error.");

    m_uiCenterid = uiID;
}

uint64_t CSnowFlake::getCurMS(void)
{
    uint64_t ulMS(H_INIT_NUMBER);
    struct timeval stTimeVal;

    H_GetTimeOfDay(stTimeVal);

    ulMS = static_cast<uint64_t>(stTimeVal.tv_usec) / 1000;//取毫秒
    ulMS += static_cast<uint64_t>(stTimeVal.tv_sec) * 1000;

    return ulMS;
}

uint64_t CSnowFlake::tilNextMillis(void)
{
    uint64_t ulCur(getCurMS());

    while (ulCur <= m_ulLastTime) 
    {
        ulCur = getCurMS();
    }

    return ulCur;
}

uint64_t CSnowFlake::getID(void)
{
    uint64_t uiCurTime(getCurMS());
    H_ASSERT(uiCurTime >= m_ulLastTime, "time error.");

    if (uiCurTime == m_ulLastTime)
    {
        m_lSequence = (m_lSequence + 1) & SequenceMask;
        if (0 == m_lSequence) 
        {
            //当前毫秒内计数满了，则等待下一秒
            uiCurTime = tilNextMillis();
        }
    }
    else
    {
        m_lSequence = 0;
    }

    m_ulLastTime = uiCurTime;

    return ((uint64_t)(uiCurTime - Epoch) << TimestampLeftShift) | 
        (m_uiCenterid << DatacenterIdShift) | 
        (m_uiWorkid << WorkerIdShift) | 
        m_lSequence;
}

H_ENAMSP;
