/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher 
 * Copyright: GPL V2
 *
 * IP/ARP/UDP/TCP functions
 *
 * Chip type           : ATMEGA88 with ENC28J60
 *********************************************/


/*********************************************
 * modified: 2007-08-08
 * Author  : awake
 * Copyright: GPL V2
 * http://www.icdev.com.cn/?2213/
 * Host chip: ADUC7026
**********************************************/



//@{
#ifndef IP_ARP_UDP_TCP_H
#define IP_ARP_UDP_TCP_H

#define  pgm_read_byte(ptr)  ((char)*(ptr))

//#define unsigned char  unsigned char
//#define unsigned  int unisgned int

static unsigned int myARPport=2012;
static unsigned char macaddr[6];
//static unsigned char ipaddr[4];
static unsigned int info_hdr_len=0;
static unsigned int info_data_len=0;
static unsigned char seqnum=0xa; // my initial tcp sequence number

unsigned char *ipaddr;



// you must call this function once before you use any of the other functions:
extern void init_ip_arp_udp_tcp(unsigned char *mymac,unsigned char *myip,unsigned int wwwp);
//
extern unsigned char eth_type_is_arp_and_my_ip(unsigned char *buf,unsigned int len);
extern unsigned char eth_type_is_ip_and_my_ip(unsigned char *buf,unsigned int len);
extern void make_arp_answer_from_request(unsigned char *buf);
extern void make_echo_reply_from_request(unsigned char *buf,unsigned int len);
extern void make_udp_reply_from_request(unsigned char *buf,char *data,unsigned char datalen,unsigned int port);
extern unsigned char check_ip_scr(unsigned char *buf,unsigned char *dbuf);

extern void make_tcp_synack_from_syn(unsigned char *buf);
extern void init_len_info(unsigned char *buf);
extern unsigned int get_tcp_data_pointer(void);
extern unsigned int fill_tcp_data_p(unsigned char *buf,unsigned int pos, const unsigned char *progmem_s);
extern unsigned int fill_tcp_data(unsigned char *buf,unsigned int pos, const char *s);
extern unsigned  int fill_tcp_buf(unsigned char *buf,unsigned  int fsize, const char *s);

extern void make_tcp_ack_from_any(unsigned char *buf);
extern void make_tcp_ack_with_data(unsigned char *buf,unsigned  int dlen, char fin);




#endif /* IP_ARP_UDP_TCP_H */
//@}
