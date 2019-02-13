#ifndef CAPTHREAD_H
#define CAPTHREAD_H

#include <QThread>
#include "wdpcap.h"
#include "devinfo.h"

class CapThread: public QThread
{
public:
    CapThread(DevInfo* nic);
    void run();
    void quit();
private:
    pcap_t *adhandle;
    DevInfo* nic;
    u_int ipConvertToInt(QString ip);
    static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
};

/* 4字节的IP地址 */
struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
};

/* IPv4 首部 */
struct ip_header{
    u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
    u_char  tos;            // 服务类型(Type of service)
    u_short tlen;           // 总长(Total length)
    u_short identification; // 标识(Identification)
    u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
    u_char  ttl;            // 存活时间(Time to live)
    u_char  proto;          // 协议(Protocol)
    u_short crc;            // 首部校验和(Header checksum)
    ip_address  saddr;      // 源地址(Source address)
    ip_address  daddr;      // 目的地址(Destination address)
    u_int   op_pad;         // 选项与填充(Option + Padding)
};

/* UDP 首部*/
struct udp_header{
    u_short sport;          // 源端口(Source port)
    u_short dport;          // 目的端口(Destination port)
    u_short len;            // UDP数据包长度(Datagram length)
    u_short crc;            // 校验和(Checksum)
};

#endif // CAPTHREAD_H
